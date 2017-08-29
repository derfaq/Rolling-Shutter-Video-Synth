/*  FullPWM_RS-VS.ino
 *  
 *  A Simple Rolling Shutter Video Synth (RS-VS)
 *  
 *  Description
 *    This scketch generate a PWM signal over pin 10 with a frequency
 *    wich depends on the scan rate of the camera (F_CAM) and the number
 *    of lines that we want create over the screen (lines). Also we can control
 *    the duty cycle by a potentiometer conected to A1.
 *    A fine tunning of frequency is perform manually by turning a potentiometer
 *    conected to A0, and the number of lines can be assignment through the 
 *    serial monitor, just typing it.
 *    
 *  The circuit:
 *    9 fh  
 *    * Two potentiometer connected to analog pin 0, and 1.
 *        Center pin of the potentiometer goes to the analog pin,
 *        side pins of the potentiometer go to +5V and ground
 *    * LED w/ 150 ~ 470 ohm resistor, 
 *        connected from digital pin 10 to ground
 *               
 *  created 27/08/2017 by derfaq 
 *  see down to the bottom of the file for license stuff
 */


#define F_CAM 30          //Change it according to your device
unsigned int lines = 2;   //Lines in screen

void setup() 
{
  Serial.begin(9600);
  
  //Initialization of Timer 1
  initTimer1();
  
  //In this mode of operation, we are restricted to certain pin
  //Pin 10 = OCR1B
  pinMode(10,OUTPUT);
}

void loop()
{
  //Manual tunning of frequency
  static int shift;
  shift = analogRead(A0) - 512;
  setFrequency(lines, shift);
  
  //Numeber of lines, defined through the serial port
  static int temp;
  if(Serial.available()>0){
      temp = Serial.parseInt();
      if(temp){
        lines = temp;
        setFrequency(lines, shift);
      }
  }

  //Set the duty cicle(0 full duty, 1023 off)
  setDuty(analogRead(A1));
  
  delay(2); 
}

void initTimer1()
{
  TCCR1A = 0; // Timer/Counter1 Control Register A, reset
  TCCR1B = 0; // Timer/Counter1 Control Register B, reset
  TCCR1A |= (1<<WGM11)|(1<<WGM10)|(1<<COM1B1)|(1<<COM1B0); //Set on compare match, when up-counting
  TCCR1B |= (1<<WGM13); //PWM, Phase Correct w/ TOP in 0CRA 
  setFrequency(lines, 0);
}

//This code is based in part of arduino core library Tone.cpp
void setFrequency(unsigned int _lines, int _shift)
{
  uint32_t ocr = F_CPU / ( F_CAM * 2 * _lines ) - 1 + _shift*2;
  uint8_t prescalarbits = 0b001;
  
  if (ocr > 0xffff)
  {
     ocr = F_CPU / ( F_CAM  * 2 * lines * 64 ) - 1 + _shift;
     prescalarbits = 0b011;
  }
  
  TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;
  OCR1A = ocr;
}

void setDuty(uint16_t _duty)
{
  OCR1B = map(_duty,0,1023,0,OCR1A);
}


/*
 * ---------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <daguerref@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Facundo Daguerre (derfaq)
 * --------------------------------------------------------------------------------- 
 */
