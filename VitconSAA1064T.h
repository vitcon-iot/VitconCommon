/**
 * Created by Park, Nil on 2016-08-11.
 * Last Revision: 2017-05-30
 *
 * 본 모듈은 SAA1064T를 사용하는 4-digit FND 구동을 위한 라이브러리이다.
 *
 * Park, Nil (2017-05-30): 네임 스페이스 추가
 */

#ifndef VITCON_SAA1064T_H_
#define VITCON_SAA1064T_H_

#include <stdint.h>

namespace vitcon
{
  const int DIGITS = 4;
  class SAA1064T
  {
  private:
    uint8_t mAddr;
    uint8_t mDigits[DIGITS];
  public:
    static void Init();
    SAA1064T();
    SAA1064T(uint8_t addr);
    void Number(uint16_t value);
    void Number(uint8_t index, uint8_t value);
    void Dot(uint8_t index);
    void Minus(uint8_t index);
    void Byte(uint8_t index, uint8_t value);
    void Clear();
    void Clear(uint8_t index);
    void Send();
  };
}

#endif /* VITCON_SAA1064T_H_ */
