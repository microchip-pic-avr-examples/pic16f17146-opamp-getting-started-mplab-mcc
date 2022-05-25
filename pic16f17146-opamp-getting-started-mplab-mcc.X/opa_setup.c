/**
  OPA Setup Source File

  Company:
    Microchip Technology Inc.

  File Name:
    opa_setup.c

  Summary:
    This is the source file for the Hello World lab

  Description:
    This source file contains the code on how the Hello World lab works.
 */

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "mcc_generated_files/system/system.h"
#include "opa_setup.h"

void ClearOPAConfiguration(void)
{
    OPA1CON0 = 0x00;
    OPA1CON1 = 0x00;
    OPA1CON2 = 0x00;
    OPA1CON3 = 0x00;
    
    OPA1HWC = 0x00;
    OPA1ORS = 0x00;
}

void ConfigureOPA_UnityGain(void)
{
    ClearOPAConfiguration();
    
    //GSEL R1 = 15R and R2 = 1R, R2/R1 = 0.07; RESON Disabled; NSS OPA1IN0-; 
    OPA1CON1 = 0x0;

    //NCH No Connection; PCH OPA1IN+; 
    OPA1CON2 = 0x2;

    //FMS No Connection; PSS OPA1IN2+; 
    OPA1CON3 = 0x2;

    //OREN Software Override; HWCH User Defined Feedback; ORPOL Non Inverted; HWCL User Defined Feedback; 
    OPA1HWC = 0x0;

    //ORS OPA1PPS; 
    OPA1ORS = 0x0;

    //EN Enabled; CPON Enabled; UG OPA Output; SOC User Defined Feedback; 
    OPA1CON0 = 0xA8;
}

void ConfigureOPA_NonInverting(uint8_t gain)
{
    ClearOPAConfiguration();
            
    //GSEL R1 = 8R and R2 = 8R, R2/R1 = 1; RESON Enabled; NSS Vss; 
    OPA1CON1 = 0x3F;

    //NCH GSEL; PCH OPA1IN+; 
    OPA1CON2 = 0x12;

    //FMS OPA1OUT; PSS OPA1IN2+; 
    OPA1CON3 = 0x82;

    //OREN Software Override; HWCH User Defined Feedback; ORPOL Non Inverted; HWCL User Defined Feedback; 
    OPA1HWC = 0x0;

    //ORS OPA1PPS; 
    OPA1ORS = 0x0;
    
    //EN Enabled; CPON Enabled; UG OPAIN- pin; SOC User Defined Feedback; 
    OPA1CON0 = 0xA0;

    //To set a gain, configure GSEL
    OPA1CON1bits.GSEL = gain; 
}

void ConfigureOPA_Inverting(uint8_t gain)
{
    ClearOPAConfiguration();
    
    //GSEL R1 = 8R and R2 = 8R, R2/R1 = 1; RESON Enabled; NSS OPA1IN2-; 
    OPA1CON1 = 0x3A;

    //NCH GSEL; PCH Vdd/2; 
    OPA1CON2 = 0x13;

    //FMS OPA1OUT; PSS OPA1IN0+; 
    OPA1CON3 = 0x80;

    //OREN Software Override; HWCH User Defined Feedback; ORPOL Non Inverted; HWCL User Defined Feedback; 
    OPA1HWC = 0x0;

    //ORS OPA1PPS; 
    OPA1ORS = 0x0;

    //EN Enabled; CPON Enabled; UG OPAIN- pin; SOC User Defined Feedback; 
    OPA1CON0 = 0xA0;    
    
    //To set a gain, configure GSEL
    OPA1CON1bits.GSEL = gain;  
}

void ConfigureOPA_External(void)
{
    ClearOPAConfiguration();
    
    //GSEL R1 = 15R and R2 = 1R, R2/R1 = 0.07; RESON Disabled; NSS OPA1IN1-; 
    OPA1CON1 = 0x1;

    //NCH OPA1IN-; PCH OPA1IN+; 
    OPA1CON2 = 0x22;

    //FMS No Connection; PSS OPA1IN2+; 
    OPA1CON3 = 0x2;

    //OREN Software Override; HWCH User Defined Feedback; ORPOL Non Inverted; HWCL User Defined Feedback; 
    OPA1HWC = 0x0;

    //ORS OPA1PPS; 
    OPA1ORS = 0x0;

    //EN Enabled; CPON Enabled; UG OPAIN- pin; SOC User Defined Feedback; 
    OPA1CON0 = 0xA0;
}