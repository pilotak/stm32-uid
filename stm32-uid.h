/*
MIT License

Copyright (c) 2018 Pavel Slama

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef STM32UID_H
#define STM32UID_H

#include "mbed.h"

static const char encoding_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '-', '_'
};

class STM32uid {
 public:
  STM32uid();
  void get(char * buffer);
  void get_base64(char * buffer);
};

STM32uid::STM32uid() {
}

void STM32uid::get(char * buffer) {
  uint32_t *uid_r = reinterpret_cast<uint32_t *>(UID_BASE);
  char id[12];

  for (uint8_t i = 0; i < 3; i++) {
    for (int8_t j = 3; j > -1; j--) {
      id[(i * 4) + abs(j - 3)] = (uid_r[i] >> (8 * j)) & 0xFF;
    }
  }

  memcpy(buffer, id, 12);
}

void STM32uid::get_base64(char * buffer) {
  char id[12];
  char encoded_data[16];
  get(id);

  for (int i = 0, j = 0; i < 12;) {
    uint32_t octet_a = i < 12 ? (unsigned char)id[i++] : 0;
    uint32_t octet_b = i < 12 ? (unsigned char)id[i++] : 0;
    uint32_t octet_c = i < 12 ? (unsigned char)id[i++] : 0;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }

  memcpy(buffer, encoded_data, 16);
}

#endif  // STM32UID_H
