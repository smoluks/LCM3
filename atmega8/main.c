#include <macros.h>

#define DLY_TMR1 54UL
#define DCADC_TIME 24872UL  // ADC confersion time
#define ulong unsigned long
#define uint unsigned int

#define LCD_CMD  0
#define LCD_DATA 1

#define LCD_E PORTB.0
#define LCD_RS PORTB.1
#define LCD_D4 PORTB.2
#define LCD_D5 PORTB.3
#define LCD_D6 PORTB.4
#define LCD_D7 PORTB.5

#define MODE_NULL PIND.6
#define MODE_CX	  PIND.7
#define MODE_SET  !PINC.1

#define CAL PORTD.5

#define RE  PORTD.0
#define DIR_RE DDRD.0
#define DIR_IN  0
#define DIR_OUT 1

void msr_Uesr(void);
void msr_ElCm(void);

volatile uint Uesr_cnt;
volatile char cnt_TMR1_OVR;
volatile char cnt_TMR0_OVR;
volatile uint cnt_TMR1;
//char Delay_3T @5;
//uint Uesr @6;

ulong time;
ulong cnt;
uint adc_dly;

// table
uint L0;
uint C0;
uint Kesr0;
uint Uesr0;
uint Re0;
ulong Cp0;
uint Ccal0;

char eeprom EE_str_off;
char lcd_LineN;
char str_pos_now;
float F1_pwr2;
float F0_pwr2;
float Fx_pwr2;
ulong Cx;
uint Fx;

uint ElCm_time;
uint Ucm0;
uint Ucm1;
uint UcmTop;
uint Utmp;
uint dUcm;

char dUc_200mS;
char dUc_100mS;
char lcd_value_point;
char var_XX = 0;
char str_pos_end;
char lcd_value_type;
uint Kesr;
char Uesr_OVR;
// char dly_uesr = 69;
ulong lcd_data;
ulong Tfx;

// flags_mode
bit fmInitTmr;
bit fmRdyOk;
bit fmElCx;
bit fmLCx;
bit fmRe;
bit fmFreqStab;
bit fmIc;
bit fmRx;

// flags_stat
bit fsDelay_1T;
bit fsDelay_2T;
bit fsElCx;
// bit fsFreqChange;
bit fsMinus;
//bit fsSt5;
bit fsCgAdr0;
bit fsCgAdr1;

#pragma keep+
eeprom char conf_lcd[] =    { 0x28,  // 4-bit interface, dual line, 5x7 dots
                            0x8,    // display off
                            0xC,    // display on, cursor off
                            0x1,    // clear display
                            0x6,    // display shift off, inc cursor move dir
                            0xFF };
eeprom char a_Cx[] =        {' ',0x5,' ','C','x',0xFF };
eeprom char a_Cp[] =        {' ',0x5,' ','C','p',0xFF };
eeprom char a_vC0[] =       {' ',0x5,' ','C','0',0xFF };
eeprom char a_Lx[] =        {' ',0x6,' ','L','x',0xFF };
eeprom char a_vL0[] =       {' ',0x6,' ','L','0',0xFF };
eeprom char a_ElCm[] =      {0x3,' ','C',' ','m',0xFF };
eeprom char a_rESR[] =      {0x4,' ','E','S','R',0xFF };
// eeprom char a_DlyUesr[] =   {' ',' ','D','l','y',0xFF };
eeprom char a_Ccal[] =      {0x3,'C','c','a','l',0xFF };
eeprom char a_F0[] =        {' ','F','0',' ',' ',0xFF };
eeprom char a_Fcal[] =      {' ','F','C','a','l',0xFF };
eeprom char a_ElCsz[] =     {0x3,'C',' ','s','z',0xFF };
eeprom char a_rRx[] =       {' ',0x4,' ','R','x',0xFF };
eeprom char a_lc_Lx[] =     {0x5,0x6,' ','L','x',0xFF };
eeprom char a_Uesr0[] =     {'U','e','s','r','0',0xFF };
eeprom char a_Fesr[] =      {'F','e','s','r',' ',0xFF };
eeprom char a_icEsr[] =     {0x2,'-','E','S','R',0xFF };
eeprom char a_Ro[] =        {' ',0x4,' ','R','o',0xFF };
eeprom char a_Re[] =        {' ',0x4,' ','R','e'};
eeprom char a_0xFF[] =      {0xFF };
eeprom char a_C0[] =        {' ',' ',' ','C','-','-','-','>','0',' ',' ',' ',' ',' ',' ',' ',0xFF };
eeprom char a_L0[] =        {' ',' ',' ','L','-','-','-','>','0',' ',' ',' ',' ',' ',' ',' ',0xFF };
eeprom char a_Err[] =       {' ',' ',' ','>','>','!','E','r','r','o','r','!','<','<',' ',' ',0xFF };
eeprom char a_SwTo[] =      {' ',' ',' ',' ','S','w','i','t','c','h',' ','t','o',' ',' ',' ',0xFF };
eeprom char a_ToMsr[] =     {' ',' ','M','e','a','s','u','r','e',' ','M','o','d','e','!',' ',0xFF };
eeprom char a_ToCx[] =      {' ',' ',' ',' ',' ','C','x',' ','M','o','d','e','!',' ',' ',' ',0xFF };
eeprom char a_ban0[] =      {'L','C','M','3','-','M','E','G','A','8',' ','C','L','O','N','E',0xFF };
eeprom char a_ban1[] =      {'v','.','1','.','0','d',' ','(','c',')','T','o','m','a','s','V',0xFF };
eeprom char zgn_lcd[] =     { 0x0, 0x0, 0x3, 0x4, 0x2, 0x5, 0x9, 0x6,
                              0x18, 0x8, 0x18, 0xB, 0x1A, 0x3, 0x1, 0x3,
                              0x0, 0x0, 0x13, 0x14, 0x14, 0x14, 0x13, 0x0,
                              0x4, 0x1F, 0x11, 0x1F, 0x0, 0x1F, 0x4, 0x0,
                              0x4, 0xE, 0xA, 0xA, 0xA, 0xE, 0x4, 0x0,
                              0x4, 0x4, 0x1F, 0x0, 0x1F, 0x4, 0x4, 0x0,
                              0x8, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x8, 0x0,
                              0x0, 0xE, 0x11, 0x11, 0x11, 0xA, 0x1B, 0x0, 0xFF };
