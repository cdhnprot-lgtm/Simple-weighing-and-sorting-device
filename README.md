# Simple Weighing and Sorting Device

> An automatic weighing and sorting device based on **STM32F103C8T6**.

## 📖 Project Introduction

This project implements an embedded automatic weighing and sorting system based on the STM32F103C8T6 microcontroller. The system uses an HX711 load cell amplifier to acquire weight data, performs digital filtering to improve measurement stability, displays real-time information on an OLED screen, and controls a motor to automatically sort objects according to preset weight thresholds.

The project is suitable for learning:

* STM32 embedded development
* HX711 weight acquisition
* OLED display
* Motor control
* Digital filtering algorithms
* Automatic sorting systems

---

## ✨ Features

* 📦 Real-time weight measurement
* ⚖️ HX711 high-precision load cell acquisition
* 📺 OLED real-time display
* 🔧 Tare calibration
* 📊 Median & Average filtering
* 🎯 Configurable weight threshold
* 🤖 Automatic object sorting
* 📈 Qualified / Unqualified statistics

---

## 🛠 Hardware Platform

| Hardware      | Description            |
| ------------- | ---------------------- |
| MCU           | STM32F103C8T6          |
| Weight Sensor | Load Cell              |
| ADC           | HX711                  |
| Display       | 0.96" OLED (I2C)       |
| Actuator      | DC Motor / Servo Motor |
| Power Supply  | 5V                     |

---

## 📂 Project Structure

```
STM32f103c8t6
│
├── Hardware        # Hardware drivers
│   ├── HX711
│   ├── OLED
│   ├── Motor
│   ├── Key
│   └── Filter
│
├── Library         # STM32 Standard Peripheral Library
│
├── Start           # Startup files
│
├── System          # System drivers
│
├── User            # Main program
│
├── Objects         # Build output
│
└── Project.uvprojx # Keil project
```

---

## ⚙️ Software Environment

* Keil MDK5
* STM32 Standard Peripheral Library
* C Language

---

## 🚀 Working Principle

1. Initialize peripherals.
2. Perform load cell tare calibration.
3. Acquire weight using the HX711 module.
4. Apply averaging and median filtering to reduce noise.
5. Display weight on the OLED.
6. Compare measured weight with the preset threshold.
7. Drive the motor to sort the object.
8. Update qualified and unqualified counters.

---

## 📷 OLED Display

The OLED displays:

* Current weight
* Qualified count
* Unqualified count

Example:

```
      称重分拣

称重: 45 g

合格: 12
不合格: 3
```

---

## ⚖️ Sorting Logic

Default parameters in the program:

| Parameter           | Default |
| ------------------- | ------- |
| Qualified Threshold | 47 g    |
| Maximum Weight      | 200 g   |

Objects below the threshold are considered **Qualified**, while objects above the threshold are classified as **Unqualified**.

These values can be modified directly in `main.c`.

---

## 📌 Main Functional Modules

* HX711 weight acquisition
* OLED display
* Key scanning
* Motor control
* Timer interrupt
* USART debugging
* Digital filtering

---

## 🔧 Build

Open

```
Project.uvprojx
```

using **Keil MDK**, compile the project and download it to the STM32F103C8T6 development board.

---

## 📸 Demonstration

You can place demonstration pictures here.

```
docs/images/demo.jpg
```

---

## 🎥 Demo Video

If available, you can add a demonstration video link here.

---

## 📈 Future Improvements

* PID motor control
* Automatic calibration
* SD card data logging
* Bluetooth communication
* WiFi remote monitoring
* Touch screen interface

---

## 📄 License

This project is intended for learning and educational purposes.

Feel free to modify and improve it.

---

## 👤 Author

GitHub: https://github.com/cdhnprot-lgtm
