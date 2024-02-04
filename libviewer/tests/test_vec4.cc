#include <gtest/gtest.h>

#include <iostream>

#include "vec4.h"

class Vec4Test : public testing::Test {};

TEST_F(Vec4Test, DefaultConstructor) {
  s21::Vec4<float> v{};
  EXPECT_EQ(v.x(), 0.0);
  EXPECT_EQ(v.y(), 0.0);
  EXPECT_EQ(v.z(), 0.0);
  EXPECT_EQ(v.w(), 1.0);
}

TEST_F(Vec4Test, Constructor) {
  const s21::Vec4<float> v1{1.0, 2.0, 3.0};
  EXPECT_EQ(v1.x(), 1.0);
  EXPECT_EQ(v1.y(), 2.0);
  EXPECT_EQ(v1.z(), 3.0);
  EXPECT_EQ(v1.w(), 1.0);

  s21::Vec4<float> v2{1.0, 2.0, 3.0, 4.0};
  EXPECT_EQ(v2.x(), 1.0);
  EXPECT_EQ(v2.y(), 2.0);
  EXPECT_EQ(v2.z(), 3.0);
  EXPECT_EQ(v2.w(), 4.0);

  v2.x() = 10;
  v2.y() = 20;
  v2.z() = 30;
  v2.w() = 40;
  EXPECT_EQ(v2.x(), 10.0);
  EXPECT_EQ(v2.y(), 20.0);
  EXPECT_EQ(v2.z(), 30.0);
  EXPECT_EQ(v2.w(), 40.0);
}

TEST_F(Vec4Test, CopyConstructor) {
  s21::Vec4<float> v{1, 2, 3, 2};
  s21::Vec4<float> vv{v};
  EXPECT_EQ(vv.x(), 1.0);
  EXPECT_EQ(vv.y(), 2.0);
  EXPECT_EQ(vv.z(), 3.0);
  EXPECT_EQ(vv.w(), 2.0);
}

TEST_F(Vec4Test, CopyAssign) {
  s21::Vec4<float> v{1, 2, 3, 2};
  s21::Vec4<float> vv{};
  vv = v;
  EXPECT_EQ(vv.x(), 1.0);
  EXPECT_EQ(vv.y(), 2.0);
  EXPECT_EQ(vv.z(), 3.0);
  EXPECT_EQ(vv.w(), 2.0);
}

TEST_F(Vec4Test, OperatorSqureBrackets) {
  s21::Vec4<float> v{1, 2, 3, 4};
  EXPECT_EQ(v[0], 1.0);
  EXPECT_EQ(v[1], 2.0);
  EXPECT_EQ(v[2], 3.0);
  EXPECT_EQ(v[3], 4.0);
}

TEST_F(Vec4Test, OperatorPlus) {
  s21::Vec4<float> v1{1, 2, 3};
  s21::Vec4<float> v2{10, 20, 30};
  s21::Vec4<float> v = v1 + v2;

  EXPECT_EQ(v[0], 11.0);
  EXPECT_EQ(v[1], 22.0);
  EXPECT_EQ(v[2], 33.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, OperatorMinus) {
  s21::Vec4<float> v1{1, 2, 3};
  s21::Vec4<float> v2{10, 20, 30};
  s21::Vec4<float> v = v1 - v2;

  EXPECT_EQ(v[0], -9.0);
  EXPECT_EQ(v[1], -18.0);
  EXPECT_EQ(v[2], -27.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, OperatorMult) {
  s21::Vec4<float> v1{1, 2, 3};
  s21::Vec4<float> v = v1 * 10;

  EXPECT_EQ(v[0], 10.0);
  EXPECT_EQ(v[1], 20.0);
  EXPECT_EQ(v[2], 30.0);
  EXPECT_EQ(v[3], 1.0);

  v = 2.0f * v;
  EXPECT_EQ(v[0], 20.0);
  EXPECT_EQ(v[1], 40.0);
  EXPECT_EQ(v[2], 60.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, OperatorPlusAssign) {
  s21::Vec4<float> v{1, 2, 3};
  s21::Vec4<float> vv{10, 20, 30};
  v += vv;

  EXPECT_EQ(v[0], 11.0);
  EXPECT_EQ(v[1], 22.0);
  EXPECT_EQ(v[2], 33.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, OperatorMinusAssign) {
  s21::Vec4<float> v{1, 2, 3};
  s21::Vec4<float> vv{10, 20, 30};
  v -= vv;

  EXPECT_EQ(v[0], -9.0);
  EXPECT_EQ(v[1], -18.0);
  EXPECT_EQ(v[2], -27.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, OperatorMultAssign) {
  s21::Vec4<float> v{1, 2, 3};
  v *= 10;

  EXPECT_EQ(v[0], 10.0);
  EXPECT_EQ(v[1], 20.0);
  EXPECT_EQ(v[2], 30.0);
  EXPECT_EQ(v[3], 1.0);
}

TEST_F(Vec4Test, Length) {
  s21::Vec4<float> v{1, 2, 3};

  EXPECT_NEAR(v.length(), 3.7416573867739413, 1.0e-6);
}
