#include <FastLED.h>
#define PACKET_SIZE 256
void setup() 
{ 
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.println("started");
}
int getMsgFromPacket(char msg[])
{
  memset(msg,0,256);
  if(Serial.read() != '!')
    return 0;
  char expectedPacketLength = Serial.read();
  if(Serial.read() != ':')
    return 0;
  char packetLength = Serial.readBytesUntil('\n',msg,expectedPacketLength+1);
  if(packetLength+3 == expectedPacketLength)
    return 1;
  else return 0;
}

void loop() 
{ 
//  char msg[] = "!8:test\n";
  char recv[PACKET_SIZE] = {0};
//  msg[1] = 8;
//  Serial.print(msg);
  delay(1000);
  if (Serial.available() > 0)
  {
      getMsgFromPacket(recv);
      Serial.print(recv);
      Serial.flush();
  }

//  else
//  {
//    //Serial.println("not available");
//    delay(1000);
//  }

}
