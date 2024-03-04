#include "HomeSpan.h" 
#include "ProjectAddon.h"

void setup() {
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"Arduino Nano ESP32 HomeSpan");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      
  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Storage Box");
    new DEV_StorageBox(5, 6);    
} 

void loop(){
  homeSpan.poll();
}