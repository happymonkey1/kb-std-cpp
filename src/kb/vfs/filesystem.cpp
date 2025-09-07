//
// Created by happy on 9/7/2025.
//

#include "kb/vfs/filesystem.hpp"
#include "kb/kb_std.hpp"
#include "kb/vfs/blob.hpp"

#include <filesystem>
#include <fstream>

namespace kb::vfs {

bool NativeFileSystem::folder_exists(const std::filesystem::path & p_path) const noexcept {
  return std::filesystem::exists(p_path) &&
    std::filesystem::is_directory(p_path);
}

bool NativeFileSystem::file_exists(const std::filesystem::path & p_path) const noexcept {
  return std::filesystem::exists(p_path) &&
    std::filesystem::is_regular_file(p_path);
}

std::shared_ptr<IBlob> NativeFileSystem::read_file(const std::filesystem::path & p_path) noexcept {
  std::ifstream file{ p_path, std::ios::binary };
  if (!file || !file.is_open()) {
    return nullptr;
  }

  file.seekg(0, std::ios::end);
  std::size_t size = file.tellg();
  file.seekg(0, std::ios::beg);

  char * data = static_cast<char *>(malloc(size));
  KB_ASSERT(data, "[NativeFileSystem] Can not allocate buffer for file, out of memory");
  if (!data) {
    return nullptr;
  }

  file.read(data, size);


  if (!file.good()) {
    KB_ASSERT(false, "[NativeFileSystem] Failed to read file");
  }

  return std::make_shared<OwningBlob>(data, size);
}

bool NativeFileSystem::write_file(const std::filesystem::path & p_path, const void * p_data, std::size_t p_size) noexcept {
  std::ofstream file{ p_path, std::ios::binary };

  if (!file.is_open()) {
    KB_LOG_ERROR("[NativeFileSystem] Failed to open file {} for writing", std::string_view{ p_path.c_str() });
    return false;
  }

  if (p_size > 0) {
    file.write(static_cast<const char *>(p_data), p_size);
  }

  if (!file.good()) {
    KB_LOG_ERROR("[NativeFileSystem] Failed to write file: {}", std::string_view{ p_path.c_str() });
    return false;
  }

  return true;
}

} // end namespace kb::vfs
