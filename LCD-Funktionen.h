//
//  LCD-Funktionen.h
//  Eieruhr 2.0
//
//  Created by Paul Funk on 21.01.17.
//  Copyright © 2017 Paul Funk. All rights reserved.
//

#ifndef LCD_Funktionen_h
#define LCD_Funktionen_h


extern uint8_t Sekunden;
extern void playTone(uint8_t, uint16_t);
char outpt[16];
/*Gehabte Begruessungssequenz*/
void Hi(void)
{
    lcd_clear();
    lcd_setcursor(6, 1);
    lcd_string("Moin");
    playTone(1, 50);
    _delay_ms(50);
    playTone(1, 50);
    _delay_ms(50);
    playTone(1, 50);
    _delay_ms(50);
    _delay_ms(1000);
    lcd_clear();
}
void Anzeige2(uint8_t duration);
/*Dauert etwa 10 ms*/
void Anzeige(uint8_t duration)
{
    lcd_clear();
    if (duration / 10 == 0)
    {
        lcd_setcursor(9, 2);

        if (Sekunden)
            lcd_string("Sek.");
        else
            lcd_string("Min.");
        lcd_setcursor(7, 2);
    }
    else
    {
        lcd_setcursor(9, 2);
        
        if (Sekunden)
            lcd_string("Sek.");
        else
            lcd_string("Min.");
        lcd_setcursor(6, 2);
    }
    itoa(duration, outpt, 10);
    lcd_string(outpt);
    
    lcd_setcursor(6, 1);
    lcd_string("Zeit:");
    _delay_ms(10);
}
void Timer(uint8_t duration, uint8_t mode)
{
    switch (mode)
    {
        case 1:
            for (uint8_t i = duration; i > 0; i--)
            {
                for (uint8_t a = 0; a < 60; a++)
                {
                    Anzeige2(i);
                    _delay_ms(990);
                }
            }
            break;
            
        case 0:
            for (uint8_t i = duration; i > 0; i--)
            {
                for (uint16_t a = 0; a < 3600; a++)
                {
                    Anzeige2(i);
                    _delay_ms(990);
                }
            }
            break;
        default:
            break;
    }
    
    Anzeige2(0);
    duration = 0;
}

void Anzeige2(uint8_t duration)
{
    lcd_clear();
    if (duration / 10 == 0)
    {
        lcd_setcursor(9, 2);
        
        if (Sekunden)
            lcd_string("Sek.");
        else
            lcd_string("Min.");
        lcd_setcursor(7, 2);
    }
    else
    {
        lcd_setcursor(9, 2);
        
        if (Sekunden)
            lcd_string("Sek.");
        else
            lcd_string("Min.");
        lcd_setcursor(6, 2);
    }
    itoa(duration, outpt, 10);
    lcd_string(outpt);
    
    lcd_setcursor(6, 1);
    lcd_string("Zeit:");
}

#endif /* LCD_Funktionen_h */
