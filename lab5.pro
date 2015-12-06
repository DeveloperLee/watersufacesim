QT += core gui opengl

TARGET = lab5
TEMPLATE = app

win32 {
    DEFINES += GLEW_STATIC
}

INCLUDEPATH += src glm cs123_lib glew-1.10.0/include
DEPENDPATH += src glm cs123_lib glew-1.10.0/include

SOURCES += \
    src/mainwindow.cpp \
    src/main.cpp \
    src/glwidget.cpp \
    src/openglshape.cpp \
    cs123_lib/resourceloader.cpp \
    cs123_lib/errorchecker.cpp \
    glew-1.10.0/src/glew.c \
    src/Databinding.cpp \
    src/Settings.cpp

HEADERS += \
    src/mainwindow.h \
    src/glwidget.h \
    src/openglshape.h \
    cs123_lib/resourceloader.h \
    cs123_lib/errorchecker.h \
    glew-1.10.0/include/GL/glew.h \
    src/Databinding.h \
    src/Settings.h

FORMS += src/mainwindow.ui

OTHER_FILES += \
    shaders/shader.frag \
    shaders/shader.vert

RESOURCES += \
    shaders/shaders.qrc
