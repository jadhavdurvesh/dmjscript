# Functions

Functions allow code to be reused throughout a program.

---

## Creating a Function

Use the `function` keyword to define a function.

```dmj
function greet

    show "Hello from DMJScript"

end
```

---

## Calling a Function

Use the `call` keyword to execute a function.

```dmj
function greet

    show "Hello from DMJScript"

end

call greet
```

Output:

```text
Hello from DMJScript
```

---

## Multiple Function Calls

A function can be called multiple times.

```dmj
function greet

    show "Welcome!"

end

call greet
call greet
call greet
```

Output:

```text
Welcome!
Welcome!
Welcome!
```

---

## Multiple Functions

```dmj
function hello

    show "Hello"

end

function bye

    show "Goodbye"

end

call hello
call bye
```

Output:

```text
Hello
Goodbye
```

---

## Function Rules

- Functions must start with `function`.
- Functions end with `end`.
- Functions execute only when called.
- Function names are case-sensitive.

Example:

```dmj
function start

    show "System Started"

end

call start
```

---

## Example Program

```dmj
function welcome

    show "Welcome to DMJScript"

end

function version

    show "Version 1.0"

end

call welcome
call version
```

Output:

```text
Welcome to DMJScript
Version 1.0
```