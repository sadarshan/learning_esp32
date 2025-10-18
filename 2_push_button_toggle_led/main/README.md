# 🔘 Push Button Input with LED Toggle on ESP32-C6  
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)](https://docs.espressif.com/projects/esp-idf/en/latest/)  
[![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Enabled-green)](https://www.freertos.org/)  
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)  
[![Board: ESP32-C6](https://img.shields.io/badge/Board-ESP32--C6-orange)](https://www.espressif.com/en/products/socs/esp32-c6)

---

## 🧠 Overview
This project demonstrates how to **read input from a push button** and **toggle an LED** on the **ESP32-C6** using **ESP-IDF** and **FreeRTOS**.  
It continuously checks the button’s state and flips the LED output each time the button is pressed.

---

## ⚙️ Project Information

| Field | Details |
|-------|----------|
| **Filename** | `2_push_button_toggle_led.c` |
| **Author** | [Darshan Savaliya](https://github.com/sadarshan) |
| **Date** | 17 Oct 2025 |
| **Board** | ESP32-C6 |
| **Framework** | ESP-IDF (FreeRTOS) |
| **Purpose** | Read button input (GPIO 8) and toggle LED (GPIO 2) accordingly |

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
#include "esp_err.h"
#include "esp_log.h"
```
Used for GPIO control, logging, FreeRTOS task handling, and error checking.

---

### 2️⃣ GPIO Configuration
```c
gpio_config_t io_conf = {0};
io_conf.pin_bit_mask = (1ULL << GPIO_NUM_8);
io_conf.mode = GPIO_MODE_INPUT;
io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
io_conf.intr_type = GPIO_INTR_DISABLE;
gpio_config(&io_conf);
```
Configures **GPIO 8** as an **input** with **internal pull-up** resistor enabled.  
This allows the button (connected to ground) to pull the pin **LOW** when pressed.

---

### 3️⃣ LED Setup
```c
gpio_reset_pin(GPIO_NUM_2);
gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
```
Resets and configures **GPIO 2** as an output pin to control the LED.

---

### 4️⃣ Main Logic Loop
```c
while (1) {
    current_button_state = gpio_get_level(GPIO_NUM_8);
    if ((current_button_state==0 && previous_button_state==1) || (current_button_state==0 && previous_button_state==0)) {
        led_state = !led_state;
        gpio_set_level(GPIO_NUM_2, led_state);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
}
```
- Checks if the button is pressed (logic LOW).  
- Toggles LED state each time the button is pressed.  
- Adds a small delay (100ms) for debounce handling.

</details>

---

## 🔌 Hardware Setup

| ESP32-C6 Pin | Connection |
|---------------|-------------|
| **GPIO 8** | Push Button → GND |
| **GPIO 2** | LED → Anode (+) |
| **GND** | LED → Cathode (−) via 220 Ω resistor |

---

## 🧰 Requirements

**Hardware**
- ESP32-C6 dev board  
- 1 × Push button  
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
2_push_button_toggle_led/
├── main/
│   └── 2_push_button_toggle_led.c
├── CMakeLists.txt
├── sdkconfig
└── README.md
```

---

## 🖥️ Setup & Build

```bash
# 1️⃣ Clone this repo
git clone https://github.com/sadarshan/learning_esp32.git
cd learning_esp32/2_push_button_toggle_led

# 2️⃣ Set target chip
idf.py set-target esp32c6

# 3️⃣ Build the project
idf.py build

# 4️⃣ Flash and monitor
idf.py -p /dev/ttyUSB0 flash monitor
```

Expected log output:
```
Reading the button state: Loop value: 0
Button is pressed; toggling LED state
Reading the button state: Loop value: 1
...
```

---

## 🧪 Troubleshooting

| Problem | Possible Cause | Fix |
|----------|----------------|-----|
| LED not toggling | Button wiring incorrect | Check connection to GND and GPIO 8 |
| Button always reads HIGH | Pull-up not enabled | Verify internal/external pull-up |
| LED flickers randomly | Button bounce | Add hardware or software debounce |
| Serial port error | Wrong COM/TTY port | Check `ls /dev/tty*` or Device Manager |

---

## 🧠 Learning Takeaways

✅ GPIO input configuration with pull-up  
✅ Button-press detection logic  
✅ LED control using GPIO output  
✅ Handling button debounce and toggling logic  
✅ Using `gpio_config()` and `gpio_get_level()`  

---

## 🚀 Next Steps

Try extending this project:
- ⏱ Add **software debounce** using timestamp checks  
- 🔄 Toggle between **multiple LEDs** on each press  
- 💾 Store LED state in **NVS flash memory**  
- ⚡ Use **GPIO interrupts** instead of polling  

---

> **Made with ❤️ by [Darshan Savaliya](https://github.com/sadarshan)**  
> *ESP32-C6 | FreeRTOS | Embedded C | 2025*
