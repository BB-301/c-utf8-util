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

#include <assert.h>
#include <stdio.h>
#include <strings.h>

#include "utf8_util.h"

int main(void)
{
    uint32_t codepoints[] = {0x0024, 0x00A3, 0x0418, 0x0939, 0x20AC, 0xD55C, 0x10348};
    size_t n_codepoints = sizeof(codepoints) / sizeof(codepoints[0]);
    uint8_t bytes[5];
    size_t n;
    for (size_t i = 0; i < n_codepoints; i++)
    {
        uint32_t value = codepoints[i];
        bzero(bytes, 5);
        n = utf8_encode(value, bytes);
        assert(utf8_decode(bytes, n) == value);
    }
    return 0;
}
