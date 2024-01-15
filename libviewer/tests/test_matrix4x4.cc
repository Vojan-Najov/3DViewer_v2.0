#include <gtest/gtest.h>

#include "matrix4x4.h"

class Matrix4x4Test : public testing::Test {};

TEST_F(Matrix4x4Test, Test1) {
    s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    m = m*m;
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            if (i == 3 && j == 3)
                EXPECT_NEAR(m(i, j), 0, 1e-7);
            else
                EXPECT_NEAR(m(i, j), 0, 1e-7);
        }
    }
}

TEST_F(Matrix4x4Test, Test2) {
    s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    m *= m;
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            if (i == 3 && j == 3)
                EXPECT_NEAR(m(i, j), 0, 1e-7);
            else
                EXPECT_NEAR(m(i, j), 0, 1e-7);
        }
    }
}

TEST_F(Matrix4x4Test, Test3) {
    s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    m(0,0) = 10;
    EXPECT_NEAR(m(0,0), 10, 1e-7);
}

TEST_F(Matrix4x4Test, Test4) {
    s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    s21::Matrix4x4<double> m2(m);
    EXPECT_NEAR(m2(0, 3), 1, 1e-7);
}

TEST_F(Matrix4x4Test, Test5) {
    s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    s21::Matrix4x4<double> m2(std::move(m));
    EXPECT_NEAR(m2(0,0), 0, 1e-7);
}

TEST_F(Matrix4x4Test, Test6) {
    const s21::Matrix4x4<double> m = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    EXPECT_NEAR(m(0,0), 0, 1e-7);
}
