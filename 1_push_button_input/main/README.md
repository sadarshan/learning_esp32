
# 🔘 Push Button Input and LED Control on ESP32-C6  
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)](https://docs.espressif.com/projects/esp-idf/en/latest/)  
[![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Enabled-green)](https://www.freertos.org/)  
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)  
[![Board: ESP32-C6](https://img.shields.io/badge/Board-ESP32--C6-orange)](https://www.espressif.com/en/products/socs/esp32-c6)

---

## 🧠 Overview
This project demonstrates **reading a push button input** on the **ESP32-C6** using **ESP-IDF** and **FreeRTOS**, and controlling an LED based on the button state.  
The LED turns **ON** when the button is pressed and **OFF** when released.

---

## ⚙️ Project Information

| Field | Details |
|-------|---------|
| **Filename** | `1_push_button_input.c` |
| **Author** | [Darshan Savaliya](https://github.com/sadarshan) |
| **Date** | 17 Oct 2025 |
| **Board** | ESP32-C6 |
| **Framework** | ESP-IDF (FreeRTOS) |
| **Purpose** | Read a push button on GPIO 8 and set LED on GPIO 2 accordingly |

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

gpio_reset_pin(GPIO_NUM_8);
gpio_set_direction(GPIO_NUM_8, GPIO_MODE_INPUT);
gpio_pullup_en(GPIO_NUM_8);
```
- GPIO 2 → LED output  
- GPIO 8 → Push button input with internal pull-up

---

### 3️⃣ Main Loop
```c
while (1) {
    button_state = gpio_get_level(GPIO_NUM_8);
    if (button_state == 0) { // pressed
        gpio_set_level(GPIO_NUM_2, 1);
    } else { // released
        gpio_set_level(GPIO_NUM_2, 0);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
}
```
Continuously reads button state and sets LED accordingly, with a 100 ms delay.
</details>

---

## 🔌 Hardware Setup

| ESP32-C6 Pin | Connection |
|---------------|------------|
| **GPIO 8**   | Push Button → One side to GPIO 8, other to GND |
| **GPIO 2**   | LED → Anode (+) |
| **GND**      | LED → Cathode (−) |

> 💡 **Tip:** Internal pull-up on GPIO 8 ensures stable HIGH reading when button is released. LED should be protected with a series resistor (220–330 Ω).

---

## 🧰 Requirements

**Hardware**
- ESP32-C6 dev board  
- 1 × LED  
- 1 × Push button  
- 1 × 220 Ω resistor (for LED)  
- Jumper wires / breadboard  

**Software**
- [ESP-IDF v5.x+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/get-started/)  
- Python 3 (for ESP-IDF tools)  
- USB cable for flashing

---

## 🧱 File Structure
```
1_push_button_input/
├── main/
│   └── 1_push_button_input.c
|   └── README.md
├── CMakeLists.txt
├── sdkconfig

```

---

## 🖥️ Setup & Build

```bash
# 1️⃣ Clone the repo
git clone https://github.com/sadarshan/learning_esp32.git
cd learning_esp32/1_push_button_input

# 2️⃣ Set target chip
idf.py set-target esp32c6

# 3️⃣ Build the project
idf.py build

# 4️⃣ Flash to board (update serial port if needed)
idf.py -p /dev/ttyUSB0 flash monitor
```

You should see logs like:
```
Reading the button state: Loop value: 1
Button is pressed; setting GPIO pin 2 to high
Reading the button state: Loop value: 2
Button is released; setting GPIO pin 2 to low
...
```

---

## 🧪 Troubleshooting

| Problem | Possible Cause | Fix |
|----------|----------------|-----|
| LED never turns ON | Button wiring wrong / pull-up missing | Check GPIO 8 connection and ensure `gpio_pullup_en(GPIO_NUM_8)` is called |
| LED always ON | Pull-up not enabled | Enable internal pull-up or check button wiring |
| Serial logs missing | Wrong port / log level | Verify serial port and increase ESP-IDF log level |
| Button bounce / flicker | Mechanical button bounce | Add software debounce or capacitor across button |

---

## 🧠 Learning Takeaways

✅ GPIO input and output configuration  
✅ Using internal pull-up resistor  
✅ Reading digital input with `gpio_get_level()`  
✅ Writing digital output with `gpio_set_level()`  
✅ FreeRTOS delay with `vTaskDelay()`  
✅ Logging with `ESP_LOGI()`  

---

## 🚀 Next Steps

- 🌟 Add multiple buttons controlling multiple LEDs  
- ⏱ Implement button debounce using software timers  
- 🔘 Use button press duration to control LED behavior (short vs long press)  


---

> **Made with ❤️ by [Darshan Savaliya](https://github.com/sadarshan)**  
> *ESP32-C6 | FreeRTOS | Embedded C | 2025*
