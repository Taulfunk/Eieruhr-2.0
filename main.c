#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <../../Libraries/LCD/lcd-routines.h>
#include <../../Libraries/LCD/lcd-routines.c>
#include "LCD-Funktionen.h"
#include <avr/eeprom.h>

#define DEBOUNCE 150
#define WAIT 500
#define SET             PD0
#define Speaker         PD6
#define SPEAKER_DDR     DDRD
#define RESETBUTTON     PD4
#define ENCODERBUTTON   PD5
#define PRESET          PD7
#define PRESET2         PD1

volatile uint8_t duration = 0;
uint8_t interruptknopf = 0;
uint8_t Sekunden = 0;
uint8_t Preset = 20;

struct
{
    uint8_t minuto;
    uint8_t sekundo;
}
Preset1, Preset2;

void playTone(uint8_t, uint16_t);
ISR(INT0_vect)
{
    _delay_us(DEBOUNCE);
    if (bit_is_set(PIND, PD2))
    {
        
        if (bit_is_set(PIND, PD3))      //rechtsdreh
        {
            if(duration < 98)
            {
                duration++;
                playTone(1, 1);
                
            }
            else if(duration < 99)
            {
                duration++;
                playTone(1, 10);
            }
            else
            {
                duration = 0;
                playTone(1, 10);
            }
        }
        
        else if(bit_is_clear(PIND, PD3))    //linksdreh
        {
            if(duration > 0)
            {
                duration--;
                playTone(1, 1);
            }
            
            else
            {
                duration = 99;
                playTone(1, 10);
            }
        }
        
        else
        {
            duration = 0;
            _delay_us(WAIT);
        }
    }
}

