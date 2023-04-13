QT       += core gui widgets svgwidgets
CONFIG   += c++17 sdk_no_version_check

SOURCES += \
    chessboard.cpp \
    chesspiece.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    chessboard.h \
    chesspiece.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

OTHER_FILES += \
    .clang-format

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md \
    doxyfile

