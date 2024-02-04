#include <gtest/gtest.h>

#include "file_reader_obj.h"

class VFObjFileReaderTest : public testing::Test {};

TEST_F(VFObjFileReaderTest, test01) {
  s21::VFObjFileReader<float, int> reader("tests/woman.obj");

  s21::Scene<float, int> sc;
  reader.Read(sc);
  const s21::Object<float, int> &wf = sc.GetObject();

  EXPECT_EQ(wf.VerticesNumber(), 1138);
  EXPECT_EQ(wf.FacesNumber(), 1136);

  s21::Vertex<float> camera = sc.GetCamera();
  float focal_ro = sc.GetCameraFocalRo();
  EXPECT_NE(camera, s21::Vertex<float>(0, 0, 0, 1));
  EXPECT_NE(focal_ro, 0);
}
