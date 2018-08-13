/*
 * Screwdriver Badge.c
 *
 * Created: 3/6/2018 9:30:52 PM
 * Author : compukidmike
 *
 * Portions of this code are from Adafruit TV-B-Gone
 * https://learn.adafruit.com/tv-b-gone-kit/
 */ 

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

//Uncomment line below to enable Goon mode.
//#define goon

int TouchRead(int Pin, int samples);
void TVBGone();
void UpdateButtons();

#define LED1PORT _SFR_IO8(0x1B) //DDRA
#define LED2PORT _SFR_IO8(0x1B) //DDRA
#define LED3PORT _SFR_IO8(0x1B) //DDRA
#define IRLEDPORT _SFR_IO8(0x1B) //DDRA
#define BUZZPORT _SFR_IO8(0x18) //DDRB

#define LED1PIN 1
#define LED2PIN 2
#define LED3PIN 3
#define IRLEDPIN 0
#define BUZZPIN 2
#define BUTTONPIN 7
#define SLIDER1PIN 4
#define SLIDER2PIN 5
#define SLIDER3PIN 6


volatile unsigned long millis = 0; //millisecond counter updated by timer1
volatile uint8_t millisCounter = 0;
const int delayTime = 250;
volatile uint8_t pulseWidth = 0; //IR pulse width from 0-42
volatile uint8_t pulseWidthCounter = 0;
volatile uint8_t pulseOn = 1;
//const int pulseMaxOnTime = 100; //max time that pulse can be on
volatile uint8_t pulseCounter = 0;
volatile uint8_t pulseCountUp = 1;
volatile uint8_t IRPulse = 0;
volatile uint16_t IRPulseCounter = 0;
int ledCounter = 0;
int ButtonValue = 0;
int ButtonRef = 0;
int Slider1Value = 0;
int Slider1Ref = 0;
int Slider2Value = 0;
int Slider2Ref = 0;
int Slider3Value = 0;
int Slider3Ref = 0;

uint8_t SliderTouched = 0;
uint8_t SliderReleased = 0;
uint8_t Slider1Touched = 0;
uint8_t Slider2Touched = 0;
uint8_t Slider3Touched = 0;
uint8_t ButtonTouched = 0;
uint8_t ButtonReleased = 0;

long nextTime = 0;
uint8_t pulseDelay = 7;
uint8_t pulseDelayCounter = 0;
uint8_t pulseDelayUp = 1;

int pulse = 0;

long nextButtonReadTime = 0;
uint8_t buttonReadDelay = 50; //mS between button reads

volatile uint8_t buzzWidth = 0;
 uint8_t buzzWidthCounter = 0;
 uint8_t buzzOn = 0;
volatile uint8_t buzzCounter = 0;
 uint8_t buzzCountUp = 0;
long nextBuzzerUpdateTime = 0;
int buzzerUpdateDelay = 10;

 int sampleCounter = 0;
 uint8_t sample = 0;
 
volatile uint8_t mode = 1;
long ledDelay = 0;
long ButtonPressedTime;
int ButtonPressedDelay = 250;

uint8_t BlingModeOn = 0;
uint8_t BlingModeCounter = 0;
long BlingTimeCounter = 0;
uint8_t BlingTimeDelay = 100;

extern const PGM_P* const powerCodes[] PROGMEM;

extern uint8_t num_codes;

uint8_t i, j;
uint16_t ontime, offtime;

uint8_t TVContinuous = 0;

#ifdef goon
uint8_t GoonMorse = 0;
uint8_t MorseDelay = 100;
uint8_t MorseCounter = 0;
const uint8_t GoonBits[52] = {1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0}; //Morse code for GOON
#endif

