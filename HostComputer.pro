QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hostcomputer.cpp \
    src/core/ringbuffer.cpp \
    src/drivers/simdevice.cpp \
    src/main.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    hostcomputer.h \
    src/core/ringbuffer.h \
    src/drivers/idevice.h \
    src/drivers/simdevice.h \
    src/ui/mainwindow.h

FORMS += \
    hostcomputer.ui

# Default rules for deployment.
QMAKE_PROJECT_DEPTH = 0
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
