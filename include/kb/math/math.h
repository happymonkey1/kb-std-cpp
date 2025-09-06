//
// Created by happy on 9/4/2025.
//

#ifndef KB_STD_MATH_MATH_HPP
#define KB_STD_MATH_MATH_HPP

#include <immintrin.h>

#ifdef __cplusplus
#  include <cstdint>
#  include <array>
#  include <cmath>
#else
#  include <stdint.h>
#  include <math.h>
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
#  define dKB_MATH_VEC4_GET_INDEX(x, index) x.m128_f32[index]
#  define KB_MATH_IVEC4_GET_X(x) x.m128_i32[0]
#  define KB_MATH_IVEC4_GET_Y(x) x.m128_i32[1]
#  define KB_MATH_IVEC4_GET_Z(x) x.m128_i32[2]
#  define KB_MATH_IVEC4_GET_W(x) x.m128_i32[3]
#else
#  define KB_MATH_VEC4_GET_X(x) x[0]
#  define KB_MATH_VEC4_GET_Y(x) x[1]
#  define KB_MATH_VEC4_GET_Z(x) x[2]
#  define KB_MATH_VEC4_GET_W(x) x[3]
#  define KB_MATH_VEC4_GET_INDEX(x, index) x[index]
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
 * @brief Matrix multiplication of two 3x3 matrices ( p_out = p_mat_a * p_mat_b )
 */
KB_FORCE_INLINE void kb_math_matmul_mat3(const f32x4 * p_mat_a, const f32x4 * p_mat_b, f32x4 * p_out) KB_NOEXCEPT {
  f32x4 b0 = p_mat_b[0];
  f32x4 b1 = p_mat_b[1];
  f32x4 b2 = p_mat_b[2];

  // Transpose matrix B
  f32x4 t0 = _mm_unpacklo_ps(b0, b1);
  f32x4 t1 = _mm_unpackhi_ps(b2, _mm_setzero_ps());
  f32x4 t2 = _mm_unpackhi_ps(b0, b1);
  f32x4 t3 = _mm_unpackhi_ps(b2, _mm_setzero_ps());

  const f32x4 b_col0 = _mm_movelh_ps(b0, t1);
  const f32x4 b_col1 = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(1, 0, 3, 2));
  const f32x4 b_col2 = _mm_movelh_ps(t2, t3);

  for (size_t i = 0; i < 3; ++i) {
    const f32x4 a_row = p_mat_a[i];

    // Dot product of A's row with each of B's columns
    f32x4 d0 = _mm_dp_ps(a_row, b_col0, 0x71);
    f32x4 d1 = _mm_dp_ps(a_row, b_col1, 0x71);
    f32x4 d2 = _mm_dp_ps(a_row, b_col2, 0x71);

    // Unpack results
    f32x4 res_xy = _mm_movelh_ps(d0, d1);
    f32x4 res_z_pad = _mm_movelh_ps(d2, _mm_setzero_ps());

    // Shuffle into out matrix
    p_out[i] = _mm_shuffle_ps(res_xy, res_z_pad, _MM_SHUFFLE(2, 0, 2, 0));
  }
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

  const f32x4 b_t0 = _mm_movelh_ps(t0, t2);
  const f32x4 b_t1 = _mm_movehl_ps(t2, t0);
  const f32x4 b_t2 = _mm_movelh_ps(t1, t3);
  const f32x4 b_t3 = _mm_movehl_ps(t3, t1);

  for (int i = 0; i < 4; ++i) {
    f32x4 a_row = p_mat_a[i];

    // Dot product of A's row with each of B's columns
    const f32x4 d0 = _mm_dp_ps(a_row, b_t0, 0xF1);
    const f32x4 d1 = _mm_dp_ps(a_row, b_t1, 0xF1);
    const f32x4 d2 = _mm_dp_ps(a_row, b_t2, 0xF1);
    const f32x4 d3 = _mm_dp_ps(a_row, b_t3, 0xF1);

    // Unpack and shuffle to gather the results into a single vector
    const f32x4 res_xy = _mm_movelh_ps(d0, d1);
    const f32x4 res_zw = _mm_movelh_ps(d2, d3);
    p_out[i] = _mm_shuffle_ps(res_xy, res_zw, _MM_SHUFFLE(2, 0, 2, 0));
  }
}

