#include <VitconHT16K33.h>

using namespace vitcon;

HT16K33 fnd;

void setup() {
  fnd.Init();
  delay(1000);
  fnd.Number(1234);
  fnd.Send();
  delay(1000);
  fnd.Number(5678);
  fnd.Send();
  delay(1000);
  fnd.Number(9012);
  fnd.Send();
  delay(1000);
  fnd.Dot(3);
  fnd.Send();
  delay(1000);
  fnd.Dot(2);
  fnd.Send();
  delay(1000);
  fnd.Dot(1);
  fnd.Send();
  delay(1000);
  fnd.Dot(0);
  fnd.Send();
  delay(1000);
  fnd.Number(0, 3);
  fnd.Send();
  delay(1000);
  fnd.Number(1, 4);
  fnd.Send();
  delay(1000);
  fnd.Minus(2);
  fnd.Send();
  delay(1000);
  fnd.Clear(3);
  fnd.Send();
  delay(1000);
  fnd.Byte(1, 0b01110000);
  fnd.Send();
  delay(1000);
  fnd.Clear();
  fnd.Send();
}

void loop(void){                                  
}
