/*
Copyright (c) 2024 BB-301 <fw3dg3@gmail.com> [Official repository](https://github.com/BB-301/c-utf8-util)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _UTF8_UTIL_H_
#define _UTF8_UTIL_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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

#endif
