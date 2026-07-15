# DMJScript v0.1

## Comments

-- This is a comment

## Variables

var name = "Durvesh"
var age = 17

## Output

show "Hello"
show name

## Input

ask name

## Conditions

if age >= 18 then
    show "Adult"
else
    show "Minor"
end

## Loops

loop
    show "Running"
end

## Hardware

pin 13 output

led 13 on
wait 1000

led 13 off
wait 1000

## Servo

servo arm = 9
move arm 90

## Arrays

Arrays store multiple values in a single variable.

Example:

```dmj
var numbers = [10, 20, 30]

show numbers
```

Future support:

```dmj
show numbers[0]
show numbers[1]
```