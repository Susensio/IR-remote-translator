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


void setup() {
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


void decodeIR() {           // Indicate what key is pressed
    static unsigned long lastCode;
    unsigned long code = 0;

    switch(irIn.value) {
        case 0x20DF10EF:    // ON/OFF
            code = 0xC2CA807F;
            break;

        case 0x20DF40BF:    // Vol+
            code = 0xC2CACC33;
            break;

        case 0x20DFC03F:    // Vol-
            code = 0xC2CADC23;
            break;

        case 0x20DF906F:    // Mute
            code = 0xC2CA9C63;
            break;
            
        case 0xFFFFFFFF:    // Repeat
            code = lastCode;
            break;

        default:        // Not a valid key
            code = 0;
            break;
    }

    if (code != 0){
        digitalWrite(LED_BUILTIN, HIGH);
        irsend.sendSAMSUNG(code, 32);

    }

    lastCode = code;

    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
}