int main(void)
{
    //Setup
	DDRA |= 1<<LED1PIN | 1<<LED2PIN | 1<<LED3PIN | 1<<IRLEDPIN; //Set LED pins to OUTPUT
	DDRB |= 1<<BUZZPIN; //Set Buzzer pin to OUTPUT

	//Setup timer1 for LEDs
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	// 76190.47619047618 Hz (8000000/((104+1)*1))
	OCR1A = 104;
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 1
	TCCR1B |= (1 << CS10);
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);

	//Setup timer0 for Sound
	TCCR0A |= 1<<COM0A1; //non-inverting mode (pin OC0A)
	TCCR0A |= 1<<WGM01 | 1<<WGM00; //Fast PWM
	OCR0A = 128;


	sei(); //enable interrupts
	
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2); //set prescaler to 64 (8MHz/64 = 125KHz)
	ADCSRA |= (1 << ADEN); //enable ADC

	//Get baseline values at startup
	ButtonRef = TouchRead(BUTTONPIN, 50);
	Slider1Ref = TouchRead(SLIDER1PIN, 50);
	Slider2Ref = TouchRead(SLIDER2PIN, 50);
	Slider3Ref = TouchRead(SLIDER3PIN, 50);

	//Get last Mode from EEPROM
	mode = eeprom_read_byte((uint8_t)0);
	if((mode > 3) | (mode < 1)){
		mode = 1;
	}
	
	
	
	
	//Main Loop
    while (1) 
    {
		if(millis > nextButtonReadTime){
			nextButtonReadTime = millis + buttonReadDelay;
			UpdateButtons();

		if(Slider3Touched == 1){
			LED1PORT |= 1<<LED1PIN;
			switch(mode)
			{
				case 1: //Screwdriver
				pulseDelay = 7;
				pulse = 1;
				buzzWidth = 40;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				break;
				case 2: //Bling
				#ifdef goon
				GoonMorse = 1;
				MorseDelay = 200;
				#else 
				pulseDelay = 7;
				pulse = 1;
				#endif
				buzzWidth = 40;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				BlingTimeDelay = 200;
				break;
				case 3: //TVBGone
				TVBGone();
				break;
			}
			
			} else {
			if(mode != 2) LED1PORT &= ~(1<<LED1PIN);
		}

		if(Slider2Touched == 1){
			LED2PORT |= 1<<LED2PIN;
			switch(mode)
			{
				case 1:
				pulseDelay = 7;
				pulse = 1;
				buzzWidth = 20;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				break;
				case 2:
				#ifdef goon
				GoonMorse = 1;
				MorseDelay = 100;
				#else
				pulseDelay = 5;
				pulse = 1;
				#endif
				buzzWidth = 20;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				BlingTimeDelay = 100;
				break;
				case 3:
				TVBGone();
				break;
			}
			} else {
			if(mode != 2) LED2PORT &= ~(1<<LED2PIN);
		}

		if(Slider1Touched == 1){
			LED3PORT |= 1<<LED3PIN;
			switch(mode)
			{
				case 1:
				pulseDelay = 7;
				pulse = 1;
				buzzWidth = 10;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				break;
				case 2:
				#ifdef goon
				GoonMorse = 1;
				MorseDelay = 50;
				#else
				pulseDelay = 3;
				pulse = 1;
				#endif
				buzzWidth = 10;
				TCCR0B |= 1<<CS00 | 1<<CS01;
				BlingTimeDelay = 50;
				break;
				case 3:
				TVBGone();
				break;
			}
			} else {
				if(mode != 2) LED3PORT &= ~(1<<LED3PIN);
		}


		if(SliderReleased == 1){
			SliderReleased = 0;
			pulse = 0;
			TCCR0B = 0;
			#ifdef goon
			GoonMorse = 0;
			MorseCounter = 0;
			#endif
		}


		if(ButtonTouched == 1){
			switch(mode)
			{
				case 1:
				LED1PORT |= 1<<LED1PIN;
				break;
				case 2:
				LED2PORT |= 1<<LED2PIN;
				LED3PORT &= ~(1<<LED3PIN);
				LED1PORT &= ~(1<<LED1PIN);
				BlingTimeCounter += 200;
				break;
				case 3:
				LED3PORT |= 1<<LED3PIN;
				break;
			}
			if(ButtonPressedTime == 0) ButtonPressedTime = millis;
			if(millis - ButtonPressedTime > ButtonPressedDelay){
				mode += 1;
				if(mode > 3) mode=1;
				//Write mode to EEPROM
				eeprom_update_byte((uint8_t*)0, mode);
				LED1PORT &= ~(1<<LED1PIN);
				LED2PORT &= ~(1<<LED2PIN);
				LED3PORT &= ~(1<<LED3PIN);
				switch(mode)
					{
						case 1:
						LED1PORT |= 1<<LED1PIN;
						ledDelay = millis + 500;
						while(ledDelay > millis){};
						LED1PORT &= ~(1<<LED1PIN);
						break;
						case 2:
						LED2PORT |= 1<<LED2PIN;
						ledDelay = millis + 500;
						while(ledDelay > millis){};
						LED2PORT &= ~(1<<LED2PIN);
						break;
						case 3:
						LED3PORT |= 1<<LED3PIN;
						ledDelay = millis + 500;
						while(ledDelay > millis){};
						LED3PORT &= ~(1<<LED3PIN);
						break;
					}
			
			} 
		} else {
			if(ButtonPressedTime > 0){
				ButtonPressedTime = 0;
				LED1PORT &= ~(1<<LED1PIN);
				LED2PORT &= ~(1<<LED2PIN);
				LED3PORT &= ~(1<<LED3PIN);
			}
		}				
	}
		
		
		if(pulse == 1){
		if(millis > nextTime){
			nextTime = millis + pulseDelay;
			if(pulseDelayUp == 1){
				pulseDelayCounter ++;
				if(pulseDelayCounter > 41){
					pulseDelayUp = 0;
				}
			} else {
				pulseDelayCounter --;
				if(pulseDelayCounter < 1){
					pulseDelayUp = 1;
				}
			}
			pulseWidth = pulseDelayCounter;
		}
		} else {
			pulseWidth = 0;
			pulseDelayUp = 1;
			pulseDelayCounter = 0;
		}
		
		#ifdef goon
		if(GoonMorse == 1){
			if(millis > nextTime){
				nextTime = millis + MorseDelay;
				MorseCounter ++;
				if(MorseCounter > 51) MorseCounter = 0;
				if(GoonBits[MorseCounter] == 1){
					pulseOn = 1;
				} else {
					pulseOn = 0;
				}
			}
		}
		#endif
		
		if(mode == 2){
			if(millis > BlingTimeCounter){
				BlingTimeCounter = millis + BlingTimeDelay;
				BlingModeCounter += 1;
				if(BlingModeCounter > 4) BlingModeCounter = 1;
				switch (BlingModeCounter)
				{
					case 1:
					LED1PORT |= 1<<LED1PIN;
					break;
					case 2:
					LED2PORT |= 1<<LED2PIN;
					LED1PORT &= ~(1<<LED1PIN);
					break;
					case 3:
					LED3PORT |= 1<<LED3PIN;
					LED2PORT &= ~(1<<LED2PIN);
					break;
					case 4:
					LED3PORT &= ~(1<<LED3PIN);
					break;
				}
			}
		}
		
}
}

