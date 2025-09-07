//
// Created by happy on 9/6/2025.
//

#ifndef KB_STD_VFS_VFS_HPP
#define KB_STD_VFS_VFS_HPP

#include <cstdint>
#include <memory>

namespace kb::vfs {

class IBlob {
public:
  virtual ~IBlob() noexcept = default;

  [[nodiscard]] virtual const void * data() const noexcept = 0;
  [[nodiscard]] virtual std::size_t size() const noexcept = 0;

  /**
   * @brief Check whether this blob contains any data
   */
  [[nodiscard]] auto is_empty() noexcept -> bool {
    return data() == nullptr || size() == 0;
  }
};

class OwningBlob : public IBlob {
public:
  OwningBlob() noexcept = default;
  ~OwningBlob() noexcept override;

  OwningBlob(const OwningBlob & p_other) noexcept = delete;
  auto operator=(const OwningBlob & p_other) noexcept -> OwningBlob & = delete;

  OwningBlob(OwningBlob && p_other) noexcept;
  auto operator=(OwningBlob && p_other) noexcept -> OwningBlob &;

  /**
   * @brief Constructs an OwningBlob from a binary data pointer and size, taking ownership of the data's lifetime
   */
  OwningBlob(void * p_data, std::size_t p_size) noexcept;

  /**
   * @brief Returns an immutable pointer to the underlying data
   */
  [[nodiscard]] const void * data() const noexcept override { return m_data; }

  /**
   * @brief Returns the size of the underlying data
   */
  [[nodiscard]] std::size_t size() const noexcept override { return m_size; }
private:
  void        * m_data;
  std::size_t   m_size;
};

} // end namespace kb::vfs

#endif  //KB_STD_VFS_VFS_HPP
