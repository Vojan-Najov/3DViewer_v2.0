TARGET = 3DViewer-v2.0
DIST_NAME = 3DViewer-2.0

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
  CXX=clang++
else
  CXX=g++
endif

CP = cp -rf
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
TARGZ = tar -czvf

DIR_BUILD = build
DIR_LIBVIEWER = libviewer
DIR_APPVIEWER = appviewer
DIR_GIFLIB = appviewer/gifLib
DIR_GIFLIB_SUB = appviewer/gifLib/giflib

ifeq (${PREFIX},)
  PREFIX := ~
endif

all: build

build:  clean
	CMPLTR=${CXX} make -C ${DIR_LIBVIEWER} re
	${MKDIR} ${DIR_BUILD} && ${MKDIR} ${DIR_BUILD}/giflib
	cd ${DIR_BUILD}/giflib && \
        cmake -DCMAKE_CXX_COMPILER=${CXX} ../../${DIR_GIFLIB} && \
        cmake --build .
	cd ${DIR_BUILD} && \
	      cmake -DCMAKE_CXX_COMPILER=${CXX} ../${DIR_APPVIEWER} && \
        cmake --build .

install: build
	install -d ${DESTDIR}${PREFIX}
	install -m 755 $(shell find build -name 3DViewer-v2.0) \
	  ${DESTDIR}${PREFIX}/${TARGET}

tests:
	make CMPLTR=g++ -C ${DIR_LIBVIEWER} test

uninstall:
	${RM} ${DESTDIR}${PREFIX}/${TARGET}

dvi: docs/3DViewer.texi
	texi2dvi $<
	${RM} 3DViewer.aux 3DViewer.cp 3DViewer.log 3DViewer.toc 3DViewer.cps
	dvipdfmx 3DViewer.dvi

dist:
	${MKDIR} ${DIST_NAME}
	${MKDIR} ${DIST_NAME}/${DIR_LIBVIEWER}
	${MKDIR} ${DIST_NAME}/${DIR_APPVIEWER}
	${MKDIR} ${DIST_NAME}/${DIR_GIFLIB}
	${MKDIR} ${DIST_NAME}/${DIR_GIFLIB_SUB}
	${CP} Makefile ${DIST_NAME}
	${CP} docs ${DIST_NAME}
	${CP} ${DIR_LIBVIEWER}/*.cc ${DIST_NAME}/${DIR_LIBVIEWER}
	${CP} ${DIR_LIBVIEWER}/*.h ${DIST_NAME}/${DIR_LIBVIEWER}
	${CP} ${DIR_LIBVIEWER}/tests ${DIST_NAME}/${DIR_LIBVIEWER}
	${CP} ${DIR_LIBVIEWER}/Makefile ${DIST_NAME}/${DIR_LIBVIEWER}
	${CP} ${DIR_APPVIEWER}/*.cc ${DIST_NAME}/${DIR_APPVIEWER}
	${CP} ${DIR_APPVIEWER}/*.h ${DIST_NAME}/${DIR_APPVIEWER}
	${CP} ${DIR_APPVIEWER}/*.ui ${DIST_NAME}/${DIR_APPVIEWER}
	${CP} ${DIR_APPVIEWER}/CMakeLists.txt ${DIST_NAME}/${DIR_APPVIEWER}
	${CP} ${DIR_GIFLIB}/CMakeLists.txt ${DIST_NAME}/${DIR_GIFLIB}
	${CP} ${DIR_GIFLIB}/*.cpp ${DIST_NAME}/${DIR_GIFLIB}
	${CP} ${DIR_GIFLIB}/*.h ${DIST_NAME}/${DIR_GIFLIB}
	${CP} ${DIR_GIFLIB_SUB}/*.c ${DIST_NAME}/${DIR_GIFLIB_SUB}
	${CP} ${DIR_GIFLIB_SUB}/*.h ${DIST_NAME}/${DIR_GIFLIB_SUB}
	${TARGZ} ${DIST_NAME}.tar.gz ${DIST_NAME}
	${RMDIR} ${DIST_NAME}

clean:
	${RMDIR} build
	make -sC ${DIR_LIBVIEWER} clean
	${RMDIR} ${DIST_NAME}
	${RM} 3DViewer.dvi 3DViewer.pdf
 
format:
	make -C ${DIR_LIBVIEWER} format
	${CP} ../materials/linters/.clang-format .
	clang-format -i ${DIR_APPVIEWER}/*.h ${DIR_APPVIEWER}/*.cc
	clang-format -i ${DIR_GIFLIB}/*.h ${DIR_GIFLIB}/*.cpp
	clang-format -i ${DIR_GIFLIB_SUB}/*.h ${DIR_GIFLIB_SUB}/*.c
	${RM} .clang-format

.PHONY: all clean install uninstall dvi dist tests format