void UpdateButtons(){
	Slider1Value = TouchRead(SLIDER1PIN, 1) - Slider1Ref;
	Slider2Value = TouchRead(SLIDER2PIN, 1) - Slider2Ref;
	Slider3Value = TouchRead(SLIDER3PIN, 1) - Slider3Ref;
	ButtonValue = TouchRead(BUTTONPIN, 1) - ButtonRef;
	
	if(Slider1Value > 100){
		Slider1Touched = 1;
		SliderTouched = 1;
	} else {
		Slider1Touched = 0;
	}
	if(Slider2Value > 100){
		Slider2Touched = 1;
		SliderTouched = 1;
	} else {
		Slider2Touched = 0;
	}
	if(Slider3Value > 100){
		Slider3Touched = 1;
		SliderTouched = 1;
	} else {
		Slider3Touched = 0;
	}
	if(ButtonValue > 100){
		ButtonTouched = 1;
	} else {
		ButtonTouched = 0;
	}
	
	if((ButtonTouched == 1) & (ButtonValue < 100)){
		ButtonReleased = 1;
		ButtonTouched = 0;
	}
	
	if((SliderTouched == 1) & (Slider1Value < 100) & (Slider2Value < 100) & (Slider3Value < 100)){
		SliderReleased = 1;
		SliderTouched = 0;
	}
}

void UpdateLEDs(){
	switch (ledCounter)
	{
		case 0:
		LED1PORT &= ~(1<<LED3PIN);
		LED1PORT |= 1<<LED1PIN;
		break;
		case 1:
		LED1PORT &= ~(1<<LED1PIN);
		LED1PORT |= 1<<LED2PIN;
		break;
		case 2:
		LED1PORT &= ~(1<<LED2PIN);
		LED1PORT |= 1<<LED3PIN;
		break;
	}
}

int TouchRead(int Pin, int samples){
	long totalValue = 0;
	for(int x=0; x<samples; x++){ 
		PORTA |= 1<<Pin; //turn on pullup
		ADMUX =   0b00100000; // connect the ADC input and the internal sample and hold capacitor to ground to discharge it
		ADCSRA |= (1 << ADSC); // start the conversion
		while((ADCSRA & (1 << ADSC)));
		PORTA &= ~(1<<Pin); //turn off pullup
		ADMUX = Pin; //set mux to correct pin
		ADCSRA |= (1 << ADSC); // start the conversion
		while((ADCSRA & (1 << ADSC)));
		totalValue += ADC;
	}
	return totalValue/samples;
}