eeprom char tbl_const[] =   { 0xE8, 0x24,   // L0=9448
                              0xAE, 0x29,   // C0=10670
                              0xC7, 0x35,   // Kesr=
                              0xE9, 0x04,   // Uesr0=1257
                              0xB8, 0x00,    // Re0=184
                              0x04, 0xC0, 0x04, 0x00,  // Cp0=311300
                              0xF4, 0x29 }; // Ccal0=10740

#pragma keep-

flash char range[] = { 'p','n','u','m',' ','k',0x0 };


interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
	if(fmInitTmr)
    {
		TCNT1 = 0;      // TMR1H=0;TMR1L=0;
		cnt_TMR1_OVR=0;
		TCNT0 = 0xC0;   // = -64
		fmInitTmr = 0;
	}
	else
    {
		cnt_TMR1 = TCNT1;
		cnt_TMR0_OVR++;
		if(cnt_TMR1_OVR > 7)
		{
			fmRdyOk=1;
			if((cnt_TMR1>>8) > 0) TIMSK &= ~(1<<TOIE1); // disable TMR1IE
		}

	}
}

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
     cnt_TMR1_OVR++;
}

interrupt [EXT_INT1] void ext_int0_isr(void)
{
	char i;
    GICR &= ~(1<<INT1);     // disable INT1
    #asm
    {
        NOP
        NOP
        MOV  R16,_Delay_3T
loop:
        SUBI  R16,1    // 1T
        BRNE loop   // 1/2T

        BST  R3,0   // 1T
        BRTC d2T    // 1/2T
        NOP
        NOP
d2T:
        BST  R3,1
        BRTC ddd
        NOP
        NOP
        NOP
ddd:
        NOP
    }
    #endasm

    ADCSRA |= (1<<ADSC);    // (2T)ADC Start Conversion
    NOP();
    NOP();

    while((ADCSRA & (1<<ADIF))==0);     // wait ADSC==0
        ADCSRA |= (1<<ADIF);    // clear ADIF

	if(!(Uesr_cnt & 1)) {
		#asm
        {
            IN R30, 0x4
            IN R31, 0x4+1
            ADD R6, R30
            ADC R7, R31
        }
        #endasm

        MCUCR |= (1<<ISC11) | (1<<ISC10);   // The rising edge of INT1 generates an interrupt request
	} else {
//		Uesr -= ADCW;
		#asm
        {
            IN R30, 0x4
            IN R31, 0x4+1
            SUB R6, R30
            SBC R7, R31
        }
        #endasm

		MCUCR &= ~(1<<ISC10);   // The falling edge of INT1 generates an interrupt request.
	}

	Uesr_cnt++;

	if((Uesr & (1<<13)) && (Uesr & (1<<12))) {
	    Uesr_OVR++;
	    Uesr &= ~(1<<13);
    }

    GIFR |= (1<<INTF1);     // clear INTF1

    if(Uesr_cnt < 3200) GICR |= (1<<INT1);  // enable INT1

    GIFR |= (1<<INTF1);     // clear INTF1

    i=0;
    while(i<64) {
        if(GIFR & (1<<INTF1)) break;
        i++;
    }

    GIFR |= (1<<INTF1);     // clear INTF1
}

