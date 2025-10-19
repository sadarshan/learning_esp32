# Rotary Encoder and Button Input with ESP32-C6

## Overview
This project demonstrates how to interface an **HW-040 rotary encoder** and a **push button** with the **ESP32-C6** board using the **ESP-IDF** framework.  
It reads encoder rotation (clockwise and counter-clockwise) and button presses, printing the results to the UART terminal.

---

## 🧠 Key Concepts
- **Rotary Encoder Reading:** Detect direction of rotation using GPIO interrupts on encoder pins A (CLK) and B (DT).  
- **Push Button Interrupt:** Detect button presses using GPIO interrupt on rising edge.  
- **ISR Handling:** Separate interrupt service routines (ISRs) for the encoder and button.  
- **GPIO Configuration:** Demonstrates use of internal pull-ups, interrupt types, and GPIO direction setup.  
- **Debouncing Logic:** Implemented basic software debounce delay for stable readings.

---

## ⚙️ Hardware Connections

| Component | Pin Name | ESP32-C6 GPIO | Description |
|------------|-----------|----------------|--------------|
| Rotary Encoder | CLK (A) | GPIO10 | Encoder output A (used for interrupt trigger) |
| Rotary Encoder | DT (B) | GPIO11 | Encoder output B (used for direction detection) |
| Rotary Encoder | SW (Button) | GPIO8 | Button input with internal pull-up |
| Rotary Encoder | VCC | 3V3 | Power supply |
| Rotary Encoder | GND | GND | Ground |

**Note:** HW-040 modules include pull-ups on A, B, and SW pins, but enabling internal pull-ups in software ensures stable logic levels.

---

## 🧩 Software Details

### File Info
```
Filename: 4_intro_to_rotary_encoder.c
Author: Darshan Savaliya (github@sadarshan)
Date: 19 Oct 2025
Board: ESP32-C6
```

### Main Functions
| Function | Description |
|-----------|--------------|
| `app_main()` | Initializes GPIOs, installs ISR service, and monitors encoder/button events. |
| `ISR_handler_for_gpio8()` | Increments button press counter on each positive edge. |
| `ISR_handler_for_gpio10()` | Detects rotation direction and increments/decrements encoder counter accordingly. |

---

## 🔄 Program Flow

1. Configure GPIO8 (button) as input with pull-up and positive-edge interrupt.  
2. Configure GPIO10 (encoder A) as input with interrupt on both edges.  
3. Configure GPIO11 (encoder B) as input with pull-up enabled (for direction reference).  
4. Register ISRs for GPIO8 and GPIO10.  
5. In the main loop:
   - Print button press and encoder rotation direction.  
   - Debounce button with a short delay.  

---

## 📜 Example Output

```
----------
Button is pressed; toggling LED state. Button print count: 1
----------
Encoder clockwise rotation detected. Encoder counter: 4
----------
Encoder anti-clockwise rotation detected. Encoder counter: 3
```

---

## 🧪 Debug Tips
- Ensure your encoder module’s **VCC and GND** are properly connected.
- If no signal is detected:
  - Check `gpio_get_level()` logic in ISR — invert levels if encoder is active-low.
  - Verify correct pin mapping in `gpio_config_t` setup.
- You can adjust the interrupt type for A pin (GPIO10) between `GPIO_INTR_POSEDGE`, `GPIO_INTR_NEGEDGE`, and `GPIO_INTR_ANYEDGE` for experimentation.

---

## 🧰 Build & Flash Instructions

1. Create a new ESP-IDF project or add this file under the `main/` folder.
2. Configure the project:
   ```bash
   idf.py set-target esp32c6
   idf.py menuconfig
   ```
3. Build and flash the firmware:
   ```bash
   idf.py build
   idf.py flash -p /dev/ttyUSB0
   ```
4. Monitor output:
   ```bash
   idf.py monitor
   ```

---

## 🧑‍💻 Author
**Darshan Savaliya**  
GitHub: [@sadarshan](https://github.com/sadarshan)  
Date: 19 Oct 2025