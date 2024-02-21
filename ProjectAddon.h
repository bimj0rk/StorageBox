#include <extras/PwmPin.h>

struct DEV_StorageBox: Service::WindowCovering {     
  SpanCharacteristic *current;                     
  SpanCharacteristic *target;                      

  ServoPin *servo;
  ServoPin *servo2;                          

  DEV_StorageBox(uint8_t servoPin, uint8_t servoPin2): Service::WindowCovering(){        
    current = new Characteristic::CurrentPosition(0);     
    target = new Characteristic::TargetPosition(0);       
    target -> setRange(100, 0, -10);  
    
    servo = new ServoPin(servoPin, -90, 0, 2000, 360, 0);
    servo2 = new ServoPin(servoPin2, -90, 0, 2000, 360, 0);
  } 

  boolean update(){                              
    if(target -> updated()){                           
      servo -> set(target -> getNewVal()); 
      servo2 -> set(target -> getNewVal());                     
    }   
    return(true);                          
  }

  void loop(){                                  
    if(current -> getVal() != target -> getVal() && target -> timeVal() > 5000){          
      current -> setVal(target -> getVal());                                      
    }
  } 
};