void msr_Freq(void)
{
    ADMUX &= 0xF0;  // Extn ref?
    ADMUX |= 5;     // 5 channel
    CAL = 0;
	delay_ms(100);
	//
	Fx_pwr2 = 0;
    Fx = 0;
    fmInitTmr = 1;
	fmRdyOk = 0;
	//
	cnt_TMR0_OVR = 0xFF;
	cnt_TMR1_OVR = 0;
	TCNT0 = 0xFE;
	TCNT1 = 0;
	// Enable interrupts
	TIFR |= (1<< TOV0);
	TIMSK |= (1<<TOIE1);
	TIMSK |= (1<<TOIE0);
	SEI();
	delay_ms(50);
    //
	if(!fmInitTmr)
    {
		if(fmRe)
			while(!fmRdyOk && !(cnt_TMR1_OVR & 0x80));
		else
			while(!fmRdyOk && !(cnt_TMR1_OVR > 39));
	}
	// Disable interrupts
	CLI();
	TIMSK &= ~(1<<TOIE0);    // disable Timer0 Overflow Interrupt
	TIMSK &= ~(1<<TOIE1);    // disable Timer1 Overflow Interrupt
	if(!fmRdyOk) return;
	cnt = ((ulong)cnt_TMR0_OVR<<2) + 1;     // = pulse_cnt/64 + 1
    time = ((ulong)cnt_TMR1_OVR<<16) + cnt_TMR1 - DLY_TMR1;   // =t[0.2 uS] DLY_TMR1==54
    time >>= 1;
    float tmp =(3200000.0*cnt/time);
	Fx = tmp;           // = F[kHz*10]
	Fx_pwr2 = tmp*tmp;  // = Fx^2[kHz^2*100]

	if(fmRe) Fx_pwr2 -= 0.6;

    Kesr = Fx_pwr2/55.0;    // = Fx^2/55.0

    Tfx = (10000.0/(Fx*0.1))*1.75;

    adc_dly = Tfx - 69.0;

	Delay_3T = 0;
    while(adc_dly > 2) {
		adc_dly -= 3;
		Delay_3T++;
	}

	fsDelay_1T = adc_dly & 1;
    fsDelay_2T = (adc_dly >> 1) & 1;
}

void lcd_prep_str(void)
{
	char str[12];
	char pos;
	uint val, data;
	char idx, i;

	pos = 7;
    str[0]=' ';
	str[1]=' ';
	str[2]=' ';
	str[3]=' ';
	str[4]=' ';
	str[5]=' ';
	str[6]=' ';
	str[7]='?';
	str[8]=' ';
	str[9]=' ';
	str[10]=' ';
	str[11]=0;

	if(fsElCx) str[2] = '=';
	else str[1] = '=';

	if((a_rESR == EE_str_off) && (fmRdyOk)) {
            str[0]=0;   // ==zgn_delta
            str[1]=1;   // ==zgn_graph
        }

	fsMinus = 0;
    if(lcd_data & (1<<31)) {
        fsMinus = 1;
        lcd_data = (uint)(0 - lcd_data);
    }

	if(lcd_LineN == 0) {
		data = lcd_data;
        idx = fmElCx ? 0 : 4;

		while((data > 16) && (idx < 6)) {
			data >>= 1;
			idx++;
		}

		idx -= 7;
		idx = (idx<<4)|(idx>>4);	// swap
		idx += (data & 0xFF);

        if(!fmRdyOk) idx=0xFF;
		var_XX += 2;
		var_XX -= idx;

		if(str_pos_now) {
			fsCgAdr0 ^= 1;
			if(!fsCgAdr0) fsCgAdr1 = 1;
			if(fsCgAdr0 && !fsCgAdr1) str_pos_now--;
		}

		if(var_XX >= 4) {
			var_XX = str_pos_end - str_pos_now;
			var_XX >>= 2;
			var_XX &= 0x3F;
			while(var_XX) {
				var_XX >>= 1;
				if(str_pos_end != 0xFF)	str_pos_end++;
			}
			if(!str_pos_now) str_pos_now = str_pos_end;
		}

		var_XX = idx;
	}

	if(!fmRdyOk) goto copy_str;

	while(lcd_data > 9743) {
        lcd_data /= 10;
        lcd_value_point++;
    }

    idx = 0;
	while(lcd_value_point > 2) {
        lcd_value_point -= 3;
        idx++;
    }

    // convert to dec
	lcd_value_point += 4;
	if(fsElCx) lcd_value_point++;
	if(lcd_value_point == 7) lcd_value_point = 0;

	// convert data to char's
	while(1) {
		if(pos == lcd_value_point) {    // init: pos==7
			str[pos] = '.';
            pos--;
			lcd_value_point = 0;
		}

		val = 0;
		while(lcd_data > 9) {
			lcd_data -= 10;
			val++;
		}

		str[pos] = lcd_data + '0';
        pos--;

        if(fsElCx) {
            pos = 7;
            fsElCx = 0;
        }

        lcd_data = val;
		if(lcd_data) continue;
        if(!lcd_value_point) break;
	}

	if(pos == 7) pos--;

	if(fsMinus) str[pos] = '-';

	str[9] = range[idx];     // idx='p','n','u','m',' ','k'

	if(dUc_100mS) { str[0] = dUc_200mS; str[1]= dUc_100mS; }

copy_str:
    str[10] = lcd_value_type;
	dUc_100mS = 0;
	// show LCD display data
	lcd_EEdata_to_DDRAM(EE_str_off);

    i=0;
	while(i<=10) lcd_wrByte(str[i++], LCD_DATA);
}

