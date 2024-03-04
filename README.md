# Storage Box v2
For this project, I created a Storage Box that acts as a Vallet Tray.

## Storage Box v1: Offline only
The storage box can be opened by either waving the hand in front of a distance sensor, either by pressing a button on a remote control. The box features two modes: autonomous, which closes the box automatically after it was opened, and manual, which closes the box manually by repeading one of the aforementioned actions.

### Components used
  *  Arduino Uno R3
  *  Ultrasonic distance sensor
  *  Servomotor
  *  IR reciever and remote control
  *  Speaker
  *  Small breadboard and wires for connectivity
![storage_box_diagram](https://github.com/bimj0rk/StorageBox-v2/assets/37622282/8eb6e6be-e4b6-4a80-abb5-5abab5d2552b)

### Hardware design
I chose a small box from IKEA for this project. There are 5 holes drilled: three in the front for the ultrasonic sensor and speaker, one on the top for the IR reciever, and one in the back for the wires. The servomotor was mounted using double-sided adhesive tape and black duck tape, to match the interior. The duck tape was also used to hide the wires inside.
![storage_box_overview](https://github.com/bimj0rk/StorageBox-v2/assets/37622282/97a76f1d-2b39-4724-a6df-ce0db81b5666)
![storage_box_inside](https://github.com/bimj0rk/StorageBox-v2/assets/37622282/267f40cc-f07d-4b82-83a2-246765b323f1)
![storage_box_connections](https://github.com/bimj0rk/StorageBox-v2/assets/37622282/a62e5ac1-eaa7-464e-a190-c6437cad00cf)

### Software design
For the software part, I used only libraries publicly available within the Arduino IDE. The program features four main functions:
  * One that translates the hexadecimal codes recieved from the remote control:
  ```
  void translateIR(){
    switch(results.value){
      case 0xFF629D: //CH button, used for autonomous
        autonomousMode();
        break;
      
      case 0xFFA857: //+ button, used for manual open
        manualOverrideOpen();
        break;

      case 0xFFE01F: //- button, used for manual close
        manualOverrideClose();
        break;

      default:
        Serial.println("Button not found");
    }
  }
  ```
  * One that dictates autonomous mode (open slowly, wait 8 seconds, play warning sound, wait another 2 seconds, close):
  ```
  void autonomousMode(){
    Serial.println("Autonomous mode");

    for(position = 0; position <= 115; position++){ 
      servoMotor.write(position);            
      delay(15);
    }

    delay(8000); 

  
    digitalWrite(activeBuzzer, HIGH);
    delay(1);
    digitalWrite(activeBuzzer, LOW);

   
    delay(2000);

    servoMotor.write(20);

    Serial.println("Autonomous mode ended");
  }
  ```
  * and one for each manual open and close:
  ```
  void manualOverrideOpen(){
    Serial.println("Manual open");

    digitalWrite(activeBuzzer, HIGH);
    delay(1);
    digitalWrite(activeBuzzer, LOW);
    delay(1000);

    for(int position = 0; position <= 115; position++){
      servoMotor.write(position);            
      delay(15);
    }

    digitalWrite(activeBuzzer, HIGH);
    delay(1);
    digitalWrite(activeBuzzer, LOW);
    delay(1);

    Serial.println("Manual open ended");
  }

  void manualOverrideClose(){
    Serial.println("Manual close");

    digitalWrite(activeBuzzer, HIGH);
    delay(1);
    digitalWrite(activeBuzzer, LOW);
    delay(1000);

    servoMotor.write(20);

    digitalWrite(activeBuzzer, HIGH);
    delay(1);
    digitalWrite(activeBuzzer, LOW);
    delay(1);

    Serial.println("Manual close ended");
  }  
  ```

## Storage Box v2: Online mode
For the second version, I upgraded the box such that it can be opened and closed via HomeKit.

### Upgrades
Instead of the Arduino Uno R3, I used the Arduino Nano ESP32, which can access my network and thus connect to HomeKit.
The library used, HomeSpan (https://github.com/HomeSpan/HomeSpan), allows the Arduino to act as a HomeKit hub and device at the same time.
I removed all sensors and added one more servomotor, for stability.
In the Home app, the box appears as a window blind, as it allows for incremental opening and closing, should it be needed.

https://github.com/bimj0rk/StorageBox-v2/assets/37622282/8b8964b3-5811-4f42-bae6-1a265eb3af62
