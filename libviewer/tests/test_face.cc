#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "face.h"
#include "vertex.h"

class FaceTest : public ::testing::Test {};

TEST_F(FaceTest, Input01) {
  std::array<int, 5> idx = {1, 2, 3, 4, 5};
  std::istringstream iss{"f 1 2 3 4 5\n"};
  s21::Face<int> f;

  EXPECT_TRUE(f.Empty());

  iss >> f;
  EXPECT_FALSE(f.Empty());
  EXPECT_EQ(*f.Data(), 1);
  auto fit = f.Begin();
  EXPECT_EQ(f.Size(), idx.size());
  for (auto it = idx.begin(); it != idx.end(); ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(fit, f.End());
}

TEST_F(FaceTest, Input02) {
  std::array<int, 5> idx = {1, 2, 3, 4, 5};
  std::istringstream iss{
      "f 1/1 2/2 3/3 4/4 5/5 \n"
      "v 10 10 10\n"};
  s21::Face<int> f;

  iss >> f;
  auto fit = f.Begin();
  EXPECT_EQ(f.Size(), idx.size());
  for (auto it = idx.begin(); it != idx.end(); ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(fit, f.End());

  s21::Vertex<float> v;
  iss >> v;
  EXPECT_EQ(v[0], 10.0f);
  EXPECT_EQ(v[1], 10.0f);
  EXPECT_EQ(v[2], 10.0f);
  EXPECT_EQ(v[3], 1.0f);
}

TEST_F(FaceTest, Input03) {
  std::array<int, 5> idx = {1, 2, 3, 4, 5};
  std::istringstream iss{"f 1/10/100 2/20/200 3/30/300 4/40/400 5/50/500"};
  s21::Face<int> f;

  iss >> f;
  auto fit = f.Begin();
  EXPECT_EQ(f.Size(), idx.size());
  for (auto it = idx.begin(); it != idx.end(); ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(fit, f.End());
}

TEST_F(FaceTest, Input04) {
  std::array<int, 5> idx = {1, 2, 3, 4, 5};
  std::istringstream iss{"f 1//100 2/20/200	 3//300   4/40/400  5//500\n"};
  s21::Face<int> f;

  iss >> f;
  auto fit = f.Begin();
  EXPECT_EQ(f.Size(), idx.size());
  for (auto it = idx.begin(); it != idx.end(); ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(fit, f.End());
}

TEST_F(FaceTest, Input05) {
  std::array<int, 5> idx = {1, 2, 3, 4, 5};
  std::istringstream iss{
      "v 10 10 10\n"
      "f 1 2 3 4 5 \n"};
  s21::Vertex<float> v;
  s21::Face<int> f;

  iss >> v;
  EXPECT_EQ(v[0], 10.0f);
  EXPECT_EQ(v[1], 10.0f);
  EXPECT_EQ(v[2], 10.0f);
  EXPECT_EQ(v[3], 1.0f);

  iss >> f;
  auto ait = idx.begin();
  EXPECT_EQ(f.Size(), idx.size());
  for (auto it = f.Begin(); it != f.End(); ++it, ++ait) {
    EXPECT_EQ(*it, *ait);
  }
  EXPECT_EQ(ait, idx.end());
}
