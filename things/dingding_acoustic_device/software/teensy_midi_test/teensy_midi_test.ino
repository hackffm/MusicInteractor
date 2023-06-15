// USB MIDI receive example, Note on/off -> LED on/off
// contributed by Alessandro Fasan

int ledPin = 13;

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Do whatever you want when a note is pressed.

  // Try to keep your callbacks short (no delays ect)
  // otherwise it would slow down the loop() and have a bad impact
  // on real-time performance.
  digitalWrite(ledPin, HIGH); 
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
  digitalWrite(ledPin, LOW); 
  Serial.println("handleNoteOff");
  Serial.print("channel: ");
  Serial.println(channel);
  Serial.print("pitch: ");
  Serial.println(pitch);
  Serial.print("velocity: ");
  Serial.println(velocity);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(19200);



  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn) ;
  digitalWrite(ledPin, HIGH);
  delay(400);                 // Blink LED once at startup
  digitalWrite(ledPin, LOW);
  Serial.println("setup done");
}

void loop() {
  usbMIDI.read();
}