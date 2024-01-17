#include "base_file_reader.h"

#include <fstream>

namespace s21 {

BaseFileReader::BaseFileReader(const char *pathname) { file_.open(pathname); }

BaseFileReader::~BaseFileReader(void) { file_.close(); }

bool BaseFileReader::Fail(void) const { return file_.fail(); }

}  // namespace s21
