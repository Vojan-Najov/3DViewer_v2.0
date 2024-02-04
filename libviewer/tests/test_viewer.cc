#include <gtest/gtest.h>

#include "viewer.h"

class ViewerTest : public testing::Test {};

TEST_F(ViewerTest, test01) {
  s21::Viewer viewer;

  s21::ViewerOperationResult result = viewer.LoadObjFile("tests/woman.obj");
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_FALSE(result.IsFail());
  EXPECT_EQ(viewer.GetVerticesNumber(), 1138);
  EXPECT_EQ(viewer.GetEdgesNumber(), 4544);
  EXPECT_EQ(viewer.GetFacesNumber(), 1136);

  EXPECT_TRUE(viewer.CheckScene());

  EXPECT_TRUE(viewer.MoveObject(1, 1, 1).IsSuccess());
  EXPECT_TRUE(viewer.RotateObject(1, 1, 1).IsSuccess());
  EXPECT_TRUE(viewer.ScaleObject(1, 1, 1).IsSuccess());
}

TEST_F(ViewerTest, test02) {
  s21::Viewer viewer;

  s21::ViewerOperationResult result = viewer.LoadObjFile("tests/noexist.obj");
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_TRUE(result.IsFail());

  EXPECT_EQ(viewer.GetVerticesNumber(), 0);
  EXPECT_EQ(viewer.GetEdgesNumber(), 0);
  EXPECT_EQ(viewer.GetFacesNumber(), 0);

  EXPECT_FALSE(viewer.CheckScene());
}

TEST_F(ViewerTest, test03) {
  s21::Viewer viewer;
  s21::ViewerOperationResult result =
      viewer.LoadObjFile("tests/test_affine.obj");
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_FALSE(result.IsFail());
  EXPECT_EQ(viewer.GetVerticesNumber(), 2);
  EXPECT_EQ(viewer.GetEdgesNumber(), 0);
  EXPECT_EQ(viewer.GetFacesNumber(), 0);
  EXPECT_NEAR(viewer.GetDimension(), 0.5, 1e-7);

  EXPECT_TRUE(viewer.CheckScene());

  EXPECT_TRUE(viewer.MoveObject(1, 1, 1).IsSuccess());
  EXPECT_TRUE(viewer.RotateObject(1, 1, 1).IsSuccess());
  EXPECT_TRUE(viewer.ScaleObject(1, 1, 1).IsSuccess());
}

TEST_F(ViewerTest, test04) {
  s21::Viewer viewer;

  EXPECT_TRUE(viewer.MoveObject(1, 1, 1).IsFail());
  EXPECT_TRUE(viewer.RotateObject(1, 1, 1).IsFail());
  EXPECT_TRUE(viewer.ScaleObject(1, 1, 1).IsFail());

  EXPECT_FALSE(viewer.CheckScene());

  auto res = viewer.ScaleCamera(10);
  EXPECT_TRUE(res.IsSuccess());
  res = viewer.RotateCamera(10, 10);
  EXPECT_TRUE(res.IsSuccess());
}
