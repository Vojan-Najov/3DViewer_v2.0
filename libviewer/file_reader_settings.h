#ifndef LIBVIEWER_FILE_READER_SETTINGS_H_
#define LIBVIEWER_FILE_READER_SETTINGS_H_

#include "file_reader_base.h"

namespace s21 {

class FileReaderSettings : public FileReaderBase {
 public:
  FileReaderSettings(const char *pathname) : FileReaderBase(pathname) {}
  ~FileReaderSettings(void) = default;

 protected:
  FileReaderSettings(void) = delete;
  FileReaderSettings(const FileReaderSettings &other) = delete;
  FileReaderSettings(FileReaderSettings &&other) = delete;
  FileReaderSettings &operator=(const FileReaderSettings &other) = delete;
  FileReaderSettings &operator=(FileReaderSettings &&other) = delete;

 public:
  void Read(void);
};

}  // namespace s21

#endif  // LIBVIEWER_FILE_READER_SETTINGS_H_
