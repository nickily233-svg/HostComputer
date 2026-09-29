QT += core gui widgets serialport printsupport opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/ringbuffer.cpp \
    src/drivers/simdevice.cpp \
    src/main.cpp \
    src/ui/common_widgets.cpp \
    src/ui/daq_page.cpp \
    src/ui/galvo_page.cpp \
    src/ui/mainwindow.cpp \
    third_party/qcustomplot.cpp \
    ui_utils/ui_utils.cpp

HEADERS += \
    src/core/ringbuffer.h \
    src/drivers/idevice.h \
    src/drivers/simdevice.h \
    src/ui/common_widgets.h \
    src/ui/daq_page.h \
    src/ui/galvo_page.h \
    src/ui/mainwindow.h \
    third_party/qcustomplot.h \
    ui_utils/ui_utils.h

FORMS +=

# Default rules for deployment.
DEFINES += QCUSTOMPLOT_USE_OPENGL
LIBS += -lopengl32 -lglu32

QMAKE_PROJECT_DEPTH = 0
QMAKE_CXXFLAGS += /utf-8

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
