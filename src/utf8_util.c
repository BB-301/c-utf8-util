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

#include <inttypes.h>
#include <stdlib.h>

#include "utf8_util.h"

// MARK: Private API declaration

static uint32_t utf8_decode_1(uint8_t const *bytes);
static uint32_t utf8_decode_2(uint8_t const *bytes);
static uint32_t utf8_decode_3(uint8_t const *bytes);
static uint32_t utf8_decode_4(uint8_t const *bytes);

static void utf8_encode_1(uint32_t value, uint8_t *dest);
static void utf8_encode_2(uint32_t value, uint8_t *dest);
static void utf8_encode_3(uint32_t value, uint8_t *dest);
static void utf8_encode_4(uint32_t value, uint8_t *dest);

// MARK: Public API implementation

uint32_t utf8_decode(uint8_t const *bytes, size_t n)
{
    if (n == 0 || n > 4)
    {
        abort();
    }
    if (n == 1)
    {
        return utf8_decode_1(bytes);
    }
    if (n == 2)
    {
        return utf8_decode_2(bytes);
    }
    if (n == 3)
    {
        return utf8_decode_3(bytes);
    }
    if (n == 4)
    {
        return utf8_decode_4(bytes);
    }
    abort();
}

void utf8_debug(uint32_t value, FILE *stream)
{
    uint8_t bytes[5] = {0};
    size_t n = utf8_encode(value, bytes);
    fprintf(stream, "%s\tU+%X\t\t%" PRIu32 "\t\tUTF-8(", bytes, value, value);
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
        {
            fprintf(stream, " ");
        }
        fprintf(stream, "%02X", bytes[i]);
    }
    fprintf(stream, ")\n");
}

size_t utf8_encode(uint32_t value, uint8_t *dest)
{
    if (value <= 0x007f)
    {
        utf8_encode_1(value, dest);
        return 1;
    }
    if (value <= 0x07ff)
    {
        utf8_encode_2(value, dest);
        return 2;
    }
    if (value <= 0xffff)
    {
        utf8_encode_3(value, dest);
        return 3;
    }
    if (value <= 0x10ffff)
    {
        utf8_encode_4(value, dest);
        return 4;
    }
    abort();
}

// MARK: Private API documentation

static uint32_t utf8_decode_1(uint8_t const *bytes)
{
    uint32_t value = bytes[0];
    if (value > 127)
    {
        abort();
    }
    return value;
}

static uint32_t utf8_decode_2(uint8_t const *bytes)
{
    uint8_t b1 = bytes[0];
    uint8_t b2 = bytes[1];

    if ((b1 & 192) != 192)
    {
        abort();
    }

    if ((b2 & 128) != 128)
    {
        abort();
    }

    b1 &= 31;
    b2 &= 63;

    uint32_t value = 0;
    value |= ((uint32_t)b1) << 6;
    value |= (uint32_t)b2;

    return value;
}

static uint32_t utf8_decode_3(uint8_t const *bytes)
{
    uint8_t b1 = bytes[0];
    uint8_t b2 = bytes[1];
    uint8_t b3 = bytes[2];

    if ((b1 & 224) != 224)
    {
        abort();
    }

    if ((b2 & 128) != 128)
    {
        abort();
    }

    if ((b3 & 128) != 128)
    {
        abort();
    }

    b1 &= 15;
    b2 &= 63;
    b3 &= 63;

    uint32_t value = 0;

    value |= ((uint32_t)b1 << 12);
    value |= ((uint32_t)b2 << 6);
    value |= (uint32_t)b3;

    return value;
}

static uint32_t utf8_decode_4(uint8_t const *bytes)
{
    uint8_t b1 = bytes[0];
    uint8_t b2 = bytes[1];
    uint8_t b3 = bytes[2];
    uint8_t b4 = bytes[3];

    if ((b1 & 240) != 240)
    {
        abort();
    }

    if ((b2 & 128) != 128)
    {
        abort();
    }

    if ((b3 & 128) != 128)
    {
        abort();
    }

    if ((b4 & 128) != 128)
    {
        abort();
    }

    b1 &= 7;
    b2 &= 63;
    b3 &= 63;
    b4 &= 63;

    uint32_t value = 0;

    value |= ((uint32_t)b1) << 18;
    value |= ((uint32_t)b2) << 12;
    value |= ((uint32_t)b3) << 6;
    value |= (uint32_t)b4;

    return value;
}

static void utf8_encode_1(uint32_t value, uint8_t *dest)
{
    uint8_t b1 = (uint8_t)(value & 127);

    dest[0] = b1;
}

static void utf8_encode_2(uint32_t value, uint8_t *dest)
{
    uint8_t b1 = (uint8_t)((value & 1984) >> 6);
    b1 |= 192;

    uint8_t b2 = (uint8_t)(value & 63);
    b2 |= 128;

    dest[0] = b1;
    dest[1] = b2;
}

static void utf8_encode_3(uint32_t value, uint8_t *dest)
{
    uint8_t b1 = (uint8_t)(value >> 12);
    b1 |= 224;

    uint8_t b2 = (uint8_t)((value & 4032) >> 6);
    b2 |= 128;

    uint8_t b3 = (uint8_t)((value & 63));
    b3 |= 128;

    dest[0] = b1;
    dest[1] = b2;
    dest[2] = b3;
}

static void utf8_encode_4(uint32_t value, uint8_t *dest)
{
    uint8_t b1 = (uint8_t)((value & 1835008) >> 18);
    b1 |= 240;

    uint8_t b2 = (uint8_t)((value & 258048) >> 12);
    b2 |= 128;

    uint8_t b3 = (uint8_t)((value & 4032) >> 6);
    b3 |= 128;

    uint8_t b4 = (uint8_t)(value & 63);
    b4 |= 128;

    dest[0] = b1;
    dest[1] = b2;
    dest[2] = b3;
    dest[3] = b4;
}
