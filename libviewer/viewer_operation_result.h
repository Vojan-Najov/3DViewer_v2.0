#ifndef LIBVIEWER_OPERATION_RESULT_VIEWER_OPERATION_RESULT_H_
#define LIBVIEWER_OPERATION_RESULT_VIEWER_OPERATION_RESULT_H_

#include <string>

namespace s21 {

struct ViewerOperationResult final {
  std::string errorMessage;

  bool IsSuccess(void) const { return errorMessage.empty(); }
  bool IsFail(void) const { return !errorMessage.empty(); }
};

}  // namespace s21

#endif  // LIBVIEWER_OPERATION_RESULT_VIEWER_OPERATION_RESULT_H_
