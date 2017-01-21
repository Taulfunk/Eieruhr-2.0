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

/*Gehabte Begruessungssequenz*/
void Hi()
{
    lcd_clear();
    lcd_setcursor(4, 1);
    lcd_string("Moin");
    _delay_ms(1000);
    lcd_clear();
}

#endif /* LCD_Funktionen_h */
