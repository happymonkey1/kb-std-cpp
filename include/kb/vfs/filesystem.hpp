//
// Created by happy on 9/6/2025.
//

#ifndef KB_STD_VFS_FILESYSTEM_HPP
#define KB_STD_VFS_FILESYSTEM_HPP

#include <cstdint>
#include <memory>
#include <filesystem>

namespace kb::vfs {

// Forward declarations
class IBlob;

class IFileSystem {
public:
  virtual ~IFileSystem() noexcept = default;

  /**
   * @brief Check for the existence of a folder
   */
  [[nodiscard]] virtual bool folder_exists(const std::filesystem::path & p_path) const noexcept = 0;

  /**
   * @brief Check for the existence of a file
   */
  [[nodiscard]] virtual bool file_exists(const std::filesystem::path & p_path) const noexcept = 0;

  /**
   * @brief Read a file into a blob
   */
  [[nodiscard]] virtual std::shared_ptr<IBlob> read_file(const std::filesystem::path & p_path) noexcept = 0;

  /**
   * @brief Write a file
   */
  [[nodiscard]] virtual bool write_file(
    const std::filesystem::path & p_path,
    const void * p_data,
    std::size_t p_size) noexcept = 0;
private:
};

class NativeFileSystem : public IFileSystem {
public:
  /**
   * @brief Check if a folder exists in the native filesystem
   */
  [[nodiscard]] bool folder_exists(const std::filesystem::path & p_path) const noexcept override;

  /**
   * @brief Check if a file exists in the native filesystem
   */
  [[nodiscard]] bool file_exists(const std::filesystem::path & p_path) const noexcept override;

  /**
   * @brief Read a file from the native filesystem into a binary blob
   */
  [[nodiscard]] std::shared_ptr<IBlob> read_file(const std::filesystem::path & p_path) noexcept override;

  /**
   * @brief Write binary blob data to the native filesystem
   */
  [[nodiscard]] virtual bool write_file(
    const std::filesystem::path & p_path,
    const void * p_data,
    std::size_t p_size) noexcept override;
};

} // end namespace kb::vfs

#endif  //KB_STD_VFS_FILESYSTEM_HPP
