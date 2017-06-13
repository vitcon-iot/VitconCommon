/**
 * Created by Park, Nil on 2017-06-13.
 * Last Revision: 2017-06-13
 *
 * Example Explanation:
 *   4-digit FND module shows distance came from IR distance sensor GP2Y0A21YK(Sharp) in cm.
 *   The FND is driven by SAA1064T led driver IC. The IC is TWI interface.
 */

#include <VitconSAA1064T.h>
#include <VitconGP2Y0A21YK.h>

using namespace vitcon;

SAA1064T fnd;
GP2Y0A21YK sensor(A0);

void setup()
{
  SAA1064T::Init();
}

void loop()
{
  float f_dist = sensor.GetDistance();
  uint16_t i_dist = f_dist * 100.0;
  fnd.Number(i_dist);
  fnd.Dot(1);
  fnd.Send();
  delay(100);
}

