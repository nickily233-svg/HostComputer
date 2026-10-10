# HostComputer

数据采集卡 / 振镜控制卡上位机软件。Qt 5.15 (qmake) + MSVC2019 64bit。

## 目录结构

```
HostComputer.pro          工程文件：源码/头文件/资源按模块分组，见文件内注释
.gitignore                构建产物、Qt Creator 本地配置不入库

src/
  main.cpp                程序入口
  mainwindow.{h,cpp}      主窗口：菜单栏 + Tab 页面

  pages/                  页面
    daq_page.*              数据采集页
    galvo_page.*            振镜控制页

  widgets/                自定义控件
    xy_control_widget.*     XY 控制面板
    centerGalvoPosPanel.*   振镜中心位置面板
    ruler_widget.*          刻度尺
    channel_selector.*      通道选择
    command_widget.*        命令面板
    data_statistics_table.* 数据统计表
    rightPanelLog.*         右侧日志面板

  dialog/                 对话框
    deviceselectdialog.*    设备选择
    adcselect.*             ADC 选择

  ui/                     通用 UI 组件（common_widgets）
  utils/                  UI 工具函数（ui_utils）

  drivers/                设备驱动层
    idevice.h               通用设备接口 IDevice（采集设备统一实现该接口）
    mock_device.*           模拟设备：无硬件时的调试/自测数据源
    xdma_driver.*           PCIe XDMA 采集卡驱动（待实现）
    udp_client.*            振镜控制卡网络通信（待实现）
    daq_worker.*            采集线程

  core/                   与界面无关的核心逻辑
    daq/DaqCsvSaver.*       采集数据 CSV 存盘
    daq/daq_data_model.*    采集数据模型（待实现）
    galvo/galvo_controller.*   振镜控制器（待实现）
    galvo/galvo_protocol.*     振镜通信协议（待实现）
    galvo/galvo_data_types.*   振镜数据类型（待实现）
    ringbuffer/ringbuffer.* 环形缓冲

third_party/              第三方库
  qcustomplot.{h,cpp}       绘图控件，列入 HEADERS 以便 moc 处理

res/                      资源
  res.qrc                   资源清单（前缀 /icons）
  NEFUIcon.ico / .png       程序图标
```

> 标“待实现”的文件目前为空占位，已在 `HostComputer.pro` 中登记，便于后续按模块补齐。
> 头文件包含规则：项目头文件统一写 `#include "src/模块/文件.h"`；第三方头文件由
> `INCLUDEPATH += $$PWD/third_party` 提供（如 `#include "qcustomplot.h"`）。

## 构建

Qt Creator 打开 `HostComputer.pro`，选择 Qt 5.15.2 msvc2019_64 套件，影子构建目录 `build/`。

命令行构建（示例）：

```bat
call "<VS>\VC\Auxiliary\Build\vcvars64.bat"
mkdir build && cd build
"D:\Qt\5.15.2\msvc2019_64\bin\qmake.exe" ..\HostComputer.pro CONFIG+=release
jom            :: 或 nmake
```

`build/` 属于本地构建产物，已被 `.gitignore` 排除，不再纳入版本管理。
