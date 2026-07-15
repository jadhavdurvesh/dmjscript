# Hardware Support

DMJScript is designed with robotics, electronics, and Arduino development in mind.

Hardware support allows simple control of LEDs, sensors, servos, and other electronic devices.

---

## LED Control

Declare an LED:

```dmj
led status = 13
```

Turn it on:

```dmj
on status
```

Turn it off:

```dmj
off status
```

Complete example:

```dmj
led status = 13

on status
wait 1000
off status
```

---

## Blink Example

```dmj
led led1 = 13

on led1
wait 500
off led1
wait 500

on led1
wait 500
off led1
```

---

## Servo Control

Declare a servo:

```dmj
servo arm = 9
```

Move the servo:

```dmj
move arm 90
```

Example:

```dmj
servo arm = 9

move arm 0
wait 1000

move arm 90
wait 1000

move arm 180
```

---

## Wait Command

Pause execution for a specified number of milliseconds.

```dmj
wait 1000
```

This pauses the program for one second.

Examples:

```dmj
show "Start"

wait 2000

show "End"
```

Output:

```text
Start
End
```

---

## Traffic Light Example

```dmj
led red = 13
led yellow = 12
led green = 11

on red
wait 3000
off red

on yellow
wait 1000
off yellow

on green
wait 3000
off green
```

---

## Robotics Example

```dmj
led status = 13
servo arm = 9

on status

move arm 90
wait 1000

move arm 0

off status
```

---

## Future Hardware Features

Planned hardware support includes:

- Buzzer control
- Ultrasonic sensors
- RFID modules
- LCD displays
- ESP8266 support
- ESP32 support
- Raspberry Pi GPIO support

---

## Example Project

```dmj
led status = 13
servo arm = 9

show "Robot Started"

on status

move arm 90
wait 1000

move arm 0

off status

show "Robot Finished"
```