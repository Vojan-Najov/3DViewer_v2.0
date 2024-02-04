TARGET = libviewer.a
TEST = test
REPORT = coverage

OS := $(shell uname -s)
ifeq ($(OS),Linux)
  OPENGL = -lGL
else
  OPENGL = -framework OpenGL
endif

ifeq (${CMPLTR},)
  CMPLTR = g++
endif

AR = ar rcs
RMDIR = rm -rf
RM = rm -f
MKDIR = mkdir -p

CXXFLAGS = -g -Wall -Wextra -Werror -std=c++17 -DGL_SILENCE_DEPRECATION
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0
TEST_LIBS = -lgtest

INCLUDE_DIR = .
SRC_DIR = .
OBJ_DIR = ${SRC_DIR}/obj
TEST_SRC_DIR = $(SRC_DIR)/tests
TEST_OBJ_DIR = $(OBJ_DIR)/tests
GCOV_DIR = ${SRC_DIR}/${REPORT}
GCOV_OBJ_DIR = ${GCOV_DIR}/objs

INCLUDE = $(wildcard ${INCLUDE_DIR}/*.h)
SRC = $(wildcard ${SRC_DIR}/*.cc)
OBJ = $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))
TEST_SRC = $(wildcard ${TEST_SRC_DIR}/*.cc)
TEST_OBJ = $(addprefix ${TEST_OBJ_DIR}/, $(notdir ${TEST_SRC:.cc=.o}))
GCOV_OBJ = $(addprefix ${GCOV_OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))
GCOV_TEST_OBJ = $(addprefix ${GCOV_OBJ_DIR}/, $(notdir ${TEST_SRC:.cc=.o}))


all: ${TARGET}

${TARGET}: ${OBJ}
	${AR} $@ $?

${TEST}: re ${TEST_OBJ}
	${CMPLTR} ${CXXFLAGS} -o $@ ${TEST_OBJ} ${TARGET} ${TEST_LIBS} ${OPENGL} -I${INCLUDE_DIR}
	./${TEST} 2>/dev/null

$(REPORT): ${GCOV_OBJ} ${GCOV_TEST_OBJ}
	@echo ${GCOV_OBJ}
	@echo ${GCOV_TEST_OBJ}
	${CMPLTR} ${GCOV_FLAGS} -o ${TEST} ${GCOV_OBJ} ${GCOV_TEST_OBJ} ${TEST_LIBS} ${OPENGL}
	./${TEST} 2>/dev/null
	gcov ${GCOV_OBJ_DIR}/*.gcno
	mv *.gcov ${GCOV_OBJ_DIR}
	#${RM} ${GCOV_OBJ_DIR}/test*
	lcov --ignore-errors mismatch -c -t "libviewer" \
	  -o ${GCOV_DIR}/report.info -d ${GCOV_OBJ_DIR}
	genhtml -o ${GCOV_DIR} ${GCOV_DIR}/report.info

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CMPLTR} ${CXXFLAGS} -I${INCLUDE_DIR} -o $@ -c $<  

${TEST_OBJ_DIR}/%.o: ${TEST_SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CMPLTR} ${CXXFLAGS} -I${INCLUDE_DIR} -o $@ -c $<

${GCOV_OBJ_DIR}/%.o: ${SRC_DIR}/%.cc
	@${MKDIR} ${@D}
	${CMPLTR} ${GCOV_FLAGS} -I${INCLUDE_DIR} -c $< -o $@

${GCOV_OBJ_DIR}/%.o: ${TEST_SRC_DIR}/%.cc
	@${MKDIR} ${@D}
	${CMPLTR} ${GCOV_FLAGS} -I${INCLUDE_DIR} -c $< -o $@

clean:
	${RMDIR} ${OBJ_DIR}
	${RMDIR} ${GCOV_DIR}
	${RMDIR} test.dSYM
	${RM} ${TARGET}
	${RM} ${TEST}

re: clean all

format:
	cp ../../materials/linters/.clang-format .
	clang-format -i ${SRC} ${INCLUDE} ${TEST_SRC}
	rm .clang-format

.PHONY: ${TEST} ${REPORT} all clean format re
