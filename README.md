# DMJScript

DMJScript is a beginner-friendly programming language designed for learning programming, robotics, electronics, embedded systems, and IoT development.

The goal of DMJScript is to make coding simple and readable while hiding unnecessary complexity. Programs are written in DMJScript and compiled into C++ code using the DMJScript Compiler (`dmjc`).

---

# Project Status

Current Version: v0.4

Implemented Features:

- Comments
- Variables
- Strings
- Integers
- Decimal Numbers
- Output (`show`)
- Input (`ask`)
- C++ Code Generation

Planned Features:

- If Statements
- Else Statements
- Loops
- Functions
- Arrays
- Modules
- Error Handling
- Classes
- Hardware Support
- Arduino Integration
- ESP32 Integration
- IoT Features

---

# Philosophy

DMJScript is built around three principles:

## 1. Easy to Learn

Instead of:

```cpp
std::cout << "Hello World" << std::endl;
```

DMJScript uses:

```dmj
show "Hello World"
```

---

## 2. Human Readable

Programs should read almost like English.

Example:

```dmj
show "What is your name?"

ask name

show "Hello"
show name
```

---

## 3. Hardware Friendly

DMJScript is being designed with robotics and electronics in mind.

Future syntax:

```dmj
led status = 13

on status
wait 1000

off status
```

---

# Hello World

```dmj
show "Hello World"
```

Output:

```text
Hello World
```

---

# Variables

## String Variables

```dmj
var name = "Durvesh"
```

Generated C++:

```cpp
string name = "Durvesh";
```

---

## Integer Variables

```dmj
var age = 17
```

Generated C++:

```cpp
int age = 17;
```

---

## Decimal Variables

```dmj
var voltage = 4.75
```

Generated C++:

```cpp
double voltage = 4.75;
```

---

# Output

Print text:

```dmj
show "Hello World"
```

Print variable:

```dmj
show name
```

Example:

```dmj
var name = "Durvesh"

show name
```

Output:

```text
Durvesh
```

---

# Input

Read user input:

```dmj
ask name
```

Example:

```dmj
show "What is your name?"

ask name

show "Hello"
show name
```

Example Output:

```text
What is your name?
Durvesh
Hello
Durvesh
```

---

# Comments

Single-line comments:

```dmj
-- This is a comment
```

Example:

```dmj
-- Program Start

show "Hello"
```

---

# Example Program

```dmj
-- Example Program

var name = "Durvesh"
var age = 17
var voltage = 4.75

show name
show age
show voltage
```

Output:

```text
Durvesh
17
4.75
```

---

# Current Language Syntax

## Variable Declaration

```dmj
var name = "Durvesh"
var age = 17
var voltage = 4.75
```

## Output

```dmj
show "Hello"
show name
```

## Input

```dmj
ask name
```

## Comments

```dmj
-- Comment
```

---

# Roadmap

## Version 0.5

Conditionals

```dmj
if age >= 18 then
    show "Adult"
else
    show "Minor"
end
```

---

## Version 0.6

Loops

```dmj
repeat 10
    show "Hello"
end
```

---

## Version 0.7

Functions

```dmj
function greet
    show "Hello"
end
```

---

## Version 0.8

Hardware Support

LED Control

```dmj
led status = 13

on status
wait 1000

off status
```

---

## Version 0.9

Servo Motors

```dmj
servo arm = 9

move arm 90
```

---

## Version 1.0

Embedded and IoT Features

- Arduino Support
- ESP32 Support
- Sensors
- RFID
- WiFi
- Bluetooth
- MQTT
- Robotics Framework

---

# Build Instructions

Compile the compiler:

```bash
gcc dmjc.c -o dmjc
```

Run the compiler:

```bash
./dmjc
```

Compile generated C++:

```bash
g++ output.cpp -o hello
```

Run program:

```bash
./hello
```

---

# Repository Structure

```text
dmjscript/
│
├── dmjc.c
├── hello.dmj
├── output.cpp
├── README.md
└── spec.md
```

---

# Creator

Durvesh Jadhav


Mechatronics Engineering Student

Founder of DMJ Group

---

# License

MIT License

Copyright (c) 2026 Durvesh Jadhav

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.