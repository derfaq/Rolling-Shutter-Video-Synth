/*  Tone_RS-VS.ino
 *  
 *  A Very very simple Rolling Shutter Video Synth (RS-VS)
 *  
 *  Description
 *    This scketch generate a tone signal (square) over pin 5,
 *    With a frequencie wich depends on the value of one potentiometer
 *    conected to A0.
 *    
 *  The circuit:
 *    * One potentiometer connected to A0.
 *        Center pin of the potentiometer goes to the analog pin,
 *        side pins of the potentiometer go to +5V and ground
 *    * LED w/ 150 ~ 470 ohm resistor, 
*/

#define LED_PIN 5

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the potentiometer:
  int sensorReading = analogRead(A0);
  Serial.println(sensorReading);
  // map the analog input range
  // to the output pitch range (31 - 1000 Hz)
  int thisPitch = map(sensorReading, 0, 1023, 31, 1000);

  // play the pitch:
  tone(LED_PIN, thisPitch);
  delay(10);        // delay in between reads for stability
}






