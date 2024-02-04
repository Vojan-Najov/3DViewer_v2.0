#ifndef LIBVIEWER_FILE_WRITER_BASE_H_
#define LIBVIEWER_FILE_WRITER_BASE_H_

#include <clocale>
#include <fstream>

namespace s21 {

class FileWriterBase {
 public:
  FileWriterBase(const char *pathname);

  bool Fail(void) const;

 protected:
  FileWriterBase(const FileWriterBase &other) = delete;
  FileWriterBase(FileWriterBase &&other) = delete;
  FileWriterBase &operator=(const FileWriterBase &other) = delete;
  FileWriterBase &operator=(FileWriterBase &&other) = delete;
  ~FileWriterBase(void);

 protected:
  std::ofstream file_;
};

}  // namespace s21

#endif  // LIBVIEWER_FILE_WRITER_BASE_H_
