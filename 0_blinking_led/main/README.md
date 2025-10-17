# 🚦 Blinking LED on ESP32-C6  
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)](https://docs.espressif.com/projects/esp-idf/en/latest/)  
[![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Enabled-green)](https://www.freertos.org/)  
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)  
[![Board: ESP32-C6](https://img.shields.io/badge/Board-ESP32--C6-orange)](https://www.espressif.com/en/products/socs/esp32-c6)

---

## 🧠 Overview
This project demonstrates the **basic GPIO control** on the **ESP32-C6** using **ESP-IDF** and **FreeRTOS**.  
It blinks an LED connected to **GPIO 2** at a **1-second interval**, showing that the board and toolchain are set up correctly.

---

## ⚙️ Project Information

| Field | Details |
|-------|----------|
| **Filename** | `0_blinking_led.c` |
| **Author** | [Darshan Savaliya](https://github.com/sadarshan) |
| **Date** | 16 Oct 2025 |
| **Board** | ESP32-C6 |
| **Framework** | ESP-IDF (FreeRTOS) |
| **Purpose** | Blink an LED connected to GPIO 2 every 1 second |

---

## 🧩 Code Breakdown

<details>
<summary><b>▶ Expand to view explanation</b></summary>

### 1️⃣ Header Files
```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
```
Used for logging, delays, and GPIO control.

---

### 2️⃣ GPIO Setup
```c
gpio_reset_pin(GPIO_NUM_2);
gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
```
Initializes and configures GPIO 2 as an output pin.

---

### 3️⃣ Main Loop
```c
while (1) {
    gpio_set_level(GPIO_NUM_2, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_NUM_2, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
```
Continuously toggles LED ON and OFF every second.
</details>

---

## 🔌 Hardware Setup

| ESP32-C6 Pin | Connection |
|---------------|-------------|
| **GPIO 2** | LED → Anode (+) |
| **GND** | LED → Cathode (−) through 220 Ω resistor |

> 💡 **Tip:** Always use a resistor (220–330 Ω) in series with the LED to limit current.

---

## 🧰 Requirements

**Hardware**
- ESP32-C6 dev board  
- 1 × LED  
- 1 × 220 Ω resistor  
- Jumper wires / breadboard  

**Software**
- [ESP-IDF v5.2+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/get-started/)
- Python 3 (for ESP-IDF tools)
- USB cable for flashing

---

## 🧱 File Structure
```
esp32-blinking-led/
├── main/
│   └── 0_blinking_led.c
├── CMakeLists.txt
├── sdkconfig
└── README.md
```

---

## 🖥️ Setup & Build

```bash
# 1️⃣ Clone this repo
git clone https://github.com/sadarshan/esp32-blinking-led.git
cd esp32-blinking-led

# 2️⃣ Set target chip
idf.py set-target esp32c6

# 3️⃣ Build the project
idf.py build

# 4️⃣ Flash to board (update serial port if needed)
idf.py -p /dev/ttyUSB0 flash monitor
```

You should see logs in the serial monitor:
```
Setting the GPIO pin to High
Setting the GPIO pin to Low
Setting the GPIO pin to High
Setting the GPIO pin to Low
...
```

And your LED will blink every 1 second.

---

## 🧪 Troubleshooting

| Problem | Possible Cause | Fix |
|----------|----------------|-----|
| LED not blinking | Wrong GPIO pin | Verify LED is on GPIO 2 |
| Serial port error | Wrong port / in use | Check `ls /dev/tty*` or Device Manager |
| No logs visible | Log level too high | `idf.py menuconfig → Component config → Log output` |

---

## 🧠 Learning Takeaways

✅ GPIO initialization and configuration  
✅ Writing digital output with ESP-IDF  
✅ Using FreeRTOS delay (`vTaskDelay`)  
✅ Logging with `ESP_LOGI()`  

---

## 🚀 Next Steps

Try extending this basic example:
- 🔘 Add a button to control LED blink rate  
- ⏱ Use a hardware timer instead of FreeRTOS delay  
- 🌈 Blink multiple LEDs in sequence  

---

## 📜 License

This project is released under the **MIT License**.  
You’re free to use, modify, and distribute — just credit the author.

---

> **Made with ❤️ by [Darshan Savaliya](https://github.com/sadarshan)**  
> *ESP32-C6 | FreeRTOS | Embedded C | 2025*
