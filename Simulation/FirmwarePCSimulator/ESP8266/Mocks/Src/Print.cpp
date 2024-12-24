/*
 Print.cpp - Base class that provides print() and println()
 Copyright (c) 2008 David A. Mellis.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Modified 23 November 2006 by David A. Mellis
 Modified December 2014 by Ivan Grokhotkov
 Modified May 2015 by Michael C. Miller - esp8266 progmem support
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Arduino.h>

#include "Print.h"

// ========================= MODIFICATIONS STARTS HERE =========================
#include <cstdarg>
#include <new>
#include <iostream>
//  ========================= MODIFICATIONS STOPS HERE  =========================

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
size_t Print::write(const uint8_t *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    /*  IAMSLOW();

      size_t n = 0;
      while (size--) {
          size_t ret = write(pgm_read_byte(buffer++));
          if (ret == 0) {
              // Write of last byte didn't complete, abort additional processing
              break;
          }
          n += ret;
      }
      return n;*/

    printf("TO WRITE: %s\n", buffer);
    return size;
}

size_t Print::printf(const char *format, ...)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    va_list args;           // Declare a variable of type va_list
    va_start(args, format); // Initialize the va_list with the last known parameter (format)

    // Retrieve the first argument as a specific type, e.g., int, double, etc.
    // Replace 'Type' with the actual type of the first argument
    auto first_arg = va_arg(args, const char *); // Retrieve the first argument as a const char*

    std::cout << first_arg << std::endl;

    /*  va_list arg;
      va_start(arg, format);
      char temp[64];
      char* buffer = temp;
      size_t len = vsnprintf(temp, sizeof(temp), format, arg);
      va_end(arg);
      if (len > sizeof(temp) - 1) {
          buffer = new (std::nothrow) char[len + 1];
          if (!buffer) {
              return 0;
          }
          va_start(arg, format);
          vsnprintf(buffer, len + 1, format, arg);
          va_end(arg);
      }
      len = write((const uint8_t*) buffer, len);
      if (buffer != temp) {
          delete[] buffer;
      }
      return len;*/
    // printf("Print::printf 1\n");

    std::cout << format << std::endl;
    va_list arg;
    va_start(arg, format);
    char temp[64];
    char *buffer = temp;
    // printf("Print::printf 2\n");

    size_t len = vsnprintf(temp, sizeof(temp), format, arg);
    va_end(arg);
    if (len > sizeof(temp) - 1)
    {
        buffer = new (std::nothrow) char[len + 1];
        if (!buffer)
        {
            return 0;
        }
        va_start(arg, format);
        vsnprintf(buffer, len + 1, format, arg);
        va_end(arg);
    }
    len = write((const uint8_t *)buffer, len);
    if (buffer != temp)
    {
        delete[] buffer;
    }
    return len;
}

size_t Print::printf_P(PGM_P format, ...)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  va_list arg;
      va_start(arg, format);
      char temp[64];
      char* buffer = temp;
      size_t len = vsnprintf_P(temp, sizeof(temp), format, arg);
      va_end(arg);
      if (len > sizeof(temp) - 1) {
          buffer = new (std::nothrow) char[len + 1];
          if (!buffer) {
              return 0;
          }
          va_start(arg, format);
          vsnprintf_P(buffer, len + 1, format, arg);
          va_end(arg);
      }
      len = write((const uint8_t*) buffer, len);
      if (buffer != temp) {
          delete[] buffer;
      }
      return len;*/
}

size_t Print::print(const __FlashStringHelper *ifsh)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  PGM_P p = reinterpret_cast<PGM_P>(ifsh);

      char buff[128] __attribute__ ((aligned(4)));
      auto len = strlen_P(p);
      size_t n = 0;
      while (n < len) {
          int to_write = std::min(sizeof(buff), len - n);
          memcpy_P(buff, p, to_write);
          auto written = write(buff, to_write);
          n += written;
          p += written;
          if (!written) {
              // Some error, write() should write at least 1 byte before returning
              break;
          }
      }
      return n;*/
}

size_t Print::print(const String &s)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    std::cout << "@@@@@@@@@@@@@@@@@@@@@ " << s.c_str() << std::endl;
    return write(s.c_str(), s.length());
}

size_t Print::print(const char str[])
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    return write(str);
}

size_t Print::print(char c)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    return write(c);
}

size_t Print::print(int n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*   return print((long) n, base);*/
}

size_t Print::print(unsigned int n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*   return print((unsigned long) n, base);*/
}

size_t Print::print(long n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /* int t = 0;
     if (base == 10 && n < 0) {
         t = print('-');
         n = -n;
     }
     return printNumber(static_cast<unsigned long>(n), base) + t;*/
}

size_t Print::print(unsigned long n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  if (base == 0) {
          return write(n);
      }
      return printNumber(n, base);*/
}

size_t Print::print(long long n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  int t = 0;
      if (base == 10 && n < 0) {
          t = print('-');
          n = -n;
      }
      return printNumber(static_cast<unsigned long long>(n), base) + t;*/
}

size_t Print::print(unsigned long long n, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    if (base == 0)
    {
        return write(n);
    }
    return printNumber(n, base);
}

size_t Print::print(const Printable &x)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return x.printTo(*this);*/
}

size_t Print::println(void)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    return print("\r\n");
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*    return _println<const __FlashStringHelper*>(ifsh);*/
}

size_t Print::println(const String &s)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    return _println(s);
}

size_t Print::println(const char c[])
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    return _println(c);
}

size_t Print::println(char c)
{
    std::cout << __func__ << " " << __LINE__ << " data: " << c << std::endl;

    return _println(c);
}

size_t Print::println(unsigned char b, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println(b, base);*/
}

size_t Print::println(int num, int base)
{
    /* return _println(num, base);*/
}

size_t Print::println(unsigned int num, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*    return _println(num, base);*/
}

size_t Print::println(long num, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println(num, base);*/
}

size_t Print::println(unsigned long num, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println(num, base);*/
}

size_t Print::println(long long num, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*   return _println(num, base);*/
}

size_t Print::println(unsigned long long num, int base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println(num, base);*/
}

size_t Print::println(double num, int digits)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println(num, digits);*/
}

size_t Print::println(const Printable &x)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    /*  return _println<const Printable&>(x);*/
}

// Private Methods /////////////////////////////////////////////////////////////

template <typename T, typename... P>
inline size_t Print::_println(T v, P... args)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    size_t n = print(v, args...);
    n += println();
    return n;
};

template <typename T>
size_t Print::printNumber(T n, uint8_t base)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;

    char buf[8 * sizeof(n) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2)
    {
        base = 10;
    }

    do
    {
        auto m = n;
        n /= base;
        char c = m - base * n;

        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while (n);

    return write(str);
}

template <>
size_t Print::printNumber(double number, uint8_t digits)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    /*  char buf[40];
      return write(dtostrf(number, 0, digits, buf));
      */
}
