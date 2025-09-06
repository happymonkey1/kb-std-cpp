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

#ifdef __cplusplus
namespace kb::math {
#endif

#ifndef KB_STD
typedef float f32;
#endif
typedef __m128 f32x4;

typedef struct kb_fixed_vec2 {
  f32 x, y;
} kb_fixed_vec2_t;

typedef struct kb_fixed_vec3 {
  f32 x, y, z;
} kb_fixed_vec3_t;

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
 * X component (0th) retrieval from a 4 component vector
 */
KB_FORCE_INLINE f32 kb_math_get_x_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_X(p_v); }
/**
 * Y component (1st) retrieval from a 4 component vector
 */
KB_FORCE_INLINE f32 kb_math_get_y_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_Y(p_v); }
/**
 * Z component (2nd) retrieval from a 4 component vector
 */
KB_FORCE_INLINE f32 kb_math_get_z_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_Z(p_v); }
/**
 * W component (3rd) retrieval from a 4 component vector
 */
KB_FORCE_INLINE f32 kb_math_get_w_f32(f32x4 p_v) KB_NOEXCEPT { return KB_MATH_VEC4_GET_W(p_v); }

/**
 * Load x, y, and z values into a 2 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec2_f32(f32 p_x, f32 p_y) KB_NOEXCEPT {
  return _mm_set_ps(0.0f, 0.0, p_y, p_x);
}

/**
 * Load x, y, and z values into a 3 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec3_f32(f32 p_x, f32 p_y, f32 p_z) KB_NOEXCEPT {
  return _mm_set_ps(0.0f, p_z, p_y, p_x);
}

/**
 * @brief Load a scalar value into a 2 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec2_f32_scalar(f32 p_v) KB_NOEXCEPT {
  return _mm_set_ps(0.0, 0.0, p_v, p_v);
}

/**
 * @brief Load a scalar value into a 3 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec3_f32_scalar(f32 p_v) KB_NOEXCEPT {
  return _mm_set_ps(0.0, p_v, p_v, p_v);
}

/**
 * @brief Load a scalar value into a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec4_f32_scalar(f32 p_v) KB_NOEXCEPT {
  return _mm_set_ps1(p_v);
}

/**
 * @brief Load x, y, z, and w values into a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_load_vec4_f32(f32 p_x, f32 p_y, f32 p_z, f32 p_w) KB_NOEXCEPT {
  return _mm_set_ps(p_w, p_z, p_y, p_x);
}

/**
 * @brief Component wise addition for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_add_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_add_ps(p_a, p_b);
}

/**
 * @brief Component wise multiplication for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_mul_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_mul_ps(p_a, p_b);
}

/**
 * @brief Component wise subtraction for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_sub_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_sub_ps(p_a, p_b);
}

/**
 * @brief Component wise division of a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_div_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  return _mm_div_ps(p_a, p_b);
}

/**
 * @brief Square root for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_sqrt_vec2(f32x4 p_v) KB_NOEXCEPT { return _mm_sqrt_ps(p_v); }

/**
 * @brief Square root for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_sqrt_vec3(f32x4 p_v) KB_NOEXCEPT { return _mm_sqrt_ps(p_v); }

/**
 * @brief Square root for a 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_sqrt_vec4(f32x4 p_v) KB_NOEXCEPT { return _mm_sqrt_ps(p_v); }

/**
 * @brief Dot product for 2 component vectors
 */
KB_FORCE_INLINE f32x4 kb_math_dot_vec2(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  // 0x31 = 0b00110001
  return _mm_dp_ps(p_a, p_b, 0x31);
}

/**
 * @brief Vector dot product for a 3 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_dot_vec3(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  // 0x71 = 0b01110001
  // High bits (0111): Use first three components of a and b
  // Low bit  (0001): Store result in first component
  return _mm_dp_ps(p_a, p_b, 0x71);
}

/**
 * @brief Dot product for 4 component vectors
 */
