#include <gtest/gtest.h>

#include "wireframe.h"

class WireframeTest : public testing::Test {};

TEST_F(WireframeTest, PushBackVertex) {
	s21::Wireframe<float> wf;

	for (float tmp = 0.0; tmp < 200; tmp += 10.0f) {
		wf.PushBack(s21::Vertex<float>{tmp, tmp + 1.f, tmp + 2.f});
	}

}
