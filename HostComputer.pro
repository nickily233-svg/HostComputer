QT += core gui widgets serialport printsupport opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/daq/daq_data_model.cpp \
    src/core/galvo/galvo_controller.cpp \
    src/core/galvo/galvo_data_types.cpp \
    src/core/galvo/galvo_protocol.cpp \
    src/core/ringbuffer/ringbuffer.cpp \
    src/dialog/deviceselectdialog.cpp \
    src/drivers/udp_client.cpp \
    src/drivers/xdma_driver.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pages/daq_page.cpp \
    src/pages/galvo_page.cpp \
    src/ui/common_widgets.cpp \
    src/utils/ui_utils.cpp \
    src/widgets/channel_selector.cpp \
    src/widgets/command_widget.cpp \
    src/widgets/data_statistics_table.cpp \
    src/widgets/ruler_widget.cpp \
    src/widgets/xy_control_widget.cpp \
    third_party/qcustomplot.cpp \
    src/widgets/xy_control_widget.cpp

HEADERS += \
    src/core/daq/daq_data_model.h \
    src/core/galvo/galvo_controller.h \
    src/core/galvo/galvo_data_types.h \
    src/core/galvo/galvo_protocol.h \
    src/core/galvo_controller.h \
    src/core/galvo_data_types.h \
    src/core/galvo_protocol.h \
    src/core/ringbuffer/ringbuffer.h \
    src/dialog/deviceselectdialog.h \
    src/drivers/idevice.h \
    src/drivers/udp_client.h \
    src/drivers/xdma_driver.h \
    src/mainwindow.h \
    src/pages/daq_page.h \
    src/pages/galvo_page.h \
    src/ui/common_widgets.h \
    src/utils/ui_utils.h \
    src/widgets/channel_selector.h \
    src/widgets/command_widget.h \
    src/widgets/data_statistics_table.h \
    src/widgets/ruler_widget.h \
    src/widgets/xy_control_widget.h \
    third_party/qcustomplot.h \
    src/widgets/xy_control_widget.h

FORMS +=

# Default rules for deployment.
DEFINES += QCUSTOMPLOT_USE_OPENGL
LIBS += -lopengl32 -lglu32

QMAKE_PROJECT_DEPTH = 0
QMAKE_CXXFLAGS += /utf-8

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
