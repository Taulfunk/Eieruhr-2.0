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

uint8_t array[8] =
{
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
};

/*Gibt einen Balken pro Dekade in der oberen Zeile aus*/
void Balken(uint8_t duration)
{
//    lcd_clear();
    
    for (uint8_t i = 0; i < duration / 10; i++)
    {
        lcd_generatechar(0, array);
        lcd_setcursor(i, 1);
        lcd_data(0);
    }
    for (uint8_t a = duration / 10; a < 10; a++)
    {
        lcd_setcursor(a, 1);
        lcd_string(" ");
    }
}

/*Zeigt die Werte ohne merkliches Flackern an*/
void Anzeige2(uint8_t duration)
{
//    lcd_clear();
    lcd_setcursor(0, 2);
    lcd_string("Zeit:");
    lcd_setcursor(10, 1);
    lcd_string("Zehner");
    
    if (duration / 10 == 0)
    {
        lcd_setcursor(0, 1);
        lcd_string("         ");
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
        {
            lcd_string("Sek.");
            Balken(duration);
        }
        
        else
        {
            lcd_string("Min.");
            Balken(duration);
        }
        
        lcd_setcursor(6, 2);
    }
    itoa(duration, outpt, 10);
    lcd_string(outpt);
}

/*Zaehlt Zeit abhaengig vom Modus herunter waehrend ein Countdown und eine Balkeanzeige wiedergegeben wird*/
void Timer(uint8_t duration, uint8_t mode)
{
    switch (mode)
    {
        case 1:
            for (uint8_t i = duration; i > 0; i--)
            {
                Anzeige2(i);
                _delay_ms(990);
            }
            break;
            
        case 0:
            for (uint8_t i = duration; i > 0; i--)
            {
                for (uint16_t a = 0; a < 60; a++)
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
    
    //duration = 0;     // call by reference um uebergebenen Parameter zu aendern
}



#endif /* LCD_Funktionen_h */
