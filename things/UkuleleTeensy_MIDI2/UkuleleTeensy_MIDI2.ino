
#include "chords.h"

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
//#include <SerialFlash.h>
#include "TimerThree.h"  
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* sound generation
 * There are four upper and four lower pins. Only the upper pins are used. These are equivalent for the 4 Uke strings
 * By using infrared diodes and receivers, the string triggers are detected.
 * 
 * There are 10 positions on the neck where 10 reed contacts are actuated by moving a tube segment containing a magnet
 * the 10 reed contacts switch different resistors and therefore modify the voltage at analog input PinBund 
 * by checking the analog values between min and max from 2 arrays, the position can be determined quite exactly
 * and different chords can be selected 
 * 
 * 
 * 
 * 
 */


#define maxbund 10
#define maxstrings 4
#define alle_x_us 1000*20
#define valConfThres 10
#define millisThres 1000
#define millisThresFactor 10
#define multiplierBund 1


const int mchannel = 7; 
const float freq1[maxbund+1] = {NOTE_G3, NOTE_G3, NOTE_Gs3, NOTE_A3, NOTE_As3, NOTE_B3, NOTE_C4, NOTE_Cs4, NOTE_D4, NOTE_Ds4, NOTE_E4};
const float freq2[maxbund+1] = {NOTE_C3, NOTE_C3, NOTE_Cs3, NOTE_D3, NOTE_Ds3, NOTE_E3, NOTE_F3, NOTE_Fs3, NOTE_G3, NOTE_Gs3, NOTE_A3};
const float freq3[maxbund+1] = {NOTE_E3, NOTE_E3, NOTE_F3, NOTE_Fs3, NOTE_G3, NOTE_Gs3, NOTE_A3, NOTE_As3, NOTE_B3, NOTE_C4, NOTE_Cs4};
const float freq4[maxbund+1] = {NOTE_A3, NOTE_A3, NOTE_As3, NOTE_B3, NOTE_C4, NOTE_Cs4, NOTE_D4, NOTE_Ds4, NOTE_E4, NOTE_F4, NOTE_Fs4};

// Chords :                      none,    C,       A,        G,       E,        D,       F,       G7,       Am,      Em,       Dm
const float afreq1[maxbund+1] = {NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_A3};
const float afreq2[maxbund+1] = {NOTE_C3, NOTE_C3, NOTE_Cs3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_C3, NOTE_E3, NOTE_D3};
const float afreq3[maxbund+1] = {NOTE_E3, NOTE_E3, NOTE_E3, NOTE_G3, NOTE_Gs3, NOTE_Fs3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_G3, NOTE_F3};
const float afreq4[maxbund+1] = {NOTE_A3, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_A3};


int config_1[10];
int config_2[10];
int PeterMode=false;

//digital inputs for upper 4 pins
const int PinO_1=3;
const int PinO_2=5;
const int PinO_3=7;
const int PinO_4=9;

//digital inputs for lower 4 pins
const int PinU_1=4;
const int PinU_2=6;
const int PinU_3=8;
const int PinU_4=10;

const int PinsO[] = {3, 5, 7, 9};
const int NotenSaiten[] = { 62, 64, 65, 67 };
int PinsOStatus[] = {0, 0, 0, 0};

const int PinTast_1=12;

const int PinConf_1 =29;
const int PinConf_2 =30;
const int PinPlay_1 =31;
const int PinPlay_2 =32;

//analog
const int PinBund=15;
const int PinConfVal=35;
int cct = 0;

// arrays for min and max values for detection of bund position
int lower[maxbund] = {87,181,306,407,500,596,690,830,920,1019};
int upper[maxbund] = {100,199,326,427,523,616,710,850,940,1024};
byte bund = 0, digiVal=0, i,n,t, last_val=0, flag_peak=1;
byte val1 = 1, val2 = 1, val3 = 1, val4 = 1, val5 = 1, val6 = 1, val7 = 1, val8 = 1;
byte ValConf_1 = 0, ValConf_2 = 0, ValPlay_1 = 0, ValPlay_2 = 0, ValTast_1 = 0;
int valAna = 0, valConf = 0, valConfOld=0, valConfDiff = 0, count = 100;
const int ledPin = 13;
int buttonState = 0;         // variable for reading the pushbutton status
const int finger_delay = 100;
const int hand_delay = 220;
unsigned long millis_old=0, millis_diff=0;
int newgain = 1;
byte dispPresent = false;
const char uString1[] = "Ukulele\n";
const char uString2[] = "BASS ";

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(2);      // 2:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.print(uString1);
  display.println(uString2);

  display.println("Teensy");
  display.println("USBMIDI2");
  display.display();
  delay(200);
}


