//
// Created by happy on 8/24/2025.
//

#include "kb/kb_core.h"
#include "kb/core/logger.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char ** argv) -> int {

  kb::core::Logger::init();

  KB_LOG_INFO("Hello from logger test");

  kb::core::Logger::shutdown();

  return 0;
}