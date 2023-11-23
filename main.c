// TM_project_buzzer 2023 by: Barto & Wisnu //

#define F_CPU 8000000UL //definiowanie zegara MHz
#include <avr/io.h>		//standardowa biblioteka
#include <util/delay.h>	//opoznienie
#include "pitches.h"	//nuty
#define BUZZER_PIN PD5	//PIN odpowiadający za PWM - nasze wyjście

void delayCustom(unsigned int duration) {
	//funkcja grająca melodie
	while (duration > 0) {
		_delay_ms(1);	//odstep pomiedzy dekrementacja
		duration--;		//odliczanie nut zmniejszanie ich dlugosci o 1
	}
}

void buzzerPlay(unsigned int frequency, unsigned int duration) {
	// Ustawienie wartości rejestru OCR0B na podstawie częstotliwości dźwięku
	unsigned int prescaler = 8;										// Wybór preskalera
	unsigned int top = F_CPU / (2 * prescaler * frequency) - 1;		// Obliczenie wartości rejestru dla PWM
	
	OCR0B = top;		//przypisanie rejestrowi OCR0B wyliczonych wartosci
	
	// Włączenie trybu PWM na Timer/Counter, ustawienie preskalera, zegara
	TCCR0A |= (1 << COM0B1) | (1 << WGM02) | (1 << WGM00);	//WGM - wave form generator ustalają dkoladny tryb pwm, COM compare output mode
	TCCR0B |= (1 << CS01);									//3 piny wybierajace rodzaj zegara dla timer counter clk/8 od prescalera clock select bit
	
	// Generowanie dźwięku przez określony czas
	delayCustom(duration);
	
	// Wyłączenie generowania dźwięku
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
}

void playfurElise() {
	//melodia Fur Elise
	DDRD |= (1 << BUZZER_PIN);	//podanie napiecia dla pinu D5 oraz rejestru DDRD - ustawienie jako wyjscie
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
		buzzerPlay(8000/melody[i], 8000/noteDuration[i]);		// dostosowanie czestotliwosci melodii oraz czasu trwania
		delayCustom(100);										// Odstęp między nutami (można dostosować)
	}
}

void playImperialMarch() {
	// Marsz Gwiezdnych Wojen - Imperial March
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

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);		//licznik dlugosci nut

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
	DDRB = 0x00;		//ustawienie wejscia dla przyciskow
	PORTB = 0x0f;		//rezystory podciagajace
	while (1) {			//glowna funckja programu
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