void cal_L0_C0(void)
{
    float sav_F1_pwr2;
    float tmpC;

    sav_F1_pwr2 = F1_pwr2;
    F1_pwr2 = Fx_pwr2;

    CAL = 1;
    delay_ms(500);
    msr_Freq();
    CAL = 0;

    F0_pwr2 = Fx_pwr2;

    Cx = (ulong)((float)Ccal0/(F1_pwr2/F0_pwr2 - 1.0));

    F0_pwr2 = F1_pwr2;

    if(!MODE_CX) F1_pwr2 = sav_F1_pwr2;

    // Lx=(1/(2*pi)^2)/(Cx*F0^2)
    if(fmRe) tmpC = 2.533029591e+14F;
    else tmpC = 2.533029591e+15F;

    lcd_data = (ulong)(tmpC/((float)Cx*F0_pwr2));

    if(!MODE_CX) {
        L0 = lcd_data;
        L0--;
        C0 = Cx;
        C0++;
    }
}

uint msr_DC_ADC(void)
{
    char i;
    uint res;

    delay_us(20);
    res = 3;

    for(i=0;i<49;i++) {
        ADCSRA |= (1<<ADSC);                // ADC Start Conversion
	    while((ADCSRA & (1<<ADIF))==0);     // wait ADIF==1
        ADCSRA |= (1<<ADIF);                // clear ADIF
        res += ADCW;
    }
    res &= 0xFFF8;
    return res;
}

void lcd_clear_line(char line)
{
    char tmp;

    tmp = lcd_LineN;
    lcd_LineN = line;
    lcd_EEdata_to_DDRAM(a_0xFF);
    lcd_LineN = tmp;
}

void init_lcm(void)
{
	char *ptr;
    char i;


    DIR_RE = DIR_OUT;
    RE = 0;

    LCD_RS=0;
    LCD_E=0;

// ====== configure LCD ==========
    delay_ms(16);		// wait 16ms or more after power-on
    lcd_wrNybble(3);	// init
    delay_ms(5);
    lcd_wrNybble(3);	// init
    delay_ms(5);
	lcd_wrNybble(2);	// set 4-bit mode

	lcd_EEdata_to_DDRAM(conf_lcd);
	delay_ms(10);		// 10mS

	lcd_wrByte(0x40,LCD_CMD);	    // Cmd=0x40(Sets CGRAM address 0x0)
	lcd_LineN=0xFF;
	lcd_EEdata_to_DDRAM(zgn_lcd);   // load LCD graphic's to CGRAM

   	DIR_RE = DIR_IN;    // Re OFF

    lcd_LineN=0;
	lcd_EEdata_to_DDRAM(a_ban0);
    lcd_LineN=1;
	lcd_EEdata_to_DDRAM(a_ban1);

	delay_ms(2000);

    lcd_LineN=0;
	str_pos_end=0x40;
	str_pos_now=0xFF;
	while(MODE_NULL) {
        lcd_show_EEstr(a_SwTo);
        lcd_LineN = 1;
        lcd_show_EEstr(a_ToMsr);
        lcd_LineN = 0;
    }
	while(!MODE_CX) {
        lcd_show_EEstr(a_SwTo);
        lcd_LineN = 1;
        lcd_show_EEstr(a_ToCx);
        lcd_LineN = 0;
    }
	str_pos_now=0x40;

    // init constants
    ptr = (char*)&L0;
	for(i=0;i<16;i++) *(ptr+i) = tbl_const[i];

	delay_ms(2000);

    msr_Freq();
	EE_str_off = a_F0;  // ' ','F','0',' ',' '
	lcd_value_type = ' ';
	lcd_value_point = 17;
	fsElCx = 0;
	dUc_100mS = 0;
	lcd_data = Fx;
    lcd_prep_str();

    cal_L0_C0();
    lcd_data = Fx;
    lcd_LineN = 1;
    lcd_value_point = 17;
    EE_str_off = a_Fcal;
    lcd_prep_str();

    delay_ms(2000);
}

