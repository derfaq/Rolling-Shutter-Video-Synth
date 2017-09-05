/*  SimplePWM_RS-VS.ino
 *  
 *  A Very Simple Rolling Shutter Video Synth (RS-VS)
 *  
 *  Description
 *    This scketch generate a square wave over pin 10 with a frequency
 *    wich depends on the scan rate of the camera (F_CAM) and the number
 *    of lines that we want create over the screen (lines).
 *    A fine tunning of frequency is done manually by turning a potentiometer
 *    conected to A0, and the number of lines through another potentiometer
 *    in A1.
 *    
 *  The circuit:
 *    * Two potentiometers connected to analogs pins A0 and A1.
 *        Center pin of the potentiometer goes to the analog pin,
 *        side pins of the potentiometer go to +5V and ground
 *    * LED w/ 150 ~ 470 ohm resistor, 
 *        connected from digital pin 10 to ground
 *               
 *  created 05/09/2017 by derfaq 
 *  see down to the bottom of the file for license stuff
 */


#define F_CAM 30          //Change it according to your device

void setup() 
{
  //Initialization of Timer 1
  initTimer1();
  
  //In this mode of operation, we are restricted to certain pin
  //Pin 10 = OCR1B
  pinMode(10,OUTPUT);
}

void loop()
{
  //Fine tunning of frequency
  static int shift;
  shift = analogRead(A0) - 512;

  //Number of lines
  static unsigned int lines; 
  lines = analogRead(A1)>>4; //1024/16 = 64 lines max

  //setFrequency
  setFrequency(lines, shift);
  
  delay(2); 
}

void initTimer1()
{
  TCCR1A = 0; // Timer/Counter1 Control Register A, reset
  TCCR1B = 0; // Timer/Counter1 Control Register B, reset
  TCCR1A |= (1<<WGM11)|(1<<WGM10)|(1<<COM1B1)|(1<<COM1B0); //Set on compare match, when up-counting
  TCCR1B |= (1<<WGM13); //PWM, Phase Correct w/ TOP in 0CRA 
  setFrequency(2, 0);
}

//This code is based in part of arduino core library Tone.cpp
void setFrequency(unsigned int _lines, int _shift)
{
  uint32_t ocr = F_CPU / ( F_CAM * 2 * _lines ) - 1 + _shift;
  uint8_t prescalarbits = 0b001;
  
  if (ocr > 0xffff)
  {
     ocr = F_CPU / ( F_CAM  * 2 * _lines * 64 ) - 1 + _shift;
     prescalarbits = 0b011;
  }
  
  TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;
  OCR1A = ocr;
  OCR1B = (OCR1A>>1);
}


/*
 * ---------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <daguerref@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Facundo Daguerre (derfaq)
 * --------------------------------------------------------------------------------- 
 */
