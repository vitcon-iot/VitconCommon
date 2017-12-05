/*
  VitconHT16K33.h
  FND제어용 HT16K33 드라이버 모듈
  2017-12-05 jjh
*/
#ifndef _VITCONHT16K33_H_
#define _VITCONHT16K33_H_

#include <Arduino.h>

namespace vitcon
{
  const int DIGITS = 4;
  class HT16K33
  {
    public:
      HT16K33();
      HT16K33(uint8_t addr);
      void Init();
      void SetBrightness(uint8_t val);
      
      void Number(uint16_t value);
      void Number(uint8_t index, uint8_t value);
      void Dot(uint8_t index);
      void Minus(uint8_t index);
      void Byte(uint8_t index, uint8_t value);
      void Clear();
      void Clear(uint8_t index);
      void Send();
      
    private:
      void SendByte(uint8_t data);
      void SendBytes(uint8_t* data, uint16_t length);

      uint8_t mDigits[DIGITS];

      int mAddress;
  };
}

#endif
