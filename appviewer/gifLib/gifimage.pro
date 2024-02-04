TARGET = QtGifImage

    QMAKE_DOCS = $$PWD / doc /
                 qtgifimage.qdocconf

                 load(qt_module)

                     CONFIG +=
    build_gifimage_lib include(qtgifimage.pri)
