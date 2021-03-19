#include <p33EP512MU810.h>

// FGS
#pragma config GWRP = OFF    //General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = OFF    //General Segment Code-Protect bit->General Segment Code protect is disabled
#pragma config GSSK = OFF    //General Segment Key bits->General Segment Write Protection and Code Protection is Disabled

// FOSCSEL
#pragma config FNOSC = FRC    //Initial Oscillator Source Selection Bits->FRC
#pragma config IESO = OFF    //Two-speed Oscillator Start-up Enable bit->Start up with user-selected oscillator source

// FOSC
#pragma config POSCMD = XT    //Primary Oscillator Mode Select bits->XT Crystal Oscillator Mode
#pragma config OSCIOFNC = ON    //OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Peripheral pin select configuration->Allow only one reconfiguration
#pragma config FCKSM = CSECMD    //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled

// FWDT
#pragma config WDTPOST = PS32768    //Watchdog Timer Postscaler Bits->1:32768
#pragma config WDTPRE = PR128    //Watchdog Timer Prescaler bit->1:128
#pragma config PLLKEN = ON    //PLL Lock Wait Enable bit->Clock switch to PLL source will wait until the PLL lock signal is valid.
#pragma config WINDIS = OFF    //Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config FWDTEN = OFF    //Watchdog Timer Enable bit->Watchdog timer enabled/disabled by user software

// FPOR
#pragma config FPWRT = PWR128    //Power-on Reset Timer Value Select bits->128ms
#pragma config BOREN = ON    //Brown-out Reset (BOR) Detection Enable bit->BOR is enabled
#pragma config ALTI2C1 = ON    //Alternate I2C pins for I2C1->ASDA1/ASCK1 pins are selected as the I/O pins for I2C1
#pragma config ALTI2C2 = OFF    //Alternate I2C pins for I2C2->SDA2/SCK2 pins are selected as the I/O pins for I2C2

// FICD
#pragma config ICS = PGD1    //ICD Communication Channel Select bits->Communicate on PGEC1 and PGED1
#pragma config RSTPRI = PF    //Reset Target Vector Select bit->Device will obtain reset instruction from Primary flash
#pragma config JTAGEN = OFF    //JTAG Enable bit->JTAG is disabled

// FAS
#pragma config AWRP = OFF    //Auxiliary Segment Write-protect bit->Auxiliary program memory is not write-protected
#pragma config APL = OFF    //Auxiliary Segment Code-protect bit->Aux Flash Code protect is disabled
#pragma config APLK = OFF    //Auxiliary Segment Key bits->Aux Flash Write Protection and Code Protection is Disabled

#include "mu810.h"


static void mu810_clock_init(void)
{
    // FRCDIV FRC/1; PLLPRE 2; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // ROON disabled; ROSEL FOSC; RODIV 0; ROSSLP disabled; 
    REFOCON = 0x00;
    // PLLDIV 62+2; 
    PLLFBD = 0x3E;
    // ENAPLL enabled; APLLPOST 1:2; FRCSEL ASRCSEL determines input clock source; SELACLK Auxiliary Oscillators; ASRCSEL Primary Oscillator; AOSCMD AUX; APLLPRE 1:2; 
    ACLKCON3 = 0xA4C1;
    // APLLDIV 24; 
    ACLKDIV3 = 0x07;
    // AD1MD enabled; PWMMD enabled; T3MD enabled; T4MD enabled; T1MD enabled; U2MD enabled; T2MD enabled; U1MD enabled; QEI1MD enabled; SPI2MD enabled; SPI1MD enabled; C2MD enabled; C1MD enabled; DCIMD enabled; T5MD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // OC5MD enabled; OC6MD enabled; OC7MD enabled; OC8MD enabled; OC1MD enabled; IC2MD enabled; OC2MD enabled; IC1MD enabled; OC3MD enabled; OC4MD enabled; IC6MD enabled; IC7MD enabled; IC5MD enabled; IC8MD enabled; IC4MD enabled; IC3MD enabled; 
    PMD2 = 0x00;
    // AD2MD enabled; PMPMD enabled; CMPMD enabled; U3MD enabled; QEI2MD enabled; RTCCMD enabled; T9MD enabled; T8MD enabled; CRCMD enabled; T7MD enabled; I2C2MD enabled; DAC1MD enabled; T6MD enabled; 
    PMD3 = 0x00;
    // U4MD enabled; USB1MD enabled; REFOMD enabled; 
    PMD4 = 0x00;
    // OC9MD enabled; OC16MD enabled; IC10MD enabled; IC11MD enabled; IC12MD enabled; IC13MD enabled; IC14MD enabled; IC15MD enabled; IC16MD enabled; IC9MD enabled; OC14MD enabled; OC15MD enabled; OC12MD enabled; OC13MD enabled; OC10MD enabled; OC11MD enabled; 
    PMD5 = 0x00;
    // PWM2MD enabled; PWM1MD enabled; SPI4MD enabled; PWM4MD enabled; SPI3MD enabled; PWM3MD enabled; PWM6MD enabled; PWM5MD enabled; 
    PMD6 = 0x00;
    // DMA8MD enabled; DMA4MD enabled; DMA12MD enabled; DMA0MD enabled; 
    PMD7 = 0x00;
    // CF no clock failure; NOSC PRIPLL; LPOSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((uint8_t) (0x03));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}

/*******************************************************************/
/* ADC Interrupt handler template (copy into main.c and uncomment) */
/*******************************************************************/
//void __attribute__((__interrupt__,no_auto_psv)) _AD1Interrupt(void) {
//    // Your handler here
//    IFS0bits.AD1IF = 0;
//}
//
//void AD1_init() {
//    IPC3bits.AD1IP = 0x07;
//    IFS0bits.AD1IF = 0;
//    IEC0bits.AD1IE = 1;
//}

static void mu810_adc_init(void) {
    // Disable the ADC module
    AD1CON1bits.ADON = 0;
    
    // Select Voltage Reference
    AD1CON2bits.VCFG = 0x0; // Vrefh = Avdd; Vrefl = Avss
    
    // Output and Resolution
    AD1CON1bits.AD12B  = 0x0 ; // 10-bit mode
    AD1CON1bits.FORM = 0b00; // Integer output
    
    // Sampling and Conversion
    AD1CON2bits.SMPI = 0x00; // Interrupt every cycle of conversion
    AD1CON1bits.SSRCG = 0x00; // Standard Sample Clock (No PWM Generator)
    AD1CON1bits.ASAM = 0x00; // No auto-start sampling. Set SAMP = 1 to start
    AD1CON1bits.SSRC = 0x07; // Automatically switch between sampling and conversion

    // Period of Auto-Sampling
    AD1CON3bits.ADCS = 0xFF; // Tad = 256 * Tcy = 39.0625ns (Fosc = 25.6Mhz)
    AD1CON3bits.SAMC = 0x1F; // Auto-sample time = 16 Tad

    // Enable the ADC module
    AD1CON1bits.ADON = 1;
}


//uint16_t mu810_adc_read(ADC_CHANNEL channel) {
//    AD1CHS0 = channel;
//    AD1CON1bits.DONE = 0;
//    AD1CON1bits.SAMP = 1;
//    while (!AD1CON1bits.DONE);
//    return ADC1BUF0;
//}


void mu810_init(void)
{
    mu810_clock_init();
    mu810_adc_init();
    return;
}