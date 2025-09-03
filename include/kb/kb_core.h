//
// Created by happymonkey1 on 8/16/25.
//

#ifndef KB_STD_CPP_KB_CORE_H
#define KB_STD_CPP_KB_CORE_H

#include <stdarg.h>

#ifdef _WIN32
#  ifdef _WIN64
#    define KB_STD_PLATFORM_WINDOWS
#  else
#    define KB_STD_PLATFORM_WINDOWS_X86
#  endif
#elif TARGET_OS_MAC
//defined(__APPLE__) || defined(__MACH__)
#  define KB_STD_PLATFORM_MACOS
#elif defined(__ANDROID__)
#  define KB_STD_PLATFORM_ANDROID
#elif defined(__linux__)
#  define KB_STD_PLATFORM_LINUX
#else
#  define KB_STD_PLATFORM_UNKNOWN
#endif

#if defined(KB_STD_SHARED) && !defined(KB_API)
#  if defined(_WIN32) && !defined(__MINGW32__)
#    ifdef KB_API
#      define KB_API __declspec(dllexport)
#    else
#      define KB_API __declspec(dllimport)
#    endif
#  else
#    define KB_API __attribute__ ((visibility("default")))
#  endif
#else
#  define KB_API
#endif

#ifndef KB_UNUSED
#  define KB_UNUSED(x) (void)(x)
#endif

#ifndef KB_OWNING_BUFFER_INIT_SIZE
#  define KB_OWNING_BUFFER_INIT_SIZE 8192
#endif

#ifdef __cplusplus

# include <fmt/format.h>

namespace kb::details {

// Abort with a formatted message
template <typename... Args>
[[noreturn]] inline void kb_abort(const char* p_file, int p_line,
                                  fmt::format_string<Args...> p_fmt, Args&&... p_args) {
  auto msg = fmt::format("{}:{}: {}", p_file, p_line,
                         fmt::format(p_fmt, std::forward<Args>(p_args)...));
  fmt::print(stderr, "{}\n", msg);
  std::abort();
}

// Overload: abort with a raw C string (no formatting)
[[noreturn]] inline void kb_abort(const char* p_file, int p_line, const char* p_msg) {
  auto msg = fmt::format("{}:{}: {}", p_file, p_line, p_msg);
  fmt::print(stderr, "{}\n", msg);
  std::abort();
}

// Safer format helper (compile-time checked)
template <typename... Args>
inline auto kb_format_str_internal(fmt::format_string<Args...> p_fmt, Args&&... p_args) -> std::string {
  return fmt::format(p_fmt, std::forward<Args>(p_args)...);
}

// Overload for plain strings
inline auto kb_format_str_internal(const char* p_str) -> std::string {
  return std::string{p_str};
}

}

#ifndef KB_ABORT
#  define KB_ABORT(...) ::kb::details::kb_abort(__FILE__, __LINE__, __VA_ARGS__)
#endif

#ifndef KB_ASSERT
#  define KB_ASSERT(x, ...) do { if (!(x)) KB_ABORT("Assertion failed ({}): {}", #x, ::kb::details::kb_format_str_internal(__VA_ARGS__)); } while (false)
#endif

#  ifndef KB_LOG_TRACE
#    define KB_LOG_TRACE(...) ::kb::core::Logger::get_core_logger()->trace(__VA_ARGS__)
#  endif

#  ifndef KB_LOG_DEBUG
#    define KB_LOG_DEBUG(...) ::kb::core::Logger::get_core_logger()->debug(__VA_ARGS__)
#  endif

#  ifndef KB_LOG_INFO
#    define KB_LOG_INFO(...) ::kb::core::Logger::get_core_logger()->info(__VA_ARGS__)
#  endif

#  ifndef KB_LOG_WARN
#    define KB_LOG_WARN(...) ::kb::core::Logger::get_core_logger()->warn(__VA_ARGS__)
#  endif

#  ifndef KB_LOG_ERROR
#    define KB_LOG_ERROR(...) ::kb::core::Logger::get_core_logger()->error(__VA_ARGS__)
#  endif

#  ifndef KB_LOG_CRITICAL
#    define KB_LOG_CRITICAL(...) ::kb::core::Logger::get_core_logger()->critical(__VA_ARGS__)
#  endif
#else

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#ifndef KB_ABORT
#  define KB_ABORT(...) kb_abort(__FILE__, __LINE__, __VA_ARGS__)
#endif

#ifndef KB_ASSERT
#  define KB_ASSERT(x, ...) do { if (!(x)) { KB_ABORT(__VA_ARGS__); } } while (0)
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

KB_API void kb_abort(const char* p_file, int p_line, const char* p_fmt, ...);
KB_API const char* kb_format_str_internal(const char* p_fmt, ...);

typedef enum kb_log_level {
  KB_LOG_LEVEL_NONE     = 0,
  KB_LOG_LEVEL_TRACE    = 1,
  KB_LOG_LEVEL_DEBUG    = 2,
  KB_LOG_LEVEL_INFO     = 3,
  KB_LOG_LEVEL_WARN     = 4,
  KB_LOG_LEVEL_ERROR    = 5,
  KB_LOG_LEVEL_CRITICAL = 6,
} kb_log_level;

KB_API void kb_log_internal_str(kb_log_level p_level, const char *p_msg);
KB_API void kb_log_internal(kb_log_level p_level, const char *p_fmt, ...);

#ifdef __cplusplus
}
#endif

#endif  //KB_STD_CPP_KB_CORE_H
