#include <mcp_can_dfs.h>
#include <Nokia_LCD.h>
#include <mcp_can.h>
#include <SPI.h>
#include <SoftwareSerial.h>
Nokia_LCD lcd(3 , 4, 5, 6, 7);

void setup() {
  
  IncializeSerial();
  InicializeLCD();
  InicializeCAN();
  pinMode(8, OUTPUT);
  analogWrite(8, HIGH);   
}

void loop() {

ReceiveSerialData();
}
