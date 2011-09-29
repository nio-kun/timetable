#-------------------------------------------------
#
# Project created by QtCreator 2011-09-26T12:04:48
#
#-------------------------------------------------

QT       += core gui sql

TARGET = timetable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authorization.cpp \
    settings.cpp \
    order_details.cpp \
    places.cpp \
    services.cpp \
    users.cpp

HEADERS  += mainwindow.h \
    authorization.h \
    settings.h \
    order_details.h \
    places.h \
    services.h \
    users.h

FORMS    += mainwindow.ui \
    settings.ui \
    order_details.ui \
    places.ui \
    services.ui \
    users.ui \
    authorization.ui
