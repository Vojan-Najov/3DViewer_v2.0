#ifndef LIBVIEWER_SCENE_SETTINGS_H_
#define LIBVIEWER_SCENE_SETTINGS_H_

namespace s21 {

enum class ProjectionType {
  kParallel,
  kCentral
};

enum class LineType {
  kSolid,
  kDashed
};

enum class VertexType {
  kNone,
  kCircle,
  kSquare
};

class SceneSettings {

 private:
  static SceneSettings *instance;

 protected:
  SceneSettings();
  SceneSettings(const SceneSettings &other) = delete;
  SceneSettings(SceneSettings &&other) = delete;
  SceneSettings &operator=(const SceneSettings &other) = delete;
  SceneSettings &operator=(SceneSettings &&other) = delete;
 public:
  ~SceneSettings(void);

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
  void GetVertexColor(float &red, float &green, float &blue, float &alpha) const;
  void GetBackgroundColor(float &red, float &green, float &blue, float &alpha) const;

 public:
  void SetProjectionType(enum ProjectionType type);
  void SetLineType(enum LineType type);
  void SetVertexType(enum VertexType type) ;
  bool SetLineSize(float size) ;
  bool SetVertexSize(float size) ;
  bool SetLineColor(float red, float green, float blue, float alpha) ;
  bool SetVertexColor(float red, float green, float blue, float alpha) ;
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

} // namespace s21

#endif  // LIBVIEWER_SCENE_SETTINGS_H_
