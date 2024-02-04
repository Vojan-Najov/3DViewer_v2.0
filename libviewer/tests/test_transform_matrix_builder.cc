#include <gtest/gtest.h>

#include "matrix4x4.h"
#include "transform_matrix_builder.h"

class TransformMatrixBuilderTest : public testing::Test {};

TEST_F(TransformMatrixBuilderTest, Test1) {
  s21::Matrix4x4<float> m =
      s21::TransformMatrixBuilder<float>::Rotation(90, 0, 0);
  EXPECT_NEAR(m(0, 0), 1, 1e-7);
  EXPECT_NEAR(m(1, 0), 0, 1e-7);
  EXPECT_NEAR(m(2, 0), 0, 1e-7);
  EXPECT_NEAR(m(3, 0), 0, 1e-7);

  EXPECT_NEAR(m(0, 1), 0, 1e-7);
  EXPECT_NEAR(m(1, 1), 0, 1e-7);
  EXPECT_NEAR(m(2, 1), 1, 1e-7);
  EXPECT_NEAR(m(3, 1), 0, 1e-7);

  EXPECT_NEAR(m(0, 2), 0, 1e-7);
  EXPECT_NEAR(m(1, 2), -1, 1e-7);
  EXPECT_NEAR(m(2, 2), 0, 1e-7);
  EXPECT_NEAR(m(3, 2), 0, 1e-7);

  EXPECT_NEAR(m(0, 3), 0, 1e-7);
  EXPECT_NEAR(m(1, 3), 0, 1e-7);
  EXPECT_NEAR(m(2, 3), 0, 1e-7);
  EXPECT_NEAR(m(3, 3), 1, 1e-7);
}

TEST_F(TransformMatrixBuilderTest, Test2) {
  s21::Matrix4x4<float> m =
      s21::TransformMatrixBuilder<float>::Rotation(0, 90, 0);
  EXPECT_NEAR(m(0, 0), 0, 1e-7);
  EXPECT_NEAR(m(1, 0), 0, 1e-7);
  EXPECT_NEAR(m(2, 0), -1, 1e-7);
  EXPECT_NEAR(m(3, 0), 0, 1e-7);

  EXPECT_NEAR(m(0, 1), 0, 1e-7);
  EXPECT_NEAR(m(1, 1), 1, 1e-7);
  EXPECT_NEAR(m(2, 1), 0, 1e-7);
  EXPECT_NEAR(m(3, 1), 0, 1e-7);

  EXPECT_NEAR(m(0, 2), 1, 1e-7);
  EXPECT_NEAR(m(1, 2), 0, 1e-7);
  EXPECT_NEAR(m(2, 2), 0, 1e-7);
  EXPECT_NEAR(m(3, 2), 0, 1e-7);

  EXPECT_NEAR(m(0, 3), 0, 1e-7);
  EXPECT_NEAR(m(1, 3), 0, 1e-7);
  EXPECT_NEAR(m(2, 3), 0, 1e-7);
  EXPECT_NEAR(m(3, 3), 1, 1e-7);
}

TEST_F(TransformMatrixBuilderTest, Test3) {
  s21::Matrix4x4<float> m =
      s21::TransformMatrixBuilder<float>::Rotation(0, 0, 90);
  EXPECT_NEAR(m(0, 0), 0, 1e-7);
  EXPECT_NEAR(m(1, 0), 1, 1e-7);
  EXPECT_NEAR(m(2, 0), 0, 1e-7);
  EXPECT_NEAR(m(3, 0), 0, 1e-7);

  EXPECT_NEAR(m(0, 1), -1, 1e-7);
  EXPECT_NEAR(m(1, 1), 0, 1e-7);
  EXPECT_NEAR(m(2, 1), 0, 1e-7);
  EXPECT_NEAR(m(3, 1), 0, 1e-7);

  EXPECT_NEAR(m(0, 2), 0, 1e-7);
  EXPECT_NEAR(m(1, 2), 0, 1e-7);
  EXPECT_NEAR(m(2, 2), 1, 1e-7);
  EXPECT_NEAR(m(3, 2), 0, 1e-7);

  EXPECT_NEAR(m(0, 3), 0, 1e-7);
  EXPECT_NEAR(m(1, 3), 0, 1e-7);
  EXPECT_NEAR(m(2, 3), 0, 1e-7);
  EXPECT_NEAR(m(3, 3), 1, 1e-7);
}

