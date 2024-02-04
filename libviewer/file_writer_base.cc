#include "file_writer_base.h"

#include <fstream>

namespace s21 {

FileWriterBase::FileWriterBase(const char *pathname) {
  std::setlocale(LC_ALL, "C");
  file_.open(pathname);
}

FileWriterBase::~FileWriterBase(void) { file_.close(); }

bool FileWriterBase::Fail(void) const { return file_.fail(); }

}  // namespace s21
