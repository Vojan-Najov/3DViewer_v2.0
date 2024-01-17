#include <gtest/gtest.h>

#include "obj_file_reader.h"

class VFObjFileReaderTest : public testing::Test {};

TEST_F(VFObjFileReaderTest, test01) {
  s21::VFObjFileReader<float, int> reader("tests/woman.obj");

  s21::Scene<float, int> *sc = reader.ReadScene();
  const s21::SceneObject<float, int> &wf = sc->GetObject();

  EXPECT_EQ(wf.VerticesNumber(), 1138);
  EXPECT_EQ(wf.FacesNumber(), 1136);
}