void msr_Uesr(void)
{
	Uesr_cnt = 0;
	Uesr = 15;
	dUc_100mS = 0;
	Uesr_OVR = 0;
	fmRdyOk=0;

	if(Fx < 650) return;   // < 65khZ
	if(Fx > 950) return;   // > 95khZ

	ADMUX &= 0xF0;  // ADC.0
    ADMUX |= 2;     //ADC.2(Uesr)
	delay_us(10);

	MCUCR &= ~(1<<ISC10);
    MCUCR |= (1<<ISC11);    // The falling edge of INT1 generates an interrupt request.
	GICR |= (1<<INT1);      // External Interrupt Request 1 Enable

    SEI();
    delay_ms(100);

	GICR &= ~(1<<INT1);     // External Interrupt Request 1 Disable
	CLI();

	ADMUX &= 0xF0;  // ADC.0
    ADMUX |= 5;     // ADC.5(ElCx)
	Uesr >>= 5;                     // divide by 32
    Uesr &= 0x7FF;
    while(Uesr_OVR) { Uesr += 256; Uesr_OVR--; }

//	Uesr += (uint)Uesr_OVR << 8;    // ==Uesr[mV*10]
	if(Uesr > 30) fmRdyOk=1;        // Uesr > 3.0[mV]
}

void msr_Cp(void)
{
    char F_ReOn, F_ReOff;
    float sav_F1_pwr2;

    sav_F1_pwr2 = F1_pwr2;  // save F1_pwr2
    fmLCx = 0;

//---- msr_Freq(ReOn) ---
    DIR_RE = DIR_OUT;
    RE = 0;
    fmRe = 1;
    msr_Freq();

//--- check F_ReOn ---
    F_ReOn = Fx & 0xFF;            // F_ReOn=Fx(ReOn);
    if(Fx >> 8) F_ReOn = 0xFF;     // Fx(ReOn) > 25.6[kHz]
    if(!F_ReOn) F_ReOn++;
    if(!fmRdyOk) F_ReOn = 0;

//--- msr_Freq(ReOff) ---
    DIR_RE = DIR_IN;
    fmRe = 0;
    msr_Freq();

//--- check F_ReOff ---
    F_ReOff = (Fx >> 3) & 0xFF;                  // F_ReOff=Fx(ReOff)/8
    if((Fx >> 9 & 0xFF) > 7) F_ReOff = 0xFF;     // Fx(ReOff) > 358.4[kHz]
    if(!F_ReOff) F_ReOff++;
    if(!fmRdyOk) F_ReOff = 0;

    if(!F_ReOn || F_ReOn > 59) goto cont;             // F_ReOn > 5.9Khz
    if((F_ReOn > 23) && (F_ReOff < F_ReOn)) goto cont;  // F_ReOn > 2.3kHz
    if(F_ReOn > 7) goto msr_ReOn;   // F_ReOn > 0.7kHz
    if(F_ReOff > 16) goto cont;     // F_ReOff > 12.8kHz

msr_ReOn:
//--- msr_Freq(ReOn) ---
    DIR_RE = DIR_OUT;
    RE = 0;
    fmRe = 1;
    msr_Freq();
    F_ReOff = 0;
    fmRdyOk = 1;

//-----------------------------------------
cont:
    F0_pwr2 = Fx_pwr2;  // F0_pwr2=F^2(CcalOff && ReOn)

    if(F_ReOff) { fmRdyOk = 1; F_ReOn = 0; }
    if(F_ReOn > 7) goto msr_CcalOn;             // F_ReOn > 0.7kHz
    if(F_ReOff > 127 || F_ReOff==0) goto exit;  // F_ReOff > 101.6kHz

msr_CcalOn:
    F1_pwr2 = F0_pwr2;  // F1_pwr2=F^2(CcalOff && ReOn)

//--- msr_Freq(CcalOn) ---
    CAL = 1;    // Ccal=On
    delay_ms(500);
    msr_Freq();
    CAL = 0;    // Ccal=Off
    F0_pwr2 = Fx_pwr2;  // F0_pwr2=F^2(CcalOn && ReOn)

//--- calc Cp0 ---
    Cx = (float)Ccal0 / (F1_pwr2 / F0_pwr2 - 1.0);
    fmLCx = 1;

exit:
    F1_pwr2 = sav_F1_pwr2;  // restore F1_pwr2
}

