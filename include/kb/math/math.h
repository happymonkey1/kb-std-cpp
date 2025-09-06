//
// Created by happy on 9/4/2025.
//

#ifndef KB_STD_MATH_MATH_HPP
#define KB_STD_MATH_MATH_HPP

#include <immintrin.h>

#ifdef __cplusplus
#  include <cstdint>
#else
#  include <stdint.h>
#endif

#ifndef KB_FORCE_INLINE
#  if defined(_MSC_VER)  // MSCV
#    define KB_FORCE_INLINE __forceinline
#  elif defined(__GNUC__) // GCC
#    define KB_FORCE_INLINE inline __attribute__((always_inline))
#  elif defined(__clang__)
#    define KB_FORCE_INLINE [[clang::always_inline]] inline
#  endif
#endif

#ifndef KB_NOEXCEPT
#  if defined(__cplusplus)
#    define KB_NOEXCEPT noexcept
#  else
#    define KB_NOEXCEPT
#  endif
#endif

namespace kb::math {

#ifndef KB_STD
typedef float f32;
#endif
typedef __m128 f32x4;

#ifdef __cplusplus
namespace details {
#endif


#if 0
#ifdef __cplusplus
template <uint32_t Index>
f32 kb_math_get_x_f32_impl(f32x4 p_v) KB_NOEXCEPT {
  return _mm_cvtss_f32(_mm_shuffle_ps(p_v, p_v, _MM_SHUFFLE(Index, Index, Index, Index)));
}
#  define KB_MATH_VEC4_GET_X(x) ::kb::math::details::kb_math_get_x_f32_impl<0>((x))
#  define KB_MATH_VEC4_GET_Y(x) ::kb::math::details::kb_math_get_x_f32_impl<1>((x))
#  define KB_MATH_VEC4_GET_Z(x) ::kb::math::details::kb_math_get_x_f32_impl<2>((x))
#  define KB_MATH_VEC4_GET_W(x) ::kb::math::details::kb_math_get_x_f32_impl<3>((x))
#else
f32 kb_math_get_x_f32_impl(uint32_t p_index, f32x4 p_v) KB_NOEXCEPT {
  return _mm_cvtss_f32(_mm_shuffle_ps(p_v, p_v, _MM_SHUFFLE(p_index, p_index, p_index, p_index)));
}
#  define KB_MATH_VEC4_GET_X(x) kb_math_get_x_f32_impl(0, (x))
#  define KB_MATH_VEC4_GET_Y(x) kb_math_get_x_f32_impl(1, (x))
#  define KB_MATH_VEC4_GET_Z(x) kb_math_get_x_f32_impl(2, (x))
#  define KB_MATH_VEC4_GET_W(x) kb_math_get_x_f32_impl(3, (x))
#endif
#endif

/**
 * Helper to define retrieval of a specific component by index
 */
#if defined(_MSC_VER)
#  define KB_MATH_VEC4_GET_X(x) x.m128_f32[0]
#  define KB_MATH_VEC4_GET_Y(x) x.m128_f32[1]
#  define KB_MATH_VEC4_GET_Z(x) x.m128_f32[2]
#  define KB_MATH_VEC4_GET_W(x) x.m128_f32[3]
#  define KB_MATH_IVEC4_GET_X(x) x.m128_i32[0]
#  define KB_MATH_IVEC4_GET_Y(x) x.m128_i32[1]
#  define KB_MATH_IVEC4_GET_Z(x) x.m128_i32[2]
#  define KB_MATH_IVEC4_GET_W(x) x.m128_i32[3]
#else
#  define KB_MATH_VEC4_GET_X(x) x[0]
#  define KB_MATH_VEC4_GET_Y(x) x[1]
#  define KB_MATH_VEC4_GET_Z(x) x[2]
#  define KB_MATH_VEC4_GET_W(x) x[3]
#  define KB_MATH_IVEC4_GET_X(x) x[0]
#  define KB_MATH_IVEC4_GET_Y(x) x[1]
#  define KB_MATH_IVEC4_GET_Z(x) x[2]
#  define KB_MATH_IVEC4_GET_W(x) x[3]
#endif

/**
 * Kablunk Math C API
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Component retrieval
 */
KB_FORCE_INLINE f32 kb_math_get_x_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_X(p_v); }
KB_FORCE_INLINE f32 kb_math_get_y_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_Y(p_v); }
KB_FORCE_INLINE f32 kb_math_get_z_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_Z(p_v); }
KB_FORCE_INLINE f32 kb_math_get_w_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_W(p_v); }

/**
 * @brief Load a scalar value into a vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec4_f32_scalar(f32 p_v) KB_NOEXCEPT {
  return _mm_set_ps1(p_v);
}

/**
 * @brief Load x, y, z, and w values into a vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec4_f32(f32 p_x, f32 p_y, f32 p_z, f32 p_w) KB_NOEXCEPT {
  return _mm_set_ps(p_w, p_z, p_y, p_x);
}

/**
 * @brief Component wise addition
 */
KB_FORCE_INLINE f32x4 kb_math_add_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_add_ps(p_a, p_b);
}

/**
 * @brief Component wise multiplication
 */
KB_FORCE_INLINE f32x4 kb_math_mul_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_mul_ps(p_a, p_b);
}

/**
 * @brief Component wise subtraction
 */
KB_FORCE_INLINE f32x4 kb_math_sub_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_sub_ps(p_a, p_b);
}

/**
 * @brief Component wise division
 */
KB_FORCE_INLINE f32x4 kb_math_div_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_div_ps(p_a, p_b);
}

