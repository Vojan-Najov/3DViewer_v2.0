TARGET = 3DViewer-v2.0
DIST_NAME = 3DViewer-2.0

CXX = g++
CP = cp -rf
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
TARGZ = tar -czvf

DIR_LIBVIEWER = libviewer
DIR_APPVIEWER = appviewer

ifeq (${PREFIX},)
  PREFIX := ~
endif

all:
	make -sC ${DIR_LIBVIEWER} all
	cd ${DIR_APPVIEWER} && cmake -DCMAKE_CXX_COMPILER=g++ . && cmake --build .

install: all
	install -d ${DESTDIR}${PREFIX}
	install -m 755 ${DIR_APPVIEWER}/smartcalc.app/Contents/*/smartcalc \
                   ${DESTDIR}${PREFIX}/${TARGET}

tests:
	make -C ${DIR_LIBVIEWER} test

uninstall:
	${RM} ${DESTDIR}${PREFIX}/${TARGET}

dvi: docs/smartcalc.texi
	texi2dvi $<
	${RM} smartcalc.aux smartcalc.cp smartcalc.log smartcalc.toc smartcalc.cps
	dvipdfmx ./smartcalc.dvi

dist:
	${MKDIR} ${DIST_NAME}
	${MKDIR} ${DIST_NAME}/${DIR_LIBVIEWER}
	${MKDIR} ${DIST_NAME}/${DIR_APPVIEWER}
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
	${TARGZ} ${DIST_NAME}.tar.gz ${DIST_NAME}
	${RMDIR} ${DIST_NAME}


clean:
	make -sC ${DIR_LIBVIEWER} clean
	${RM} ${DIR_APPVIEWER}/CMakeCache.txt 
	${RMDIR} ${DIR_APPVIEWER}/CMakeFiles
	${RM} ${DIR_APPVIEWER}/Makefile
	${RM} ${DIR_APPVIEWER}/cmake_install.cmake
	#${RMDIR} ${DIR_APPVIEWER}/smartcalc.app
	#${RMDIR} ${DIR_APPVIEWER}/smartcalc_autogen
	${RMDIR} ${DIST_NAME}
	#${RM} smartcalc.dvi smartcalc.pdf
 
format:
	make -C ${DIR_LIBVIEWER} format
	${CP} linters/.clang-format .
	clang-format -i ${DIR_APPVIEWER}/*.h ${DIR_APPVIEWER}/*.cc
	${RM} .clang-format

.PHONY: all clean install uninstall dvi dist tests format