KB_FORCE_INLINE f32x4 kb_math_matmul_mat3_vec3(const f32x4 * p_mat, const f32x4 p_vec) KB_NOEXCEPT {
  // Dot matrix rows with vector
  f32x4 d0 = _mm_dp_ps(p_mat[0], p_vec, 0x71);
  f32x4 d1 = _mm_dp_ps(p_mat[1], p_vec, 0x71);
  f32x4 d2 = _mm_dp_ps(p_mat[2], p_vec, 0x71);

  f32x4 r0 = _mm_unpacklo_ps(d0, d1);
  f32x4 r1 = _mm_movelh_ps  (r0, d2);
  return r1;
}

KB_FORCE_INLINE f32x4 kb_math_matmul_mat4_vec4(const f32x4 * p_mat, const f32x4 p_vec) KB_NOEXCEPT {
  // Dot matrix rows with vector
  f32x4 d0 = _mm_dp_ps(p_mat[0], p_vec, 0xF1);
  f32x4 d1 = _mm_dp_ps(p_mat[1], p_vec, 0xF1);
  f32x4 d2 = _mm_dp_ps(p_mat[2], p_vec, 0xF1);
  f32x4 d3 = _mm_dp_ps(p_mat[3], p_vec, 0xF1);

  const f32x4 res_xy = _mm_unpacklo_ps(d0, d1);
  const f32x4 res_zw = _mm_unpacklo_ps(d2, d3);

  return _mm_movelh_ps(res_xy, res_zw);
}

/**
 * @brief Element wise equality for two 3x3 matrices
 */
KB_FORCE_INLINE bool kb_math_equal_mat3(const f32x4 * p_mat_a, const f32x4 * p_mat_b) KB_NOEXCEPT {
  const f32x4 cmp0 = _mm_cmpeq_ps(p_mat_a[0], p_mat_b[0]);
  const f32x4 cmp1 = _mm_cmpeq_ps(p_mat_a[1], p_mat_b[1]);
  const f32x4 cmp2 = _mm_cmpeq_ps(p_mat_a[2], p_mat_b[2]);
  const f32x4 cmp3 = _mm_cmpeq_ps(p_mat_a[3], p_mat_b[3]);

  // Combine all row equality results
  f32x4 all_rows_eq = _mm_and_ps(cmp0, cmp1);
  all_rows_eq       = _mm_and_ps(all_rows_eq, cmp2);
  all_rows_eq       = _mm_and_ps(all_rows_eq, cmp3);

  const int32_t mask = _mm_movemask_ps(all_rows_eq);
  // 0x7 = 0b0111
  // We don't care about the W component
  return mask == 0x7;
}

/**
 * @brief Element wise equality for two 4x4 matrices
 */
KB_FORCE_INLINE bool kb_math_equal_mat4(const f32x4 * p_mat_a, const f32x4 * p_mat_b) KB_NOEXCEPT {
  const f32x4 cmp0 = _mm_cmpeq_ps(p_mat_a[0], p_mat_b[0]);
  const f32x4 cmp1 = _mm_cmpeq_ps(p_mat_a[1], p_mat_b[1]);
  const f32x4 cmp2 = _mm_cmpeq_ps(p_mat_a[2], p_mat_b[2]);
  const f32x4 cmp3 = _mm_cmpeq_ps(p_mat_a[3], p_mat_b[3]);

  // Combine all row equality results
  f32x4 all_rows_eq = _mm_and_ps(cmp0, cmp1);
  all_rows_eq       = _mm_and_ps(all_rows_eq, cmp2);
  all_rows_eq       = _mm_and_ps(all_rows_eq, cmp3);

  const int32_t mask = _mm_movemask_ps(all_rows_eq);
  return mask == 0xF;
}

/**
 * Computes an orthographic project from a 4x4 matrix
 */
