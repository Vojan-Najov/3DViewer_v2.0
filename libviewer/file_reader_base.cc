#include "file_reader_base.h"

#include <clocale>
#include <fstream>

namespace s21 {

FileReaderBase::FileReaderBase(const char *pathname) {
  std::setlocale(LC_ALL, "C");
  file_.open(pathname);
}

FileReaderBase::~FileReaderBase(void) { file_.close(); }

bool FileReaderBase::Fail(void) const { return file_.fail(); }

}  // namespace s21
