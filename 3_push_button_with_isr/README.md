# Push Button with ISR (ESP32-C6)

**Filename:** `3_push_button_with_isr.c`  
**Author:** Darshan Savaliya (github@sadarshan)  
**Date:** 18 Oct 2025  
**Board:** ESP32-C6  
**Purpose:** Detect push button press on GPIO 8 using an interrupt (ISR) and toggle LED on GPIO 2.

---

## 🧠 Description
This program demonstrates how to use an **interrupt service routine (ISR)** to handle a push button input on ESP32-C6.  
When the button (connected to GPIO 8) is pressed, the ISR triggers and increments a counter. The main loop then detects this event and toggles the LED connected to GPIO 2.

---

## ⚙️ Hardware Setup
| Component | Pin | Connection |
|------------|-----|-------------|
| Push Button | GPIO 8 | Connected between **GPIO8** and **GND** |
| LED | GPIO 2 | Connected between **GPIO2** and **GND** |

---

## 🧩 How It Works
1. The button pin (GPIO 8) is configured as an **input** with **interrupt on rising edge**.  
2. When the button is pressed, the IS   R (`ISR_handler_for_gpio8`) increments `button_push_count`.  
3. The main loop checks this count, toggles LED state, and resets the counter.  
4. The LED connected to GPIO 2 toggles between HIGH and LOW each time the button is pressed.

---

## 🧱 Key Functions
| Function | Description |
|-----------|--------------|
| `gpio_config()` | Configures GPIO mode, pull-up/down, and interrupt type |
| `gpio_install_isr_service()` | Initializes ISR service for GPIOs |
| `gpio_isr_handler_add()` | Links the ISR handler to a specific GPIO pin |
| `gpio_set_level()` | Sets output level (HIGH/LOW) of GPIO pin |
| `vTaskDelay()` | Creates delay for debouncing and timing |

---

## ⚠️ Notes
- Ensure proper hardware pull-up or pull-down for stable button readings.
- Debouncing delay (`vTaskDelay(50/portTICK_PERIOD_MS)`) prevents multiple triggers.
- `ESP_LOGI()` prints debug info for troubleshooting.

---

## ▶️ Build and Flash Instructions
```bash
idf.py set-target esp32c6
idf.py build
idf.py flash -p /dev/ttyUSB0
idf.py monitor
```

---

## 🧾 Output Example
```
Reading the button state: Loop value: 10 button push count: 1
Button is pressed; toggling LED state
```

---

## 🧩 Files
- `3_push_button_with_isr.c` — Source code implementing ISR-based button control
- `README.md` — This file

---

## 🧠 Author Notes
This project demonstrates a clean ISR approach for ESP32 GPIO event handling.  
Useful for applications like button inputs, encoders, and low-latency event detection.
