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
void Hi()
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

void Anzeige(uint8_t duration)
{
    itoa(duration, outpt, 10);
    lcd_clear();
    lcd_setcursor(6, 2);
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
                for (uint8_t a = 0; a<60; a++)
                {
                    Anzeige(i);
                }
            }
            break;
            
        case 2:
            for (uint8_t i = duration; i > 0; i--)
            {
                for (uint8_t a = 0; a<60; a++)
                {
                    Anzeige(i);
                }
            }
            break;
        default:
            break;
    }
    
    Anzeige(0);
    duration = 0;
}

#endif /* LCD_Funktionen_h */