KB_FORCE_INLINE f32x4 kb_math_dot_vec4(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  // 0xF1 = 0b11110001
  return _mm_dp_ps(p_a, p_b, 0xF1);
}

/**
 * @brief Cross product for 3 component vectors
 */
KB_FORCE_INLINE f32x4 kb_math_cross_vec3(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  f32x4 t0 = _mm_shuffle_ps(p_a, p_a, _MM_SHUFFLE(3, 0, 2, 1));
  f32x4 t1 = _mm_shuffle_ps(p_b, p_b, _MM_SHUFFLE(3, 1, 0, 2));
  f32x4 t2 = _mm_mul_ps(t0, t1);
  f32x4 t3 = _mm_shuffle_ps(p_a, p_a, _MM_SHUFFLE(3, 1, 0, 2));
  f32x4 t4 = _mm_shuffle_ps(p_b, p_b, _MM_SHUFFLE(3, 0, 2, 1));
  f32x4 t5 = _mm_mul_ps(t3, t4);
  return _mm_sub_ps(t2, t5);
}

/**
 * @brief Compute the magnitude of the 2 component vector, returning the resultant in the 0th component (x) of the vector
 */
KB_FORCE_INLINE f32x4 kb_math_magnitude_vec2(f32x4 p_v) KB_NOEXCEPT {
  f32x4 self = kb_math_dot_vec2(p_v, p_v);
  return _mm_sqrt_ps(self);
}

/**
 * @brief Compute the magnitude of the 3 component vector, returning the resultant in the 0th component (x) of the vector
 */
KB_FORCE_INLINE f32x4 kb_math_magnitude_vec3(f32x4 p_v) KB_NOEXCEPT {
  f32x4 self = kb_math_dot_vec3(p_v, p_v);
  return _mm_sqrt_ps(self);
}

/**
 * @brief Compute the magnitude of the 4 component vector, returning the resultant in the 0th component (x) of the vector
 */
KB_FORCE_INLINE f32x4 kb_math_magnitude_vec4(f32x4 p_v) KB_NOEXCEPT {
  f32x4 self = kb_math_dot_vec4(p_v, p_v);
  return _mm_sqrt_ps(self);
}

/**
 * @brief Computes the normal of the 2 component vector, returning a new 2 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_normalize_vec2(f32x4 p_v) KB_NOEXCEPT {
  f32x4 mag = kb_math_magnitude_vec2(p_v);
  // Broadcast magnitude into all components to prevent div by zero
  f32x4 div = _mm_shuffle_ps(mag, mag, _MM_SHUFFLE(0, 0, 0, 0));
  return _mm_div_ps(p_v, div);
}

/**
 * @brief Computes the normal of the 3 component vector, returning a new 3 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_normalize_vec3(f32x4 p_v) KB_NOEXCEPT {
  f32x4 mag = kb_math_magnitude_vec3(p_v);
  // Broadcast magnitude into all components to prevent div by zero
  f32x4 div = _mm_shuffle_ps(mag, mag, _MM_SHUFFLE(0, 0, 0, 0));
  return _mm_div_ps(p_v, div);
}

/**
 * @brief Computes the normal of the 4 component vector, returning a new 4 component vector
 */
KB_FORCE_INLINE f32x4 kb_math_normalize_vec4(f32x4 p_v) KB_NOEXCEPT {
  f32x4 mag = kb_math_magnitude_vec4(p_v);
  // Broadcast magnitude into all components to prevent div by zero
  f32x4 div = _mm_shuffle_ps(mag, mag, _MM_SHUFFLE(0, 0, 0, 0));
  return _mm_div_ps(p_v, div);
}

/**
 * @brief Component wise equality comparison for a 2 component vector
 */
KB_FORCE_INLINE bool kb_math_equal_vec2(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  const f32x4 cmp = _mm_cmpeq_ps(p_a, p_b);
  return !(
    kb_math_get_x_f32(cmp) == 0 ||
    kb_math_get_y_f32(cmp) == 0
  );
}

