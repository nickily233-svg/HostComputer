QT += core gui widgets serialport printsupport opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/daq/ringbuffer.cpp \
    src/core/galvo/galvo_controller.cpp \
    src/core/galvo/galvo_data_types.cpp \
    src/core/galvo/galvo_protocol.cpp \
    src/core/galvo_controller.cpp \
    src/core/galvo_data_types.cpp \
    src/core/galvo_protocol.cpp \
    src/core/ringbuffer.cpp \
    src/drivers/simdevice.cpp \
    src/drivers/udp_client.cpp \
    src/drivers/xdma_driver.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pages/daq_page.cpp \
    src/pages/galvo_page.cpp \
    src/ui/common_widgets.cpp \
    src/ui/daq_page.cpp \
    src/ui/galvo_page.cpp \
    src/ui/mainwindow.cpp \
    src/utils/ui_utils.cpp \
    src/widgets/ruler_widget.cpp \
    src/widgets/xy_control_widget.cpp \
    third_party/qcustomplot.cpp \
    ui_utils/ui_utils.cpp \
    widgets/xy_control_widget.cpp

HEADERS += \
    src/core/daq/ringbuffer.h \
    src/core/galvo/galvo_controller.h \
    src/core/galvo/galvo_data_types.h \
    src/core/galvo/galvo_protocol.h \
    src/core/galvo_controller.h \
    src/core/galvo_data_types.h \
    src/core/galvo_protocol.h \
    src/core/ringbuffer.h \
    src/drivers/idevice.h \
    src/drivers/simdevice.h \
    src/drivers/udp_client.h \
    src/drivers/xdma_driver.h \
    src/mainwindow.h \
    src/pages/daq_page.h \
    src/pages/galvo_page.h \
    src/ui/common_widgets.h \
    src/ui/daq_page.h \
    src/ui/galvo_page.h \
    src/ui/mainwindow.h \
    src/utils/ui_utils.h \
    src/widgets/ruler_widget.h \
    src/widgets/xy_control_widget.h \
    third_party/qcustomplot.h \
    ui_utils/ui_utils.h \
    widgets/xy_control_widget.h

FORMS +=

# Default rules for deployment.
DEFINES += QCUSTOMPLOT_USE_OPENGL
LIBS += -lopengl32 -lglu32

QMAKE_PROJECT_DEPTH = 0
QMAKE_CXXFLAGS += /utf-8

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