void set_Null(void)
{
    uint Ucal;
    char i;
    char *ptr;

    lcd_clear_line(1);
    lcd_LineN = 0;

    delay_ms(100);

    if(!fmRdyOk || MODE_NULL==0)
    {
        lcd_EEdata_to_DDRAM(a_Err);
        goto exit;
    }

    while(MODE_SET)
    {
        if(!MODE_NULL)
            if((Ccal0 >> 8) < 46) Ccal0++;  // < 1177.6[pF]
        if(!MODE_CX)
            if((Ccal0 >> 8) > 34) Ccal0--;  // > 870.4[pf]

        lcd_value_type = 'F';
        lcd_data = Ccal0;
        EE_str_off = a_Ccal;    // ' ', 'C', 'c', 'a', 'l'
        lcd_value_point = 2;
        str_pos_now = str_pos_end;
        lcd_prep_str();
        delay_ms(100);
    }

    DIR_RE = DIR_OUT;
    RE = 1;
    delay_us(35);

    Ucal = msr_DC_ADC();  // ADC.2(AN6)

#define URE  47120UL      // [mV*10]
#define RCAL 49UL         // [Ohm]

    if(((Ucal >> 8) & 0xFF) > 27)  // > 691.2 mV
    {
        lcd_data = (URE*RCAL/Ucal)-RCAL;     // Re=(Rcal*U0)/Ux - Rcal
        if(lcd_data != Re0) Re0 = lcd_data;
    }

    DIR_RE = DIR_IN;

    lcd_clear_line(0);
    lcd_value_type = 7;   // "Ohm"
    lcd_value_point = 15;
    lcd_data = Re0;
    EE_str_off = a_Re;  //' ',' ',' ','R','e'
    fsElCx = 0;
    lcd_prep_str();

    delay_ms(2000);

    lcd_EEdata_to_DDRAM(a_SwTo);
    lcd_LineN = 1;
    lcd_EEdata_to_DDRAM(a_ToMsr);
    str_pos_now = 0xFF;

    while(MODE_NULL) {
        lcd_LineN = 0;
        lcd_show_EEstr(a_SwTo);
        lcd_LineN = 1;
        lcd_EEdata_to_DDRAM(a_ToMsr);
    }

    lcd_LineN = 0;
    str_pos_now = str_pos_end;

    delay_ms(2000);

    msr_Freq();

    if(Fx > 1050) {      // >105kHZ
        cal_L0_C0();
        fmElCx = 0;
        lcd_clear_line(0);
        if(MODE_CX) {
            lcd_value_type = 'F';
            lcd_value_point = 2;
            EE_str_off = a_vC0;
            lcd_data = Cx;
            lcd_prep_str();
            lcd_LineN = 1;
            lcd_EEdata_to_DDRAM(a_C0);  // 'C', '-', '>', '0', 0FF
        } else {
            lcd_value_type = 'H';
            lcd_value_point = 7;
            EE_str_off = a_vL0;
            lcd_prep_str();
            lcd_LineN = 1;
            lcd_EEdata_to_DDRAM(a_L0);  // 'L', '-', '>', '0', 0FF
        }
    } else {
        Kesr0 = Kesr;
        msr_Uesr();
        Uesr0 = Uesr;
        msr_Cp();
        Cp0 = Cx;

        //show Ro0
        lcd_data = L0;
        lcd_data *= L0;
        lcd_data >>= 16;
        lcd_data *= Kesr;
        lcd_data /= Uesr0;
//        Ro0 = lcd_data;

        lcd_LineN = 0;
        lcd_value_type = 7;       // "Ohm"
        lcd_value_point = 11;
        EE_str_off = a_Ro;
        lcd_prep_str();

       // show Cp
//        lcd_clear_line(1);
        lcd_LineN = 1;
        lcd_value_type = 'F';
        lcd_value_point = 2;
        EE_str_off = a_Cp;  // ' ',' ',' ','C','p'
        lcd_data = Cx;
        lcd_prep_str();
        delay_ms(8000);

        // show Uesr
        lcd_LineN = 0;
        lcd_value_type = 'V';
        lcd_value_point = 11;
        EE_str_off = a_Uesr0;
        fsElCx = 0;
        lcd_data = Uesr0;
        lcd_prep_str();
//        delay_ms(4000);

        lcd_LineN = 1;
        lcd_value_type = ' ';
        lcd_value_point = 17;
        EE_str_off = a_Fesr;
        lcd_data = Fx;
        lcd_prep_str();
    }
    // write to EEPROM
    ptr = (char*)&L0;
	for(i=0;i<16;i++) tbl_const[i] = *(ptr+i);

exit:
    delay_ms(4000);
}

