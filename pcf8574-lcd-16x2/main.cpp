/*
 * main.cpp
 *
 *  Created on: 26 сент. 2016 г.
 *      Author: Iskander
 */
#include "pcf8574-lcd-16x2.h"

int main (void)
{
  int fd2 ;

  cout << "LCD test program" << endl ;

  MyLCD LCD(0x3f);

  LCD.Init();
  sleep(1);
  LCD.Clear();
 // LCD.Cursor();
  LCD.Putc('%');
  sleep(1);

  LCD.Print("OrangePI");
  LCD.BackLight();

  /*
  lcd_init(fd2);
  lcd_clear(fd2);
  lcd_cursorOn(fd2);

  lcd_putc(fd2, '%');
  sleep (1) ;
  lcd_print(fd2, "OrangePI", 13, 1);
  sleep (2) ;
  lcd_cursorOff(fd2);
  lcd_putc(fd2, '%');
  sleep (1) ;
  lcd_BackLightOff(fd2);
  sleep (1) ;
  lcd_print(fd2, "OrangePI", 13, 0);
  sleep (1) ;
  //lcd_BackLightOn(fd2);
  sleep (2) ;
  lcd_cursorOn(fd2);
*/

  return 0;
}


