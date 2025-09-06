#include "kb/kb_std.hpp"
#include "kb/math/math.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

#define KB_ASSERT_CLOSE(a, b, epsilon, message, ...)                        \
  do {                                                                      \
    if (std::abs((a) - (b)) > (epsilon)) {                                  \
      std::string formatted_msg = fmt::format(message, ##__VA_ARGS__);    \
      KB_LOG_ERROR("Assertion failed in {} line {}: {}", __FILE__, __LINE__, formatted_msg.c_str()); \
      KB_LOG_ERROR("       Expected: {}, Got: {}", (double)(b), (double)(a));                        \
      std::exit(1);                                                         \
    }                                                                       \
  } while (false)

using namespace kb;
using namespace kb::math;

constexpr f32 TEST_EPSILON = 1e-6f;

void test_vec2_constructors() {
  KB_LOG_INFO("  Running test_vec2_constructors...");
  vec2 v_default;
  (void)v_default;

  vec2 v_scalar{ 5.0f };
  KB_ASSERT(v_scalar.x == 5.0f && v_scalar.y == 5.0f, "vec2 scalar constructor failed.");

  vec2 v_xy{ 1.0f, 2.0f };
  KB_ASSERT(v_xy.x == 1.0f && v_xy.y == 2.0f, "vec2 component constructor failed.");

  KB_ASSERT(::kb::math::details::kb_math_get_z_f32(v_xy.vec) == 0.0f, "vec2 z-component should be 0.");
  KB_ASSERT(::kb::math::details::kb_math_get_w_f32(v_xy.vec) == 0.0f, "vec2 w-component should be 0.");
}

void test_vec2_operators() {
  KB_LOG_INFO("  Running test_vec2_operators...");
  vec2 v0{ 1.0f, 2.0f };
  vec2 v1{ 3.0f, 4.0f };

  vec2 v_add = v0 + v1;
  KB_ASSERT(v_add.x == 4.0f && v_add.y == 6.0f, "vec2 addition failed.");

  vec2 v_sub = v1 - v0;
  KB_ASSERT(v_sub.x == 2.0f && v_sub.y == 2.0f, "vec2 subtraction failed.");

  vec2 v_mul = v0 * v1;
  KB_ASSERT(v_mul.x == 3.0f && v_mul.y == 8.0f, "vec2 multiplication failed.");

  vec2 v_div = v1 / vec2{ 3.0f, 2.0f };
  KB_ASSERT(v_div.x == 1.0f && v_div.y == 2.0f, "vec2 division failed.");

  KB_ASSERT(v0 == vec2(1.0f, 2.0f), "vec2 equality failed.");
  KB_ASSERT(!(v0 == v1), "vec2 inequality failed.");
}

void test_vec2_methods() {
  KB_LOG_INFO("  Running test_vec2_methods...");
  vec2 v0{ 3.0f, 4.0f };
  vec2 v1{ -4.0f, 3.0f };

  f32 dot_res = v0.dot(v1);
  KB_ASSERT_CLOSE(dot_res, 0.0f, TEST_EPSILON, "vec2 dot product of orthogonal vectors should be 0.");
  KB_ASSERT_CLOSE(v0.dot(v0), 25.0f, TEST_EPSILON, "vec2 dot product with self failed.");

  f32 mag = v0.magnitude();
  KB_ASSERT_CLOSE(mag, 5.0f, TEST_EPSILON, "vec2 magnitude calculation failed.");

  vec2 norm = v0.normal();
  KB_ASSERT_CLOSE(norm.x, 0.6f, TEST_EPSILON, "vec2 normal x-component is wrong.");
  KB_ASSERT_CLOSE(norm.y, 0.8f, TEST_EPSILON, "vec2 normal y-component is wrong.");
  KB_ASSERT_CLOSE(norm.magnitude(), 1.0f, TEST_EPSILON, "Normalized vector magnitude should be 1.");

  v0.normalize();
  KB_ASSERT_CLOSE(v0.x, 0.6f, TEST_EPSILON, "vec2 normalize method x-component is wrong.");
  KB_ASSERT_CLOSE(v0.y, 0.8f, TEST_EPSILON, "vec2 normalize method y-component is wrong.");
}

void test_vec3_constructors() {
  KB_LOG_INFO("  Running test_vec3_constructors...");
  vec3 v_default;
  (void)v_default;

  vec3 v_scalar{ 5.0f };
  KB_ASSERT(v_scalar.x == 5.0f && v_scalar.y == 5.0f && v_scalar.z == 5.0f, "vec3 scalar constructor failed.");

  vec3 v_xyz{ 1.0f, 2.0f, 3.0f };
  KB_ASSERT(v_xyz.x == 1.0f && v_xyz.y == 2.0f && v_xyz.z == 3.0f, "vec3 component constructor failed.");
  KB_ASSERT(::kb::math::details::kb_math_get_w_f32(v_xyz.vec) == 0.0f, "vec3 w-component should be 0.");
}

void test_vec3_methods() {
  KB_LOG_INFO("  Running test_vec3_methods...");
  vec3 v0{ 2.0f, 3.0f, 4.0f };
  KB_ASSERT_CLOSE(v0.magnitude(), std::sqrt(29.0f), TEST_EPSILON, "vec3 magnitude failed. Got %f", v0.magnitude());

  v0.normalize();
  KB_ASSERT_CLOSE(v0.magnitude(), 1.0f, TEST_EPSILON, "vec3 normalize failed.");
}

void test_vec3_cross_product() {
  KB_LOG_INFO("  Running test_vec3_cross_product...");
  vec3 i{ 1.0f, 0.0f, 0.0f };
  vec3 j{ 0.0f, 1.0f, 0.0f };
  vec3 k{ 0.0f, 0.0f, 1.0f };

  vec3 res_k = i.cross(j);
  KB_ASSERT_CLOSE(res_k.x, k.x, TEST_EPSILON, "Cross product i x j should be k (x-component).");
  KB_ASSERT_CLOSE(res_k.y, k.y, TEST_EPSILON, "Cross product i x j should be k (y-component).");
  KB_ASSERT_CLOSE(res_k.z, k.z, TEST_EPSILON, "Cross product i x j should be k (z-component).");

  vec3 res_neg_k = j.cross(i);
  KB_ASSERT_CLOSE(res_neg_k.z, -1.0f, TEST_EPSILON, "Cross product j x i should be -k.");

  vec3 res_zero = i.cross(i);
  KB_ASSERT_CLOSE(res_zero.magnitude(), 0.0f, TEST_EPSILON, "Cross product of a vector with itself should be zero.");
}

auto test_vec4_add() -> void {
  KB_LOG_INFO("  Running test_vec4_add...");
  vec4 v0{ 0.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 + v1;
  KB_ASSERT(res.x == 1, "x addition should be 1");
  KB_ASSERT(res.y == 1, "y addition should be 1");
  KB_ASSERT(res.z == 1, "z addition should be 1");
  KB_ASSERT(res.w == 1, "w addition should be 1");
}

auto test_vec4_mul() -> void {
  KB_LOG_INFO("  Running test_vec4_mul...");
  vec4 v0{ 0.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 * v1;
  KB_ASSERT(res.x == 0, "x mul should be 0");
  KB_ASSERT(res.y == 0, "y mul should be 0");
  KB_ASSERT(res.z == 0, "z mul should be 0");
  KB_ASSERT(res.w == 0, "w mul should be 0");
}

auto test_vec4_sub() -> void {
  KB_LOG_INFO("  Running test_vec4_sub...");
  vec4 v0{ 4.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 - v1;
  KB_ASSERT(res.x == 3, "x sub should be 3");
  KB_ASSERT(res.y == 3, "y sub should be 3");
  KB_ASSERT(res.z == 3, "z sub should be 3");
  KB_ASSERT(res.w == 3, "w sub should be 3");
}

auto test_vec4_div() -> void {
  KB_LOG_INFO("  Running test_vec4_div...");
  vec4 v0{ 12.0 };
  vec4 v1{ 3.0 };

  vec4 res = v0 / v1;
  KB_ASSERT(res.x == 4, "x div should be 4");
  KB_ASSERT(res.y == 4, "y div should be 4");
  KB_ASSERT(res.z == 4, "z div should be 4");
  KB_ASSERT(res.w == 4, "w div should be 4");
}

auto test_vec4_dot() -> void {
  KB_LOG_INFO("  Running test_vec4_dot...");
  vec4 v0{ 2.0 };
  vec4 v1{ 1.0 };
  f32 res = v0.dot(v1);
  KB_ASSERT_CLOSE(res, 8.0f, TEST_EPSILON, "dot product should be 8");
}

auto test_vec4_magnitude() -> void {
  KB_LOG_INFO("  Running test_vec4_magnitude...");
  vec4 v0{ 1.0 };
  f32 mag = v0.magnitude();
  KB_ASSERT_CLOSE(mag, 2.0f, TEST_EPSILON, "magnitude should be 2, found %f", mag);
}

auto test_vec4_normals() -> void {
  KB_LOG_INFO("  Running test_vec4_normals...");
  vec4 v0{ 2.0 };
  vec4 res = v0.normal();
  KB_ASSERT_CLOSE(res.x, 0.5f, TEST_EPSILON, "x normal should be 0.5, found {}", res.x);
  KB_ASSERT_CLOSE(res.y, 0.5f, TEST_EPSILON, "y normal should be 0.5, found {}", res.y);
  KB_ASSERT_CLOSE(res.z, 0.5f, TEST_EPSILON, "z normal should be 0.5, found {}", res.z);
  KB_ASSERT_CLOSE(res.w, 0.5f, TEST_EPSILON, "w normal should be 0.5, found {}", res.w);

  KB_ASSERT(v0.x == 2, "x should be unchanged, found %f", v0.x);
  KB_ASSERT(v0.y == 2, "y should be unchanged, found %f", v0.y);
  KB_ASSERT(v0.z == 2, "z should be unchanged, found %f", v0.z);
  KB_ASSERT(v0.w == 2, "w should be unchanged, found %f", v0.w);

  v0.normalize();
  KB_ASSERT_CLOSE(v0.x, 0.5f, TEST_EPSILON, "x normal should be 0.5 after normalize");
  KB_ASSERT_CLOSE(v0.y, 0.5f, TEST_EPSILON, "y normal should be 0.5 after normalize");
  KB_ASSERT_CLOSE(v0.z, 0.5f, TEST_EPSILON, "z normal should be 0.5 after normalize");
  KB_ASSERT_CLOSE(v0.w, 0.5f, TEST_EPSILON, "w normal should be 0.5 after normalize");
}

auto test_vec4_indexing() -> void {
  KB_LOG_INFO("  Running test_vec4_indexing...");
  vec4 v0{ 1.0, 2.0, 3.0, 4.0 };
  KB_ASSERT_CLOSE(v0[0], 1.0, TEST_EPSILON, "v[0] should be 1.0, found {}", float{ v0[0] });
  KB_ASSERT_CLOSE(v0[1], 2.0, TEST_EPSILON, "v[1] should be 2.0, found {}", float{ v0[1] });
  KB_ASSERT_CLOSE(v0[2], 3.0, TEST_EPSILON, "v[2] should be 3.0, found {}", float{ v0[2] });
  KB_ASSERT_CLOSE(v0[3], 4.0, TEST_EPSILON, "v[3] should be 4.0, found {}", float{ v0[3] });

  v0[0] = 5.0;
  v0[1] = 6.0;
  v0[2] = 7.0;
  v0[3] = 8.0;
  KB_ASSERT_CLOSE(v0[0], 5.0, TEST_EPSILON, "v[0] should be 5.0, found {}", float{ v0[0] });
  KB_ASSERT_CLOSE(v0[1], 6.0, TEST_EPSILON, "v[1] should be 6.0, found {}", float{ v0[1] });
  KB_ASSERT_CLOSE(v0[2], 7.0, TEST_EPSILON, "v[2] should be 7.0, found {}", float{ v0[2] });
  KB_ASSERT_CLOSE(v0[3], 8.0, TEST_EPSILON, "v[3] should be 8.0, found {}", float{ v0[3] });
}

void test_mat3_vec3_multiplication() {
  KB_LOG_INFO("  Running test_mat3_vec3_multiplication...");
  mat3 rotation;
  rotation.rows[0] = vec3{0.f, -1.f, 0.f};
  rotation.rows[1] = vec3{1.f, 0.f, 0.f};
  rotation.rows[2] = vec3{0.f, 0.f, 1.f};

  vec3 direction{10.f, 0.f, 0.f};

  vec3 result = rotation * direction;

  kb::math::vec3 expected{0.f, 10.f, 0.f};

  KB_ASSERT(result == expected, "mat3 * vec3 multiplication failed. Expected: {}, found: {}", expected, result);
}

void test_mat4_multiplication() {
  KB_LOG_INFO("  Running test_mat4_multiplication...");
  mat4 identity;
  identity.rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
  identity.rows[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
  identity.rows[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
  identity.rows[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

  mat4 m;
  m.rows[0] = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
  m.rows[1] = _mm_set_ps(5.0f, 6.0f, 7.0f, 8.0f);
  m.rows[2] = _mm_set_ps(8.0f, 7.0f, 6.0f, 5.0f);
  m.rows[3] = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);

  mat4 res_ident = m * identity;

  for (int i = 0; i < 4; ++i) {
    KB_ASSERT(
      vec4{res_ident.rows[i]} == vec4{m.rows[i]},
      "Matrix multiplied by identity should not change (row {}). Expected: {}, found: {}",
      i,
      vec4{ res_ident.rows[i] },
      vec4{ m.rows[i] }
    );
  }

  mat4 scale;
  scale.rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 2.0f);
  scale.rows[1] = _mm_set_ps(0.0f, 0.0f, 2.0f, 0.0f);
  scale.rows[2] = _mm_set_ps(0.0f, 2.0f, 0.0f, 0.0f);
  scale.rows[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

  mat4 trans;
  trans.rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
  trans.rows[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
  trans.rows[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
  trans.rows[3] = _mm_set_ps(1.0f, 30.0f, 20.0f, 10.0f);

  mat4 res_mat = scale * trans;

  mat4 expected;
  expected.rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 2.0f);
  expected.rows[1] = _mm_set_ps(0.0f, 0.0f, 2.0f, 0.0f);
  expected.rows[2] = _mm_set_ps(0.0f, 2.0f, 0.0f, 0.0f);
  expected.rows[3] = _mm_set_ps(1.0f, 30.0f, 20.0f, 10.0f);

  for (int i = 0; i < 4; ++i) {
    KB_ASSERT(
      vec4{res_mat.rows[i]} == vec4{expected.rows[i]},
      "Scale * Translation result is incorrect (row {}). Expected: {}, found: {}",
      i,
      vec4{ expected.rows[i] },
      vec4{ res_mat.rows[i] }
    );
  }
}

void test_mat4_vec4_multiplication() {
  KB_LOG_INFO("  Running test_mat4_vec4_multiplication...");
  mat4 transform{};
  transform.rows[0] = vec4{1.f, 0.f, 0.f, 10.f}.vec;
  transform.rows[1] = vec4{0.f, 2.f, 0.f, 0.f}.vec;
  transform.rows[2] = vec4{0.f, 0.f, 1.f, -5.f}.vec;
  transform.rows[3] = vec4{0.f, 0.f, 0.f, 1.f}.vec;

  vec4 point{3.f, 5.f, 8.f, 1.f};

  vec4 result = transform * point;

  kb::math::vec4 expected{13.f, 10.f, 3.f, 1.f};

  KB_ASSERT(result == expected, "mat4 * vec4 multiplication failed. Expected: {}, found: {}", expected, result);
}

void test_ortho_common() {
  KB_LOG_INFO("  Running test_ortho_common...");

  KB_LOG_INFO("    Testing symmetric ortho");
  mat4 result = ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

  mat4 expected{};
  expected.rows[0] = vec4{1.0f, 0.0f, 0.0f, 0.0f}.vec;
  expected.rows[1] = vec4{0.0f, 1.0f, 0.0f, 0.0f}.vec;
  expected.rows[2] = vec4{0.0f, 0.0f, -1.0f, 0.0f}.vec;
  expected.rows[3] = vec4{0.0f, 0.0f, 0.0f, 1.0f}.vec;

  KB_ASSERT(result == expected, "Expected {}, found {}", expected, result);

  KB_LOG_INFO("    Testing screen space ortho");
  float width = 1024.0f;
  float height = 768.0f;
  result = ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);

  expected.rows[0] = vec4{2.0f / width, 0.0f, 0.0f, 0.0f}.vec;
  expected.rows[1] = vec4{0.0f, -2.0f / height, 0.0f, 0.0f}.vec;
  expected.rows[2] = vec4{0.0f, 0.0f, -1.0f, 0.0f}.vec;
  expected.rows[3] = vec4{-1.0f, 1.0f, 0.0f, 1.0f}.vec;

  KB_ASSERT(result == expected, "Expected {}, found {}", expected, result);
}

void test_perspective_common() {
  KB_LOG_INFO("  Running test_perspective_common...");
  const float fovy_rad = M_PI / 2.0f; // 90 degrees
  const float aspect = 16.0f / 9.0f;
  const float z_near = 0.1f;
  const float z_far = 100.0f;

  mat4 result = perspective(fovy_rad, aspect, z_near, z_far);

  const float tan_half_fovy = tanf(fovy_rad / 2.0f);
  const float x_scale = (1.0f / tan_half_fovy) / aspect;
  const float y_scale = 1.0f / tan_half_fovy;
  const float z_c = (z_far + z_near) / (z_near - z_far);
  const float z_d = (2.0f * z_far * z_near) / (z_near - z_far);

  mat4 expected{};
  expected.rows[0] = vec4{x_scale, 0.0f, 0.0f, 0.0f}.vec;
  expected.rows[1] = vec4{0.0f, y_scale, 0.0f, 0.0f}.vec;
  expected.rows[2] = vec4{0.0f, 0.0f, z_c, z_d}.vec;
  expected.rows[3] = vec4{0.0f, 0.0f, -1.0f, 0.0f}.vec;

  KB_ASSERT(result == expected, "Expected perspective matrices to be equal. Expected: {}, found: {}", expected, result);
}

void test_fixed_interop() {
  KB_LOG_INFO("  Running test_fixed_interop...");
  vec2 v2_original{ 12.3f, -45.6f };
  fixed_vec2 f2{ v2_original };
  KB_ASSERT_CLOSE(f2.x, 12.3f, TEST_EPSILON, "vec2 to fixed_vec2 x failed.");
  KB_ASSERT_CLOSE(f2.y, -45.6f, TEST_EPSILON, "vec2 to fixed_vec2 y failed.");

  vec2 v2_restored{ f2 };
  KB_ASSERT(v2_original == v2_restored, "fixed_vec2 to vec2 restoration failed.");

  vec3 v3_original{ 1.1f, -2.2f, 3.3f };
  fixed_vec3 f3{ v3_original };
  KB_ASSERT_CLOSE(f3.x, 1.1f, TEST_EPSILON, "vec3 to fixed_vec3 x failed.");
  KB_ASSERT_CLOSE(f3.y, -2.2f, TEST_EPSILON, "vec3 to fixed_vec3 y failed.");
  KB_ASSERT_CLOSE(f3.z, 3.3f, TEST_EPSILON, "vec3 to fixed_vec3 z failed.");

  vec3 v3_restored{ f3 };
  KB_ASSERT(v3_original == v3_restored, "fixed_vec3 to vec3 restoration failed.");
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int {
  kb::core::Logger::init();
  KB_LOG_INFO("Starting Kablunk Math Library Test Suite...");

  KB_LOG_INFO("\n[ Running Original vec4 Tests ]");
  test_vec4_add();
  test_vec4_mul();
  test_vec4_sub();
  test_vec4_div();
  test_vec4_dot();
  test_vec4_magnitude();
  test_vec4_normals();
  test_vec4_indexing();

  KB_LOG_INFO("\n[ Running vec2 Tests ]");
  test_vec2_constructors();
  test_vec2_operators();
  test_vec2_methods();

  KB_LOG_INFO("\n[ Running vec3 Tests ]");
  test_vec3_constructors();
  test_vec3_methods();
  test_vec3_cross_product();

  KB_LOG_INFO("\n[ Running mat3 Tests ]");
  test_mat3_vec3_multiplication();

  KB_LOG_INFO("\n[ Running mat4 Tests ]");
  test_mat4_multiplication();
  test_mat4_vec4_multiplication();
  test_ortho_common();
  test_perspective_common();

  KB_LOG_INFO("\n[ Running Interop Tests ]");
  test_fixed_interop();

  KB_LOG_INFO("\nAll tests passed successfully!");
  kb::core::Logger::shutdown();

  return 0;
}