KB_FORCE_INLINE void kb_math_ortho_mat4(
  f32 p_left,
  f32 p_right,
  f32 p_bottom,
  f32 p_top,
  f32 p_z_near,
  f32 p_z_far,
  f32x4 * p_out
) KB_NOEXCEPT {
  const f32x4 v_r_t_zf = kb_math_load_vec4_f32(p_right, p_top, p_z_far, 0.f);
  const f32x4 v_l_b_zn = kb_math_load_vec4_f32(p_left, p_bottom, p_z_near, 0.f);

  // { r-l, t-b, zf-zn, 0 }
  const f32x4 v_diffs = kb_math_sub_vec4(v_r_t_zf, v_l_b_zn);
  // { r+l, t+b, zf+zn, 0 }
  const f32x4 v_sums  = kb_math_add_vec4(v_r_t_zf, v_l_b_zn);

  // { 2.0, 2.0, -2.0, IGNORE }
  const f32x4 v_numerators_diag = kb_math_load_vec4_f32(2.f, 2.f, -2.f, 1.f);
  const f32x4 v_diag = _mm_div_ps(v_numerators_diag, v_diffs);

  // -(sum / diff)
  const f32x4 t0 = _mm_sub_ps(_mm_setzero_ps(), v_sums);
  const f32x4 v_tran = _mm_div_ps(t0, v_diffs);

  p_out[0] = kb_math_load_vec4_f32(KB_MATH_VEC4_GET_X(v_diag), 0.0f,                       0.0f,                       0.0f);
  p_out[1] = kb_math_load_vec4_f32(0.0f,                       KB_MATH_VEC4_GET_Y(v_diag), 0.0f,                       0.0f);
  p_out[2] = kb_math_load_vec4_f32(0.0f,                       0.0f,                       KB_MATH_VEC4_GET_Z(v_diag), 0.0f);
  p_out[3] = kb_math_load_vec4_f32(KB_MATH_VEC4_GET_X(v_tran), KB_MATH_VEC4_GET_Y(v_tran), KB_MATH_VEC4_GET_Z(v_tran), 1.0f);
}

/**
 * @brief Computes a SIMD optimized perspective matrix
 */
