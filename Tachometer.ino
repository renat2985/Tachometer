#include "SSD1306Wire.h"
SSD1306Wire display(0x3c, 4, 5, GEOMETRY_128_32); //DISPLAY: GPIO4, GPIO5 (NodeMCU - D1, D2)

unsigned long lastflash;
int RPM;
void ICACHE_RAM_ATTR sens() {
  RPM++;
}

void setup() {
Serial.begin(9600);

// Display
display.init();
display.flipScreenVertically();
display.setFont(ArialMT_Plain_16);

// Sensor
attachInterrupt(0,sens,RISING); //SENSOR: GPIO0 (NodeMCU - D3)
}

void loop() {
  display.clear(); // clearing the display
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(40, 0, String(RPM));
  display.drawString(40, 14, String(RPM*60));
  display.display();
  
  noInterrupts();
  Serial.print(RPM);
  Serial.print(" RPM sek / ");
  Serial.print(RPM*60);
  Serial.println("RPM min. "); 
  RPM=0;
  interrupts(); 
  delay(1000);  //1 sek.
}
