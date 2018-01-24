//  Henry's Bench IR Remote Tutorial 1
// An IR detector/demodulator must be connected to the input RECV_PIN.
// An IR LED must be connected to the output PWM pin 3.
 
#include <IRremote.h>

int IR_PIN = 11;

IRrecv irDetect(IR_PIN);

decode_results irIn;

unsigned long lastCode;

unsigned int  onOff[67] = {4400,4450, 550,1650, 550,1650, 600,500, 550,550, 550,550, 600,500, 550,1650, 550,550, 550,1650, 550,1650, 600,500, 550,550, 600,1600, 600,500, 550,1700, 550,500, 550,1700, 550,550, 600,500, 550,550, 600,500, 550,550, 600,500, 550,550, 550,550, 600,1600, 550,1650, 550,1650, 550,1650, 550,1650, 550,1650, 550,1650, 550};  // SAMSUNG C2CA807F
unsigned int  volUp[67] = {4450,4400, 600,1650, 550,1650, 550,550, 550,550, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,1650, 550,550, 550,550, 550,1650, 600,500, 550,1650, 600,500, 550,1650, 550,1650, 550,550, 600,500, 550,1650, 600,1600, 600,550, 550,550, 550,550, 550,500, 600,1650, 550,1650, 550,550, 550,550, 550,1650, 550,1650, 550};  // SAMSUNG C2CACC33
unsigned int  volDown[67] = {4450,4400, 600,1650, 550,1650, 550,550, 550,550, 550,550, 550,550, 550,1650, 600,500, 550,1650, 550,1650, 550,550, 550,550, 550,1650, 600,500, 550,1600, 650,500, 550,1650, 550,1650, 550,550, 550,1650, 550,1650, 550,1650, 600,500, 600,500, 600,500, 600,500, 550,1700, 550,550, 550,550, 550,500, 600,1650, 550,1600, 600};  // SAMSUNG C2CADC23


void setup() {
    //Serial.begin(115200);
    irDetect.enableIRIn(); // Start the Receiver
    pinMode(13,OUTPUT);
}

void loop() {
    if (irDetect.decode(&irIn)) {
        decodeIR();
        irDetect.resume(); // Receive the next value
    }
}


void decodeIR() { // Indicate what key is pressed
    switch(irIn.value) {

        case 0x20DF10EF:  // ON/OFF
            //Serial.println("On/off"); 
            lastCode = 0xC2CA807F;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0x20DF40BF:  // Vol+
            digitalWrite(13,HIGH);
            //Serial.println("Vol up"); 
            lastCode = 0xC2CACC33;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0x20DFC03F:  // Vol-
            digitalWrite(13,LOW);
            //Serial.println("Vol down"); 
            lastCode = 0xC2CADC23;
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        case 0xFFFFFFFF:  
            //Serial.println("Repeat"); 
            irsend.sendSAMSUNG(lastCode, 32);
            break;

        default: 
            break;

    }
    delay(100);
    irDetect.enableIRIn(); // Re-enable receiver
    
    //Serial.println(lastCode,HEX);
}
