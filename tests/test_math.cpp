//
// Created by happy on 9/4/2025.
//

#include "kb/kb_std.hpp"
#include "kb/math/math.h"

using namespace kb;
using namespace kb::math;

auto test_vec4_add() -> void {
  vec4 v0{ 0.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 + v1;
  KB_ASSERT(res.x == 1, "x addition should be 1");
  KB_ASSERT(res.y == 1, "y addition should be 1");
  KB_ASSERT(res.z == 1, "z addition should be 1");
  KB_ASSERT(res.w == 1, "w addition should be 1");
}

auto test_vec4_mul() -> void {
  vec4 v0{ 0.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 * v1;
  KB_ASSERT(res.x == 0, "x mul should be 0");
  KB_ASSERT(res.y == 0, "y mul should be 0");
  KB_ASSERT(res.z == 0, "z mul should be 0");
  KB_ASSERT(res.w == 0, "w mul should be 0");
}

auto test_vec4_sub() -> void {
  vec4 v0{ 4.0 };
  vec4 v1{ 1.0 };

  vec4 res = v0 - v1;
  KB_ASSERT(res.x == 3, "x sub should be 3");
  KB_ASSERT(res.y == 3, "y sub should be 3");
  KB_ASSERT(res.z == 3, "z sub should be 3");
  KB_ASSERT(res.w == 3, "w sub should be 3");
}

auto test_vec4_div() -> void {
  vec4 v0{ 12.0 };
  vec4 v1{ 3.0 };

  vec4 res = v0 / v1;
  KB_ASSERT(res.x == 4, "x div should be 4");
  KB_ASSERT(res.y == 4, "y div should be 4");
  KB_ASSERT(res.z == 4, "z div should be 4");
  KB_ASSERT(res.w == 4, "w div should be 4");
}

auto test_vec4_dot() -> void {
  vec4 v0{ 2.0 };
  vec4 v1{ 1.0 };
  f32 res = v0.dot(v1);
  KB_ASSERT(res == 8, "dot product should be 8");
}

auto test_vec4_magnitude() -> void {
  vec4 v0{ 1.0 };
  f32 mag = v0.magnitude();
  KB_ASSERT(mag == 2, "magnitude should be 2, found {}", mag);
}

auto test_vec4_normals() -> void {
  vec4 v0{ 2.0 };
  vec4 res = v0.normal();
  KB_ASSERT(res.x == 0.5, "x normal should be 1, found {}", res.x);
  KB_ASSERT(res.y == 0.5, "y normal should be 1, found {}", res.y);
  KB_ASSERT(res.z == 0.5, "z normal should be 1, found {}", res.z);
  KB_ASSERT(res.w == 0.5, "w normal should be 1, found {}", res.w);

  KB_ASSERT(v0.x == 2, "x should be unchanged, found {}", res.x);
  KB_ASSERT(v0.y == 2, "x should be unchanged, found {}", res.y);
  KB_ASSERT(v0.z == 2, "x should be unchanged, found {}", res.z);
  KB_ASSERT(v0.w == 2, "x should be unchanged, found {}", res.w);

  v0.normalize();
  KB_ASSERT(v0.x == 0.5, "x normal should be 1");
  KB_ASSERT(v0.y == 0.5, "y normal should be 1");
  KB_ASSERT(v0.z == 0.5, "z normal should be 1");
  KB_ASSERT(v0.w == 0.5, "w normal should be 1");
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char ** argv) -> int {
  test_vec4_add();
  test_vec4_mul();
  test_vec4_sub();
  test_vec4_div();
  test_vec4_dot();
  test_vec4_magnitude();
  test_vec4_normals();

  return 0;
}