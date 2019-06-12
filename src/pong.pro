#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T17:29:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pong
TEMPLATE = app
QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    ball.cpp \
    game.cpp \
    paddle.cpp \
    gameobject.cpp \
    logic.cpp \
    gameview.cpp \
    line.cpp \
    wall.cpp \
    player.cpp \
    ballcontactlistener.cpp

HEADERS  += \
    ball.h \
    game.h \
    paddle.h \
    gameobject.h \
    logic.h \
    gameview.h \
    line.h \
    wall.h \
    player.h \
    constants.h \
    ballcontactlistener.h \
    nn.h

FORMS    += mainwindow.ui

# Include LibTorch
QMAKE_RPATHDIR += $$PWD/../libtorch/lib
LIBS += -L$$PWD/../libtorch/lib -ltorch -lc10 -lcaffe2 -l:libgomp-8bba0e50.so.1
#LIBS += -L$$PWD/../libtorch/lib -ltorch -lc10 -lc10d -lnnpack -lcaffe2 -lcaffe2_detectron_ops -lcaffe2_module_test_dynamic -l:libgomp-8bba0e50.so.1
INCLUDEPATH += $$PWD/../libtorch/include/torch/csrc/api/include
DEPENDPATH += $$PWD/../libtorch/include/torch/csrc/api/include
INCLUDEPATH += $$PWD/../libtorch/include
DEPENDPATH += $$PWD/../libtorch/include

# Include Box2D
LIBS += -L$$PWD/../Box2D/Box2D/Build/gmake/bin/Release/ -lBox2D
INCLUDEPATH += $$PWD/../Box2D/Box2D
DEPENDPATH += $$PWD/../Box2D/Box2D
PRE_TARGETDEPS += $$PWD/../Box2D/Box2D/Build/gmake/bin/Release/libBox2D.a
