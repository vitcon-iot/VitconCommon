/**
 * Created by Park, Nil on 2017-04-26.
 * Last Revision: 2017-04-26
 *
 * 본 모듈은 ZIP에서 사용하는 계산 식과 동일한 CRC32의 클래스이다.
 * AVR 전용
 *
 * Park, Nil (2017-03-24): 네임 스페이스 추가, 배열을 프로그램 영역으로 확정
 * Park, Nil (2017-04-26): Get() 함수를 제거하고 uint32_t operator로 변경
 */

#ifndef VITCON_CRC32_H_
#define VITCON_CRC32_H_

#include <stdint.h>

namespace vitcon
{
  const uint32_t CRC32_BASE = 0;
  class CRC32
  {
  private:
    uint32_t mCrc;
  public:
    CRC32();
    CRC32(uint32_t base);
    void Reset();
    void Update(uint8_t b);
    void Update(const uint8_t *bytes, int len);
    operator uint32_t();
  };
  //const uint32_t CRC32_Compute(const uint8_t *bytes, const int len, const uint32_t base);
}

#endif /* VITCON_CRC32_H_ */
