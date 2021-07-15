#line 28 "C:\LCM3\main.c"
void msr_Uesr(void);
void msr_ElCm(void);

#line 35 "C:\Program Files\include\AVRdef.h"
unsigned char FlashReadByte(unsigned char ramp, unsigned addr);
unsigned FlashReadWord(unsigned char ramp, unsigned addr);
unsigned long FlashReadLWord(unsigned char ramp, unsigned addr);
void FlashReadBytes(unsigned char ramp, unsigned addr, unsigned char *buf, int n);



unsigned char EDataReadByte(unsigned char ramp, unsigned addr);
unsigned EDataReadWord(unsigned char ramp, unsigned addr);
unsigned long EDataReadLWord(unsigned char ramp, unsigned addr);
void EDataReadBytes(unsigned char ramp, unsigned addr, unsigned char *buf, int n);

void EDataWriteByte(unsigned char ramp, unsigned addr, unsigned char v);
void EDataWriteWord(unsigned char ramp, unsigned addr, unsigned int v);
void EDataWriteLWord(unsigned char ramp, unsigned addr, unsigned long v);
void EDataWriteBytes(unsigned char ramp, unsigned addr, unsigned char *buf, int n);






















void _StackCheck(void);
void _StackOverflowed(char);

#line 33 "C:\LCM3\main.c"
#pragma regalloc+
volatile unsigned int Uesr_cnt;
volatile char cnt_TMR1_OVR;
volatile char cnt_TMR0_OVR;
volatile unsigned int cnt_TMR1;


#pragma regalloc-

unsigned long time;
unsigned long cnt;
unsigned int adc_dly;


unsigned int L0;
unsigned int C0;
unsigned int Kesr0;
unsigned int Uesr0;
unsigned int Re0;
unsigned long Cp0;
unsigned int Ccal0;

char eeprom EE_str_off;
char lcd_LineN;
char str_pos_now;
float F1_pwr2;
float F0_pwr2;
float Fx_pwr2;
unsigned long Cx;
unsigned int Fx;

unsigned int ElCm_time;
unsigned int Ucm0;
unsigned int Ucm1;
unsigned int UcmTop;
unsigned int Utmp;
unsigned int dUcm;

char dUc_200mS;
char dUc_100mS;
char lcd_value_point;
char var_XX = 0;
char str_pos_end;
char lcd_value_type;
unsigned int Kesr;
char Uesr_OVR;

unsigned long lcd_data;
unsigned long Tfx;


bit fmInitTmr;
bit fmRdyOk;
bit fmElCx;
bit fmLCx;
bit fmRe;
bit fmFreqStab;
bit fmIc;
bit fmRx;


bit fsDelay_1T;
bit fsDelay_2T;
bit fsElCx;

bit fsMinus;

bit fsCgAdr0;
bit fsCgAdr1;

#pragma keep+
eeprom char conf_lcd[] = { 0x28, 
 0x8, 
 0xC, 
 0x1, 
 0x6, 
 0xFF };
eeprom char a_Cx[] = {' ',0x5,' ','C','x',0xFF };
eeprom char a_Cp[] = {' ',0x5,' ','C','p',0xFF };
eeprom char a_vC0[] = {' ',0x5,' ','C','0',0xFF };
eeprom char a_Lx[] = {' ',0x6,' ','L','x',0xFF };
eeprom char a_vL0[] = {' ',0x6,' ','L','0',0xFF };
eeprom char a_ElCm[] = {0x3,' ','C',' ','m',0xFF };
eeprom char a_rESR[] = {0x4,' ','E','S','R',0xFF };