void msr_ElCm(void)
{
    uint Ux;

    ElCm_time = 0;
    lcd_data = 0;

    if(fmRx || fmIc) {
        delay_ms(500);
        return;
    }

    EE_str_off = a_ElCm;       // 3,' ','C',' ','m'
    fmElCx = 0;

    DIR_RE = DIR_OUT;
    RE = 0;
    delay_ms(500);          // discharge elCm 500mS
    DIR_RE = DIR_IN;

    Ucm0 = msr_DC_ADC();    // ADC.2

    if(Ucm0 & (1<<15)) goto discharge_Cm_5mS;   // Ucm0 > 3276.8[mV]

    Ucm1 = (Ucm0 + 10000) / 49;     // Ucm1 = Ucm0 + 1000.0[mV]

    // charge Cm to Ucm0 + 1000.0[mV]
    DIR_RE = DIR_OUT;
    RE = 1;

    while(1) {
        ElCm_time++;
        ADCSRA |= (1<<ADSC);                // ADC Start Conversion
	    while((ADCSRA & (1<<ADIF))==0);     // wait ADSC==0
        ADCSRA |= (1<<ADIF);
        if((ElCm_time & (1<<14)) || (ADCW >= Ucm1)) break;
    }

    DIR_RE = DIR_IN;

    UcmTop = msr_DC_ADC();
    if((ElCm_time & (1<<14)) && ((Ucm0+256) > UcmTop)) fmRx = 1;
    if(ElCm_time < 2) goto discharge_Cm_5mS;

    // ElCm connected
    fmElCx = 1;
    fsElCx = 1;
    lcd_value_point = 6;
    lcd_value_type = 'F';
    Utmp = UcmTop;

    while(1) {
        delay_ms(100);
        Ux = msr_DC_ADC();    //ADC.2
        Utmp -= Ux;
        Utmp >>= 4;
        Utmp &= 0xFFF;
        dUc_200mS = 0;
        if((Utmp & (1<<11))) goto next;

        if(Utmp > 99) Utmp = 99;    // 158.4[mV]

        if(fmElCx) dUc_100mS = (char)Utmp;
        else {
            dUc_200mS = (char)Utmp;
            if(dUc_200mS <= 1) dUc_200mS = 0;
            dUc_200mS <<= 1;
        }
next:
        fmElCx ^= 1;
        Utmp = Ux;
        if(fmElCx) break;
    }

    // --- show el_C_sz ---
    if(dUc_100mS >= dUc_200mS) EE_str_off = a_ElCsz;    // 3,'C',' ','s','z'

    dUc_200mS = '0';
    while(dUc_100mS > 9) { dUc_100mS -= 10; dUc_200mS++; }
    dUc_100mS += '0';

    if(dUc_200mS == '0') { dUc_200mS = dUc_100mS; dUc_100mS = ' '; }

    dUcm = UcmTop - Ucm0;

    // elC = [(50127-Ucm0)*23400/dUcm-12500]/Re*cnt-49
    // elC = (Ue/Re)/dUc*Tc

    lcd_data = (((((50127UL - Ucm0) * DCADC_TIME)
                / dUcm) - 12500UL) / Re0)
                * ElCm_time - 49UL;


    if(lcd_data < (3<<8)) {   // elC < 768[nF]
        lcd_data *= 10;
        lcd_value_point--;
    }

discharge_Cm_5mS:
    DIR_RE = DIR_OUT;
    RE = 0;
    delay_ms(5);
    Utmp = msr_DC_ADC();
    DIR_RE = DIR_IN;

    if(!(ElCm_time & (1<<14))) return;
    if((Ucm0 >> 8) & 0xFF) return;          // Ucm0 > 256
    if(((dUcm >> 8) & 0xFF) <= 0) return;   // dUcm <= 256
    if((Utmp >> 8) & 0xFF) return;         // disUcm > 256

    if(fmFreqStab) { fmFreqStab = 0; fmRdyOk = 0; }
    else { fmRx = 0; fmIc = 1; }    // mode=Ic
}

void calc_Cx(void)
{
    lcd_data = (float)Cx*(F1_pwr2/F0_pwr2 - 1.0);
    EE_str_off = a_Cx;      // ' ',5,' ','C','x'
    lcd_value_point = 2;
    lcd_value_type = 'F';
}

void calc_Lx(void)
{
    float tmpC;

    lcd_value_type = 'H';
    lcd_value_point = 7;
    EE_str_off = a_Lx;      // ' ',6,' ','L','x'
/*
    if(fmFreqStab) {
        if(fmRdyOk) fmFreqStab = 0;
        msr_Cp();   // set fmLCx!!!
    }
*/
    if(!fmLCx) {
        if(fmRe) Cx = Cp0;  // Re==On
        else Cx = C0;       // Re==Off
    }

    // Lx=(1/(2*pi)^2)/(Cx*F0^2)
    if(fmRe) tmpC = 2.533029591e+14F;
    else tmpC = 2.533029591e+15F;

    lcd_data = (ulong)(tmpC/((float)Cx*F0_pwr2));

    if(fmLCx) EE_str_off = a_lc_Lx;

    if(fmRe) {
        lcd_value_point++;
        fsElCx = 1;
        return;
    }

    delay_ms(500);
    lcd_data -= L0;  // = Lx-L0
}

