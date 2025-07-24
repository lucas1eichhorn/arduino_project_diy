# 🔧 DIY Arduino 🧪

Welcome to my collection of DIY Arduino experiments! 🚀  
This repo is a digital playground where I tinker, test, and explore electronics using Arduino boards, sensors, and lots of jumper wires. Whether you're into blinking LEDs or building complex gadgets, you're in the right place.

---

## 🧠 What You'll Find Here

This repository contains a growing set of small to medium projects, all made with Arduino. Some are useful, some are just for fun, and all are part of my learning journey.

### 🔬 Example Projects (more coming soon!)
- 🌡️ **Temperature & Humidity Logger** – Reads data from a DHT11 sensor and displays it on an LCD.
- 📡 **Wireless Communication Test** – Experiments with NRF24L01 modules.

---

## 🧰 Tools & Components I Use

- Arduino Uno R4 Minima
- Sensors: DHT11, PIR, Ultrasonic, Light (LDR), etc.
- Actuators: Servos, buzzers, relays, LEDs
- Displays: LCD 16x2, OLED
- Breadboards, wires, patience... and coffee ☕️

---

## 📚 Learning & Inspiration

Each project helps me learn a bit more about:
- C/C++ programming for microcontrollers
- Electronics and sensor integration
- Prototyping and debugging

---

## 📦 Project Structure

Each folder is a separate project with:
- `*.ino` Arduino sketch file
- `README.md` with quick description 
- Schematics or photos (in progress)


### 🖥️ Viewing Arduino Serial Logs on macOS (No PuTTY Required)

If you're using **macOS** and want to view your Arduino's serial output (like you would with PuTTY on Windows), you can use the built-in `screen` command in Terminal — no extra software needed!

#### 📋 Steps:

1. Connect your Arduino to your Mac via USB

2. Open the Terminal:
   Press `Cmd + Space`, type `Terminal`, and hit Enter.

3. Find the serial device name
Run the following command:
```
   ls /dev/tty.*
```

You'll see output like:
```
/dev/tty.usbmodem1101
/dev/tty.Bluetooth-Incoming-Port
```

Look for a device that starts with tty.usbmodem or tty.usbserial — that's your Arduino.

Connect to the serial port using screen
Replace the port name and use the correct baud rate (usually 9600):

```
screen /dev/tty.usbmodem1101 9600
```
To exit screen, press:
Ctrl + A, then K, then confirm with Y.