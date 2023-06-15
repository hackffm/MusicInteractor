#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int led = 13;

int solenoid_1 = 34;
int solenoid_2 = 35;
int solenoid_3 = 36;
int solenoid_4 = 37;
int solenoid_5 = 38;

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.

    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    digitalWrite(led, HIGH); 
    Serial.println("handleNoteOn");
    Serial.print("channel: ");
    Serial.println(channel);
    Serial.print("pitch: ");
    Serial.println(pitch);
    Serial.print("velocity: ");
    Serial.println(velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    digitalWrite(led, LOW); 
    Serial.println("handleNoteOff");
    Serial.print("channel: ");
    Serial.println(channel);
    Serial.print("pitch: ");
    Serial.println(pitch);
    Serial.print("velocity: ");
    Serial.println(velocity);
}

// the setup routine runs once when you press reset:
void setup() {
    // initialize the digital pin as an output.
    pinMode(led, OUTPUT);
    pinMode(solenoid_1, OUTPUT);
    digitalWrite(solenoid_1, LOW);    // turn the LED off by making the voltage LOW

    pinMode(solenoid_2, OUTPUT);
    digitalWrite(solenoid_2, LOW);    // turn the LED off by making the voltage LOW

    pinMode(solenoid_3, OUTPUT);
    digitalWrite(solenoid_3, LOW);    // turn the LED off by making the voltage LOW

    pinMode(solenoid_4, OUTPUT);
    digitalWrite(solenoid_4, LOW);    // turn the LED off by making the voltage LOW

    pinMode(solenoid_5, OUTPUT);
    digitalWrite(solenoid_5, LOW);    // turn the LED off by making the voltage LOW

    Serial.begin(19200);

    Serial.println("setup done");

    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(3);
}




// the loop routine runs over and over again forever:
void loop() {
    MIDI.read();

    /*
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(solenoid_1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);               // wait for a second
    digitalWrite(solenoid_1, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(400);               // wait for a second

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(solenoid_2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);               // wait for a second
    digitalWrite(solenoid_2, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(400);               // wait for a second

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(solenoid_3, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);               // wait for a second
    digitalWrite(solenoid_3, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(400);               // wait for a second

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(solenoid_4, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);               // wait for a second
    digitalWrite(solenoid_4, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(400);               // wait for a second

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(solenoid_5, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);               // wait for a second
    digitalWrite(solenoid_5, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(400);               // wait for a second
    */
}

