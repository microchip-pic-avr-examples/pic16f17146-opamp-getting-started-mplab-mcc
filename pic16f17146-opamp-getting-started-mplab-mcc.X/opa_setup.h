/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef OPA_SETUP_H
#define	OPA_SETUP_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define GAIN_16_NON_INVERTING       (0b111U)
#define GAIN_8_NON_INVERTING        (0b110U)
#define GAIN_4_NON_INVERTING        (0b101U)
#define GAIN_8by3_NON_INVERTING     (0b100U)
#define GAIN_2_NON_INVERTING        (0b011U)
#define GAIN_4by3_NON_INVERTING     (0b010U)
#define GAIN_8by7_NON_INVERTING     (0b001U)
#define GAIN_16by15_NON_INVERTING   (0b000U)
      
#define GAIN_15_INVERTING       (0b111U)
#define GAIN_7_INVERTING        (0b110U)
#define GAIN_3_INVERTING        (0b101U)
#define GAIN_5by3_INVERTING     (0b100U)
#define GAIN_1_INVERTING        (0b011U)
#define GAIN_1by3_INVERTING     (0b010U)
#define GAIN_1by7_INVERTING     (0b001U)
#define GAIN_1by15_INVERTING    (0b000U)
  
/**
 * @brief This function Clears all registers in the OPA module.
 * @param none
 * @return none
*/
void ClearOPAConfiguration(void);
         
/**
 * @brief This function configures the OPA module as a unity gain buffer. 
 * Pin Configuration
 * OPA1OUT = RC2
 * In+ = RA2 
 * @param none
 * @return none
*/
void ConfigureOPA_UnityGain(void);
     
/**
 * @brief This function configures the OPA module into a non-inverting amplifier using the internal resistor ladder.
 * Non-Inverting Defaults: Gain = 2
 * Referring datasheet, the values that can be given to GSEL for determining gain
 *  GSEL        (1+R2/R1)
 *  111          16
 *  110           8
 *  101           4
 *  100           8/3
 *  011           2
 *  010           4/3
 *  001           8/7
 *  000           16/15
 * 
 * Pin Configuration
 * OPA1OUT = RC2
 * In+ = RA2 
 * @param none
 * @return none
*/
void ConfigureOPA_NonInverting(uint8_t gain);
    
/**
 * @brief This function configures the OPA module into an inverting amplifier using the internal resistor ladder
 * Inverting Defaults: Gain = -1, Vbias = Vdd/2
 * Referring datasheet, the values that can be given to GSEL for determining gain
 *  GSEL        R2/R1
 *  111          15
 *  110           7
 *  101           3
 *  100           5/3
 *  011           1
 *  010           1/3
 *  001           1/7
 *  000           1/15
 * 
 * Pin Configuration
 * OPA1OUT = RC2
 * In+ = Vdd/2(Vbias)is connected internally. Vbias is used to level-shift the output of
   the operational amplifier in this configuration. 
 * In- = RA2 
 * @param none
 * @return none
*/
void ConfigureOPA_Inverting(uint8_t gain);
   
/**
 * @brief This function set the OPA module to use the external components for configuration.
 * The external pin configurations :  
 *  OPA1OUT = RC2
 *  In+ = RB5 
 *  In- = RB4 
 * @param none
 * @return none
*/
void ConfigureOPA_External(void);

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

// TODO If C++ is being used, regular C code needs function names to have C 
// linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* OPA_SETUP_H */

