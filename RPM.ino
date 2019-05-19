/////////////////////////////////////////////////////////////////////
// This is a simple example of sending CAN messages with 11bit id's
//
// https://matthewcmcmillan.blogspot.com
// Twitter: @matthewmcmillan
//

#include "mcp_can.h"
#include <SPI.h>

MCP_CAN CAN(10); //CAN CS  pin

int sensorPin = A0; //Pot for adusting value
int sensorValue = 0;
int cantxValue = 0;

void setup()
{
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN.begin(CAN_500KBPS) ==CAN_OK) Serial.print("CAN init ok\r\n");
  else Serial.print("CAN init failed\r\n");
}

void loop()
{
  sensorValue = analogRead(sensorPin);  //Read the value of the pot
  cantxValue = sensorValue / 30; //Divide by 4 to get us in the 0-255 range
  Serial.print("cantxValue: ");
  Serial.print(cantxValue);
  Serial.println();
  //Create data packet for CAN message
  unsigned char canMsg[8] = {0x00, cantxValue, cantxValue, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
  // format:    (id, id_type, dlc, data buf)
  CAN.sendMsgBuf(0x308, 0, 8, canMsg);
  delay(20);
}
