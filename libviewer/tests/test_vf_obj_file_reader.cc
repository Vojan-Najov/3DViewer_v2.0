#include <gtest/gtest.h>

#include "file_reader.h"

class VFObjFileReaderTest : public testing::Test {};

TEST_F(VFObjFileReaderTest, test01) {
	s21::VFObjFileReader<float> reader("tests/woman.obj");

	s21::Scene<float> *sc = reader.ReadScene();
	const s21::SceneObject<float> &wf = sc->GetObject();

	EXPECT_EQ(wf.VerticesNumber(), 1138);
}
