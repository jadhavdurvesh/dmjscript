# DMJScript

A beginner-friendly programming language created by Durvesh Jadhav.

DMJScript is designed to make programming simple while providing built-in support for robotics, electronics, embedded systems, and Arduino development.

Version: 1.0.0

---

## Features

### Core Language

- Variables
- Strings
- Integers
- Decimal Numbers
- User Input
- Output
- Conditions
- Loops
- Functions
- Math Expressions

### Hardware Features

- Arduino Mode
- LED Control
- Servo Control
- Delays

---

## Hello World

DMJScript:

```dmj
show "Hello World"
```

Generated C++:

```cpp
cout << "Hello World" << endl;
```

---

## Variables

### String

```dmj
var name = "Durvesh"
show name
```

### Integer

```dmj
var age = 17
show age
```

### Decimal

```dmj
var voltage = 4.75
show voltage
```

---

## User Input

```dmj
ask name
show name
```

---

## Conditions

```dmj
var age = 18

if age >= 18 then
    show "Adult"
else
    show "Minor"
end
```

---

## Loops

```dmj
repeat 3
    show "Hello"
end
```

---

## Math Expressions

```dmj
var a = 10
var b = 20

var total = a + b
var difference = b - a
var multiply = a * b

show total
show difference
show multiply
```

---

## Functions

```dmj
function greet

    show "Hello from DMJScript"

end

call greet
```

---

# Arduino Mode

DMJScript can generate Arduino-compatible code.

## Blink Example

DMJScript:

```dmj
hardware arduino

led status = 13

on status
wait 1000
off status
```

Generated Arduino Sketch:

```cpp
#include <Arduino.h>

void setup()
{
    pinMode(13, OUTPUT);

    int status = 13;

    digitalWrite(status, HIGH);
    delay(1000);
    digitalWrite(status, LOW);
}

void loop()
{
}
```

---

## LED Control

```dmj
led status = 13

on status
off status
```

---

## Servo Control

```dmj
servo arm = 9

move arm 0
wait 1000

move arm 90
wait 1000

move arm 180
```

Generated:

```cpp
Servo arm;
arm.attach(9);

arm.write(0);
delay(1000);

arm.write(90);
delay(1000);

arm.write(180);
```

---

## Delay

```dmj
wait 1000
```

Generated:

```cpp
delay(1000);
```

---

# Build Instructions

Compile the DMJScript compiler:

```bash
gcc dmjc.c -o dmjc
```

Run the compiler:

```bash
./dmjc
```

Generated output:

```text
output.cpp
```

Compile generated C++:

```bash
g++ output.cpp -o hello
```

Run:

```bash
./hello
```

---

# Example Program

```dmj
function greet

    show "Welcome to DMJScript"

end

show "Start"

call greet

repeat 3
    show "Running..."
end

show "End"
```

---

# Roadmap

## Completed

- Variables
- Strings
- Numbers
- Input
- Output
- Conditions
- Loops
- Math Expressions
- Functions
- Arduino Mode
- LED Support
- Servo Support
- Delays

## Future Plans

### v1.1

- Buzzer Support

### v1.2

- Ultrasonic Sensor Support

### v1.3

- LCD Display Support

### v1.4

- ESP8266 WiFi Support

### v2.0

- Raspberry Pi Support

---

# License

This project is licensed under the MIT License.

See the LICENSE file for details.

---

# Creator

Durvesh Jadhav

GitHub:
https://github.com/jadhavdurvesh

Created with C and built for learning programming, robotics, and embedded systems.
