#ifndef LIBVIEWER_SCENE_SETTINGS_H_
#define LIBVIEWER_SCENE_SETTINGS_H_

#ifndef VIEWER_SETTINGS_PATHNAME
#define VIEWER_SETTINGS_PATHNAME ".3DViewer.conf"
#endif

#include <iostream>
namespace s21 {

enum class ProjectionType : std::size_t { kParallel = 0, kCentral = 1 };

enum class LineType : std::size_t { kSolid = 0, kDashed = 1 };

enum class VertexType : std::size_t { kNone = 0, kCircle = 1, kSquare = 2 };

class SceneSettings {
 private:
  static SceneSettings *instance;

 protected:
  SceneSettings();
  SceneSettings(SceneSettings &&other) = delete;
  SceneSettings &operator=(SceneSettings &&other) = delete;
  SceneSettings(const SceneSettings &other) = delete;
  SceneSettings &operator=(const SceneSettings &other) = delete;
  ~SceneSettings(void) = default;

 public:
  static SceneSettings &GetInstance(void);
  static void DestroyInstance(void);

 public:
  enum ProjectionType GetProjectionType(void) const;
  enum LineType GetLineType(void) const;
  enum VertexType GetVertexType(void) const;
  float GetLineSize(void) const;
  float GetVertexSize(void) const;
  void GetLineColor(float &red, float &green, float &blue, float &alpha) const;
  void GetVertexColor(float &red, float &green, float &blue,
                      float &alpha) const;
  void GetBackgroundColor(float &red, float &green, float &blue,
                          float &alpha) const;

 public:
  void SetProjectionType(enum ProjectionType type);
  void SetLineType(enum LineType type);
  void SetVertexType(enum VertexType type);
  bool SetLineSize(float size);
  bool SetVertexSize(float size);
  bool SetLineColor(float red, float green, float blue, float alpha);
  bool SetVertexColor(float red, float green, float blue, float alpha);
  bool SetBackgroundColor(float red, float green, float blue, float alpha);

 private:
  enum ProjectionType projection_type_;
  enum LineType line_type_;
  enum VertexType vertex_type_;
  float line_size_;
  float vertex_size_;
  float line_color_[4];
  float vertex_color_[4];
  float background_color_[4];
};

}  // namespace s21

#endif  // LIBVIEWER_SCENE_SETTINGS_H_
