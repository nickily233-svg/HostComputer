#-------------------------------------------------------------------------------
# HostComputer — 数据采集卡 / 振镜控制卡 上位机
# 构建环境: Qt 5.15 (msvc2019_64) + qmake
#-------------------------------------------------------------------------------

QT += core gui widgets serialport printsupport opengl

CONFIG += c++17
TEMPLATE = app
TARGET = HostComputer

# 头文件搜索路径:
#   $$PWD             项目根目录 —— 源码内统一用 "src/..." 形式包含项目头文件
#   $$PWD/third_party 第三方库头文件 (qcustomplot 等)
INCLUDEPATH += $$PWD \
               $$PWD/third_party

#-------------------------------------------------------------------------------
# 应用入口与主窗口
#-------------------------------------------------------------------------------
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/mainwindow.h

#-------------------------------------------------------------------------------
# 页面 (pages)
#-------------------------------------------------------------------------------
SOURCES += \
    src/pages/daq_page.cpp \
    src/pages/galvo_page.cpp

HEADERS += \
    src/pages/daq_page.h \
    src/pages/galvo_page.h

#-------------------------------------------------------------------------------
# 自定义控件 (widgets)
#-------------------------------------------------------------------------------
SOURCES += \
    src/widgets/centerGalvoPosPanel.cpp \
    src/widgets/channel_selector.cpp \
    src/widgets/command_widget.cpp \
    src/widgets/data_statistics_table.cpp \
    src/widgets/rightPanelLog.cpp \
    src/widgets/ruler_widget.cpp \
    src/widgets/xy_control_widget.cpp

HEADERS += \
    src/widgets/centerGalvoPosPanel.h \
    src/widgets/channel_selector.h \
    src/widgets/command_widget.h \
    src/widgets/data_statistics_table.h \
    src/widgets/rightPanelLog.h \
    src/widgets/ruler_widget.h \
    src/widgets/xy_control_widget.h

#-------------------------------------------------------------------------------
# 对话框 (dialog)
#-------------------------------------------------------------------------------
SOURCES += \
    src/dialog/adcselect.cpp \
    src/dialog/deviceselectdialog.cpp

HEADERS += \
    src/dialog/adcselect.h \
    src/dialog/deviceselectdialog.h

#-------------------------------------------------------------------------------
# 通用 UI 组件与工具 (ui / utils)
#-------------------------------------------------------------------------------
SOURCES += \
    src/ui/common_widgets.cpp \
    src/utils/ui_utils.cpp

HEADERS += \
    src/ui/common_widgets.h \
    src/utils/ui_utils.h

#-------------------------------------------------------------------------------
# 设备驱动层 (drivers)
#   idevice.h     —— 通用设备接口 IDevice
#   mock_device   —— 模拟设备(开发/自测)
#   xdma_driver   —— PCIe XDMA 采集卡
#   udp_client    —— 振镜控制卡网络通信
#   daq_worker    —— 采集线程
#-------------------------------------------------------------------------------
SOURCES += \
    src/drivers/daq_worker.cpp \
    src/drivers/mock_device.cpp \
    src/drivers/udp_client.cpp \
    src/drivers/xdma_driver.cpp

HEADERS += \
    src/drivers/daq_worker.h \
    src/drivers/idevice.h \
    src/drivers/mock_device.h \
    src/drivers/udp_client.h \
    src/drivers/xdma_driver.h

#-------------------------------------------------------------------------------
# 核心层 (core): 采集数据模型与存盘 / 振镜协议 / 环形缓冲
#-------------------------------------------------------------------------------
SOURCES += \
    src/core/daq/DaqCsvSaver.cpp \
    src/core/daq/daq_data_model.cpp \
    src/core/galvo/galvo_controller.cpp \
    src/core/galvo/galvo_data_types.cpp \
    src/core/galvo/galvo_protocol.cpp \
    src/core/ringbuffer/ringbuffer.cpp

HEADERS += \
    src/core/daq/DaqCsvSaver.h \
    src/core/daq/daq_data_model.h \
    src/core/galvo/galvo_controller.h \
    src/core/galvo/galvo_data_types.h \
    src/core/galvo/galvo_protocol.h \
    src/core/ringbuffer/ringbuffer.h

#-------------------------------------------------------------------------------
# 第三方库 (third_party)
#   qcustomplot 需列入 HEADERS, 以便 moc 处理其中的 Q_OBJECT 类
#-------------------------------------------------------------------------------
SOURCES += \
    third_party/qcustomplot.cpp

HEADERS += \
    third_party/qcustomplot.h

#-------------------------------------------------------------------------------
# 资源 (res)
#-------------------------------------------------------------------------------
RESOURCES += \
    res/res.qrc

#-------------------------------------------------------------------------------
# 平台与编译选项
#-------------------------------------------------------------------------------
DEFINES += QCUSTOMPLOT_USE_OPENGL
LIBS += -lopengl32 -lglu32

QMAKE_PROJECT_DEPTH = 0
QMAKE_CXXFLAGS += /utf-8

# QMAKE_CXXFLAGS += -fsanitize=address
# QMAKE_LFLAGS += -fsanitize=address

# 部署规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
