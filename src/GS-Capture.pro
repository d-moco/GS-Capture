QT       += core gui svg charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basedialog.cpp \
    common/QtCustomStylesheet.cpp \
    common/circularbutton.cpp \
    common/clickableframe.cpp \
    common/commonstylesheet.cpp \
    common/countdownwidget.cpp \
    common/grayscaleselector.cpp \
    common/imageviewtoolwidget.cpp \
    common/maintitlebar.cpp \
    common/sigslotmgr.cpp \
    common/switchbuttoninside.cpp \
    common/titlebar.cpp \
    common/histogramwidget.cpp \
    imageeditwidget.cpp \
    imageitemwidget.cpp \
    imagemanager.cpp \
    imageview/imageview.cpp \
    imageview/photoinfo.cpp \
    imageview/toolbar.cpp \
    main.cpp \
    maindialog.cpp \
    mainwidget.cpp \
    themeset.cpp

HEADERS += \
    basedialog.h \
    common/QtCustomStylesheet.h \
    common/circularbutton.h \
    common/clickableframe.h \
    common/commonstylesheet.h \
    common/countdownwidget.h \
    common/define.h \
    common/grayscaleselector.h \
    common/histogramwidget.h \
    common/imageviewtoolwidget.h \
    common/istylesheet.h \
    common/maintitlebar.h \
    common/sigslotmgr.h \
    common/switchbuttoninside.h \
    common/titlebar.h \
    imageeditwidget.h \
    imageitemwidget.h \
    imagemanager.h \
    imageview/imageview.h \
    imageview/photoinfo.h \
    imageview/toolbar.h \
    maindialog.h \
    mainwidget.h \
    themeset.h

FORMS += \
    basedialog.ui \
    common/clickableframe.ui \
    common/countdownwidget.ui \
    imageeditwidget.ui \
    imageitemwidget.ui \
    imagemanager.ui \
    imageview/imageview.ui \
    imageview/photoinfo.ui \
    maindialog.ui \
    mainwidget.ui \
    themeset.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += common

RESOURCES += \
    img.qrc

DEFINES += "STYLES_DIR=$$PWD/styles"

TRANSLATIONS += translations/app_zh_CN.ts
