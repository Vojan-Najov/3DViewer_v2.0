#ifndef LIBVIEWER_FILE_READER_BASE_H_
#define LIBVIEWER_FILE_READER_BASE_H_

#include <fstream>

namespace s21 {

class FileReaderBase {
 public:
  FileReaderBase(const char *pathname);

  bool Fail(void) const;

 protected:
  FileReaderBase(const FileReaderBase &other) = delete;
  FileReaderBase(FileReaderBase &&other) = delete;
  FileReaderBase &operator=(const FileReaderBase &other) = delete;
  FileReaderBase &operator=(FileReaderBase &&other) = delete;
  ~FileReaderBase(void);

 protected:
  std::ifstream file_;
};

}  // namespace s21

#endif  // LIBVIEWER_FILE_READER_BASE_H_
