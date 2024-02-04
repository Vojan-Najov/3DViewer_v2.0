#ifndef LIBVIEWER_FILE_WRITER_SETTINGS_H_
#define LIBVIEWER_FILE_WRITER_SETTINGS_H_

#include "file_writer_base.h"

namespace s21 {

class FileWriterSettings : public FileWriterBase {
 public:
  FileWriterSettings(const char *pathname) : FileWriterBase(pathname) {}
  ~FileWriterSettings(void) = default;

 protected:
  FileWriterSettings(void) = delete;
  FileWriterSettings(const FileWriterSettings &other) = delete;
  FileWriterSettings(FileWriterSettings &&other) = delete;
  FileWriterSettings &operator=(const FileWriterSettings &other) = delete;
  FileWriterSettings &operator=(FileWriterSettings &&other) = delete;

 public:
  void Write(void);
};

}  // namespace s21

#endif  // LIBVIEWER_FILE_WRITER_SETTINGS_H_