eeprom char a_Ccal[] = {0x3,'C','c','a','l',0xFF };
eeprom char a_F0[] = {' ','F','0',' ',' ',0xFF };
eeprom char a_Fcal[] = {' ','F','C','a','l',0xFF };
eeprom char a_ElCsz[] = {0x3,'C',' ','s','z',0xFF };
eeprom char a_rRx[] = {' ',0x4,' ','R','x',0xFF };
eeprom char a_lc_Lx[] = {0x5,0x6,' ','L','x',0xFF };
eeprom char a_Uesr0[] = {'U','e','s','r','0',0xFF };
eeprom char a_Fesr[] = {'F','e','s','r',' ',0xFF };
eeprom char a_icEsr[] = {0x2,'-','E','S','R',0xFF };
eeprom char a_Ro[] = {' ',0x4,' ','R','o',0xFF };
eeprom char a_Re[] = {' ',0x4,' ','R','e'};
eeprom char a_0xFF[] = {0xFF };
eeprom char a_C0[] = {' ',' ',' ','C','-','-','-','>','0',' ',' ',' ',' ',' ',' ',' ',0xFF };
eeprom char a_L0[] = {' ',' ',' ','L','-','-','-','>','0',' ',' ',' ',' ',' ',' ',' ',0xFF };
eeprom char a_Err[] = {' ',' ',' ','>','>','!','E','r','r','o','r','!','<','<',' ',' ',0xFF };
eeprom char a_SwTo[] = {' ',' ',' ',' ','S','w','i','t','c','h',' ','t','o',' ',' ',' ',0xFF };
eeprom char a_ToMsr[] = {' ',' ','M','e','a','s','u','r','e',' ','M','o','d','e','!',' ',0xFF };
eeprom char a_ToCx[] = {' ',' ',' ',' ',' ','C','x',' ','M','o','d','e','!',' ',' ',' ',0xFF };
eeprom char a_ban0[] = {'L','C','M','3','-','M','E','G','A','8',' ','C','L','O','N','E',0xFF };
eeprom char a_ban1[] = {'v','.','1','.','0','d',' ','(','c',')','T','o','m','a','s','V',0xFF };
eeprom char zgn_lcd[] = { 0x0, 0x0, 0x3, 0x4, 0x2, 0x5, 0x9, 0x6,
 0x18, 0x8, 0x18, 0xB, 0x1A, 0x3, 0x1, 0x3,
 0x0, 0x0, 0x13, 0x14, 0x14, 0x14, 0x13, 0x0,
 0x4, 0x1F, 0x11, 0x1F, 0x0, 0x1F, 0x4, 0x0,
 0x4, 0xE, 0xA, 0xA, 0xA, 0xE, 0x4, 0x0,
 0x4, 0x4, 0x1F, 0x0, 0x1F, 0x4, 0x4, 0x0,
 0x8, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x8, 0x0,
 0x0, 0xE, 0x11, 0x11, 0x11, 0xA, 0x1B, 0x0, 0xFF };
eeprom char tbl_const[] = { 0xE8, 0x24, 
 0xAE, 0x29, 
 0xC7, 0x35, 
 0xE9, 0x04, 
 0xB8, 0x00, 
 0x04, 0xC0, 0x04, 0x00, 
 0xF4, 0x29 }; 

#pragma keep-

__flash char range[] = { 'p','n','u','m',' ','k',0x0 };

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
 if(fmInitTmr) {
 TCNT1 = 0; 
 cnt_TMR1_OVR=0;
 TCNT0 = 0xC0; 
 fmInitTmr = 0;
 } else {
 cnt_TMR1 = TCNT1;
 cnt_TMR0_OVR++;

 if(cnt_TMR1_OVR > 7) {
 fmRdyOk=1;
 if((cnt_TMR1>>8) > 0) TIMSK &= ~(1<<TOIE1); 
 }

 }
}

interrupt [TIM1_OVF] void timer1_ovf_isr(void) { cnt_TMR1_OVR++; }

interrupt [EXT_INT1] void ext_int0_isr(void)
{
 char i;
 GICR &= ~(1<<INT1); 
 #asm
 {
 NOP
 NOP
 MOV R16,_Delay_3T
loop:
 SUBI R16,1 
 BRNE loop 

 BST R3,0 
 BRTC d2T 
 NOP
 NOP
d2T:
 BST R3,1
 BRTC ddd
 NOP
 NOP
 NOP
ddd:
 NOP
 }
 #endasm

 ADCSRA |= (1<<ADSC); 
 asm("nop");
 asm("nop");

 while((ADCSRA & (1<<ADIF))==0); 
 ADCSRA |= (1<<ADIF); 

 if(!(Uesr_cnt & 1)) {
 #asm
 {
 IN R30, 0x4
 IN R31, 0x4+1
 ADD R6, R30
 ADC R7, R31
 }
 #endasm

 MCUCR |= (1<<ISC11) | (1<<ISC10); 
 } else {

 #asm
 {
 IN R30, 0x4
 IN R31, 0x4+1
 SUB R6, R30
 SBC R7, R31
 }
 #endasm

 MCUCR &= ~(1<<ISC10); 
 }

 Uesr_cnt++;

 if((Uesr & (1<<13)) && (Uesr & (1<<12))) {
 Uesr_OVR++;
 Uesr &= ~(1<<13);
 }

 GIFR |= (1<<INTF1); 

 if(Uesr_cnt < 3200) GICR |= (1<<INT1); 

 GIFR |= (1<<INTF1); 

 i=0;
 while(i<64) {
 if(GIFR & (1<<INTF1)) break;
 i++;
 }

 GIFR |= (1<<INTF1); 
}

