/*
  VitconHT16K33.cpp
  FND제어용 HT16K33 드라이버 모듈
  2017-12-05 jjh

  VitconHT16K33.h 주석 참조
*/
#include "VitconHT16K33.h"
#include <Wire.h>

using namespace vitcon;

static const uint8_t FND_DIGITS[10]
  = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
      0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111
    }; // from 0 to 9
static const uint8_t FND_DIGIT = 0b01111111;
static const uint8_t FND_DOT = 0b10000000;
static const uint8_t FND_MINUS = 0b01000000;
static const uint8_t FND_CLEAR = 0b00000000;

HT16K33::HT16K33()
{ 
  mAddress = 0x70;
  Clear();
}

HT16K33::HT16K33(uint8_t addr)
{
  mAddress = addr;
  Clear();
}

void HT16K33::Init()
{
  Wire.begin(mAddress);
  //Turn on oscillator
  SendByte(0x21);

  //Blink off
  SendByte(0x81);
}

void HT16K33::SetBrightness(uint8_t val)
{
  if ( val > 15 ) val = 15;
  SendByte(0xE0 | val);
}

void HT16K33::Send()
{
  Wire.beginTransmission(mAddress);
  Wire.write(0x00);
  for(int i=0;i<DIGITS;i++)
  {
    Wire.write(mDigits[i]);
    Wire.write(0xFF);
    if( i == 1 )
    {
      Wire.write(0x00);
      Wire.write(0x00);
    }
  }
  Wire.endTransmission();
  
}

void HT16K33::Number(uint16_t value)
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
      mDigits[i] = (FND_DIGITS[r / m] & FND_DIGIT) | (mDigits[i] & ~FND_DIGIT);
      r %= m;
      m /= 10;
    }
  }
}

void HT16K33::Number(uint8_t index, uint8_t value)
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

void HT16K33::Dot(uint8_t index)
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

void HT16K33::Minus(uint8_t index)
{
  if (index < DIGITS)
  {
    mDigits[index] = (FND_MINUS & FND_DIGIT) | (mDigits[index] & ~FND_DIGIT);
  }
}

void HT16K33::Byte(uint8_t index, uint8_t value)
{
  if (index < DIGITS)
  {
    mDigits[index] = value;
  }
}

void HT16K33::Clear()
{
  for (uint8_t i = 0; i < DIGITS; i++)
  {
    mDigits[i] = FND_CLEAR;
  }
}

void HT16K33::Clear(uint8_t index)
{
  if (index < DIGITS)
  {
    mDigits[index] = FND_CLEAR;
  }
}

void HT16K33::SendByte(uint8_t data)
{
  Wire.beginTransmission(mAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void HT16K33::SendBytes(uint8_t* data, uint16_t length)
{
  Wire.beginTransmission(mAddress);
  for (int i = 0; i < length; i++)
  {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

