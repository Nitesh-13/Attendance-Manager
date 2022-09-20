QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

SOURCES += \
    attendance.cpp \
    dblogin.cpp \
    error.cpp \
    genlog.cpp \
    main.cpp \
    mainwindow.cpp \
    sheet.cpp \
    viewmyattendance.cpp

HEADERS += \
    attendance.h \
    dblogin.h \
    error.h \
    genlog.h \
    mainwindow.h \
    sheet.h \
    viewmyattendance.h

FORMS += \
    attendance.ui \
    error.ui \
    mainwindow.ui \
    sheet.ui \
    viewmyattendance.ui

VERSION = 1.3.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

RC_ICONS = icon.ico
