# APCPPLib
A C++ library (currently a WIP) containing useful objects and tests along with it. (All-Purpose C++ Library)

## What is currently available

### Benchmarking

>  Breakpoint class

Breakpoint object that mesure the time spent until end of scope.

### Exceptions

> Exception

A little class that format throwable exception messages.

### Log

> Logger class

An set of static methods that access an object that create debug message with options.

### Maths

> calculate_hypotenuse

A templated function that calculates the hypotenuse of a rectangle triangle.

> is_triangle_rectangle

A function that checks if the triangle passed as parameter is rectangle.

> Vector class

Two classes of vectors that contains 2 or 3 coordinates.

### Utils

> max_tuple_value

A meta-driven function that calculates the maximum value contained in a tuple.

> tuple_sum

A meta-driven function that calculates the sum of all elements of a tuple.

## How to install

Using cmake, the project compiles into a static library.

```mkdir build && cd build && cmake .. && make```

Compile the libAPCPPLib.a library with your project.