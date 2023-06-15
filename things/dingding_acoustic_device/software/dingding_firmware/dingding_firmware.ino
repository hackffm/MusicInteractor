/*
 * MIDI Solenoids
 *
 * Author: L. Lisseck 
 */ 

#include <MIDIUSB.h>
#include <AccelStepper.h>

// must have both same amount of entries
const byte solenoids[] =      { 36, 37, 38, 35, 34 };
const byte solenoid_notes[] = { 48, 50, 51, 52, 55 };

uint8_t solenoid_count = sizeof(solenoids)/sizeof(solenoids[0]);

uint32_t solenoid_ontime[sizeof(solenoids)/sizeof(solenoids[0])];
uint16_t solenoid_maxtime[sizeof(solenoids)/sizeof(solenoids[0])];

#define DO_DEBUGPRINTS  1

#define MAX_ONTIME 1000

// stepper driver pin definitions
#define STEPPER_PIN_ENABLE  32
#define STEPPER_PIN_MS1  31
#define STEPPER_PIN_MS2  30
#define STEPPER_PIN_SPREAD  29
#define STEPPER_PIN_PDN_UART1  28
#define STEPPER_PIN_PDN_UART2  27
#define STEPPER_PIN_STEP  26
#define STEPPER_PIN_DIR  25

// stepper constants and variables

// the stepper notes positions is initialized with zeros
long stepper_notes_position[] = { 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L };
const byte stepper_notes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };


AccelStepper stepper(1, STEPPER_PIN_STEP, STEPPER_PIN_DIR); // pin 3 = step, pin 6 = direction

const char* pitch_name(byte pitch) {
  static const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  return names[pitch % 12];
}

int pitch_octave(byte pitch) {
  return (pitch / 12) - 1;
}

// returns -1 if not found
int8_t get_solenoid_index(byte pitch) {
  int8_t ret = -1;
  for(uint8_t i = 0; i<solenoid_count; i++) {
    if(solenoid_notes[i] == pitch) {
      ret = i;
      break;
    }
  }
  return(ret);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  int8_t solenoid_index = -2;
  solenoid_index = get_solenoid_index(pitch);
  if(solenoid_index >= 0) {
    solenoid_ontime[solenoid_index] = millis();
    digitalWrite(solenoids[solenoid_index], HIGH);
    solenoid_maxtime[solenoid_index] = MAX_ONTIME;
    if(channel == 1) solenoid_maxtime[solenoid_index] = velocity;
    #ifdef DO_DEBUGPRINTS
    Serial.print("Solenoid port ON:");
    Serial.println(solenoids[solenoid_index]);
    #endif
  }
  
#ifdef DO_DEBUGPRINTS
  Serial.print("Note On: ");
  Serial.print(pitch);
  Serial.print("=");
  Serial.print(pitch_name(pitch));
  Serial.print(pitch_octave(pitch));
  Serial.print(", solenoid=");
  Serial.print(solenoid_index);
  Serial.print(", channel=");
  Serial.print(channel);
  Serial.print(", velocity=");
  Serial.println(velocity);
#endif
}

void noteOff(byte channel, byte pitch, byte velocity) {
  int8_t solenoid_index = -2;
  solenoid_index = get_solenoid_index(pitch);
  if(solenoid_index >= 0) {
    solenoid_ontime[solenoid_index] = 0;
    digitalWrite(solenoids[solenoid_index], LOW);
    #ifdef DO_DEBUGPRINTS
    Serial.print("Solenoid port OFF:");
    Serial.println(solenoids[solenoid_index]);
    #endif
  }
#ifdef DO_DEBUGPRINTS
  Serial.print("Note Off: ");
  Serial.print(pitch_name(pitch));
  Serial.print(pitch_octave(pitch));
  Serial.print(", channel=");
  Serial.print(channel);
  Serial.print(", velocity=");
  Serial.println(velocity);
#endif
}

void controlChange(byte channel, byte control, byte value) {
#ifdef DO_DEBUGPRINTS  
  Serial.print("Control change: control=");
  Serial.print(control);
  Serial.print(", value=");
  Serial.print(value);
  Serial.print(", channel=");
  Serial.println(channel);
#endif
}

void setupStepperDriver() {
    pinMode(STEPPER_PIN_ENABLE, OUTPUT);
    pinMode(STEPPER_PIN_MS1, OUTPUT);
    pinMode(STEPPER_PIN_MS2, OUTPUT);
    pinMode(STEPPER_PIN_SPREAD, OUTPUT);
    pinMode(STEPPER_PIN_PDN_UART1, OUTPUT);
    pinMode(STEPPER_PIN_PDN_UART2, OUTPUT);
    pinMode(STEPPER_PIN_STEP, OUTPUT);
    pinMode(STEPPER_PIN_DIR, OUTPUT);

    // set micro step settings
    // for more detail see manual at https://learn.watterott.com/silentstepstick/pinconfig/tmc2209/
    digitalWrite(STEPPER_PIN_MS1, LOW); 
    digitalWrite(STEPPER_PIN_MS2, HIGH); 
    digitalWrite(STEPPER_PIN_SPREAD, LOW); 


    stepper.setMaxSpeed(10000);
    stepper.setAcceleration(20000);
    stepper.moveTo(60000);
}

void setup() {
  Serial.begin(115200);
  for(uint8_t i = 0; i<solenoid_count; i++) {
    pinMode(solenoids[i], OUTPUT);
    digitalWrite(solenoids[i], LOW);
    solenoid_ontime[i] = 0;
    solenoid_maxtime[i] = MAX_ONTIME;
  }

  // setup stepper driver
  setupStepperDriver();

  // Test all Solenoids
  delay(1000);
  for(uint8_t i = 0; i<solenoid_count; i++) {
    digitalWrite(solenoids[i], HIGH);
    delay(250);
    digitalWrite(solenoids[i], LOW);
    delay(50);
  }
}

void loop() {

  // clear stuck solenoids
  for(uint8_t i = 0; i<solenoid_count; i++) {
    if(solenoid_ontime[i] > 0) {
      if(millis() - solenoid_ontime[i] > solenoid_maxtime[i]) {
        digitalWrite(solenoids[i], LOW);
        solenoid_ontime[i] = 0; 
        #ifdef DO_DEBUGPRINTS
          Serial.print("Solenoid port TIMEOUT OFF:");
          Serial.println(solenoids[i]);
        #endif       
      }
    }
  }
  
  if(Serial.available()) {
    Serial.read();
    //Serial.println(solenoid_count);
  }
  
  midiEventPacket_t rx = MidiUSB.read();
  switch (rx.header) {
    case 0:
      break; //No pending events
      
    case 0x9:
      noteOn(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;
      
    case 0x8:
      noteOff(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;
      
    case 0xB:
      controlChange(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //control
        rx.byte3         //value
      );
      break;
      
    default:
      #ifdef DO_DEBUGPRINTS
      Serial.print("Unhandled MIDI message: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
      #endif
  }
}


void stepperPositionCalibration() {
    
}