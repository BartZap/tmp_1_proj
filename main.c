// TM_project_buzzer 2023 by: Barto & Wisnu //

#define F_CPU 8000000UL		//Defining clock
#include <avr/io.h>		
#include <util/delay.h>		//delay
#include "pitches.h"		//pitches 
#define BUZZER_PIN PD5		//Buzzer OUT PIN

void delayCustom(unsigned int duration) {
	//funkcja grająca melodie
	while (duration > 0) {
		_delay_ms(1);		//Delay each decramentation
		duration--;		//Counting pitches
	}
}

void buzzerPlay(unsigned int frequency, unsigned int duration) {
	//Setting pins, PWM, clocks, prescalers to adjust right freq
	unsigned int prescaler = 8;						//choosing prescaler
	unsigned int top = F_CPU / (2 * prescaler * frequency) - 1;		//Counting PWM value
	
	OCR0B = top;		//Setting OCR0B caltulated value
	
	//Enable PWM timer counter
	TCCR0A |= (1 << COM0B1) | (1 << WGM02) | (1 << WGM00);					//WGM - wave form generator, COM compare output mode
	TCCR0B |= (1 << CS01);									//Clock select bit
	
	// Generating tunes for specific amount of time
	delayCustom(duration);
	
	// Stop playing 
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
}

void playfurElise() {
	//melodia Fur Elise
	DDRD |= (1 << BUZZER_PIN);	
	unsigned int melody[] = {
		
		NOTE_E5, NOTE_DS5,
		NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
		NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4,
		NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4,
		NOTE_C5, 0,  NOTE_E4, NOTE_E5, NOTE_DS5,
		
		NOTE_E5,  NOTE_DS5,  NOTE_E5,  NOTE_B4,  NOTE_D5,  NOTE_C5, //6
		NOTE_A4,  NOTE_C4,  NOTE_E4,  NOTE_A4,
		NOTE_B4, NOTE_E4,  NOTE_C5,  NOTE_B4,
		NOTE_A4 ,  

	};

	unsigned int noteDuration[] = {
		16,16,16,16,16,16,16,16,
		8,16,16,16,
		8,16,16,16,
		8,16,16,16,16,

		16,16,16,16,16,16,
		8,16,16,16,
		8,16,16,16,
		4,

	};

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);

	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(8000/melody[i], 8000/noteDuration[i]);		// Adjust freq and time
		delayCustom(100);						
	}
}

void playImperialMarch() {
	
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
		NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_C5,
		NOTE_E4, NOTE_F4, NOTE_C5, NOTE_E4,
		NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5,
		NOTE_G4, NOTE_F4, NOTE_C5, NOTE_E4,
	};

	unsigned int noteDuration[] = {
		4,4,4,8,
		16,4,8,16,2,
		4,4,4,8,
		16,4,8,16,2,
	};
	
	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);
	
	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(8000/melody[i], 2000/noteDuration[i]);
		delayCustom(500);
	}
}

void playHappyBirthday() {
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
		NOTE_C4, NOTE_C4,
		NOTE_D4, NOTE_C4, NOTE_F4,
		NOTE_E4, NOTE_C4, NOTE_C4,
		NOTE_D4, NOTE_C4, NOTE_G4,
		NOTE_F4, NOTE_C4, NOTE_C4,

		NOTE_C5, NOTE_A4, NOTE_F4,
		NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
		NOTE_A4, NOTE_F4, NOTE_G4,
		NOTE_F4,
	};

	unsigned int noteDuration[] = {
		4,8,4,4,
		4,2,4,8,
		4,4,4,2,
		4,8,4,4,
		4,4,4,4,
		8,4,4,4,2,
	};

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);		//Pitches length count

	for (unsigned int i = 0; i < numNotes; i++)
	{
		buzzerPlay(8000/melody[i], 3000/noteDuration[i]);
		delayCustom(100);
	}
}

void playPinkPantherTheme() {
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
		NOTE_DS4, NOTE_E4,
		NOTE_FS4, NOTE_G4,
		NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5,
		NOTE_B4, NOTE_E4,
		NOTE_G4, NOTE_B4, NOTE_AS4,

		NOTE_A4, NOTE_G4, NOTE_E4,
		NOTE_D4, NOTE_E4,
		
		NOTE_DS4, NOTE_E4,
		NOTE_FS4, NOTE_G4, NOTE_DS4,
		NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5,
		NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5, NOTE_DS5,
	};

	unsigned int noteDuration[] = {
		8,2,8,2,
		8,8,8,8,
		8,8,8,8,8,1,
		8,16,16,8,1,
		8,2,8,2,
		8,8,8,8,
		8,8,8,8,8,1,
	};

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);

	for (unsigned int i = 0; i < numNotes; i++)
	{
		buzzerPlay(4000/melody[i], 3000/noteDuration[i]);
		delayCustom(100);
	}
}
int main(void) {
	DDRB = 0x00;		//Enable input for tact switches
	PORTB = 0x0f;		//Setting pull-up resistors
	while (1) {			
		if(((PINB == 0x87)||(PINB == 0x97)))
		{
			playfurElise();
		}
		else if((PINB == 0x8b)||(PINB == 0x9b))
		{
			playImperialMarch();
		}
		else if((PINB==0x8d)||(PINB == 0x9d))
		{
			playHappyBirthday();
		}
		else if((PINB==0x8e)||(PINB==0x9e))
		{
			playPinkPantherTheme();
		}
	}
}
