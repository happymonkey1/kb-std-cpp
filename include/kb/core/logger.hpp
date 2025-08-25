//
// Created by happy on 8/24/2025.
//

#ifndef KB_STD_CORE_LOGGER_H
#define KB_STD_CORE_LOGGER_H

#include "kb/kb_core.h"
#include <spdlog/spdlog.h>

#include <string_view>

namespace kb::core {

class Logger {
 public:
  static auto init(std::string_view p_app_name = "kb") noexcept -> void;
  static auto shutdown() noexcept -> void;
  static auto get_core_logger() noexcept -> std::shared_ptr<spdlog::logger>;
  static auto set_core_logger_level(kb_log_level p_log_level) noexcept -> void;
};

}

#endif  // KB_STD_CORE_LOGGER_H
