void lcd_wrNybble(char n)
{
		LCD_D4 = (n & 1) ? 1 : 0;
		LCD_D5 = (n & 2) ? 1 : 0;
		LCD_D6 = (n & 4) ? 1 : 0;
		LCD_D7 = (n & 8) ? 1 : 0;
		delay_us(2);
		LCD_E=1;
		delay_us(2);
		LCD_E=0;
		delay_us(2);
}

void lcd_wrByte(char data, char rs)
{
	LCD_RS=0;
	delay_us(60);

	if(rs) LCD_RS=1;    // write data

	lcd_wrNybble((data >> 4) & 0xF);
	lcd_wrNybble(data & 0xF);
    delay_us(2);
	if(!str_pos_now) LCD_RS=0;
}

void lcd_EEdata_to_DDRAM(char eeprom *EE_adr)
{
	char tmp;
    char eeprom *adr;

	if(lcd_LineN != 0xFF) {
		tmp = 0x80;
		if(lcd_LineN) tmp |= 0x40;	// lcd_line=1
		lcd_wrByte(tmp, LCD_CMD);   // set display line
	}

	adr=EE_adr;
	while(1) {
		tmp = *adr;
		if(tmp==0xFF) break;    // end data
		if(EE_adr==conf_lcd) lcd_wrByte(tmp, LCD_CMD);
		else lcd_wrByte(tmp, LCD_DATA);
		adr++;
	}

	if(adr == EE_adr) {     // display clear line
		for(tmp=0; tmp<16; tmp++) lcd_wrByte(' ', LCD_DATA);
	}
}

void lcd_show_EEstr(char eeprom *EE_Adr)
{
	lcd_EEdata_to_DDRAM(EE_Adr);
	delay_ms(100);
	if(str_pos_now) str_pos_now--;
}
