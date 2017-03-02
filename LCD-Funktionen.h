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

uint8_t kochen1a[8] =
{
    0b01001000,
    0b10110010,
    0b00100100,
    0b01010001,
    0b01101010,
    0b00111111,
    0b11111111,
    0b11111111
};
uint8_t kochen1b[8] =
{
    0b00000000,
    0b01010010,
    0b01101100,
    0b11011010,
    0b00100010,
    0b00111101,
    0b11111111,
    0b11111111
};

uint8_t kochen2a[8] =
{
    0b00000000,
    0b01001000,
    0b10101000,
    0b01100100,
    0b01101100,
    0b00110101,
    0b11111111,
    0b11111111
};

uint8_t kochen2b[8] =
{
    0b00000000,
    0b01000010,
    0b10101100,
    0b01011010,
    0b01100010,
    0b00110111,
    0b11111110,
    0b11111111
};

uint8_t kochen3a[8] =
{
    0b00000000,
    0b00010000,
    0b10100000,
    0b01000010,
    0b00100110,
    0b10010001,
    0b11111111,
    0b11111111
};

uint8_t kochen3b[8] =
{
    0b00000000,
    0b00000010,
    0b00100100,
    0b01001001,
    0b00100010,
    0b10110101,
    0b11111011,
    0b11111111
};

uint8_t kochen4a[8] =
{
    0b00000000,
    0b00110011,
    0b11111111,
    0b11101101,
    0b11110001,
    0b11111111,
    0b11111111,
    0b11111111
};

uint8_t kochen4b[8] =
{
    0b10001100,
    0b01000100,
    0b00001100,
    0b11100011,
    0b00011100,
    0b11111111,
    0b11111111,
    0b11111111
};

/*Gibt einen Balken pro Dekade in der oberen Zeile aus*/
void Balken(uint8_t duration)
{
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
    lcd_setcursor(0, 2);
    lcd_string("Zeit:");
    
    if (duration / 10 == 0)
    {
        lcd_setcursor(0, 1);
        lcd_string("          ");
        lcd_setcursor(9, 2);
        
        if (Sekunden)
            lcd_string("Sek.");
        else
            lcd_string("Min.");
        
        lcd_setcursor(6, 2);
        lcd_string(" ");
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
                _delay_us(26);
                
                /*stellt einen brodelnden Kochtopf dar*/
                if ((i % 2) == 0)
                {
                    lcd_generatechar(1, kochen1a);
                    lcd_setcursor(10, 1);
                    lcd_data(1);
                    lcd_generatechar(2, kochen2a);
                    lcd_setcursor(11, 1);
                    lcd_data(2);
                    lcd_generatechar(3, kochen3a);
                    lcd_setcursor(12, 1);
                    lcd_data(3);
                    lcd_generatechar(4, kochen4a);
                    lcd_setcursor(13, 1);
                    lcd_data(4);
                }
                else
                {
                    lcd_generatechar(1, kochen1b);
                    lcd_setcursor(10, 1);
                    lcd_data(1);
                    lcd_generatechar(2, kochen2b);
                    lcd_setcursor(11, 1);
                    lcd_data(2);
                    lcd_generatechar(3, kochen3b);
                    lcd_setcursor(12, 1);
                    lcd_data(3);
                    lcd_generatechar(4, kochen4b);
                    lcd_setcursor(13, 1);
                    lcd_data(4);
                }
            }
            break;
            
        case 0:
            for (uint8_t i = duration; i > 0; i--)
            {
                for (uint16_t a = 0; a < 60; a++)
                {
                    Anzeige2(i);
                    _delay_ms(990);
                    
                    /*stellt einen brodelnden Kochtopf dar*/
                    if ((a % 2) == 0)
                    {
                        lcd_generatechar(1, kochen1a);
                        lcd_setcursor(10, 1);
                        lcd_data(1);
                        lcd_generatechar(2, kochen2a);
                        lcd_setcursor(11, 1);
                        lcd_data(2);
                        lcd_generatechar(3, kochen3a);
                        lcd_setcursor(12, 1);
                        lcd_data(3);
                        lcd_generatechar(4, kochen4a);
                        lcd_setcursor(13, 1);
                        lcd_data(4);
                    }
                    else
                    {
                        lcd_generatechar(1, kochen1b);
                        lcd_setcursor(10, 1);
                        lcd_data(1);
                        lcd_generatechar(2, kochen2b);
                        lcd_setcursor(11, 1);
                        lcd_data(2);
                        lcd_generatechar(3, kochen3b);
                        lcd_setcursor(12, 1);
                        lcd_data(3);
                        lcd_generatechar(4, kochen4b);
                        lcd_setcursor(13, 1);
                        lcd_data(4);
                    }

                }
                _delay_us(1600);
            }
            break;
        default:
            break;
    }
    
    Anzeige2(0);
    
    //duration = 0;     // call by reference um uebergebenen Parameter zu aendern
}

#endif /* LCD_Funktionen_h */