void lcd_wrNybble(char n)
{
 PORTB.2 = (n & 1) ? 1 : 0;
 PORTB.3 = (n & 2) ? 1 : 0;
 PORTB.4 = (n & 4) ? 1 : 0;
 PORTB.5 = (n & 8) ? 1 : 0;
 delay_us(2);
 PORTB.0=1;
 delay_us(2);
 PORTB.0=0;
 delay_us(2);
}

void lcd_wrByte(char data, char rs)
{
 PORTB.1=0;
 delay_us(60);

 if(rs) PORTB.1=1; 

 lcd_wrNybble((data >> 4) & 0xF);
 lcd_wrNybble(data & 0xF);
 delay_us(2);
 if(!str_pos_now) PORTB.1=0;
}

void lcd_EEdata_to_DDRAM(char eeprom *EE_adr)
{
 char tmp;
 char eeprom *adr;

 if(lcd_LineN != 0xFF) {
 tmp = 0x80;
 if(lcd_LineN) tmp |= 0x40; 
 lcd_wrByte(tmp, 0); 
 }

 adr=EE_adr;
 while(1) {
 tmp = *adr;
 if(tmp==0xFF) break; 
 if(EE_adr==conf_lcd) lcd_wrByte(tmp, 0);
 else lcd_wrByte(tmp, 1);
 adr++;
 }

 if(adr == EE_adr) { 
 for(tmp=0; tmp<16; tmp++) lcd_wrByte(' ', 1);
 }
}

void lcd_show_EEstr(char eeprom *EE_Adr)
{
 lcd_EEdata_to_DDRAM(EE_Adr);
 delay_ms(100);
 if(str_pos_now) str_pos_now--;
}

