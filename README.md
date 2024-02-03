# Encoding unicode codepoints to UTF-8 bytes in C

A simple C library with functions for encoding and decoding between unicode codepoints and UTF-8 bytes.

## Context

This is the result of a learning activity that I did in which my goal was to implement encoding of a 32-bit unicode codepoint into UTF-8 bytes in C. My reference for this exercise was the [UTF-8 Wikipedia article](https://en.wikipedia.org/wiki/UTF-8#Encoding), which I recommend to anyone wishing to better understand how UTF-8 works.

## A quick example

```c
#include <stdio.h>

#include "utf8_util.h"

int main(void)
{
    uint32_t codepoints[] = {0x0024, 0x00A3, 0x0418, 0x0939, 0x20AC, 0xD55C, 0x10348};
    size_t n = sizeof(codepoints) / sizeof(codepoints[0]);
    for (size_t i = 0; i < n; i++)
    {
        utf8_debug(codepoints[i], stdout);
    }
    /* Output:
    $       U+24            36              UTF-8(24)
    £       U+A3            163             UTF-8(C2 A3)
    И       U+418           1048            UTF-8(D0 98)
    ह       U+939           2361            UTF-8(E0 A4 B9)
    €       U+20AC          8364            UTF-8(E2 82 AC)
    한      U+D55C          54620           UTF-8(ED 95 9C)
    𐍈       U+10348         66376           UTF-8(F0 90 8D 88)
    */    
    return 0;
}
```

**NOTE:** You should also have a look at [examples/unit_testing.c](./examples/unit_testing.c) to see how to use `utf8_encode` and `utf8_decode`.

## Library's API

The library [exposes](./include/utf8_util.h) the following three functions:

```c
// Generates a 32-bit unicode codepoint for the `n`
// UTF-8 character bytes pointed to by `bytes`.
uint32_t utf8_decode(uint8_t const *bytes, size_t n);

// Populates `dest` with the UTF-8 bytes for the unicode
// codepoint `value`, and returns the number of UTF-8 bytes
// written to `dest`. NOTE: `n` will always be between 1 and 4,
// so `dest` should point to a location in memory with at least
// 4 bytes available.
size_t utf8_encode(uint32_t value, uint8_t *dest);

// Prints a summary to `stream` (e.g., `stdout`) for unicode
// codepoint `value`.
void utf8_debug(uint32_t value, FILE *stream);
```

## Disclaimer

This is just a draft project that I created for fun. It appears to be working fine, but it was not thoroughly tested, so please make sure to carefully review the code if you ever decide to use this library in a project of yours.

## Contact

If you have any questions, if you find bugs, or if you have suggestions for this project, please feel free to contact me by opening an issue on the [repository](https://github.com/BB-301/c-utf8-util/issues).

## License

This project is released under the [MIT License](./LICENSE).

## Copyright

Copyright (c) 2024 BB-301 (fw3dg3@gmail.com)