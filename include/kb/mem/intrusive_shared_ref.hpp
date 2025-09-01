//
// Created by happy on 9/1/2025.
//

#ifndef KB_STD_MEM_INTRUSIVE_SHARED_REF_HPP
#define KB_STD_MEM_INTRUSIVE_SHARED_REF_HPP

#include "kb/kb_core.h"

#include <atomic>

namespace kb::mem {

//////////////////////////////////////////////////////////////////////////
// IntrusiveSharedRef
// Mostly a copy of Microsoft::WRL::ComPtr<T>
//////////////////////////////////////////////////////////////////////////

template <typename T>
class IntrusiveSharedRef
{
public:
  typedef T InterfaceType;

  template <bool b, typename U = void>
  struct EnableIf
  {
  };

  template <typename U>
  struct EnableIf<true, U>
  {
    typedef U type;
  };

protected:
  InterfaceType * m_ptr;
  template<class U> friend class IntrusiveSharedRef;

  void internal_add_ref() const noexcept
  {
    if (m_ptr != nullptr)
    {
      m_ptr->add_ref();
    }
  }

  unsigned long internal_release() noexcept
  {
    unsigned long ref = 0;
    T* temp = m_ptr;

    if (temp != nullptr)
    {
      m_ptr = nullptr;
      ref = temp->release();
    }

    return ref;
  }

public:

  IntrusiveSharedRef() noexcept : m_ptr{ nullptr }
  {
  }

  IntrusiveSharedRef(std::nullptr_t) noexcept : m_ptr{ nullptr }
  {
  }

  template<class U>
  IntrusiveSharedRef(U * p_other) noexcept : m_ptr{ p_other }
  {
    internal_add_ref();
  }

  IntrusiveSharedRef(const IntrusiveSharedRef & p_other) noexcept : m_ptr{ p_other.m_ptr }
  {
    internal_add_ref();
  }

  // copy ctor that allows to instanatiate class when U* is convertible to T*
  template<class U>
  IntrusiveSharedRef(
    const IntrusiveSharedRef<U> & p_other,
    typename std::enable_if<std::is_convertible<U*, T*>::value, void *>::type * = nullptr
  ) noexcept : m_ptr{ p_other.m_ptr }
  {
    internal_add_ref();
  }

  IntrusiveSharedRef(IntrusiveSharedRef &&other) noexcept : m_ptr(nullptr)
  {
    if (this != reinterpret_cast<IntrusiveSharedRef*>(&reinterpret_cast<unsigned char&>(other)))
    {
      swap(other);
    }
  }

  // Move ctor that allows instantiation of a class when U* is convertible to T*
  template<class U>
  IntrusiveSharedRef(
    IntrusiveSharedRef<U> && p_other,
    typename std::enable_if<std::is_convertible<U*, T*>::value, void *>::type * = nullptr
  ) noexcept : m_ptr(p_other.m_ptr)
  {
    p_other.m_ptr = nullptr;
  }

  ~IntrusiveSharedRef() noexcept
  {
    internal_release();
  }

  IntrusiveSharedRef & operator=(std::nullptr_t) noexcept
  {
    internal_release();
    return *this;
  }

  IntrusiveSharedRef & operator=(T * p_other) noexcept
  {
    if (m_ptr != p_other)
    {
      IntrusiveSharedRef(p_other).swap(*this);
    }
    return *this;
  }

  template <typename U>
  IntrusiveSharedRef& operator=(U * p_other) noexcept
  {
    IntrusiveSharedRef(p_other).swap(*this);
    return *this;
  }

  IntrusiveSharedRef& operator=(const IntrusiveSharedRef & p_other) noexcept
  {
    if (m_ptr != p_other.m_ptr)
    {
      IntrusiveSharedRef{ p_other }.swap(*this);
    }
    return *this;
  }

  template<class U>
  IntrusiveSharedRef & operator=(const IntrusiveSharedRef<U>& p_other) noexcept
  {
    IntrusiveSharedRef{ p_other }.swap(*this);
    return *this;
  }

  IntrusiveSharedRef & operator=(IntrusiveSharedRef && p_other) noexcept
  {
    IntrusiveSharedRef(static_cast<IntrusiveSharedRef &&>(p_other)).swap(*this);
    return *this;
  }

  template<class U>
  IntrusiveSharedRef & operator=(IntrusiveSharedRef<U> && p_other) noexcept
  {
    IntrusiveSharedRef(static_cast<IntrusiveSharedRef<U> &&>(p_other)).swap(*this);
    return *this;
  }

  void swap(IntrusiveSharedRef && r) noexcept
  {
    T * tmp = m_ptr;
    m_ptr = r.m_ptr;
    r.m_ptr = tmp;
  }

  void swap(IntrusiveSharedRef & r) noexcept
  {
    T * tmp = m_ptr;
    m_ptr = r.m_ptr;
    r.m_ptr = tmp;
  }

  [[nodiscard]] T* get() const noexcept
  {
    return m_ptr;
  }

  operator T*() const
  {
    return m_ptr;
  }

  InterfaceType* operator->() const noexcept
  {
    return m_ptr;
  }

  T** operator&()
  {
    return &m_ptr;
  }

  [[nodiscard]] T * const * get_address_of() const noexcept
  {
    return &m_ptr;
  }

  [[nodiscard]] T ** get_address_of() noexcept
  {
    return &m_ptr;
  }

  [[nodiscard]] T ** release_and_get_address_of() noexcept
  {
    internal_release();
    return &m_ptr;
  }

  T * detach() noexcept
  {
    T * ptr = m_ptr;
    m_ptr = nullptr;
    return ptr;
  }

  // Set the pointer while keeping the object's reference count unchanged
  void attach(InterfaceType * p_other)
  {
    if (m_ptr != nullptr)
    {
      auto ref = m_ptr->release();
      KB_UNUSED(ref);

      // Attaching to the same object only works if duplicate references are being coalesced. Otherwise
      // re-attaching will cause the pointer to be released and may cause a crash on a subsequent dereference.
      KB_ASSERT(ref != 0 || m_ptr != p_other, "Failed to attach pointer due to invalid state");
    }

    m_ptr = p_other;
  }

  // Create a wrapper around a raw object while keeping the object's reference count unchanged
  static IntrusiveSharedRef<T> create(T * p_other)
  {
    IntrusiveSharedRef<T> ptr;
    ptr.attach(p_other);
    return ptr;
  }

  unsigned long reset()
  {
    return internal_release();
  }
};

//////////////////////////////////////////////////////////////////////////
// RefCounted<T>
// A class that implements reference counting in a way compatible with IntrusiveSharedRef.
// Intended usage is to use it as a base class for interface implementations, like so:
// class Texture : public RefCounted<ITexture> { ... }
//////////////////////////////////////////////////////////////////////////

template<class T>
class RefCounted : public T
{
private:
  std::atomic<unsigned long> m_refCount = 1;
public:
  virtual unsigned long add_ref() override
  {
    return ++m_refCount;
  }

  virtual unsigned long release() override
  {
    unsigned long result = --m_refCount;
    if (result == 0) {
      delete this;
    }
    return result;
  }
};

} // end namespace kb::mem

#endif  //KB_STD_MEM_INTRUSIVE_SHARED_REF_HPP