TEST_F(TransformMatrixBuilderTest, Test4) {
  s21::Matrix4x4<float> m = s21::TransformMatrixBuilder<float>::Move(2, 3, 4);
  EXPECT_NEAR(m(0, 0), 1, 1e-7);
  EXPECT_NEAR(m(1, 0), 0, 1e-7);
  EXPECT_NEAR(m(2, 0), 0, 1e-7);
  EXPECT_NEAR(m(3, 0), 0, 1e-7);

  EXPECT_NEAR(m(0, 1), 0, 1e-7);
  EXPECT_NEAR(m(1, 1), 1, 1e-7);
  EXPECT_NEAR(m(2, 1), 0, 1e-7);
  EXPECT_NEAR(m(3, 1), 0, 1e-7);

  EXPECT_NEAR(m(0, 2), 0, 1e-7);
  EXPECT_NEAR(m(1, 2), 0, 1e-7);
  EXPECT_NEAR(m(2, 2), 1, 1e-7);
  EXPECT_NEAR(m(3, 2), 0, 1e-7);

  EXPECT_NEAR(m(0, 3), 2, 1e-7);
  EXPECT_NEAR(m(1, 3), 3, 1e-7);
  EXPECT_NEAR(m(2, 3), 4, 1e-7);
  EXPECT_NEAR(m(3, 3), 1, 1e-7);
}

TEST_F(TransformMatrixBuilderTest, Test5) {
  s21::Matrix4x4<float> m = s21::TransformMatrixBuilder<float>::Scale(2, 3, 4);
  EXPECT_NEAR(m(0, 0), 2, 1e-7);
  EXPECT_NEAR(m(1, 0), 0, 1e-7);
  EXPECT_NEAR(m(2, 0), 0, 1e-7);
  EXPECT_NEAR(m(3, 0), 0, 1e-7);

  EXPECT_NEAR(m(0, 1), 0, 1e-7);
  EXPECT_NEAR(m(1, 1), 3, 1e-7);
  EXPECT_NEAR(m(2, 1), 0, 1e-7);
  EXPECT_NEAR(m(3, 1), 0, 1e-7);

  EXPECT_NEAR(m(0, 2), 0, 1e-7);
  EXPECT_NEAR(m(1, 2), 0, 1e-7);
  EXPECT_NEAR(m(2, 2), 4, 1e-7);
  EXPECT_NEAR(m(3, 2), 0, 1e-7);

  EXPECT_NEAR(m(0, 3), 0, 1e-7);
  EXPECT_NEAR(m(1, 3), 0, 1e-7);
  EXPECT_NEAR(m(2, 3), 0, 1e-7);
  EXPECT_NEAR(m(3, 3), 1, 1e-7);
}

TEST_F(TransformMatrixBuilderTest, Test6) {
  s21::Matrix4x4<float> m =
      s21::TransformMatrixBuilder<float>::Rotation(90, 90, 90);
  EXPECT_NEAR(m(0, 0), 0, 1e-6);
  EXPECT_NEAR(m(1, 0), 0, 1e-6);
  EXPECT_NEAR(m(2, 0), 1, 1e-6);
  EXPECT_NEAR(m(3, 0), 0, 1e-6);

  EXPECT_NEAR(m(0, 1), 0, 1e-6);
  EXPECT_NEAR(m(1, 1), -1, 1e-6);
  EXPECT_NEAR(m(2, 1), 0, 1e-6);
  EXPECT_NEAR(m(3, 1), 0, 1e-6);

  EXPECT_NEAR(m(0, 2), 1, 1e-6);
  EXPECT_NEAR(m(1, 2), 0, 1e-6);
  EXPECT_NEAR(m(2, 2), 0, 1e-6);
  EXPECT_NEAR(m(3, 2), 0, 1e-6);

  EXPECT_NEAR(m(0, 3), 0, 1e-6);
  EXPECT_NEAR(m(1, 3), 0, 1e-6);
  EXPECT_NEAR(m(2, 3), 0, 1e-6);
  EXPECT_NEAR(m(3, 3), 1, 1e-6);
}