void TVBGone(){ 

	 for (i=0; i<num_codes; i++) {   // for every POWER code in our collection

		 PGM_P thecode_p = pgm_read_word(powerCodes+i);     // point to next POWER code

		 uint8_t freq = pgm_read_byte(thecode_p);

		 // set OCR for Timer1 and Timer0 to output this POWER code's carrier frequency
		 OCR1A = freq;
		 
		 // transmit all codeElements for this POWER code (a codeElement is an onTime and an offTime)
		 // transmitting onTime means pulsing the IR emitters at the carrier frequency for the length of time specified in onTime
		 // transmitting offTime means no output from the IR emitters for the length of time specified in offTime
		 j = 0;  // index into codeElements of this POWER code
		 do {
			 // read the onTime and offTime from the program memory
			 ontime = pgm_read_word(thecode_p+(j*4)+1);
			 offtime = pgm_read_word(thecode_p+(j*4)+3);

			 // transmit this codeElement (ontime and offtime)
			 IRPulse = 1;
			 
			 // keep transmitting carrier for onTime
			 IRPulseCounter = ontime;
			 while(IRPulseCounter > 0){};

			 IRPulse = 0;         
			 IRLEDPORT &= ~(1<<IRLEDPIN); // turn off IR LED

			 IRPulseCounter = offtime;
			 while(IRPulseCounter > 0){};
				 
			 j++;
		 } while ( offtime != 0 );  // offTime = 0 signifies last codeElement for a POWER code
         
		 IRLEDPORT &= ~(1<<IRLEDPIN); // turn off IR LED
		 
		 UpdateButtons();
		 
		 if(Slider2Touched == 1){
			 LED2PORT |= 1<<LED2PIN;
		 } else {
			 LED2PORT &= ~(1<<LED2PIN);
		 }
		 if(Slider3Touched == 1){
			 LED1PORT |= 1<<LED1PIN;
		 } else {
			 LED1PORT &= ~(1<<LED1PIN);
		 }
		 if(Slider1Touched == 1){
			 TVContinuous = 1;
		 }
		 
		 if(TVContinuous == 1){
			 LED1PORT |= 1<<LED1PIN;
			 LED2PORT |= 1<<LED2PIN;
			 LED3PORT |= 1<<LED3PIN;
		 }
		 
		 if((SliderTouched == 1) & (SliderReleased == 1)){
			 if(TVContinuous == 1){
				 SliderReleased = 0;
				 LED1PORT &= ~(1<<LED1PIN);
				 LED2PORT &= ~(1<<LED2PIN);
				 LED3PORT &= ~(1<<LED3PIN);
				 while(SliderReleased == 0) UpdateButtons();
				 SliderReleased = 0;
				 TVContinuous = 0;
				 break;
			 }
		 }
		 
		 
		 if((SliderTouched == 0) & (TVContinuous == 0) ){
			 LED1PORT &= ~(1<<LED1PIN);
			 LED2PORT &= ~(1<<LED2PIN);
			 LED3PORT &= ~(1<<LED3PIN);
			 SliderReleased = 0;
			 break;
		 }
		 
		 OCR1A = 104; //Put timer back to normal
		 IRPulseCounter = 20000; //delay ~250mS between codes
		 while(IRPulseCounter > 0){};
	 }
	 
	 LED1PORT &= ~(1<<LED1PIN);
	 LED2PORT &= ~(1<<LED2PIN);
	 LED3PORT &= ~(1<<LED3PIN);
	 TVContinuous = 0;
	 OCR1A = 104; //Put timer back to normal
}

ISR(TIM1_COMPA_vect) {
	if(mode == 3){
	if(IRPulse == 1){
		PINA = (1<<IRLEDPIN);
	}
	
	if(IRPulseCounter > 0)	{
		IRPulseCounter --;
	}
	} else {

		if(pulseCountUp == 1){
			pulseCounter ++;
			if(pulseCounter > 15){
				pulseCountUp = 0;
			}
			if(pulseOn == 1){
				IRLEDPORT ^= 1<<IRLEDPIN;
			} else {
			IRLEDPORT &= ~(1<<IRLEDPIN);
			}
		} else {
			pulseCounter --;
			if(pulseCounter < 1){
				pulseCountUp = 1;
				pulseWidthCounter ++;
			}
			IRLEDPORT &= ~(1<<IRLEDPIN);
		}
		
		#ifdef goon
		if(GoonMorse == 0){
		#endif
		if(pulseWidthCounter > pulseWidth){
			pulseOn = 0;
			if(pulseWidthCounter > 42){
				pulseWidthCounter = 0;
				if(pulseWidth > 0){
					pulseOn = 1;
				}
			}
			
		}
		#ifdef goon
		}
		#endif
		
		buzzCounter ++;
		if(buzzCounter > buzzWidth){
			buzzCounter = 0;
			sampleCounter ++;
			if(sampleCounter > 511) sampleCounter = 0;
			if(sampleCounter > 255){
				OCR0A = 512-sampleCounter;
			} else {
				OCR0A = sampleCounter;
			}
		}
		}
		
		//crude millis implementation. Accurate enough for our application
		millisCounter ++;
		if(millisCounter == 75){
			millis ++;
			millisCounter = 0;
		}

}
