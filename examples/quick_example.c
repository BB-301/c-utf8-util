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
