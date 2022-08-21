/*TimerOverflow Interrupt with PIC16F877A */
#include <xc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_ON & CPD_OFF & WRT_OFF & CP_OFF);
#define _XTAL_FREQ 20000000
unsigned char timer_count=0;// unsigned char type global variable timer_count initial value is 0

void interrupt timer_0()//interrupt routine function
{
    if(INTCONbits.TMR0IF == 1)//if Timer0 flag is = 1
    {
        timer_count++;//increment the value of timer_count
        INTCONbits.TMR0IF = 0;//clear Timer flag
    }
}


void main(void) 
{
     INTCONbits.GIE = 1;// Global Interrupt Enable Bit
    INTCONbits.PEIE = 1;// Peripheral Interrupt Enable Bit
    INTCONbits.TMR0IE = 1;// Timer0 Interrupt Enable Bit
    
    OPTION_REG = 0x07;//option register value(set Pre scaler to 256)
    TMR0 = 59;    // Calculated load value( delay 10MS)
    
    
     TRISB0 = 0;// set portB0 as an output
    while(1)
    {
        if(timer_count == 0)// if timer count value is 0
            {
              PORTBbits.RB0 = 1; // set portB0 to HIGH    
            }
        if(timer_count == 100)
        {
            PORTBbits.RB0 = 0;
        }
        if(timer_count == 200)
        {
            timer_count = 0;
        }
    }
    
     return;
}