KB_FORCE_INLINE f32x4 kb_math_sqrt_vec4(f32x4 p_v) KB_NOEXCEPT {
  return _mm_sqrt_ps(p_v);
}

/**
 * @brief Vector dot product
 */
KB_FORCE_INLINE f32x4 kb_math_dot_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_dp_ps(p_a, p_b, 0xF1);
}

/**
 * @brief Compute the magnitude of the vector, returning the resultant in the 0th component (x) of the vector
 */
KB_FORCE_INLINE f32x4 kb_math_magnitude_vec4(f32x4 p_v) KB_NOEXCEPT {
  f32x4 self = kb_math_dot_vec4(p_v, p_v);
  return _mm_sqrt_ps(self);
}

KB_FORCE_INLINE f32x4 kb_math_normalize_vec4(f32x4 p_v) KB_NOEXCEPT {
  f32x4 mag = kb_math_magnitude_vec4(p_v);
  // Broadcast magnitude into all components to prevent div by zero
  f32x4 div = _mm_shuffle_ps(mag, mag, _MM_SHUFFLE(0, 0, 0, 0));
  return _mm_div_ps(p_v, div);
}

/**
 * @brief Component wise equality comparison
 */
KB_FORCE_INLINE bool kb_math_equal_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  const f32x4 cmp = _mm_cmpeq_ps(p_a, p_b);
  return !(
    kb_math_get_x_f32(cmp) == 0 ||
    kb_math_get_y_f32(cmp) == 0 ||
    kb_math_get_z_f32(cmp) == 0 ||
    kb_math_get_w_f32(cmp) == 0
  );
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
} // end namespace ::details
#endif

struct vec4 {
  union {
    struct {
      f32 x, y, z, w;
    };

    f32x4 vec;
  };

  vec4() noexcept = default;
  ~vec4() noexcept = default;

  vec4(const vec4 & p_other) noexcept {
    vec = p_other.vec;
  }

  auto operator=(const vec4 & p_other) noexcept -> vec4 & {
    vec = p_other.vec;
    return *this;
  }

  vec4(vec4 && p_other) noexcept {
    vec = p_other.vec;
  }

  auto operator=(vec4 && p_other) noexcept -> vec4 & {
    vec = p_other.vec;
    return *this;
  }

  explicit vec4(f32 p_v) noexcept {
    vec = details::kb_math_load_vec4_f32_scalar(p_v);
  }

  explicit vec4(f32x4 p_v) noexcept {
    vec = p_v;
  }

  vec4(f32 p_x, f32 p_y, f32 p_z, f32 p_w) noexcept {
    vec = details::kb_math_load_vec4_f32(p_x, p_y, p_z, p_w);
  }

  KB_FORCE_INLINE auto operator+(const vec4 & p_v) noexcept -> vec4 {
    return vec4{ details::kb_math_add_vec4(vec, p_v.vec) };
  }

  KB_FORCE_INLINE auto operator+=(const vec4 & p_v) noexcept -> vec4 & {
    vec = details::kb_math_add_vec4(vec, p_v.vec);
    return *this;
  }

  KB_FORCE_INLINE auto operator*(const vec4 & p_v) noexcept -> vec4 {
    return vec4{ details::kb_math_mul_vec4(vec, p_v.vec) };
  }

  KB_FORCE_INLINE auto operator*=(const vec4 & p_v) noexcept -> vec4 & {
    vec = details::kb_math_mul_vec4(vec, p_v.vec);
    return *this;
  }

  KB_FORCE_INLINE auto operator-(const vec4 & p_v) noexcept -> vec4 {
    return vec4{ details::kb_math_sub_vec4(vec, p_v.vec) };
  }

  KB_FORCE_INLINE auto operator-=(const vec4 & p_v) noexcept -> vec4 & {
    vec = details::kb_math_sub_vec4(vec, p_v.vec);
    return *this;
  }

  KB_FORCE_INLINE auto operator/(const vec4 & p_v) noexcept -> vec4 {
    return vec4{ details::kb_math_div_vec4(vec, p_v.vec) };
  }

  KB_FORCE_INLINE auto operator/=(const vec4 & p_v) noexcept -> vec4 & {
    vec = details::kb_math_div_vec4(vec, p_v.vec);
    return *this;
  }

  KB_FORCE_INLINE auto dot(const vec4 & p_v) noexcept -> f32 {
    const f32x4 dot_vec = details::kb_math_dot_vec4(vec, p_v.vec);
    return KB_MATH_VEC4_GET_X(dot_vec);
  }

  KB_FORCE_INLINE auto normal() noexcept -> vec4 {
    return vec4{ details::kb_math_normalize_vec4(vec) };
  }

  KB_FORCE_INLINE auto normalize() noexcept -> void {
    f32x4 res = details::kb_math_normalize_vec4(vec);
    vec = res;
  }

  KB_FORCE_INLINE auto sqrt() noexcept -> f32 {
    const f32x4 res = details::kb_math_sqrt_vec4(vec);
    return res[0];
  }

  KB_FORCE_INLINE auto magnitude() noexcept -> f32 {
    const f32x4 res = details::kb_math_magnitude_vec4(vec);
    return res[0];
  }

  KB_FORCE_INLINE auto operator==(const vec4 & p_v) noexcept -> bool {
    return details::kb_math_equal_vec4(vec, p_v.vec);
  }
};

#ifdef __cplusplus
} // end namespace kb::math
#endif

#endif  //KB_STD_MATH_MATH_HPP
