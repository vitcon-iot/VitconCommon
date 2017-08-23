/*
 * VitconNTC.h
 *
 * 2017-08-23 jjh
 * NTC센서를 사용하기 위한 라이브러리.
 */

#ifndef _VITCONNTC_H_
#define _VITCONNTC_H_

#define NTC_SAMPLES 20 // moving average count
#define NTC_INIT_RESISTOR 10000.0 // 10 kohm
#define NTC_MAXADC 1023.0 // maximum ADC value (5V)
#define NTC_ABSOULTE_ZERO 273.15

namespace vitcon
{
	class VitconNTC
	{
	private:
	  int samples[NTC_SAMPLES];
	  int index;
	  float mResistor;

	  float t0; // nominal temperature of NTC sensor
	  float r0; // nominal resistance of NTC sensor
	  float b; // coefficient of NTC sensor
	  float t; // calculated when SetADC(int) or GetTemperature(int) have been called
	  void Init(float t0, float r0, float b);
	  void CalculateTemperature();
	public:
	  VitconNTC();
	  VitconNTC(float t0, float r0, float b);
	  void SetADC(int adc);
	  void SetResistor(float resistor);
	  float GetTemperature();
	  float GetTemperature(int adc); // combined GetTemperature with SetADC
	};
}

#endif /* MODLINKNTC_H_ */