void msr_Rx(void)
{
    float Ro, dUesr;
    uint tmp;
    char mask, graph;

    fsMinus = 0;
    fsElCx = 1;

//    lcd_data = Uesr0;
/*
    if(Kesr0 > Kesr) lcd_data *= Kesr0;
    else {
        lcd_data *= Kesr;
        Kesr = Kesr0;
    }

    lcd_data /= Kesr;
*/
    msr_Uesr();         // res=Uesr

    if(!fmRdyOk) return;

    Ro = (float)L0;
    Ro *= Ro;
    Ro *= (float)Kesr;
//    Ro /= 65536.0;
    Ro /= 53603.8;
    Ro /= (float)Uesr0;

    dUesr = (float)(Uesr0 - Uesr);
    if(Uesr > Uesr0) {
        fsMinus = 1;
        dUesr = (float)(Uesr - Uesr0);
    }

    Ro *= dUesr;
/*
    if(fmIc) {
        tmp = (Uesr0 >> 16) / 3;
        if(Uesr > tmp) fmRdyOk = 0;
        Uesr -= tmp;
        if(Uesr < 29) fmRdyOk = 0;
    }
*/
    lcd_data = (ulong)(Ro/(float)Uesr);

/*
    lcd_data = L0;
    lcd_data *= L0;
    lcd_data >>= 16;
    lcd_data *= Kesr;
    lcd_data /= Uesr;

    if(lcd_data < Ro0) { fsMinus = 1; lcd_data = Ro0 - lcd_data; }
    else lcd_data -= Ro0;
*/
    if(fsMinus) { lcd_data = 0 - lcd_data; return; }
    if(fmRx) return;
    if(fmIc) return;
// =============================================================
// ================ graph ElCx ESR ===================================
    ElCm_time |= 1;
    tmp = (ulong)(lcd_data * ElCm_time) >> 16;  // =Resr*ElCm

    lcd_wrByte(0x48,LCD_CMD);     // Sets_CGRAM_address 0x8

    graph = (tmp >> 8) ? 0x1F : 0;

    mask = 0xFF;
    while(mask)
    {
        mask >>= 1;
        if(mask > (tmp & 0xFF)) {
            graph <<= 1;
            graph |= 1;
        }
        graph &= 0x1F;
        lcd_wrByte(graph,LCD_DATA);
    }
}

void main(void)
{
//ports
PORTB=0x00;
DDRB=0b00111111;
PORTC=0x00;
DDRC=0x00;
PORTD=0x00;
DDRD=0b00100001;
// Timer/Counter 0 initialization
// Clock source: T0 pin Falling Edge - частота контура
TCCR0=0x06;
TCNT0=0x00;
// Timer/Counter 1 initialization - системная частота
TCCR1A=0x00;
TCCR1B=0x01;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
// Timer/Counter 2 initialization
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;
// External Interrupt(s) initialization
MCUCR=0x00;
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x05;// OCB+T0
// Comp disable lold
ACSR=0x80;
SFIOR=0x00;
//SFIOR |= (1<<PUD);  // Pull-up Disable
// ADC initialization
ADMUX = (1<<REFS0);     // Vref = AVCC with external capacitor at AREF pin
ADCSRA = (1<<ADPS2);    // Division Factor=16
ADCSRA |= (1<<ADEN);    // ADC Enable
//
init_lcm();
//
while(1)
{
    msr_Freq();
    F0_pwr2 = Fx_pwr2;
    if(Fx > 1050)
    {  // > 105kHz
        fmRx = 0;
        fmIc = 0;
        fmElCx = 0;
    }
    if(MODE_NULL)
       set_Null();
    if(MODE_CX)
    {
        if(fmRe)
        {
            DIR_RE = DIR_IN;
            fmRe = 0;
        }
        fmLCx = 0;
        msr_ElCm();
        if(!fmElCx)
        calc_Cx();
    }
    else calc_Lx();
    //LCD хрень
    lcd_LineN = 0;
    if(!fmRx && !fmIc) lcd_prep_str();
    lcd_LineN++;
    if(MODE_NULL) set_Null();
    if(fmElCx)
    {
        msr_Rx();
        lcd_value_type = 7;       // "Ohm"
        lcd_value_point = 11;
        EE_str_off = a_rESR;    // 4,' ','E','S','R'
        if(fmRx)
        {
            EE_str_off = a_rRx;  // ' ',4,' ','R','x'
            lcd_LineN = 0;
        }
        if(fmIc)
        {
            EE_str_off = a_icEsr;  // 2,'-','E','S','R'
            lcd_LineN = 0;
        }
        lcd_prep_str();
        if(fmRx)
        {
                lcd_LineN = 1;
                lcd_value_type = 'V';
                lcd_value_point = 11;
                EE_str_off = a_Uesr0;
                lcd_data = Uesr;
                lcd_prep_str();
            }
            goto is_lcd_LineN;
        }

        // show_Cp
        lcd_value_type = 'F';
        lcd_value_point = 2;
        if(!fmLCx) goto clr_lcd_LineN;

        EE_str_off = a_Cp;  // ' ',' ',' ','C','p'
        lcd_data = Cx;

        if(fmRe) {
            fsElCx = 1;
            lcd_data -= Cp0;
            if(lcd_data < 63) fmLCx = 0;
        } else lcd_data -= C0;

        if(lcd_data & (1<<31)) fmLCx = 0;
        if(fmLCx) lcd_prep_str();
        goto is_lcd_LineN;

clr_lcd_LineN:
        lcd_LineN = 0;
is_lcd_LineN:
        if(!lcd_LineN) {
            lcd_LineN++;
            lcd_clear_line(lcd_LineN);
        }
    };

}
