QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    account.cpp \
    admin.cpp \
    bankingsystem.cpp \
    checkingaccount.cpp \
    currentaccount.cpp \
    customer.cpp \
    depositaccount.cpp \
    main.cpp \
    mainwindow.cpp \
    qarzaccount.cpp \
    user.cpp

HEADERS += \
    account.h \
    admin.h \
    bankingsystem.h \
    checkingaccount.h \
    currentaccount.h \
    customer.h \
    depositaccount.h \
    linkedlist.h \
    mainwindow.h \
    qarzaccount.h \
    user.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc