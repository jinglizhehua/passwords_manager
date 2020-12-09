QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    dialog_add_data.cpp \
    dialog_change_password.cpp \
    dialog_login.cpp \
    main.cpp \
    mainwindow.cpp \
    userdatas.cpp

HEADERS += \
    database.h \
    dialog_add_data.h \
    dialog_change_password.h \
    dialog_login.h \
    mainwindow.h \
    userdatas.h

FORMS += \
    dialog_add_data.ui \
    dialog_change_password.ui \
    dialog_login.ui \
    mainwindow.ui

TRANSLATIONS += \
    passwords_manager_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    users.db

RC_ICONS = password.ico
