#include <VitconNTC.h>

#define THERMISTORPIN A0 // Analog Input for Thermistor

// 25 Celsius - 10 Kohm, B = 4200 for NTC-10KD-5J
// There may error rate depending on the thermistor specification.
// Please change the values
#define NTC_NORM_TEMPERATURE 25.0
#define NTC_NORM_RESISTANCE 10000.0
#define NTC_DIVIDER_RESISTANCE 10000.0
#define NTC_B_VALUE 4200

using namespace vitcon;

VitconNTC ntc(NTC_NORM_TEMPERATURE, NTC_NORM_RESISTANCE, NTC_B_VALUE);

void setup()
{
  Serial.begin(115200);
  ntc.SetResistor(NTC_DIVIDER_RESISTANCE);
}

void loop()
{
  int raw_adc = analogRead(THERMISTORPIN);
  float temperature = ntc.GetTemperature(raw_adc);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(", Raw: ");
  Serial.println(raw_adc);

  delay(100);
}

