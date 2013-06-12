#-------------------------------------------------
#
# Project created by QtCreator 2013-06-11T21:17:04
#
#-------------------------------------------------

QT       += core gui

TARGET = ProyectoFinalGraficacion
TEMPLATE = app
TARGET        = main
QT           += opengl widgets
DEPENDPATH   += .
INCLUDEPATH  += . /usr/include/GL
LIBS         += -L/usr/lib/ -L/usr/X11/lib -lGLEW -lGLU -lGL -lglut -lpng


SOURCES += main.cpp\
        mainwindow.cpp \
        GLWidget.cpp \
        textfile.cpp \
        glslProgram.cpp \
         xcmodel.cpp \
        loadOBJ.cpp \
        glInfo.cpp \
        museo.cpp \
        texture.cpp

HEADERS  += mainwindow.h \
            GLWidget.h \
            textfile.h \
            glslProgram.h \
            xcmodel.h \
            xcstructures.h \
            loadOBJ.h \
            glInfo.h \
            museo.h \
            texture.hpp

FORMS    += mainwindow.ui
