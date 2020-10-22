#-------------------------------------------------
#
# Project created by QtCreator 2019-05-09T06:37:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BreakTimeAdmin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialoglogin.cpp \
    dialogconnsuccess.cpp \
    dialogconnfailure.cpp \
    dialogmenu.cpp \
    dialoguserregister.cpp \
    dialoginscripcion.cpp \
    dialogaltas.cpp \
    dialogaltapacks.cpp \
    dialogaltastylos.cpp \
    dialogaltaclases.cpp \
    dialoginformes.cpp \
    dialogadministracion.cpp \
    dialogfacturacion.cpp \
    dialogaltadocente.cpp \
    dialoghorasdias.cpp \
    dialogtipoactividad.cpp \
    dialogventas.cpp

HEADERS  += mainwindow.h \
    dialoglogin.h \
    dialogconnsuccess.h \
    dialogconnfailure.h \
    dialogmenu.h \
    dialoguserregister.h \
    dialoginscripcion.h \
    dialogaltas.h \
    dialogaltapacks.h \
    dialogaltastylos.h \
    dialogaltaclases.h \
    dialoginformes.h \
    dialogadministracion.h \
    dialogfacturacion.h \
    dialogaltadocente.h \
    dialoghorasdias.h \
    dialogtipoactividad.h \
    dialogventas.h

FORMS    += mainwindow.ui \
    dialoglogin.ui \
    dialogconnsuccess.ui \
    dialogconnfailure.ui \
    dialogmenu.ui \
    dialoguserregister.ui \
    dialoginscripcion.ui \
    dialogaltas.ui \
    dialogaltapacks.ui \
    dialogaltastylos.ui \
    dialogaltaclases.ui \
    dialoginformes.ui \
    dialogadministracion.ui \
    dialogfacturacion.ui \
    dialogaltadocente.ui \
    dialoghorasdias.ui \
    dialogtipoactividad.ui \
    dialogventas.ui

RESOURCES += \
    icons.qrc
