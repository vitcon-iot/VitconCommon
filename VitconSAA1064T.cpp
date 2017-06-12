/**
 * Created by Park, Nil on 2016-08-11.
 * Last Revision: 2017-05-30
 *
 * VitconSAA1064T.h의 Description 참조
 */

#include "VitconSAA1064T.h"
#include <Wire.h>
#include <math.h>

using namespace vitcon;

static const uint8_t SAA1064T_ADDR_COUNT = 4;
static const uint8_t SAA1064T_ADDR[SAA1064T_ADDR_COUNT] = { 0x38, 0x39, 0x40, 0x41 };
static const uint8_t SAA1064T_CONFIG0 = 0b00000000;
static const uint8_t SAA1064T_CONFIG1 = 0b01000111;

static const uint8_t FND_DIGITS[10]
  = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
      0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111 }; // from 0 to 9
static const uint8_t FND_DIGIT = 0b01111111;
static const uint8_t FND_DOT = 0b10000000;
static const uint8_t FND_MINUS = 0b01000000;
static const uint8_t FND_CLEAR = 0b00000000;

void SAA1064T::Init()
{
  Wire.begin();
  for (uint8_t i = 0; i < SAA1064T_ADDR_COUNT; i++)
  {
    Wire.beginTransmission(SAA1064T_ADDR[i]);
    Wire.write(SAA1064T_CONFIG0);
    Wire.write(SAA1064T_CONFIG1);
    Wire.endTransmission();
  }
}

SAA1064T::SAA1064T()
{
  mAddr = SAA1064T_ADDR[0];
  Clear();
}
SAA1064T::SAA1064T(uint8_t addr)
{
  if (addr >= SAA1064T_ADDR_COUNT)
    addr = SAA1064T_ADDR_COUNT - 1;
  mAddr = SAA1064T_ADDR[addr];
  Clear();
}

void SAA1064T::Send()
{
  Wire.beginTransmission(mAddr);
  Wire.write(1);
  for (uint8_t i = 0; i < DIGITS; i++)
  {
    Wire.write(mDigits[i]);
  }
  Wire.endTransmission();
}

void SAA1064T::Number(uint16_t value)
{
  if (value > pow(10, DIGITS) - 1)
  {
    for (uint8_t i = 0; i < DIGITS; i++)
    {
      mDigits[i] = (FND_DIGITS[9] & FND_DIGIT) | (mDigits[i] & ~FND_DIGIT);
    }
  }
  else
  {
    uint16_t r = value;
    uint16_t m = pow(10, DIGITS - 1);
    for (uint8_t i = 0; i < DIGITS; i++)
    {
      mDigits[i] = (FND_DIGITS[r/m] & FND_DIGIT) | (mDigits[i] & ~FND_DIGIT);
      r %= m;
      m /= 10;
    }
  }
}
void SAA1064T::Number(uint8_t index, uint8_t value)
{
  if (index < DIGITS)
  {
    if (value > 9)
    {
      mDigits[index] = (FND_DIGITS[9] & FND_DIGIT) | (mDigits[index] & ~FND_DIGIT);
    }
    else
    {
      mDigits[index] = (FND_DIGITS[value] & FND_DIGIT) | (mDigits[index] & ~FND_DIGIT);
    }
  }
}

void SAA1064T::Dot(uint8_t index)
{
  for (uint8_t i = 0; i < DIGITS; i++)
  {
    if (index == i)
    {
      mDigits[i] |= FND_DOT;
    }
    else
    {
      mDigits[i] &= ~FND_DOT;
    }
  }
}

void SAA1064T::Minus(uint8_t index)
{
  if (index < DIGITS)
  {
    mDigits[index] = (FND_MINUS & FND_DIGIT) | (mDigits[index] & ~FND_DIGIT);
  }
}

void SAA1064T::Byte(uint8_t index, uint8_t value)
{
  if (index < DIGITS)
  {
    mDigits[index] = value;
  }
}

void SAA1064T::Clear()
{
  for (uint8_t i = 0; i < DIGITS; i++)
  {
    mDigits[i] = FND_CLEAR;
  }
}

void SAA1064T::Clear(uint8_t index)
{
  if (index < DIGITS)
  {
    mDigits[index] = FND_CLEAR;
  }
}