KB_FORCE_INLINE void kb_math_perspective_mat4(
  f32 p_fovy_radians,
  f32 p_aspect_ratio,
  f32 p_z_near,
  f32 p_z_far,
  f32x4 * p_out
) KB_NOEXCEPT {
  const f32 tan_half_fovy = tanf(p_fovy_radians * 0.5f);

  const f32 y_scale = 1.0f / tan_half_fovy;
  const f32 x_scale = y_scale / p_aspect_ratio;

  // { z_far, z_near, 0.0f, 0.0f }
  const f32x4 v_zf_zn = kb_math_load_vec2_f32(p_z_far, p_z_near);

  const f32 two_zf_zn = 2.0f * p_z_far * p_z_near;
  const f32 zf_plus_zn = p_z_far + p_z_near;
  // { 2 * z_far * z_near, z_far + z_near, 0.0f, 0.0f }
  const f32x4 v_num = kb_math_load_vec2_f32(two_zf_zn, zf_plus_zn);

  const f32 zn_minus_zf = p_z_near - p_z_far;
  const f32x4 v_den = _mm_set_ps1(zn_minus_zf);

  const f32x4 v_z_components = _mm_div_ps(v_num, v_den);

  p_out[0] = kb_math_load_vec4_f32(x_scale, 0.0f,    0.0f,                               0.0f);
  p_out[1] = kb_math_load_vec4_f32(0.0f,    y_scale, 0.0f,                               0.0f);
  p_out[2] = kb_math_load_vec4_f32(0.0f,    0.0f,    KB_MATH_VEC4_GET_Y(v_z_components), KB_MATH_VEC4_GET_X(v_z_components));
  p_out[3] = kb_math_load_vec4_f32(0.0f,    0.0f,    -1.0f,                              0.0f);
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
  KB_FORCE_INLINE auto operator+(const type & p_v) const noexcept -> type { return type{ details::kb_math_add_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_PLUS_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator+=(const type & p_v) noexcept -> type & { vec = details::kb_math_add_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_MUL_IMPL(type) \
  KB_FORCE_INLINE auto operator*(const type & p_v) const noexcept -> type { return type{ details::kb_math_mul_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_MUL_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator*=(const type & p_v) noexcept -> type & { vec = details::kb_math_mul_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_MINUS_IMPL(type) \
  KB_FORCE_INLINE auto operator-(const type & p_v) const noexcept -> type { return type{ details::kb_math_sub_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_MINUS_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator-=(const type & p_v) noexcept -> type & { vec = details::kb_math_sub_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_DIV_IMPL(type) \
  KB_FORCE_INLINE auto operator/(const type & p_v) const noexcept -> type { return type{ details::kb_math_div_vec4(vec, p_v.vec) }; }
#define KB_MATH_OPERATOR_DIV_EQUALS_IMPL(type) \
  KB_FORCE_INLINE auto operator/=(const type & p_v) noexcept -> type & { vec = details::kb_math_div_vec4(vec, p_v.vec); return *this; }
#define KB_MATH_OPERATOR_DOT_IMPL(type) \
  KB_FORCE_INLINE auto dot(const type & p_v) const noexcept -> type::value_t { const f32x4 dot_vec = details::kb_math_dot_##type(vec, p_v.vec); return KB_MATH_VEC4_GET_X(dot_vec); }
#define KB_MATH_OPERATOR_CROSS_IMPL(type) \
  KB_FORCE_INLINE auto cross(const type & p_v) const noexcept -> type { const f32x4 dot_vec = details::kb_math_cross_##type(vec, p_v.vec); return type{ dot_vec }; }
#define KB_MATH_OPERATOR_NORMAL_IMPL(type) \
  KB_FORCE_INLINE auto normal() const noexcept -> type { return type{ details::kb_math_normalize_##type(vec) }; }
#define KB_MATH_OPERATOR_NORMALIZE_IMPL(type) \
  KB_FORCE_INLINE auto normalize() noexcept -> void { f32x4 res = details::kb_math_normalize_##type(vec); vec = res; }
#define KB_MATH_OPERTAOR_SQRT_IMPL(type) \
  KB_FORCE_INLINE auto sqrt() const noexcept -> type::value_t { const f32x4 res = details::kb_math_sqrt_##type(vec); return res[0]; }
#define KB_MATH_OPERATOR_MAG_IMPL(type) \
  KB_FORCE_INLINE auto magnitude() const noexcept -> type::value_t { const f32x4 res = details::kb_math_magnitude_##type(vec); return res[0]; }
#define KB_MATH_OPERATOR_EQUALITY_IMPL(type) \
  KB_FORCE_INLINE auto operator==(const type & p_v) const noexcept -> bool { return details::kb_math_equal_##type(vec, p_v.vec); }
#define KB_MATH_OPERATOR_INDEX_IMPL(type) \
  KB_FORCE_INLINE auto operator[](std::size_t p_index) const noexcept -> type::value_t const & { return KB_MATH_VEC4_GET_INDEX(vec, p_index); } \
  KB_FORCE_INLINE auto operator[](std::size_t p_index) noexcept -> type::value_t & { return reinterpret_cast<type::value_t *>(this)[p_index]; }
// TODO: we can include all assignment operators
#define KB_MATH_OPERATOR_ASSIGNMENTS_IMPL(type) \
  KB_FORCE_INLINE auto operator=(f32x4 p_vec) noexcept -> type & { vec = p_vec; return *this; }
/**
 * End internal macros for less typing
 */

#if defined(_MSC_VER)
// MSVC Compiler
__pragma(warning(push))
// C4324 is a related warning for struct padding, but MSVC typically
// does not warn for ignored attributes on template arguments like GCC/Clang.
// This structure is included for completeness and future-proofing.
// __pragma(warning(disable : WARNING_NUMBER_IF_NEEDED))
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

#ifndef KB_STD_CORE_ALIGNED_ARRAY_HPP

template <typename T, std::size_t N, std::size_t Alignment>
struct alignas(Alignment) AlignedArray {
  T m_data[N];

  using value_type      = T;
  using size_type       = std::size_t;
  using reference       = T&;
  using const_reference = const T&;
  using pointer         = T*;
  using const_pointer   = const T*;
  using iterator        = T*;
  using const_iterator  = const T*;

  KB_FORCE_INLINE constexpr auto operator[](size_type p_pos) noexcept -> reference {
    return m_data[p_pos];
  }

  KB_FORCE_INLINE constexpr auto operator[](size_type p_pos) const noexcept -> const_reference {
    return m_data[p_pos];
  }

  KB_FORCE_INLINE auto at(size_type p_pos) -> reference {
    KB_ASSERT(p_pos < N, "AlignedArray::at: Index out of range");
    return m_data[p_pos];
  }

  KB_FORCE_INLINE auto at(size_type p_pos) const -> const_reference {
    KB_ASSERT(p_pos < N, "AlignedArray::at: Index out of range");
    return m_data[p_pos];
  }

  KB_FORCE_INLINE constexpr auto begin() noexcept -> iterator { return m_data; }
  KB_FORCE_INLINE constexpr auto end() noexcept -> iterator { return m_data + N; }
  KB_FORCE_INLINE constexpr auto begin() const noexcept -> const_iterator { return m_data; }
  KB_FORCE_INLINE constexpr auto end() const noexcept -> const_iterator { return m_data + N; }

  KB_FORCE_INLINE constexpr auto size() const noexcept -> size_type { return N; }
  KB_FORCE_INLINE constexpr bool empty() const noexcept { return N == 0; }

  KB_FORCE_INLINE constexpr auto data() noexcept -> pointer { return m_data; }
  KB_FORCE_INLINE constexpr auto data() const noexcept -> const_pointer { return m_data; }
};

#endif //KB_STD_CORE_ALIGNED_ARRAY_HPP
template <typename T, std::size_t N>
using f32x4_aligned_array_t = AlignedArray<T, N, 16>;

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
  using value_t = f32;
  union {
    struct {
      value_t x, y;
    };
    f32x4 vec;
  };

  vec2() noexcept = default;
  explicit vec2(value_t p_v) noexcept { vec = details::kb_math_load_vec2_f32_scalar(p_v); }
  vec2(value_t p_x, value_t p_y) noexcept { vec = details::kb_math_load_vec2_f32(p_x, p_y); }

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
  KB_MATH_OPERATOR_INDEX_IMPL(vec2)
  KB_MATH_OPERATOR_ASSIGNMENTS_IMPL(vec2)
};

/**
 * @brief SIMD optimized 3 component vector
 */
struct vec3 {
  using value_t = f32;
  union {
    struct {
      value_t x, y, z;
    };
    f32x4 vec;
  };

  vec3() noexcept = default;
  explicit vec3(value_t p_v) noexcept { vec = details::kb_math_load_vec3_f32_scalar(p_v); }
  vec3(value_t p_x, value_t p_y, value_t p_z) noexcept { vec = details::kb_math_load_vec3_f32(p_x, p_y, p_z); }

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
  KB_MATH_OPERATOR_CROSS_IMPL(vec3)
  KB_MATH_OPERATOR_NORMAL_IMPL(vec3)
  KB_MATH_OPERATOR_NORMALIZE_IMPL(vec3)
  KB_MATH_OPERTAOR_SQRT_IMPL(vec3)
  KB_MATH_OPERATOR_MAG_IMPL(vec3)
  KB_MATH_OPERATOR_EQUALITY_IMPL(vec3)
  KB_MATH_OPERATOR_INDEX_IMPL(vec3)
  KB_MATH_OPERATOR_ASSIGNMENTS_IMPL(vec3)
};

/**
 * @brief SIMD optimized 4 component vector
 */
struct vec4 {
  using value_t = f32;
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
  KB_MATH_OPERATOR_INDEX_IMPL(vec4)
  KB_MATH_OPERATOR_ASSIGNMENTS_IMPL(vec4)
};

/**
 * @brief SIMD optimized 3x3 matrix
 */
struct mat3 {
  // Padded for SIMD optimization
  vec3 rows[3];

  mat3() noexcept = default;

  explicit mat3(f32 p_scalar) noexcept {
    rows[0] = details::kb_math_load_vec3_f32_scalar(p_scalar);
    rows[1] = details::kb_math_load_vec3_f32_scalar(p_scalar);
    rows[2] = details::kb_math_load_vec3_f32_scalar(p_scalar);
  }

  /**
   * @brief Constructs a mat4 wrapper from a pointer to a 4 row SIMD representation of a matrix
   */
  explicit mat3(f32x4_aligned_array_t<f32x4, 3> p_mat4) noexcept {
    rows[0] = p_mat4[0];
    rows[1] = p_mat4[1];
    rows[2] = p_mat4[2];
  }

  /**
   * @brief Performs a matrix multiplication for two 3x3 matrices, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto matmul(const mat3 & p_other) noexcept -> mat3 {
    f32x4_aligned_array_t<f32x4, 3> out;
    details::kb_math_matmul_mat3(as_simd(), p_other.as_simd(), out.data());
    return mat3{ out };
  }

  /**
   * @brief Performs a matrix multiplication for two 3x3 matrices, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto operator*(const mat3 & p_other) noexcept -> mat3 {
    f32x4_aligned_array_t<f32x4, 3> out;
    details::kb_math_matmul_mat3(as_simd(), p_other.as_simd(), out.data());
    return mat3{ out };
  }

  /**
   * @brief Multiplies a 3x3 matrix with a 3 component vector
   */
  KB_FORCE_INLINE auto operator*(const vec3 & p_vec) noexcept -> vec3 {
    return vec3{ details::kb_math_matmul_mat3_vec3(as_simd(), p_vec.vec) };
  }

  /**
   * @brief Indexing operator to retrive a mutable reference to a matrix row
   */
  KB_FORCE_INLINE auto operator[](std::size_t p_index) const noexcept -> const vec3 & { return rows[p_index]; }

  /**
   * @brief Indexing operator to retrive a mutable reference to a matrix row
   */
  KB_FORCE_INLINE auto operator[](std::size_t p_index) noexcept -> vec3 & { return rows[p_index]; }

  /**
   * @brief Equality comparison with another 4x4 matrix
   */
  KB_FORCE_INLINE auto operator==(const mat3 & p_other) const noexcept -> bool {
    return details::kb_math_equal_mat4(as_simd(), p_other.as_simd());
  }
private:
  KB_FORCE_INLINE auto as_simd() const noexcept -> const f32x4 * { return reinterpret_cast<const f32x4 *>(rows); }
};

/**
 * @brief SIMD optimized 4x4 matrix
 */
struct mat4 {
  vec4 rows[4];

  mat4() noexcept = default;

  explicit mat4(f32 p_scalar) noexcept {
    rows[0] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[1] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[2] = details::kb_math_load_vec4_f32_scalar(p_scalar);
    rows[3] = details::kb_math_load_vec4_f32_scalar(p_scalar);
  }

  /**
   * @brief Constructs a mat4 wrapper from a pointer to a 4 row SIMD representation of a matrix
   */
  explicit mat4(f32x4_aligned_array_t<f32x4, 4> p_mat4) noexcept {
    rows[0] = p_mat4[0];
    rows[1] = p_mat4[1];
    rows[2] = p_mat4[2];
    rows[3] = p_mat4[3];
  }

  /**
   * @brief Performs a matrix multiplication, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto matmul(const mat4 & p_other) noexcept -> mat4 {
    f32x4_aligned_array_t<f32x4, 4> out;
    details::kb_math_matmul_mat4(as_simd(), p_other.as_simd(), out.data());
    return mat4{ out };
  }

  /**
   * @brief Performs a matrix multiplication, returning a new resultant matrix
   */
  KB_FORCE_INLINE auto operator*(const mat4 & p_other) noexcept -> mat4 {
    f32x4_aligned_array_t<f32x4, 4> out;
    details::kb_math_matmul_mat4(as_simd(), p_other.as_simd(), out.data());
    return mat4{ out };
  }

  /**
   * @brief Multiplies a 4x4 matrix with a 4 component vector
   */
  KB_FORCE_INLINE auto operator*(const vec4 & p_vec) noexcept -> vec4 {
    return vec4{ details::kb_math_matmul_mat4_vec4(as_simd(), p_vec.vec) };
  }

  /**
   * @brief Indexing operator returning a mutable reference to a 4 component vector row
   */
  KB_FORCE_INLINE auto operator[](std::size_t p_index) noexcept -> vec4 & {
    return rows[p_index];
  }

  /**
   * @brief Equality comparison with another 4x4 matrix
   */
  KB_FORCE_INLINE auto operator==(const mat4 & p_other) const noexcept -> bool {
    return details::kb_math_equal_mat4(as_simd(), p_other.as_simd());
  }

private:
  KB_FORCE_INLINE auto as_simd() const noexcept -> const f32x4 * { return reinterpret_cast<const f32x4 *>(rows); }
};

/**
 * @brief Computes an orthographic matrix
 */
KB_FORCE_INLINE auto ortho(
  f32 p_left,
  f32 p_right,
  f32 p_bottom,
  f32 p_top,
  f32 p_z_near,
  f32 p_z_far
) noexcept -> mat4 {
  f32x4_aligned_array_t<f32x4, 4> out;
  details::kb_math_ortho_mat4(p_left, p_right, p_bottom, p_top, p_z_near, p_z_far, out.data());
  return mat4{ out };
}

/**
 * @brief Computes a perspective matrix
 */
KB_FORCE_INLINE auto perspective(
  f32 p_fovy_radians,
  f32 p_aspect_ratio,
  f32 p_z_near,
  f32 p_z_far
) noexcept -> mat4 {
  f32x4_aligned_array_t<f32x4, 4> out;
  details::kb_math_perspective_mat4(p_fovy_radians, p_aspect_ratio, p_z_near, p_z_far, out.data());
  return mat4{ out };
}

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

#if defined(_MSC_VER)
__pragma(warning(pop))
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

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
#undef KB_MATH_OPERATOR_CROSS_IMPL
#undef KB_MATH_OPERATOR_NORMAL_IMPL
#undef KB_MATH_OPERATOR_NORMALIZE_IMPL
#undef KB_MATH_OPERTAOR_SQRT_IMPL
#undef KB_MATH_OPERATOR_MAG_IMPL
#undef KB_MATH_OPERATOR_EQUALITY_IMPL
#undef KB_MATH_OPERATOR_INDEX_IMPL
#undef KB_MATH_OPERATOR_ASSIGNMENTS_IMPL

#if defined(KB_STD) && defined(__cplusplus)
template <> class fmt::formatter<::kb::math::vec2> {
public:
  constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); }
  template <typename Context>
  constexpr auto format (::kb::math::vec2 const& p_vec, Context& p_ctx) const {
    return format_to(p_ctx.out(), "vec2({}, {})", p_vec.x, p_vec.y);
  }
};

template <> class fmt::formatter<::kb::math::vec3> {
public:
  constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); }
  template <typename Context>
  constexpr auto format (::kb::math::vec3 const& p_vec, Context& p_ctx) const {
    return format_to(p_ctx.out(), "vec3({}, {}, {})", p_vec.x, p_vec.y, p_vec.z);
  }
};

template <> class fmt::formatter<::kb::math::vec4> {
public:
  constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); }
  template <typename Context>
  constexpr auto format (::kb::math::vec4 const& p_vec, Context& p_ctx) const {
    return format_to(p_ctx.out(), "vec4({}, {}, {}, {})", p_vec.x, p_vec.y, p_vec.z, p_vec.w);
  }
};

template <> class fmt::formatter<::kb::math::mat3> {
public:
  constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); }
  template <typename Context>
  constexpr auto format (::kb::math::mat3 const& p_mat, Context& p_ctx) const {
    return format_to(
      p_ctx.out(),
      "mat3(\n  {},\n  {},\n  {}\n)", // A clean multi-line format
      ::kb::math::vec3{p_mat.rows[0]},
      ::kb::math::vec3{p_mat.rows[1]},
      ::kb::math::vec3{p_mat.rows[2]}
    );
  }
};

template <> class fmt::formatter<::kb::math::mat4> {
public:
  constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); }
  template <typename Context>
  constexpr auto format (::kb::math::mat4 const& p_mat, Context& p_ctx) const {
    return format_to(
      p_ctx.out(),
      "mat4(\n  {},\n  {},\n  {},\n  {}\n)", // A clean multi-line format
      ::kb::math::vec4{p_mat.rows[0]},
      ::kb::math::vec4{p_mat.rows[1]},
      ::kb::math::vec4{p_mat.rows[2]},
      ::kb::math::vec4{p_mat.rows[3]}
    );
  }
};
#endif

#endif  //KB_STD_MATH_MATH_HPP
