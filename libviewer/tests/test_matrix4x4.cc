#include <gtest/gtest.h>

#include "matrix4x4.h"

class Matrix4x4Test : public testing::Test {};

TEST_F(Matrix4x4Test, Constructor) {
  s21::Matrix4x4<float> m = {{1.0f, 2.0f, 3.0f, 4.0f},
                             {5.0f, 6.0f, 7.0f, 8.0f},
                             {9.0f, 10.0f, 11.0f, 12.0f},
                             {13.0f, 14.0f, 15.0f, 16.0f}};
  float num = 1.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), num);
      num += 1.0f;
    }
  }
}

TEST_F(Matrix4x4Test, CopyConstructor) {
  s21::Matrix4x4<float> mm = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m{mm};

  float num = 1.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), num);
      num += 1.0f;
    }
  }
}

TEST_F(Matrix4x4Test, CopyAssign) {
  s21::Matrix4x4<float> mm = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m{};

  m = mm;
  float num = 1.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), num);
      num += 1.0f;
    }
  }
}

TEST_F(Matrix4x4Test, OperatorBrackets) {
  s21::Matrix4x4<float> mm = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m{};

  m = mm;
  float num = -1.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m(i, j) *= -1;
      EXPECT_EQ(m(i, j), num);
      num -= 1.0f;
    }
  }
}

TEST_F(Matrix4x4Test, OperatrMultScalar) {
  s21::Matrix4x4<float> mm = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m = mm * 10;
  float num = 10.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), num);
      num += 10.0f;
    }
  }
}

TEST_F(Matrix4x4Test, OperatrMultAssignScalar) {
  s21::Matrix4x4<float> m = {{1.0f, 2.0f, 3.0f, 4.0f},
                             {5.0f, 6.0f, 7.0f, 8.0f},
                             {9.0f, 10.0f, 11.0f, 12.0f},
                             {13.0f, 14.0f, 15.0f, 16.0f}};
  m *= 10.0;
  float num = 10.0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), num);
      num += 10.0f;
    }
  }
}

/*
538 650 762 874
612 740 868 996
686 830 974 1118
760 920 1080 1240
*/
/*
  250 260 270 280
  618 644 670 696
  986 1028 1070 1112
  1354 1412 1470 1528
*/

TEST_F(Matrix4x4Test, OperatrMultMatrix) {
  s21::Matrix4x4<float> m1 = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m2 = {{17.0f, 18.0f, 19.0f, 20.0f},
                              {21.0f, 22.0f, 23.0f, 24.0f},
                              {25.0f, 26.0f, 27.0f, 28.0f},
                              {29.0f, 30.0f, 31.0f, 32.0f}};
  s21::Matrix4x4<float> m = {{250.0f, 260.0f, 270.0f, 280.0f},
                             {618.0f, 644.0f, 670.0f, 696.0f},
                             {986.0f, 1028.0f, 1070.0f, 1112.0f},
                             {1354.0f, 1412.0f, 1470.0f, 1528.0f}};

  s21::Matrix4x4<float> res = m1 * m2;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(res(i, j), m(i, j));
    }
  }
}

TEST_F(Matrix4x4Test, OperatrMultAssignMatrix) {
  s21::Matrix4x4<float> m1 = {{1.0f, 2.0f, 3.0f, 4.0f},
                              {5.0f, 6.0f, 7.0f, 8.0f},
                              {9.0f, 10.0f, 11.0f, 12.0f},
                              {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Matrix4x4<float> m2 = {{17.0f, 18.0f, 19.0f, 20.0f},
                              {21.0f, 22.0f, 23.0f, 24.0f},
                              {25.0f, 26.0f, 27.0f, 28.0f},
                              {29.0f, 30.0f, 31.0f, 32.0f}};
  s21::Matrix4x4<float> m = {{250.0f, 260.0f, 270.0f, 280.0f},
                             {618.0f, 644.0f, 670.0f, 696.0f},
                             {986.0f, 1028.0f, 1070.0f, 1112.0f},
                             {1354.0f, 1412.0f, 1470.0f, 1528.0f}};

  m1 *= m2;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m1(i, j), m(i, j));
    }
  }
}

TEST_F(Matrix4x4Test, OperatrMultVector) {
  s21::Matrix4x4<float> m = {{1.0f, 2.0f, 3.0f, 4.0f},
                             {5.0f, 6.0f, 7.0f, 8.0f},
                             {9.0f, 10.0f, 11.0f, 12.0f},
                             {13.0f, 14.0f, 15.0f, 16.0f}};
  s21::Vec4<float> v = {17, 18, 19, 20};
  s21::Vec4<float> res = {190, 486, 782, 1078};
  s21::Vec4<float> vv = m * v;

  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(vv[i], res[i]);
  }
}
