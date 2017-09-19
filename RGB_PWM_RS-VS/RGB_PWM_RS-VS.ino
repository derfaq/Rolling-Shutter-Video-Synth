/*  RGB_PWM_RS-VS.ino
 *  
 *  A Very Simple RGB Rolling Shutter Video Synth (RS-VS)
 *  
 *  Description
 *    This scketch generate three PWM signals over pins 3, 5, and 10 
 *    with a frequencies wichs depends on the value of three potentiometers 
 *    conected to A0..A2. Also we can control the dutys cycles by anothers 
 *    three potentiometers conected to A3..A5.
 *    
 *  The circuit:
 *    * Six potentiometers connected to A0..A5.
 *        Center pin of the potentiometer goes to the analog pin,
 *        side pins of the potentiometer go to +5V and ground
 *    * RGB LED w/ three 150 ~ 470 ohm resistors, 
 *        connected from digital pin 10, 5, 3 and cathode to ground
 *               
 *  created 27/08/2017 by derfaq 
 *  see down to the bottom of the file for license stuff
 */

void setup() {
  

  initTimer(0);
  pinMode(5,OUTPUT); // Pin 5 Arduino = PD5 AVR = OC0B
  /* By changing the frequency of timer 0, we are not longer able to use
   *  delay() and millis() functions :( 
   *  For delay propusses use _delay_ms() or _delay_us();
   */

  initTimer(1);
  pinMode(10,OUTPUT);  // Pin 10 Arduino = PB2 AVR = OC1B

  initTimer(2);
  pinMode(3,OUTPUT);  // Pin 3 Arduino = PD3 AVR = OC2B

  noInterrupts();
  /* No interrupts, we use the PWM module of each timer insted of interrupts.
   *  The cons: we are limitated to specific pins to conect the rgb led
   *  The pros: it's really easy to change the duty cicle.
   */
}

void loop() {
   
  //Set the frequency and the duty cicle of each timer, in funtion of pots values
  setFrequency(0,analogRead(A0)); setDuty(0,analogRead(A3));
  setFrequency(1,analogRead(A1)); setDuty(1,analogRead(A4));
  setFrequency(2,analogRead(A2)); setDuty(2,analogRead(A5));
  
}


void initTimer(uint8_t _timer){
  
  switch(_timer){
    case 0:
      TCCR0A = 0; // Timer/Counter1 Control Register A, reset
      TCCR0B = 0; // Timer/Counter1 Control Register B, reset
      TCCR0A |= (1<<COM0B1); //Clear OC0B on compare match, when up-counting
      TCCR0A |= (1<<WGM00);
      TCCR0B |= (1<<WGM02); //PWM, phase correct w/ TOP in 0CRA
      break;
    case 1:
      TCCR1A = 0; // Timer/Counter1 Control Register A, reset
      TCCR1B = 0; // Timer/Counter1 Control Register B, reset
      TCCR1A |= (1<<COM1B1); //Clear OC1B on compare match, when up-counting
      TCCR1A |= (1<<WGM11)|(1<<WGM10);
      TCCR1B |= (1<<WGM13); //PWM, phase correct w/ TOP in 0CRA
      break;
    case 2:
      TCCR2A = 0; // Timer/Counter1 Control Register A, reset
      TCCR2B = 0; // Timer/Counter1 Control Register B, reset
      TCCR2A = (1<<COM2B1); //Clear OC2B on compare match, when up-counting
      TCCR2A |= (1<<WGM20);
      TCCR2B |= (1<<WGM22); //PWM, Phase Correct w/ TOP in 0CRA
      break;
    default:
      break;
  }
}

// modification of function tone() //See: Arduino/hardware/arduino/avr/cores/arduino/Tone.cpp
// frequency in hertz              //https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Tone.cpp

void setFrequency(uint8_t _timer, unsigned int frequency)
{
  uint8_t prescalarbits = 0b001;
  uint32_t ocr = 0;
  
  _timer = constrain(_timer,0,2);
  frequency = constrain(frequency,31,65535);

  // if we are using an 8 bit timer, scan through prescalars to find the best fit
  if (_timer == 0 || _timer == 2)
  {
    ocr = F_CPU / frequency / 2 - 1;
    prescalarbits = 0b001;  // ck/1: same for both timers
    if (ocr > 255)
    {
      ocr = F_CPU / frequency / 2 / 8 - 1;
      prescalarbits = 0b010;  // ck/8: same for both timers

      if (_timer == 2 && ocr > 255)
      {
        ocr = F_CPU / frequency / 2 / 32 - 1;
        prescalarbits = 0b011;
      }

      if (ocr > 255)
      {
        ocr = F_CPU / frequency / 2 / 64 - 1;
        prescalarbits = _timer == 0 ? 0b011 : 0b100;

        if (_timer == 2 && ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 128 - 1;
          prescalarbits = 0b101;
        }

        if (ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 256 - 1;
          prescalarbits = _timer == 0 ? 0b100 : 0b110;
          if (ocr > 255)
          {
            // can't do any better than /1024
            ocr = F_CPU / frequency / 2 / 1024 - 1;
            prescalarbits = _timer == 0 ? 0b101 : 0b111;
          }
        }
      }
    }
      //Now we can set the preescaler
      if (_timer == 0)
      {
        TCCR0B = (TCCR0B & 0b11111000) | prescalarbits;
      }
      else
      {
        TCCR2B = (TCCR2B & 0b11111000) | prescalarbits;
      }

    }
    else //If, timer1
    {
      // two choices for the 16 bit timers: ck/1 or ck/64
      ocr = F_CPU / frequency / 2 - 1;

      prescalarbits = 0b001;
      if (ocr > 0xffff)
      {
        ocr = F_CPU / frequency / 2 / 64 - 1;
        prescalarbits = 0b011;
      }

      if (_timer == 1)
      {
        TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;

      }
    }

    // Set the OCR for the given timer
    
    switch (_timer)
    {
      case 0:
        OCR0A = ocr;
        break;
      case 1:
        OCR1A = ocr;
        break;
      case 2:
        OCR2A = ocr;
        break;
      default:
        break;
    }

}

void setDuty(uint8_t _timer, uint16_t duty){
  switch(_timer){
    case 0:
      OCR0B = (uint8_t)map(duty,0,1023,0,OCR0A);
      break;
    case 1:
      OCR1B = (uint16_t)map(duty,0,1023,0,OCR1A);
      break;
    case 2:
      OCR2B = (uint8_t)map(duty,0,1023,0,OCR2A);
      break;
  }
}

/*
 * ---------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <daguerref@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Facundo Daguerre (derfaq)
 * --------------------------------------------------------------------------------- 
 */
