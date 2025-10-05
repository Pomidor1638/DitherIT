QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bayermatrix.cpp \
    dither_item.cpp \
    ditherlistwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    ordered.cpp \
    palletedialog.cpp \
    random.cpp

HEADERS += \
    IDither.h \
    dither_item.h \
    ditherlistwidget.h \
    mainwindow.h \
    orderedDithering.h \
    palletedialog.h \
    random.h

FORMS += \
    mainwindow.ui \
    palletedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    style.qss