void msr_Freq(void)
{
 float tmp;

 delay_ms(100);
 Fx_pwr2 = 0;
 Fx = 0;
 fmInitTmr = 1;
 fmRdyOk = 0;
 cnt_TMR0_OVR = 0xFF;
 cnt_TMR1_OVR = 0;
 TCNT0 = 0xFE;
 TCNT1 = 0;
 TIFR |= (1<< TOV0); 

 TIMSK |= (1<<TOIE1); 
 TIMSK |= (1<<TOIE0); 
 asm("sei"); 
 delay_ms(50);

 if(!fmInitTmr) {
 if(fmRe)
 while(!fmRdyOk && !(cnt_TMR1_OVR & 0x80));
 else
 while(!fmRdyOk && !(cnt_TMR1_OVR > 39));
 }


 asm("cli");
 TIMSK &= ~(1<<TOIE0); 
 TIMSK &= ~(1<<TOIE1); 

 if(!fmRdyOk) return;

 cnt = ((unsigned long)cnt_TMR0_OVR<<2) + 1; 

 time = ((unsigned long)cnt_TMR1_OVR<<16) + cnt_TMR1 - 54UL; 

 time >>= 1;

 tmp =(3200000.0*cnt/time);
 Fx = tmp; 
 Fx_pwr2 = tmp*tmp; 

 if(fmRe) Fx_pwr2 -= 0.6;

 Kesr = Fx_pwr2/55.0; 

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
 unsigned int val, data;
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
 str[0]=0; 
 str[1]=1; 
 }

 fsMinus = 0;
 if(lcd_data & (1<<31)) {
 fsMinus = 1;
 lcd_data = (unsigned int)(0 - lcd_data);
 }

 if(lcd_LineN == 0) {
 data = lcd_data;
 idx = fmElCx ? 0 : 4;

 while((data > 16) && (idx < 6)) {
 data >>= 1;
 idx++;
 }

 idx -= 7;
 idx = (idx<<4)|(idx>>4); 
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
 if(str_pos_end != 0xFF) str_pos_end++;
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


 lcd_value_point += 4;
 if(fsElCx) lcd_value_point++;
 if(lcd_value_point == 7) lcd_value_point = 0;


 while(1) {
 if(pos == lcd_value_point) { 
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

 str[9] = range[idx]; 

 if(dUc_100mS) { str[0] = dUc_200mS; str[1]= dUc_100mS; }

copy_str:
 str[10] = lcd_value_type;
 dUc_100mS = 0;

 lcd_EEdata_to_DDRAM(EE_str_off);

 i=0;
 while(i<=10) lcd_wrByte(str[i++], 1);
}

void cal_L0_C0(void)
{
 float sav_F1_pwr2;
 float tmpC;

 sav_F1_pwr2 = F1_pwr2;
 F1_pwr2 = Fx_pwr2;

 PORTD.5 = 1;
 delay_ms(500);
 msr_Freq();
 PORTD.5 = 0;

 F0_pwr2 = Fx_pwr2;

 Cx = (unsigned long)((float)Ccal0/(F1_pwr2/F0_pwr2 - 1.0));

 F0_pwr2 = F1_pwr2;

 if(!PIND.7) F1_pwr2 = sav_F1_pwr2;


 if(fmRe) tmpC = 2.533029591e+14F;
 else tmpC = 2.533029591e+15F;

 lcd_data = (unsigned long)(tmpC/((float)Cx*F0_pwr2));

 if(!PIND.7) {
 L0 = lcd_data;
 L0--;
 C0 = Cx;
 C0++;
 }
}

unsigned int msr_DC_ADC(void)
{
 char i;
 unsigned int res;

 delay_us(20);
 res = 3;

 for(i=0;i<49;i++) {
 ADCSRA |= (1<<ADSC); 
 while((ADCSRA & (1<<ADIF))==0); 
 ADCSRA |= (1<<ADIF); 
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

 ADMUX &= 0xF0; 
 ADMUX |= 5; 
 PORTD.5 = 0;
 DDRD.0 = 1;
 PORTD.0 = 0;

 PORTB.1=0;
 PORTB.0=0;


 delay_ms(16); 
 lcd_wrNybble(3); 
 delay_ms(5);
 lcd_wrNybble(3); 
 delay_ms(5);
 lcd_wrNybble(2); 

 lcd_EEdata_to_DDRAM(conf_lcd);
 delay_ms(10); 

 lcd_wrByte(0x40,0); 
 lcd_LineN=0xFF;
 lcd_EEdata_to_DDRAM(zgn_lcd); 

 DDRD.0 = 0; 

 lcd_LineN=0;
 lcd_EEdata_to_DDRAM(a_ban0);
 lcd_LineN=1;
 lcd_EEdata_to_DDRAM(a_ban1);

 delay_ms(2000);

 lcd_LineN=0;
 str_pos_end=0x40;
 str_pos_now=0xFF;
 while(PIND.6) {
 lcd_show_EEstr(a_SwTo);
 lcd_LineN = 1;
 lcd_show_EEstr(a_ToMsr);
 lcd_LineN = 0;
 }
 while(!PIND.7) {
 lcd_show_EEstr(a_SwTo);
 lcd_LineN = 1;
 lcd_show_EEstr(a_ToCx);
 lcd_LineN = 0;
 }
 str_pos_now=0x40;


 ptr = (char*)&L0;
 for(i=0;i<16;i++) *(ptr+i) = tbl_const[i];

 delay_ms(2000);

 msr_Freq();
 EE_str_off = a_F0; 
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

 if(Fx < 650) return; 
 if(Fx > 950) return; 

 ADMUX &= 0xF0; 
 ADMUX |= 2; 
 delay_us(10);

 MCUCR &= ~(1<<ISC10);
 MCUCR |= (1<<ISC11); 
 GICR |= (1<<INT1); 

 asm("sei");
 delay_ms(100);

 GICR &= ~(1<<INT1); 
 asm("cli");

 ADMUX &= 0xF0; 
 ADMUX |= 5; 
 Uesr >>= 5; 
 Uesr &= 0x7FF;
 while(Uesr_OVR) { Uesr += 256; Uesr_OVR--; }


 if(Uesr > 30) fmRdyOk=1; 
}

void msr_Cp(void)
{
 char F_ReOn, F_ReOff;
 float sav_F1_pwr2;

 sav_F1_pwr2 = F1_pwr2; 
 fmLCx = 0;


 DDRD.0 = 1;
 PORTD.0 = 0;
 fmRe = 1;
 msr_Freq();


 F_ReOn = Fx & 0xFF; 
 if(Fx >> 8) F_ReOn = 0xFF; 
 if(!F_ReOn) F_ReOn++;
 if(!fmRdyOk) F_ReOn = 0;


 DDRD.0 = 0;
 fmRe = 0;
 msr_Freq();


 F_ReOff = (Fx >> 3) & 0xFF; 
 if((Fx >> 9 & 0xFF) > 7) F_ReOff = 0xFF; 
 if(!F_ReOff) F_ReOff++;
 if(!fmRdyOk) F_ReOff = 0;

 if(!F_ReOn || F_ReOn > 59) goto cont; 
 if((F_ReOn > 23) && (F_ReOff < F_ReOn)) goto cont; 
 if(F_ReOn > 7) goto msr_ReOn; 
 if(F_ReOff > 16) goto cont; 

msr_ReOn:

 DDRD.0 = 1;
 PORTD.0 = 0;
 fmRe = 1;
 msr_Freq();
 F_ReOff = 0;
 fmRdyOk = 1;


cont:
 F0_pwr2 = Fx_pwr2; 

 if(F_ReOff) { fmRdyOk = 1; F_ReOn = 0; }
 if(F_ReOn > 7) goto msr_CcalOn; 
 if(F_ReOff > 127 || F_ReOff==0) goto exit; 

msr_CcalOn:
 F1_pwr2 = F0_pwr2; 


 PORTD.5 = 1; 
 delay_ms(500);
 msr_Freq();
 PORTD.5 = 0; 
 F0_pwr2 = Fx_pwr2; 


 Cx = (float)Ccal0 / (F1_pwr2 / F0_pwr2 - 1.0);
 fmLCx = 1;

exit:
 F1_pwr2 = sav_F1_pwr2; 
}

void set_Null(void)
{
 unsigned int Ucal;
 char i;
 char *ptr;

 lcd_clear_line(1);
 lcd_LineN = 0;

 delay_ms(100);

 if(!fmRdyOk || PIND.6==0)
 {
 lcd_EEdata_to_DDRAM(a_Err);
 goto exit;
 }

 while(!PINC.1)
 {
 if(!PIND.6)
 if((Ccal0 >> 8) < 46) Ccal0++; 
 if(!PIND.7)
 if((Ccal0 >> 8) > 34) Ccal0--; 

 lcd_value_type = 'F';
 lcd_data = Ccal0;
 EE_str_off = a_Ccal; 
 lcd_value_point = 2;
 str_pos_now = str_pos_end;
 lcd_prep_str();
 delay_ms(100);
 }

 DDRD.0 = 1;
 PORTD.0 = 1;
 delay_us(35);

 Ucal = msr_DC_ADC(); 




 if(((Ucal >> 8) & 0xFF) > 27) 
 {
 lcd_data = (47120UL*49UL/Ucal)-49UL; 
 if(lcd_data != Re0) Re0 = lcd_data;
 }

 DDRD.0 = 0;

 lcd_clear_line(0);
 lcd_value_type = 7; 
 lcd_value_point = 15;
 lcd_data = Re0;
 EE_str_off = a_Re; 
 fsElCx = 0;
 lcd_prep_str();

 delay_ms(2000);

 lcd_EEdata_to_DDRAM(a_SwTo);
 lcd_LineN = 1;
 lcd_EEdata_to_DDRAM(a_ToMsr);
 str_pos_now = 0xFF;

 while(PIND.6) {
 lcd_LineN = 0;
 lcd_show_EEstr(a_SwTo);
 lcd_LineN = 1;
 lcd_EEdata_to_DDRAM(a_ToMsr);
 }

 lcd_LineN = 0;
 str_pos_now = str_pos_end;

 delay_ms(2000);

 msr_Freq();

 if(Fx > 1050) { 
 cal_L0_C0();
 fmElCx = 0;
 lcd_clear_line(0);
 if(PIND.7) {
 lcd_value_type = 'F';
 lcd_value_point = 2;
 EE_str_off = a_vC0;
 lcd_data = Cx;
 lcd_prep_str();
 lcd_LineN = 1;
 lcd_EEdata_to_DDRAM(a_C0); 
 } else {
 lcd_value_type = 'H';
 lcd_value_point = 7;
 EE_str_off = a_vL0;
 lcd_prep_str();
 lcd_LineN = 1;
 lcd_EEdata_to_DDRAM(a_L0); 
 }
 } else {
 Kesr0 = Kesr;
 msr_Uesr();
 Uesr0 = Uesr;
 msr_Cp();
 Cp0 = Cx;


 lcd_data = L0;
 lcd_data *= L0;
 lcd_data >>= 16;
 lcd_data *= Kesr;
 lcd_data /= Uesr0;


 lcd_LineN = 0;
 lcd_value_type = 7; 
 lcd_value_point = 11;
 EE_str_off = a_Ro;
 lcd_prep_str();



 lcd_LineN = 1;
 lcd_value_type = 'F';
 lcd_value_point = 2;
 EE_str_off = a_Cp; 
 lcd_data = Cx;
 lcd_prep_str();
 delay_ms(8000);


 lcd_LineN = 0;
 lcd_value_type = 'V';
 lcd_value_point = 11;
 EE_str_off = a_Uesr0;
 fsElCx = 0;
 lcd_data = Uesr0;
 lcd_prep_str();


 lcd_LineN = 1;
 lcd_value_type = ' ';
 lcd_value_point = 17;
 EE_str_off = a_Fesr;
 lcd_data = Fx;
 lcd_prep_str();
 }

 ptr = (char*)&L0;
 for(i=0;i<16;i++) tbl_const[i] = *(ptr+i);

exit:
 delay_ms(4000);
}

void msr_ElCm(void)
{
 unsigned int Ux;

 ElCm_time = 0;
 lcd_data = 0;

 if(fmRx || fmIc) {
 delay_ms(500);
 return;
 }

 EE_str_off = a_ElCm; 
 fmElCx = 0;

 DDRD.0 = 1;
 PORTD.0 = 0;
 delay_ms(500); 
 DDRD.0 = 0;

 Ucm0 = msr_DC_ADC(); 

 if(Ucm0 & (1<<15)) goto discharge_Cm_5mS; 

 Ucm1 = (Ucm0 + 10000) / 49; 


 DDRD.0 = 1;
 PORTD.0 = 1;

 while(1) {
 ElCm_time++;
 ADCSRA |= (1<<ADSC); 
 while((ADCSRA & (1<<ADIF))==0); 
 ADCSRA |= (1<<ADIF);
 if((ElCm_time & (1<<14)) || (ADCW >= Ucm1)) break;
 }

 DDRD.0 = 0;

 UcmTop = msr_DC_ADC();
 if((ElCm_time & (1<<14)) && ((Ucm0+256) > UcmTop)) fmRx = 1;
 if(ElCm_time < 2) goto discharge_Cm_5mS;


 fmElCx = 1;
 fsElCx = 1;
 lcd_value_point = 6;
 lcd_value_type = 'F';
 Utmp = UcmTop;

 while(1) {
 delay_ms(100);
 Ux = msr_DC_ADC(); 
 Utmp -= Ux;
 Utmp >>= 4;
 Utmp &= 0xFFF;
 dUc_200mS = 0;
 if((Utmp & (1<<11))) goto next;

 if(Utmp > 99) Utmp = 99; 

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


 if(dUc_100mS >= dUc_200mS) EE_str_off = a_ElCsz; 

 dUc_200mS = '0';
 while(dUc_100mS > 9) { dUc_100mS -= 10; dUc_200mS++; }
 dUc_100mS += '0';

 if(dUc_200mS == '0') { dUc_200mS = dUc_100mS; dUc_100mS = ' '; }

 dUcm = UcmTop - Ucm0;




 lcd_data = (((((50127UL - Ucm0) * 24872UL)
 / dUcm) - 12500UL) / Re0)
 * ElCm_time - 49UL;


 if(lcd_data < (3<<8)) { 
 lcd_data *= 10;
 lcd_value_point--;
 }

discharge_Cm_5mS:
 DDRD.0 = 1;
 PORTD.0 = 0;
 delay_ms(5);
 Utmp = msr_DC_ADC();
 DDRD.0 = 0;

 if(!(ElCm_time & (1<<14))) return;
 if((Ucm0 >> 8) & 0xFF) return; 
 if(((dUcm >> 8) & 0xFF) <= 0) return; 
 if((Utmp >> 8) & 0xFF) return; 

 if(fmFreqStab) { fmFreqStab = 0; fmRdyOk = 0; }
 else { fmRx = 0; fmIc = 1; } 
}

void calc_Cx(void)
{
 lcd_data = (float)Cx*(F1_pwr2/F0_pwr2 - 1.0);
 EE_str_off = a_Cx; 
 lcd_value_point = 2;
 lcd_value_type = 'F';
}

void calc_Lx(void)
{
 float tmpC;

 lcd_value_type = 'H';
 lcd_value_point = 7;
 EE_str_off = a_Lx; 






 if(!fmLCx) {
 if(fmRe) Cx = Cp0; 
 else Cx = C0; 
 }


 if(fmRe) tmpC = 2.533029591e+14F;
 else tmpC = 2.533029591e+15F;

 lcd_data = (unsigned long)(tmpC/((float)Cx*F0_pwr2));

 if(fmLCx) EE_str_off = a_lc_Lx;

 if(fmRe) {
 lcd_value_point++;
 fsElCx = 1;
 return;
 }

 delay_ms(500);
 lcd_data -= L0; 
}

void msr_Rx(void)
{
 float Ro, dUesr;
 unsigned int tmp;
 char mask, graph;

 fsMinus = 0;
 fsElCx = 1;











 msr_Uesr(); 

 if(!fmRdyOk) return;

 Ro = (float)L0;
 Ro *= Ro;
 Ro *= (float)Kesr;

 Ro /= 53603.8;
 Ro /= (float)Uesr0;

 dUesr = (float)(Uesr0 - Uesr);
 if(Uesr > Uesr0) {
 fsMinus = 1;
 dUesr = (float)(Uesr - Uesr0);
 }

 Ro *= dUesr;








 lcd_data = (unsigned long)(Ro/(float)Uesr);











 if(fsMinus) { lcd_data = 0 - lcd_data; return; }
 if(fmRx) return;
 if(fmIc) return;


 ElCm_time |= 1;
 tmp = (unsigned long)(lcd_data * ElCm_time) >> 16; 

 lcd_wrByte(0x48,0); 

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
 lcd_wrByte(graph,1);
 }
}

void main(void)
{

PORTB=0x00;
DDRB=0b00111111;

PORTC=0x00;
DDRC=0x00;


PORTD=0x00;
DDRD=0b00100001;


TCCR0=0x06;
TCNT0=0x00;

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

ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

MCUCR=0x00;

TIMSK=0x05;

ACSR=0x80;
SFIOR=0x00;
SFIOR |= (1<<PUD); 

ADMUX = (1<<REFS0); 
ADCSRA = (1<<ADPS2); 
ADCSRA |= (1<<ADEN); 

 init_lcm();

 while(1)
 {
 msr_Freq();
 F0_pwr2 = Fx_pwr2;














 if(Fx > 1050) { 
 fmRx = 0;
 fmIc = 0;
 fmElCx = 0;
 }

 if(PIND.6) set_Null();

 if(PIND.7)
 {
 if(fmRe) {
 DDRD.0 = 0;
 fmRe = 0;
 }

 fmLCx = 0;
 msr_ElCm();
 if(!fmElCx) calc_Cx();
 } else calc_Lx();

 lcd_LineN = 0;
 if(!fmRx && !fmIc) lcd_prep_str();
 lcd_LineN++;

 if(PIND.6) set_Null();

 if(fmElCx) {
 msr_Rx();
 lcd_value_type = 7; 
 lcd_value_point = 11;
 EE_str_off = a_rESR; 

 if(fmRx) {
 EE_str_off = a_rRx; 
 lcd_LineN = 0;
 }

 if(fmIc) {
 EE_str_off = a_icEsr; 
 lcd_LineN = 0;
 }

 lcd_prep_str();

 if(fmRx) {
 lcd_LineN = 1;
 lcd_value_type = 'V';
 lcd_value_point = 11;
 EE_str_off = a_Uesr0;
 lcd_data = Uesr;
 lcd_prep_str();
 }
 goto is_lcd_LineN;
 }


 lcd_value_type = 'F';
 lcd_value_point = 2;
 if(!fmLCx) goto clr_lcd_LineN;

 EE_str_off = a_Cp; 
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
