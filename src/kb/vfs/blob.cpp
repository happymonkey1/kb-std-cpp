//
// Created by happy on 9/6/2025.
//

#include "kb/vfs/blob.hpp"

namespace kb::vfs {

OwningBlob::OwningBlob(void * p_data, std::size_t p_size) noexcept
  : m_data{ p_data }, m_size{ p_size } {

}

OwningBlob::~OwningBlob() noexcept {
  free(m_data);
  m_size = 0;
}

OwningBlob::OwningBlob(OwningBlob && p_other) noexcept
    : m_data{ p_other.m_data }, m_size{ p_other.m_size } {
  p_other.m_data = nullptr;
  p_other.m_size = 0;
}

auto OwningBlob::operator=(kb::vfs::OwningBlob && p_other) noexcept -> OwningBlob & {
  m_data = p_other.m_data;
  m_size = p_other.m_size;

  p_other.m_data = nullptr;
  p_other.m_size = 0;
  return *this;
}

} // end namespace kb::vfs
