# ⚖️ Simple Weighing and Sorting Device

### 基于 STM32F103 的智能称重分拣系统 | STM32-Based Intelligent Weighing & Sorting System

> 一个基于 **STM32F103C8T6**、**HX711** 和 **OLED** 的自动称重分拣系统。
> An automatic weighing and sorting system based on **STM32F103C8T6**, **HX711**, and **OLED**.

---

## 📖 项目简介 | Project Overview

### 中文

本项目基于 STM32F103C8T6 微控制器设计，实现了一个智能称重分拣系统。系统利用 HX711 高精度称重模块采集重量数据，通过数字滤波提高测量稳定性，并在 OLED 屏幕上实时显示重量及统计信息。根据预设重量阈值，控制电机自动完成物品分拣。

该项目适合作为：

* STM32 嵌入式开发课程设计
* 自动控制课程实验
* 智能制造入门项目
* HX711 称重系统学习案例

---

### English

This project implements an intelligent weighing and sorting system based on the STM32F103C8T6 microcontroller. Weight data is collected using an HX711 load cell amplifier, filtered for improved stability, displayed on an OLED screen, and automatically classified by controlling a motor according to a preset weight threshold.

Suitable for:

* STM32 Embedded Development
* Automatic Control Projects
* Smart Manufacturing Demonstrations
* HX711 Learning Project

---

# ✨ 功能特点 | Features

* ✅ 实时重量采集（Real-time Weight Measurement）
* ✅ HX711 高精度称重（HX711 Load Cell Acquisition）
* ✅ OLED 实时数据显示（OLED Display）
* ✅ 去皮/校准功能（Tare Calibration）
* ✅ 中值滤波 + 均值滤波（Median & Average Filtering）
* ✅ 自动重量判定（Automatic Weight Classification）
* ✅ 电机自动分拣（Automatic Motor Sorting）
* ✅ 合格/不合格数量统计（Qualified/Unqualified Counter）

---

# 🛠 硬件平台 | Hardware

| 模块            | Hardware               |
| ------------- | ---------------------- |
| MCU           | STM32F103C8T6          |
| Weight Sensor | Load Cell              |
| ADC           | HX711                  |
| Display       | OLED (I2C)             |
| Actuator      | DC Motor / Servo Motor |
| Power         | 5V                     |

---

# 📂 项目结构 | Project Structure

```text
STM32f103c8t6/
│
├── Hardware/          # Hardware drivers
│   ├── HX711/
│   ├── OLED/
│   ├── Motor/
│   ├── Key/
│   └── Filter/
│
├── Library/           # STM32 Standard Peripheral Library
├── Start/             # Startup files
├── System/            # System drivers
├── User/              # Application
├── Objects/           # Build output
└── Project.uvprojx    # Keil MDK Project
```

---

# ⚙️ 软件环境 | Software Environment

| 软件       | Version                           |
| -------- | --------------------------------- |
| Keil MDK | V5.x                              |
| Language | C                                 |
| Library  | STM32 Standard Peripheral Library |

---

# 🚀 系统工作流程 | Workflow

```text
Start
   │
   ▼
Initialize MCU
   │
   ▼
HX711 Weight Acquisition
   │
   ▼
Digital Filtering
   │
   ▼
OLED Display
   │
   ▼
Compare with Threshold
   │
   ▼
Motor Sorting
   │
   ▼
Update Statistics
```

---

# ⚖️ 分拣逻辑 | Sorting Logic

系统默认重量阈值约为 **47 g**。

* 小于阈值 → 合格（Qualified）
* 大于阈值 → 不合格（Unqualified）

可根据需求修改程序中的阈值参数。

---

# 📺 OLED 显示内容 | OLED Display

```text
      称重分拣

重量：45.6 g

合格：12
不合格：3
```

实时显示：

* 当前重量
* 合格数量
* 不合格数量

---

# 📷 项目展示 | Demonstration

建议在此处添加：

```
docs/images/device.jpg
docs/images/hardware.jpg
docs/images/demo.gif
```

GitHub README 将自动显示图片。

---

# 🔧 编译与下载 | Build & Flash

## 编译

使用 **Keil MDK5** 打开：

```
Project.uvprojx
```

点击 **Build** 编译工程。

---

## 下载

下载到 STM32F103C8T6 开发板即可运行。

支持：

* ST-Link
* J-Link
* CMSIS-DAP

---

# 📚 学习内容 | Learning Topics

本项目涉及：

* STM32 外设开发
* GPIO
* 定时器
* I2C
* HX711 驱动
* OLED 驱动
* 电机控制
* 数字滤波
* 嵌入式系统设计

---

# 🤝 Contributing

欢迎提交：

* Issue
* Pull Request
* 功能优化建议
* Bug 修复

Contributions are welcome!

---

# 📄 License

This project is released for educational purposes.

If you use this project in your coursework or research, please consider giving appropriate credit.

---

# 👤 Author

**GitHub**

https://github.com/cdhnprot-lgtm

---

⭐ If this project helps you, please consider giving it a **Star**!
