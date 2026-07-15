# Getting Started with DMJScript

DMJScript is a beginner-friendly programming language designed for learning programming, robotics, electronics, and Arduino development.

---

## Hello World

Create a file named `hello.dmj`:

```dmj
show "Hello, World!"
```

Compile:

```bash
./dmjc hello.dmj
```

This generates:

```text
output.cpp
```

Build the generated C++ file:

```bash
g++ output.cpp -o output
```

Run:

```bash
./output
```

Output:

```text
Hello, World!
```

---

## Variables

```dmj
var name = "Durvesh"
var age = 17
var voltage = 4.75

show name
show age
show voltage
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

## Hardware Example

```dmj
led status = 13

on status
wait 1000
off status
```

---

## Project Structure

```text
dmjscript/
├── dmjc.c
├── spec.md
├── examples/
├── docs/
└── README.md
```

---

## License

MIT License

Copyright (c) 2026 Durvesh Jadhav