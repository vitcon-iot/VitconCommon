/**
 * Created by Park, Nil on 2016-12-16.
 * Last Revision: 2017-05-30
 *
 * VitconGP2Y0A21YK.h의 Description 참조
 */

#include <Arduino.h>
#include "VitconGP2Y0A21YK.h"
using namespace vitcon;

GP2Y0A21YK::GP2Y0A21YK(uint8_t pin)
{
  mPin = pin;
}

float GP2Y0A21YK::GetDistance()
{
  float distance;
  int sig = analogRead(mPin);
  if (sig < MAX_SIG) distance = MAX_DIST;
  else if (sig > MIN_SIG) distance = MIN_DIST;
  else distance = BASE / ((float)sig - OFFSET);
  return distance;
}
