/*
 * VitconNTC.cpp
 *
 * 2017-08-23 jjh

 * VitconNTC.h의 주석을 참고.
 */

#include "VitconNTC.h"
#include "Arduino.h"
#include <Math.h>

using namespace vitcon;

VitconNTC::VitconNTC()
{
  // Based on NTC-10KD-5J
  Init(25.0, 10000.0, 4200.0);
}

VitconNTC::VitconNTC(float t0, float r0, float b)
{
  Init(t0, r0, b);
}

void VitconNTC::Init(float t0, float r0, float b)
{
  mResistor = NTC_INIT_RESISTOR;
  this->t0 = t0;
  this->r0 = r0;
  this->b = b;
  t = t0;

  // nominal adc at r0 :   Amax * R0 / (R1 + R0)
  // came from   R / (R + R1) = A / Amax
  float adc = NTC_MAXADC * r0 / (mResistor + r0);
  for (int i = 0; i < NTC_SAMPLES; i++)
  {
    samples[i] = (int)adc;
  }
  index = 0;

  // String formatter
//  str[0] = ' ';
//  str[1] = ' ';
//  str[2] = '2';
//  str[3] = '5';
//  str[4] = '.';
//  str[5] = '0';
//  str[6] = '0';
//  str[7] = '\0';
}

void VitconNTC::CalculateTemperature()
{
  // Moving average
  float avg = 0;
  for (int i = 0; i < NTC_SAMPLES; i++)
  {
    avg += (float)samples[i];
  }
  avg /= NTC_SAMPLES;
  // Get NTC Resistance :   R1 / ( Amax / A - 1 )
  // came from   R / (R + R1) = A / Amax
  float r = mResistor / (NTC_MAXADC / avg - 1);
  // Get Temperature :   1 / (1 / T0 + 1 / B * (ln (R / R0))
  // came from   steinhart equation 1 / T = 1 / T0 + 1 / B * ln (R / R0) in absolute temperature for T and T0
  //return (t0 + b / log (r / r0));
  t = (1.0 / (1.0 / (NTC_ABSOULTE_ZERO + t0) + 1.0 / b * log (r / r0))) - NTC_ABSOULTE_ZERO;
}

void VitconNTC::SetADC(int adc)
{
  samples[index] = adc;
  index = (index + 1) % NTC_SAMPLES;
  CalculateTemperature();
}

void VitconNTC::SetResistor(float resistor)
{
	mResistor = resistor;
}

float VitconNTC::GetTemperature()
{
  return t;
}

float VitconNTC::GetTemperature(int adc)
{
  SetADC(adc);
  return t;
}
