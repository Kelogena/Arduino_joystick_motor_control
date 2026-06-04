# Arduino Joystick Motor Control

Control a servo motor and a 28BYJ-48 stepper motor using a dual-axis joystick and an Arduino Uno.

## Features

* 🎮 Real-time joystick control
* 🔄 X-axis controls servo position (0°–180°)
* ⚙️ Y-axis controls stepper motor direction and speed
* 🛑 Emergency stop/start using joystick button
* 📊 Serial monitor debugging output
* 🔧 Simple hardware setup using common Arduino components

---

## Hardware Requirements

| Component                              | Quantity  |
| -------------------------------------- | --------- |
| Arduino Uno                            | 1         |
| Joystick Module (KY-023 or equivalent) | 1         |
| SG90 Servo Motor (or compatible)       | 1         |
| 28BYJ-48 Stepper Motor                 | 1         |
| ULN2003 Driver Board                   | 1         |
| Breadboard & Jumper Wires              | As needed |

---

## Wiring
![Arduino Wiring Schematic](docs/arduino_joystick_motor_contro.svg)
### Joystick

| Joystick Pin | Arduino |
| ------------ | ------- |
| VRX          | A0      |
| VRY          | A1      |
| SW           | D2      |
| VCC          | 5V      |
| GND          | GND     |

### Servo

| Servo Wire | Arduino |
| ---------- | ------- |
| Signal     | D9      |
| VCC        | 5V      |
| GND        | GND     |

### Stepper Driver (ULN2003)

| ULN2003 Pin | Arduino |
| ----------- | ------- |
| IN1         | D8      |
| IN2         | D6      |
| IN3         | D7      |
| IN4         | D5      |
| VCC         | 5V      |
| GND         | GND     |

Connect the 28BYJ-48 motor directly to the ULN2003 board using the included 5-pin connector.

---

## Control Scheme

### Servo Control

Move the joystick left or right:

* Left → Servo rotates toward 0°
* Right → Servo rotates toward 180°

### Stepper Control

Move the joystick forward or backward:

* Forward → Stepper rotates clockwise
* Backward → Stepper rotates counter-clockwise
* Further movement from center → Higher speed
* Center position → Motor stops

### Emergency Stop

Press the joystick button:

* Stops all motion
* Centers the servo at 90°
* Press again to resume operation

---

## Serial Output

The Serial Monitor displays live diagnostic information:

```text
X:512  Y:300  Servo:90°
X:720  Y:850  Servo:126°
```

Useful for calibration and debugging.

---

## Libraries Used

```cpp
#include <Servo.h>
#include <Stepper.h>
```

Both libraries are included with the Arduino IDE.

---

## Uploading

1. Open Arduino IDE.
2. Connect your Arduino Uno.
3. Select the correct board and COM port.
4. Upload the sketch.
5. Open Serial Monitor at 9600 baud.

---

## Notes

* The 28BYJ-48 stepper motor uses approximately 2048 steps per revolution.
* For stable operation, an external 5V power supply is recommended for the stepper motor.
* Make sure the grounds of the Arduino and external power supply are connected together.
* Maximum practical speed for the 28BYJ-48 is around 15–17 RPM.

---

## Future Improvements

* Acceleration and deceleration control
* OLED status display
* Wireless control via Bluetooth
* Preset servo positions
* Smooth stepper control using AccelStepper library

---

## License

MIT License

Feel free to use, modify, and distribute this project.
