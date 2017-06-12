/**
 * Created by Park, Nil on 2016-12-16.
 * Last Revision: 2017-05-30
 *
 * 본 모듈은 SHARP 전자의 10 ~ 80cm 거리를 IR 방식으로 측정하는 GP2Y0A21YK 거리센서의 구동을 위한 라이브러리다.
 *
 * Park, Nil (2017-05-30): 네임 스페이스 추가
 */

#ifndef VITCON_GP2Y0A21YK_H_
#define VITCON_GP2Y0A21YK_H_

#include <stdint.h>
namespace vitcon
{
  class GP2Y0A21YK
  {
  private:
    const float MIN_DIST = 10;
    const float MAX_DIST = 80;
    const int MIN_SIG = 500;
    const int MAX_SIG = 80;
    const float OFFSET = 20.0;
    const float BASE = 4800.0;
    uint8_t mPin;
  public:
    GP2Y0A21YK(uint8_t pin);
    float GetDistance();
  };
}



#endif /* VITCON_GP2Y0A21YK_H_ */
