#include <iostream>
#include <gtest/gtest.h>

#include "vertex.h"

class VertexTest : public testing::Test {};

TEST_F(VertexTest, DefaultConstructor) {
	s21::Vertex<float> v{};
	EXPECT_EQ(v.x(), 0.0);
	EXPECT_EQ(v.y(), 0.0);
	EXPECT_EQ(v.z(), 0.0);
	EXPECT_EQ(v.w(), 1.0);
}

TEST_F(VertexTest, Constructor) {
	s21::Vertex<float> v1{1.0, 2.0, 3.0};
	EXPECT_EQ(v1.x(), 1.0);
	EXPECT_EQ(v1.y(), 2.0);
	EXPECT_EQ(v1.z(), 3.0);
	EXPECT_EQ(v1.w(), 1.0);

	s21::Vertex<float> v2{1.0, 2.0, 3.0, 4.0};
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

TEST_F(VertexTest, OperatorSquareBrackets) {
	s21::Vertex<float> v{1.0, 2.0, 3.0};
	
	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 2.0);
	EXPECT_EQ(v[2], 3.0);
	EXPECT_EQ(v[3], 1.0);

	v[0] = 10;
	v[1] = 20;
	v[2] = 30;
	v[3] = 40;
	EXPECT_EQ(v[0], 10.0);
	EXPECT_EQ(v[1], 20.0);
	EXPECT_EQ(v[2], 30.0);
	EXPECT_EQ(v[3], 40.0);
}

TEST_F(VertexTest, OperatorMult) {
	s21::Vertex<float> v{1.0, 2.0, 3.0};
	s21::Vertex<float> vt = v * 4;

	EXPECT_EQ(vt[0], 4.0);
	EXPECT_EQ(vt[1], 8.0);
	EXPECT_EQ(vt[2], 12.0);
	EXPECT_EQ(vt[3], 1.0);
}

TEST_F(VertexTest, FunctionMult) {
	s21::Vertex<float> v{1.0, 2.0, 3.0};
	s21::Vertex<float> vt = 4.f * v;

	EXPECT_EQ(vt[0], 4.0);
	EXPECT_EQ(vt[1], 8.0);
	EXPECT_EQ(vt[2], 12.0);
	EXPECT_EQ(vt[3], 1.0);
}

TEST_F(VertexTest, OperatorMultAssign) {
	s21::Vertex<float> v{1.0, 2.0, 3.0};

	v *= 4;
	EXPECT_EQ(v[0], 4.0);
	EXPECT_EQ(v[1], 8.0);
	EXPECT_EQ(v[2], 12.0);
	EXPECT_EQ(v[3], 1.0);
}

TEST_F(VertexTest, Input01) {
	std::istringstream iss{"v 1 2 3"};
	s21::Vertex<float> v;
	iss >> v;

	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 2.0);
	EXPECT_EQ(v[2], 3.0);
	EXPECT_EQ(v[3], 1.0);
}

TEST_F(VertexTest, Input02) {
	std::istringstream iss{"v 1 2 3 1"};
	s21::Vertex<float> v;
	iss >> v;

	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 2.0);
	EXPECT_EQ(v[2], 3.0);
	EXPECT_EQ(v[3], 1.0);
}
