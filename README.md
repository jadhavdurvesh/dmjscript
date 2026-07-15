# DMJScript

A beginner-friendly programming language focused on robotics, electronics, Arduino, and embedded systems.

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-DMJScript-orange)

---

## What is DMJScript?

DMJScript is a programming language created to make learning programming and hardware development easier.

The language focuses on:

- Arduino Development
- Robotics
- Electronics
- Embedded Systems
- Mechatronics Projects
- Beginner-Friendly Syntax

DMJScript source files use the `.dmj` extension.

---

## Features

### Variables

```dmj
var name = "Durvesh"
var age = 17

show name
show age
```

### Functions

```dmj
function greet

    show "Hello from DMJScript"

end

call greet
```

### Conditions

```dmj
if age >= 18 then

    show "Adult"

else

    show "Minor"

end
```

### Loops

```dmj
repeat 3

    show "Hello"

end
```

### Hardware Control

```dmj
led status = 13

on status
wait 1000
off status
```

### Servo Control

```dmj
servo arm = 9

move arm 90
```

---

## Installation

Clone the repository:

```bash
git clone https://github.com/jadhavdurvesh/dmjscript.git
cd dmjscript
```

Compile the compiler:

```bash
gcc dmjc.c -o dmjc
```

---

## First Program

Create:

```text
hello.dmj
```

Contents:

```dmj
show "Hello World"
```

Compile:

```bash
./dmjc hello.dmj
```

Build:

```bash
g++ output.cpp -o output
```

Run:

```bash
./output
```

Output:

```text
Hello World
```

---

## Documentation

Documentation is available in the `docs` folder.

- Getting Started
- Variables
- Functions
- Hardware Support

---

## Examples

Example programs can be found in:

```text
examples/
```

Current examples:

```text
hello.dmj
variables.dmj
functions.dmj
blink.dmj
servo.dmj
```

---

## Project Structure

```text
dmjscript/
├── README.md
├── LICENSE
├── spec.md
├── dmjc.c
├── docs/
├── examples/
├── generated/
└── archive/
```

---


## New Features

### Arrays

```dmj
var numbers = [10, 20, 30]
```

### Run Mode

```bash
./dmjc run examples/test.dmj
```

Automatically:
1. Compiles DMJScript
2. Generates C++
3. Builds executable
4. Runs program

## Roadmap

### Version 1.1

- Better Hardware Support
- Buzzer Control
- Sensor Support
- Additional Examples

### Version 1.2

- Arrays
- Enhanced Functions
- Standard Library

### Version 2.0

- ESP32 Support
- Raspberry Pi Support
- Package Manager
- DMJ IDE

---

## VS Code Extension

Official VS Code extension:

https://marketplace.visualstudio.com/items?itemName=durveshjadhav.dmjscript

Repository:

https://github.com/jadhavdurvesh/dmjscript-vscode

---

## Author

Durvesh Jadhav

---

## License

MIT License

Copyright (c) 2026 Durvesh Jadhav