/**
 * @brief Component wise equality comparison for a 3 component vector
 */
KB_FORCE_INLINE bool kb_math_equal_vec3(f32x4 p_a, f32x4 p_b) KB_NOEXCEPT {
  const f32x4 cmp = _mm_cmpeq_ps(p_a, p_b);
  return !(
    kb_math_get_x_f32(cmp) == 0 ||
    kb_math_get_y_f32(cmp) == 0 ||
    kb_math_get_z_f32(cmp) == 0
  );
}

/**
 * @brief Component wise equality comparison for a 4 component vector
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

/**
 * @brief Convert a 4 component SIMD vector to a fixed size 2 component vector
 */
KB_FORCE_INLINE void kb_math_vec4_to_fixed_vec2(f32x4 p_vec, kb_fixed_vec2_t * p_out) KB_NOEXCEPT {
  p_out->x = KB_MATH_VEC4_GET_X(p_vec);
  p_out->y = KB_MATH_VEC4_GET_Y(p_vec);
}

/**
 * @brief Convert a 4 component SIMD vector to a fixed sized 3 component vector
 */
KB_FORCE_INLINE void kb_math_vec4_to_fixed_vec3(f32x4 p_vec, kb_fixed_vec3_t * p_out) KB_NOEXCEPT {
  p_out->x = KB_MATH_VEC4_GET_X(p_vec);
  p_out->y = KB_MATH_VEC4_GET_Y(p_vec);
  p_out->z = KB_MATH_VEC4_GET_Z(p_vec);
}

/**
 * @brief Matrix multiplication of two 4x4 matrices ( p_out = p_mat_a * p_mat_b )
 */
