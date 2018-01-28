// Based on Henry's Bench IR Remote Tutorial
// An IR detector/demodulator must be connected to the input RECV_PIN.
// An IR LED must be connected to the output PWM pin 3.
 
#include <IRremote.h>

int IR_PIN = 4;
int IR_GND_PIN = 5;
int IR_VCC_PIN = 6;

IRrecv irDetect(IR_PIN);
IRsend irsend;

decode_results irIn;

unsigned long lastCode;

//unsigned int  onOff[67] = {4400,4450, 550,1650, 550,1650, 600,500, 550,550, 550,550, 600,500, 550,1650, 550,550, 550,1650, 550,1650, 600,500, 550,550, 600,1600, 600,500, 550,1700, 550,500, 550,1700, 550,550, 600,500, 550,550, 600,500, 550,550, 600,500, 550,550, 550,550, 600,1600, 550,1650, 550,1650, 550,1650, 550,1650, 550,1650, 550,1650, 550};  // SAMSUNG C2CA807F
//unsigned int  volUp[67] = {4450,4400, 600,1650, 550,1650, 550,550, 550,550, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,1650, 550,550, 550,550, 550,1650, 600,500, 550,1650, 600,500, 550,1650, 550,1650, 550,550, 600,500, 550,1650, 600,1600, 600,550, 550,550, 550,550, 550,500, 600,1650, 550,1650, 550,550, 550,550, 550,1650, 550,1650, 550};  // SAMSUNG C2CACC33
//unsigned int  volDown[67] = {4450,4400, 600,1650, 550,1650, 550,550, 550,550, 550,550, 550,550, 550,1650, 600,500, 550,1650, 550,1650, 550,550, 550,550, 550,1650, 600,500, 550,1600, 650,500, 550,1650, 550,1650, 550,550, 550,1650, 550,1650, 550,1650, 600,500, 600,500, 600,500, 600,500, 550,1700, 550,550, 550,550, 550,500, 600,1650, 550,1600, 600};  // SAMSUNG C2CADC23


void setup() {
    // Serial.begin(115200);
    irDetect.enableIRIn(); // Start the Receiver
    pinMode(LED_BUILTIN ,OUTPUT);

    // IR receiver power pins
    pinMode(IR_VCC_PIN, OUTPUT);
    digitalWrite(IR_VCC_PIN, HIGH);
    pinMode(IR_GND_PIN, OUTPUT);
    digitalWrite(IR_GND_PIN, LOW);
}

void loop() {
    if (irDetect.decode(&irIn)) {
        decodeIR();
        irDetect.resume(); // Receive the next value
        irDetect.enableIRIn(); // Re-enable receiver
    }
}


void decodeIR() { // Indicate what key is pressed
    switch(irIn.value) {
        case 0x20DF10EF:  // ON/OFF
            digitalWrite(LED_BUILTIN, HIGH);
            // Serial.println("On/off"); 
            lastCode = 0xC2CA807F;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0x20DF40BF:  // Vol+
            digitalWrite(LED_BUILTIN, HIGH);
            // Serial.println("Vol up"); 
            lastCode = 0xC2CACC33;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0x20DFC03F:  // Vol-
            digitalWrite(LED_BUILTIN, HIGH);
            // Serial.println("Vol down"); 
            lastCode = 0xC2CADC23;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0x20DF906F:  // Mute
            digitalWrite(LED_BUILTIN, HIGH);
            // Serial.println("Mute"); 
            lastCode = 0xC2CA9C63;
            irsend.sendSAMSUNG(lastCode, 32);
            break;
            
        case 0xFFFFFFFF:  
            // Serial.println("Repeat"); 
            if (lastCode != 0){
                digitalWrite(LED_BUILTIN, HIGH);
                irsend.sendSAMSUNG(lastCode, 32);
            }
            break;

        default: 
            // Serial.println("Other"); 
            lastCode = 0;
            break;

    }
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
    
    // Serial.println(lastCode,HEX);
}
