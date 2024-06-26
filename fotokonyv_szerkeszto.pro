QT       += core gui svg printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customview.cpp \
    elrendezesvalaszto.cpp \
    exportwindow.cpp \
    kepvalaszto.cpp \
    keretvalaszto.cpp \
    kimenet.cpp \
    main.cpp \
    mainwindow.cpp \
    abra.cpp \
    belyeg.cpp \
    elem.cpp \
    elrendezes.cpp \
    keret.cpp \
    minta.cpp \
    oldal.cpp \
    projekt.cpp \
    stilus.cpp \
    szoveg.cpp \
    ujprojekt.cpp

HEADERS += \
    customview.h \
    elrendezesvalaszto.h \
    exportwindow.h \
    kepvalaszto.h \
    keretvalaszto.h \
    kimenet.h \
    mainwindow.h \
    abra.h \
    belyeg.h \
    elem.h \
    elrendezes.h \
    keret.h \
    minta.h \
    oldal.h \
    projekt.h \
    stilus.h \
    szoveg.h \
    ujprojekt.h

FORMS += \
    elrendezesvalaszto.ui \
    exportwindow.ui \
    kepvalaszto.ui \
    keretvalaszto.ui \
    mainwindow.ui \
    ujprojekt.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