/*ResetButtonInterrupt*/
/*EncoderButtonInterrupt*/
ISR(PCINT2_vect)
{
    _delay_us(DEBOUNCE);
    bit_is_set(PIND, SET) ? (Sekunden = 1) : (Sekunden = 0);
    _delay_us(DEBOUNCE);
    if (bit_is_set(PIND, RESETBUTTON))      /*Anzeige auf 60*/
    {
        playTone(1, 5);
        Sekunden?(duration = 60):(duration = 20);
    }
    
    /*Erster der beiden Presetbuttons*/
    else if (bit_is_set(PIND, PRESET))
    {
        _delay_ms(200);
        if (bit_is_set(PIND, PRESET))
        {
            switch(Sekunden)
            {
                case 1:
                    if(Preset1.sekundo != duration)
                    {
                        eeprom_update_byte((uint8_t*)47, duration);
                        Preset1.sekundo = duration;
                        
                        for (uint8_t i = 0; i < 3; i++)
                        {
                            playTone(1, 10);
                            _delay_ms(100);
                        }
                    }
                    else
                    {
                        duration = Preset1.sekundo;
                        playTone(10, 10);
                    }
                    break;
                case 0:
                    if(Preset1.minuto != duration)
                    {
                        eeprom_update_byte((uint8_t*)46, duration);
                        Preset1.minuto = duration;
                        for (uint8_t i = 0; i < 3; i++)
                        {
                            playTone(1, 10);
                            _delay_ms(100);
                        }
                    }
                    else
                    {
                        duration = Preset1.minuto;
                        playTone(10, 10);
                    }
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch (Sekunden)
            {
                case 1:
                    duration = Preset1.sekundo;
                    break;
                case 0:
                    duration = Preset1.minuto;
                default:
                    break;
            }
        }
    }
    /*Zweiter der beiden Presetbuttons*/
    else if (bit_is_set(PIND, PRESET2))
    {
        /*Wird der Knopf gedrueckt gehalten?*/
        _delay_ms(200);
        if (bit_is_set(PIND, PRESET2))
        {
            switch(Sekunden)
            {
                case 1:
                    if(Preset2.sekundo != duration)
                    {
                        eeprom_update_byte((uint8_t*)49, duration);
                        Preset2.sekundo = duration;
                        for (uint8_t i = 0; i < 3; i++)
                        {
                            playTone(1, 10);
                            _delay_ms(100);
                        }
                    }
                    else
                    {
                        duration = Preset2.sekundo;
                        playTone(10, 10);
                    }
                    break;
                case 0:
                    if(Preset2.minuto != duration)
                    {
                        eeprom_update_byte((uint8_t*)48, duration);
                        Preset2.minuto = duration;
                        for (uint8_t i = 0; i < 3; i++)
                        {
                            playTone(1, 10);
                            _delay_ms(100);
                        }
                    }
                    else
                    {
                        duration = Preset2.minuto;
                        playTone(10, 10);
                    }
                    break;
                default:
                    break;
                    
            }
        }
        else
        {
            switch (Sekunden)
            {
                case 1:
                    duration = Preset2.sekundo;
                    break;
                case 0:
                    duration = Preset2.minuto;
                default:
                    break;
            }
        }
    }
    else if (bit_is_set(PIND, ENCODERBUTTON))       /*Countdown starten*/
    {
        /*Verhindert eine Störung durch Bedienung der Knoepfe waehrend des Kochvorganges*/
        cli();
        
        switch (Sekunden)
        {
            case 1:
                Timer(duration, 1);
                break;
            case 0:
                Timer(duration, 0);
                break;
            default:
                break;
        }
        
   //     Anzeige(0);
        duration = 0;
        
        /*Interrupts reenabled um dem Piepen ein Ende setzen zu koennen*/
        sei();
        
        for (uint8_t i = 0; i <= 20; i++)
        {
            for (uint8_t a = 0; a < 2; a++)
            {
                if (duration != 0)
                {
                    /*keine Ahnung was das war, vermutlich nicht mehr noetig*/
                    i = 22;
                    a = 3;
                    return;
                }
                playTone(1, 100);
                
                if(a >= 2)
                    break;
            }
            if(i > 20)
                break;
            _delay_ms(855);
        }
    }
    sei();
}

void initInterrupt0(void)
{
    EIMSK  |= (1 << INT0);                  /*enablet INT0*/
    
    EICRA  |= (1 << ISC00) | (1 << ISC01);  /*triggert INT0 bei aufsteigender Kante*/
    
    PCICR  |= (1 << PCIE2);                 /*Versuch, PD$ mit einem Interruptbutton auszustatten*/
    PCMSK2 |= (1 << RESETBUTTON);
    PCMSK2 |= (1 << ENCODERBUTTON);
    PCMSK2 |= (1 << SET);
    PCMSK2 |= (1 << PRESET);
    PCMSK2 |= (1 << PRESET2);
    sei();                                  /*setzt (global) interrupt enable bit*/
}

void initTimer(void)
{
    TCCR0A |= (1 << WGM01);                 /*entert ctc mode*/
    TCCR0A |= (1 << COM0A0);                /*Togglet OC0A bei Compare Match*/
    TCCR0B |= (1 << CS00) | (1 << CS01) ;    /*clk/64*/
    
    /*OCR0A enthält den tongebenden vergleichenden Wert*/
}

/*macht irgendwie brauchbare Töne*/
void playTone(uint8_t wavelength, uint16_t duration)
{
    /*lässt OCSR0A nach ja initialisierter Timer-ctc-Funktion den zu erreichenden Wert beinhalten*/
    OCR0A = wavelength;
    SPEAKER_DDR |= (1 << Speaker);
    
    while (duration)
    {
        _delay_ms(1);
        duration--;
    }
    SPEAKER_DDR &= ~(1 << Speaker);
}

int main(void)
{
    lcd_init();
    initTimer();
    initInterrupt0();
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0;
    
    PORTD &= ~(1 << PD2);                   /*debounct durch Pulldowns*/
    PORTD &= ~(1 << SET);
    PORTD &= ~(1 << PRESET);
    PORTD &= ~(1 << PRESET2);
    
    /*Befähigt den Avr zur Wiederaufnahme der voreingestellten Presets nach Reset*/
    Preset1.minuto = eeprom_read_byte((uint8_t*)46);
    Preset1.sekundo = eeprom_read_byte((uint8_t*)47);
    Preset2.minuto = eeprom_read_byte((uint8_t*)48);
    Preset2.sekundo = eeprom_read_byte((uint8_t*)49);
    
    /*Überprüfung des Minuten/Sekundeschalters*/
    bit_is_set(PIND, SET) ? (Sekunden = 1) : (Sekunden = 0);
    
    /*Initialisiert den Startwert der Uhr.
     Die favoritisierten Werte sollten also mit dem ersten Preset gespeichert werden*/
    Sekunden ? (duration = Preset1.sekundo) : (duration = Preset1.minuto);
    
    /*Begrüßung*/
    Hi();
    PORTB = 0xff;
    
    /*Initialisiert das wechsselseitige Erden der Segementanzeigen*/
    PORTC = (1 << PC4) & ~(1 << PC5);
    
    while(1)
    {
        /*Gibt einfach nur die Anzeige wieder. Die Musik spielt in den ISRs*/
        Anzeige(duration);
    }
    return 0;
}

