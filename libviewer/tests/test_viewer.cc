#include <gtest/gtest.h>

#include "viewer.h"

class ViewerTest : public testing::Test {};

TEST_F(ViewerTest, test01) {
  s21::Viewer viewer;

  s21::ViewerOperationResult result = viewer.LoadObjFile("tests/woman.obj");
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_FALSE(result.IsFail());
}

TEST_F(ViewerTest, test02) {
  s21::Viewer viewer;

  s21::ViewerOperationResult result = viewer.LoadObjFile("tests/noexist.obj");
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_TRUE(result.IsFail());
}