KB_FORCE_INLINE void kb_math_matmul_mat4(const f32x4 * p_mat_a, const f32x4 * p_mat_b, f32x4 * p_out) KB_NOEXCEPT {
  f32x4 b0 = p_mat_b[0];
  f32x4 b1 = p_mat_b[1];
  f32x4 b2 = p_mat_b[2];
  f32x4 b3 = p_mat_b[3];

  // Transpose matrix B
  f32x4 t0 = _mm_unpacklo_ps(b0, b1);
  f32x4 t1 = _mm_unpackhi_ps(b0, b1);
  f32x4 t2 = _mm_unpacklo_ps(b2, b3);
  f32x4 t3 = _mm_unpackhi_ps(b2, b3);

  for (int i = 0; i < 4; ++i) {
    __m128 a_row = p_mat_a[i];
    __m128 c_row;

    // Splat (broadcast) the x, y, z, w components into their own vectors
    __m128 a_xxxx = _mm_shuffle_ps(a_row, a_row, _MM_SHUFFLE(0, 0, 0, 0));
    __m128 a_yyyy = _mm_shuffle_ps(a_row, a_row, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 a_zzzz = _mm_shuffle_ps(a_row, a_row, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 a_wwww = _mm_shuffle_ps(a_row, a_row, _MM_SHUFFLE(3, 3, 3, 3));

    // Multiply each component by the corresponding row of the transposed matrix
    __m128 mul0 = _mm_mul_ps(a_xxxx, t0);
    __m128 mul1 = _mm_mul_ps(a_yyyy, t1);
    __m128 mul2 = _mm_mul_ps(a_zzzz, t2);
    __m128 mul3 = _mm_mul_ps(a_wwww, t3);

    // Sum the results
    __m128 sum01 = _mm_add_ps(mul0, mul1);
    __m128 sum23 = _mm_add_ps(mul2, mul3);
    c_row = _mm_add_ps(sum01, sum23);
    p_out[i] = c_row;
  }
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
} // end namespace ::details
#endif

/**
 * Internal macros for less typing
 */

#define KB_MATH_OPERATOR_PLUS_IMPL(type) \
  KB_FORCE_INLINE auto operator+(const type & p_v) noexcept -> type { return type{ details::kb_math_add_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_PLUS_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator+=(const type & p_v) noexcept -> type & { vec = details::kb_math_add_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_MUL_IMPL(type) \
  KB_FORCE_INLINE auto operator*(const type & p_v) noexcept -> type { return type{ details::kb_math_mul_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_MUL_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator*=(const type & p_v) noexcept -> type & { vec = details::kb_math_mul_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_MINUS_IMPL(type) \
  KB_FORCE_INLINE auto operator-(const type & p_v) noexcept -> type { return type{ details::kb_math_sub_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_MINUS_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator-=(const type & p_v) noexcept -> type & { vec = details::kb_math_sub_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_DIV_IMPL(type) \
  KB_FORCE_INLINE auto operator/(const type & p_v) noexcept -> type { return type{ details::kb_math_div_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_DIV_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator/=(const type & p_v) noexcept -> type & { vec = details::kb_math_div_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_DOT_IMPL(type) \
  KB_FORCE_INLINE auto dot(const type & p_v) noexcept -> f32 { const f32x4 dot_vec = details::kb_math_dot_##type(vec, p_v.vec); return KB_MATH_VEC4_GET_X(dot_vec); }
#define KB_MATH_OPERATOR_NORMAL_IMPL(type) \
  KB_FORCE_INLINE auto normal() noexcept -> type { return type{ details::kb_math_normalize_##type(vec) }; }
#define KB_MATH_OPERATOR_NORMALIZE_IMPL(type) \
  KB_FORCE_INLINE auto normalize() noexcept -> void { f32x4 res = details::kb_math_normalize_##type(vec); vec = res; }
#define KB_MATH_OPERTAOR_SQRT_IMPL(type) \
  KB_FORCE_INLINE auto sqrt() noexcept -> f32 { const f32x4 res = details::kb_math_sqrt_##type(vec); return res[0]; }
#define KB_MATH_OPERATOR_MAG_IMPL(type) \
  KB_FORCE_INLINE auto magnitude() noexcept -> f32 { const f32x4 res = details::kb_math_magnitude_##type(vec); return res[0]; }
#define KB_MATH_OPERATOR_EQUALITY_IMPL(type) \
  KB_FORCE_INLINE auto operator==(const type & p_v) noexcept -> bool { return details::kb_math_equal_##type(vec, p_v.vec); }

/**
 * End internal macros for less typing
 */

// Forward declarations
class vec2;
class vec3;

/**
 * @brief Fixed size 2 component vector for interop with graphics APIs
 */
struct fixed_vec2 {
  f32 x, y;

  KB_FORCE_INLINE explicit fixed_vec2(const vec2 & p_vec);
};

/**
 * @brief Fixed size 3 component vector for interop with graphics APIs
 */
struct fixed_vec3 {
  f32 x, y, z;

  KB_FORCE_INLINE explicit fixed_vec3(const vec3 & p_vec);
};

/**
 * SIMD optimized 2 component vector
 */
struct vec2 {
  union {
    struct {
      f32 x, y;
    };
    f32x4 vec;
  };

  /**
   * Constructs a 2 component vector from a SIMD vector
   */
  explicit vec2(f32x4 p_v) noexcept { vec = p_v; }

  /**
   * Constructs a 2 component vector from a fixed size 2 component vector
   */
  explicit vec2(const fixed_vec2 & p_v) noexcept { vec = details::kb_math_load_vec2_f32(p_v.x, p_v.y); }

  KB_MATH_OPERATOR_PLUS_IMPL(vec2)
  KB_MATH_OPERATOR_PLUS_EQUALS_IMPL(vec2)
  KB_MATH_OPERATOR_MUL_IMPL(vec2)
  KB_MATH_OPERATOR_MUL_EQUALS_IMPL(vec2)
  KB_MATH_OPERATOR_MINUS_IMPL(vec2)
  KB_MATH_OPERATOR_MINUS_EQUALS_IMPL(vec2)
  KB_MATH_OPERATOR_DIV_IMPL(vec2)
  KB_MATH_OPERATOR_DIV_EQUALS_IMPL(vec2)
  KB_MATH_OPERATOR_DOT_IMPL(vec2)
  KB_MATH_OPERATOR_NORMAL_IMPL(vec2)
  KB_MATH_OPERATOR_NORMALIZE_IMPL(vec2)
  KB_MATH_OPERTAOR_SQRT_IMPL(vec2)
  KB_MATH_OPERATOR_MAG_IMPL(vec2)
  KB_MATH_OPERATOR_EQUALITY_IMPL(vec2)
};

/**
 * @brief SIMD optimized 3 component vector
 */
struct vec3 {
  union {
    struct {
      f32 x, y, z;
    };
    f32x4 vec;
  };

  /**
   * @brief Constructs a 3 component vector from a SIMD vector
   */
  explicit vec3(f32x4 p_v) noexcept {
    vec = p_v;
  }

  /**
   * @brief Constructs a 3 component vector from a fixed size 3 component vector
   */
  explicit vec3(const fixed_vec3& p_v) noexcept {
    vec = details::kb_math_load_vec3_f32(p_v.x, p_v.y, p_v.z);
  }

  KB_MATH_OPERATOR_PLUS_IMPL(vec3)
  KB_MATH_OPERATOR_PLUS_EQUALS_IMPL(vec3)
  KB_MATH_OPERATOR_MUL_IMPL(vec3)
  KB_MATH_OPERATOR_MUL_EQUALS_IMPL(vec3)
  KB_MATH_OPERATOR_MINUS_IMPL(vec3)
  KB_MATH_OPERATOR_MINUS_EQUALS_IMPL(vec3)
  KB_MATH_OPERATOR_DIV_IMPL(vec3)
  KB_MATH_OPERATOR_DIV_EQUALS_IMPL(vec3)
  KB_MATH_OPERATOR_DOT_IMPL(vec3)
  KB_MATH_OPERATOR_NORMAL_IMPL(vec3)
  KB_MATH_OPERATOR_NORMALIZE_IMPL(vec3)
  KB_MATH_OPERTAOR_SQRT_IMPL(vec3)
  KB_MATH_OPERATOR_MAG_IMPL(vec3)
  KB_MATH_OPERATOR_EQUALITY_IMPL(vec3)
};

/**
 * @brief SIMD optimized 4 component vector
 */
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

  /**
   * @brief Constructs a 4 component vector from a scalar 32 bit float
   */
  explicit vec4(f32 p_v) noexcept { vec = details::kb_math_load_vec4_f32_scalar(p_v); }

  /**
   * @brief Constructs a 4 component vector from a SIMD 4 component vector representation
   */
  explicit vec4(f32x4 p_v) noexcept { vec = p_v; }

  /**
   * @brief Constructs a 4 component vector from individual x, y, z, and w components
   */
  vec4(f32 p_x, f32 p_y, f32 p_z, f32 p_w) noexcept { vec = details::kb_math_load_vec4_f32(p_x, p_y, p_z, p_w); }

  KB_MATH_OPERATOR_PLUS_IMPL(vec4)
  KB_MATH_OPERATOR_PLUS_EQUALS_IMPL(vec4)
  KB_MATH_OPERATOR_MUL_IMPL(vec4)
  KB_MATH_OPERATOR_MUL_EQUALS_IMPL(vec4)
  KB_MATH_OPERATOR_MINUS_IMPL(vec4)
  KB_MATH_OPERATOR_MINUS_EQUALS_IMPL(vec4)
  KB_MATH_OPERATOR_DIV_IMPL(vec4)
  KB_MATH_OPERATOR_DIV_EQUALS_IMPL(vec4)
  KB_MATH_OPERATOR_DOT_IMPL(vec4)
  KB_MATH_OPERATOR_NORMAL_IMPL(vec4)
  KB_MATH_OPERATOR_NORMALIZE_IMPL(vec4)
  KB_MATH_OPERTAOR_SQRT_IMPL(vec4)
  KB_MATH_OPERATOR_MAG_IMPL(vec4)
  KB_MATH_OPERATOR_EQUALITY_IMPL(vec4)
};

/**
 * @brief SIMD optimized 3x3 matrix
 */
struct mat3 {
  // Padded for SIMD optimization
  f32x4 rows[3];

  explicit mat3(f32 p_scalar) noexcept {
    rows[0] = details::kb_math_load_vec3_f32_scalar(p_scalar);
    rows[1] = details::kb_math_load_vec3_f32_scalar(p_scalar);
    rows[2] = details::kb_math_load_vec3_f32_scalar(p_scalar);
  }
};

/**
 * @brief SIMD optimized 4x4 matrix
 */
struct mat4 {
  f32x4 rows[4];

  explicit mat4(f32 p_scalar) noexcept {
    rows[0] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[1] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[2] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[3] = details::kb_math_load_vec4_f32_scalar(p_scalar);
  }

  /**
   * @brief Constructs a mat4 wrapper from a pointer to a 4 row SIMD representation of a matrix
   */
  explicit mat4(f32x4 * p_mat4) noexcept {
    rows[0] = p_mat4[0];
    rows[1] = p_mat4[1];
    rows[2] = p_mat4[2];
    rows[3] = p_mat4[3];
  }

  /**
   * @brief Performs a matrix multiplication, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto matmul(const mat4 & p_other) noexcept -> mat4 {
    f32x4 out[4];
    details::kb_math_matmul_mat4(rows, p_other.rows, out);
    return mat4{ out };
  }

  /**
   * @brief Performs a matrix multiplication, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto operator*(const mat4 & p_other) noexcept -> mat4 {
    f32x4 out[4];
    details::kb_math_matmul_mat4(rows, p_other.rows, out);
    return mat4{ out };
  }
};

/**
 * @brief Constructs a fixed_vec2 from a SIMD optimized vec2
 */
fixed_vec2::fixed_vec2(const kb::math::vec2 & p_vec) {
  const auto & vec = p_vec.vec;
  x = KB_MATH_VEC4_GET_X(vec);
  y = KB_MATH_VEC4_GET_Y(vec);
}

/**
 * @brief Constructs a fixed_vec3 from a SIMD optimized vec3
 */
fixed_vec3::fixed_vec3(const kb::math::vec3 & p_vec) {
  const auto & vec = p_vec.vec;
  x = KB_MATH_VEC4_GET_X(vec);
  y = KB_MATH_VEC4_GET_Y(vec);
  z = KB_MATH_VEC4_GET_Z(vec);
}

#ifdef __cplusplus
} // end namespace kb::math
#endif

/**
 * Be a nice neighbor and undef our internal macros
 */
#undef KB_MATH_OPERATOR_PLUS_IMPL
#undef KB_MATH_OPERATOR_PLUS_EQUALS_IMPL
#undef KB_MATH_OPERATOR_MUL_IMPL
#undef KB_MATH_OPERATOR_MUL_EQUALS_IMPL
#undef KB_MATH_OPERATOR_MINUS_IMPL
#undef KB_MATH_OPERATOR_MINUS_EQUALS_IMPL
#undef KB_MATH_OPERATOR_DIV_IMPL
#undef KB_MATH_OPERATOR_DIV_EQUALS_IMPL
#undef KB_MATH_OPERATOR_DOT_IMPL
#undef KB_MATH_OPERATOR_NORMAL_IMPL
#undef KB_MATH_OPERATOR_NORMALIZE_IMPL
#undef KB_MATH_OPERTAOR_SQRT_IMPL
#undef KB_MATH_OPERATOR_MAG_IMPL
#undef KB_MATH_OPERATOR_EQUALITY_IMPL

#endif  //KB_STD_MATH_MATH_HPP
