#include <gtest/gtest.h>

#include <iostream>

#include "object.h"
#include "transform_matrix_builder.h"

class ObjectTest : public ::testing::Test {
 protected:
  void SetUp(void) override {
    std::istringstream iss{
        "v 2 1 -1\nv 2 1 +1\n"
        "v 0 1 +1\nv 0 1 -1\n"
        "v 2 -1 -1\nv 2 -1 1\n"
        "v 0 -1 1\nv 0 -1 -1\n"
        "f 1 2 3 4\nf 5 6 7 8\n"
        "f 1 2 6 5\nf 2 3 7 8\n"
        "f 3 4 8 7\nf 4 1 5 8\n"};
    while (iss) {
      std::string token;
      iss >> std::ws >> token;
      if (token == "v") {
        s21::Vertex<float> v;
        iss >> v;
        obj.PushBack(std::move(v));
      } else if (token == "f") {
        s21::Face<int> f;
        iss >> f;
        obj.PushBack(f);
      } else {
        break;
      }
    }
    obj.PrepareToRendering();
  }

  s21::Object<float, int> obj;
};

TEST_F(ObjectTest, test01) {
  EXPECT_EQ(obj.VerticesNumber(), 8);
  EXPECT_EQ(obj.FacesNumber(), 6);
  EXPECT_EQ(obj.EdgesNumber(), 24);
  EXPECT_EQ(obj.Centre(), s21::Vertex<float>(1, 0, 0, 1));
  EXPECT_NEAR(obj.Dimension(), std::sqrt(3.0), 1.0e-6);
  obj.Transform(s21::TransformMatrixBuilder<float>::Move(1, 2, 3));
  EXPECT_EQ(obj.Centre(), s21::Vertex<float>(2, 2, 3, 1));
  EXPECT_NEAR(obj.Dimension(), std::sqrt(3.0), 1.0e-6);
}