void setup() {
  Serial.begin(38400); 
  delay(200); // Pause for .2 seconds
  pinMode(ledPin, OUTPUT);
  pinMode(PinO_1, INPUT_PULLUP);     
  pinMode(PinO_2, INPUT_PULLUP);     
  pinMode(PinO_3, INPUT_PULLUP);     
  pinMode(PinO_4, INPUT_PULLUP);     
  pinMode(PinU_1, INPUT_PULLUP);     
  pinMode(PinU_2, INPUT_PULLUP);     
  pinMode(PinU_3, INPUT_PULLUP);     
  pinMode(PinU_4, INPUT_PULLUP);     
  pinMode(PinConf_1, INPUT_PULLUP);     
  pinMode(PinConf_2, INPUT_PULLUP);     
  pinMode(PinPlay_1, INPUT_PULLUP);     
  pinMode(PinPlay_2, INPUT_PULLUP);     
  pinMode(PinTast_1, INPUT_PULLUP);     
  Timer3.initialize(alle_x_us);
  Timer3.attachInterrupt(inputs);

  delay(100);
  valConfOld = analogRead(PinConfVal);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println("SSD1306 allocation failed");
    dispPresent = false;
  } else {
    Serial.println("SSD1306 positive response: ");
    dispPresent = true;  
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
     //turn 180degr
    delay(200); // Pause for .2 seconds
    display.setRotation(2);
    delay(200); // Pause for .2 seconds
  
    display.display();
    testdrawchar();      // Draw characters of the default font
    delay(700);
  }
/*
  */
}

void calcDiff() {
  millis_diff = millis() - millis_old;
  millis_old = millis();
  if (millis_diff < 260) {
    newgain = -(millis_diff / 130) + 2;
  }
}



void sendMidiOn(int note, int velo, const int channel) {
  usbMIDI.sendNoteOn(note, velo, channel); 
  /*
  Serial.println("NoteOn:");
  Serial.print(note,DEC);
  Serial.print(" ");
  Serial.print(velo,DEC);
  Serial.print(" ");
  Serial.println(channel,DEC);
  */
 if (dispPresent == true) {
  display.clearDisplay();
  display.setCursor(0, 0); 
  display.println("NoteOn:");
  display.print(note,DEC);
  display.print(" ");
  display.print(velo,DEC);
  display.print(" ");
  display.println(channel,DEC);
  display.display();
 }
    
}
void sendMidiOff(int note, int velo, const int channel) {
  usbMIDI.sendNoteOff(note, velo, channel); 
  /*
  Serial.println("NoteOff:");
  Serial.print(note,DEC);
  Serial.print(" ");
  Serial.print(velo,DEC);
  Serial.print(" ");
  Serial.println(channel,DEC);
  */
  
 if (dispPresent == true) {
  display.clearDisplay();
  display.setCursor(0, 0); 
  display.println("NoteOff:");
  display.print(note,DEC);
  display.print(" ");
  display.print(velo,DEC);
  display.print(" ");
  display.println(channel,DEC);
  display.display();
  }
 
}


void loop() {
 
 digitalWrite(ledPin, HIGH);   // set the LED on
 delay(finger_delay);
 digitalWrite(ledPin, LOW);   // set the LED on
 delay(finger_delay);
}


int vorheriger_bund = -1;
int aktueller_bund = -1;

void inputs() {
  uint32_t sum = 0;
  for(int i=0; i<2; i++) {
    sum += analogRead(PinBund);
  }
  valAna = sum / 2;
  
  if (cct++ > 40) {
    cct=0;
  }
  
  aktueller_bund = -1;
  for (int i=0;i<maxbund;i++) {
    if ((valAna >= lower[i]) && (valAna <= upper[i])) { 
      aktueller_bund = i;
    }
  }

  if(aktueller_bund != vorheriger_bund) {
    //Serial.println(valAna,DEC);
    if(vorheriger_bund != -1) sendMidiOff(vorheriger_bund + 48, 0, mchannel);
    if(aktueller_bund != -1) { 
      sendMidiOn(aktueller_bund + 48, 99, mchannel);
    }
    
    vorheriger_bund = aktueller_bund;
  }
  

  for(int i=0; i<=3; i++) {
    if(digitalRead(PinsO[i])) {
      // unten
      if(PinsOStatus[i] == 0) {
        PinsOStatus[i] = 1;
        sendMidiOn(NotenSaiten[i], 99, mchannel);
      }
      
    } else {
      // oben
      if(PinsOStatus[i] == 1) {
        PinsOStatus[i] = 0;
        sendMidiOff(NotenSaiten[i], 0, mchannel);
      }      
    }
    
  }

 
  
}
  
