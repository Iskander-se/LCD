/*
 * pcf8574-lcd-16x2.h
 *
 *  Created on: 26 сент. 2016 г.
 *      Author: Iskander
 */

#ifndef PCF8574_LCD_16X2_H_
#define PCF8574_LCD_16X2_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>

#include <wiringPiI2C.h>
#include <lcd.h>

using namespace std;

class MyLCD
{
public:
	#define ON 0xFF
	#define OFF 0x00
	typedef unsigned char u8;


private:
	int dev ;
	#define LCD_DISPLAYCONTROL 0x08

	void lcd_notify(int dev){
	    int v;
	    usleep(2);
	    v = (wiringPiI2CRead(dev)| 0x04)| LCD_DISPLAYCONTROL; // 0x04 = Е в единицу
	    usleep(2);
	    wiringPiI2CWrite(dev, v );
	    usleep(2);
	    v = (wiringPiI2CRead(dev)& 0xFB) | LCD_DISPLAYCONTROL; // 0xFB = Е в ноль
	    usleep(2);
	    wiringPiI2CWrite(dev, v);
	}

	void lcd_cmd(int dev, int cmd){
		wiringPiI2CWrite(dev, (cmd & 0xF0)   | LCD_DISPLAYCONTROL);
	    lcd_notify(dev);
	    usleep(2);
	    wiringPiI2CWrite(dev, (cmd & 0x0F)<<4| LCD_DISPLAYCONTROL);
	    lcd_notify(dev);
	    wiringPiI2CWrite(dev, 0x0 | LCD_DISPLAYCONTROL);
	    usleep(2);
	}


public:
	MyLCD(int address)
	{
		dev = wiringPiI2CSetup (0x3f);
	};

	void Init()
	{
		usleep(400);
		wiringPiI2CWrite(dev, 0x30 | LCD_DISPLAYCONTROL); // enable 8 bit mode
		lcd_notify(dev);
		usleep(8);
		wiringPiI2CWrite(dev, 0x20 | LCD_DISPLAYCONTROL); // enable 4 bit mode
		lcd_notify(dev);
		usleep(8);
		lcd_notify(dev);
		usleep(8);
		wiringPiI2CWrite(dev, 0x30 | LCD_DISPLAYCONTROL); // enable 8 bit mode
		lcd_notify(dev);
		usleep(8);
		wiringPiI2CWrite(dev, 0x20 | LCD_DISPLAYCONTROL); // enable 4 bit mode
		lcd_notify(dev);
		usleep(8);
		lcd_notify(dev);
		usleep(80);
		lcd_cmd(dev, 0x28);
		lcd_cmd(dev, 0x08);
		lcd_cmd(dev, 0x01);
		lcd_cmd(dev, 0x06);
		lcd_cmd(dev, 0x0F);

	}

	void Clear(){
	    lcd_cmd(dev, 0x1);
	    lcd_cmd(dev, 0x2);
	    lcd_cmd(dev, 0x0C);
	}

	void Cursor(int set=1){
		if(set==1) lcd_cmd(dev, 0x0F);
		else lcd_cmd(dev, 0x0C);
		usleep(200);
	}

	void Putc(u8 c){
		wiringPiI2CWrite(dev, 0x01 | (c & 0xF0)   | LCD_DISPLAYCONTROL);
	    lcd_notify(dev);
	    wiringPiI2CWrite(dev, 0x01 | (c & 0x0F)<<4| LCD_DISPLAYCONTROL);
	    lcd_notify(dev);
	    wiringPiI2CWrite(dev, 0x00 | LCD_DISPLAYCONTROL);
	}


	void Print(char* str){
		unsigned int i, len =strlen(str);
	    for(i=0; i<len; ++i)
	        Putc(str[i]);
	}

	void Print(const char* str, u8 len, u8 line){
		u8 i;
		u8 rows[] = {0x00, 0x40, 0x14, 0x54};
		lcd_cmd(dev, 0x80 | rows[line]);
		for(i=0; i<len; ++i)
		    Putc(str[i]);
	}


	void BackLight(int set=1){
		if(set==1) wiringPiI2CWrite(dev, 0x08 );
		else wiringPiI2CWrite(dev, 0x00 );
		usleep(400);
	}


};

#endif /* PCF8574_LCD_16X2_H_ */
