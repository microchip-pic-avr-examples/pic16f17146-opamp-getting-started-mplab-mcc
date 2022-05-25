 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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

/*
 *                  -- OPA Module I/O --
 * OPA1OUT pin connection
 * RC2 (for all the OPA configurations)
 * 
 * OPAIN pin connections
   Unity Gain       Inverting       Non-Inverting       External 
   In+ = RA2        In- = RA2       In+ = RA2           In+ = RA2
                                                        In- = RC3 
 */


/**
 * @enum Lab_State_t
 * @brief Enumeration for OPA configuration and switch state
*/
typedef enum 
{
    WAIT_FOR_SWITCH_PRESS,
    CONFIG_UNITY_GAIN,
    CONFIG_NON_INVERTING,
    CONFIG_INVERTING,
    CONFIG_EXTERNAL_SETUP
} FSM_State_t;

void TMR2_UserInterruptHandler(void);

FSM_State_t currentState = WAIT_FOR_SWITCH_PRESS;
FSM_State_t nextLabToConfig = CONFIG_UNITY_GAIN;

bool isSwitchPressed = false;

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 


    //User defined Interrupt routine on TMR2 interrupt caused by switch press
    Timer2.TimeoutCallbackRegister(TMR2_UserInterruptHandler);

    printf(" Op-amp labs using PIC16F17146 \r\n");

    while (1) 
    {
        switch (currentState) 
        {
            case WAIT_FOR_SWITCH_PRESS: 

                if(isSwitchPressed)
                {
                    isSwitchPressed = false;
                            
                    //Upon switch press, the OPA configuration is changed 
                    currentState = nextLabToConfig;
                }
                
                break;

            case CONFIG_UNITY_GAIN: 

                printf("Lab 1: Unity Gain \r\n");

                //Set OPA configurations to unity mode
                ConfigureOPA_UnityGain();

                //After configuring OPA once, FSM state is waiting for another switch press for change of OPA configuration
                currentState = WAIT_FOR_SWITCH_PRESS;

                //The next OPA configuration to be set on switch press
                nextLabToConfig = CONFIG_NON_INVERTING;
                break;

            case CONFIG_NON_INVERTING: 

                printf("Lab 2: Non-inverting amplifier \r\n");

                //Set OPA configurations to Non-inverting mode
                ConfigureOPA_NonInverting(GAIN_2_NON_INVERTING); 

                //After configuring OPA once, FSM state is waiting for another switch press for change of OPA configuration
                currentState = WAIT_FOR_SWITCH_PRESS;

                //The next OPA configuration to be set on switch press
                nextLabToConfig = CONFIG_INVERTING;
                break;

            case CONFIG_INVERTING: 

                printf("Lab 3: Inverting amplifier \r\n");

                //Set OPA configurations to Inverting mode
                ConfigureOPA_Inverting(GAIN_1_INVERTING); 

                //After configuring OPA once, FSM state is waiting for another switch press for change of OPA configuration
                currentState = WAIT_FOR_SWITCH_PRESS;

                //The next OPA configuration to be set on switch press
                nextLabToConfig = CONFIG_EXTERNAL_SETUP;
                break;

            case CONFIG_EXTERNAL_SETUP:

                printf("Lab 4: External configuration \r\n");

                //Set OPA to External configuration mode
                ConfigureOPA_External();

                //After configuring OPA once, FSM state is waiting for another switch press for change of OPA configuration
                currentState = WAIT_FOR_SWITCH_PRESS;

                //The next OPA configuration to be set on switch press
                nextLabToConfig = CONFIG_UNITY_GAIN;
                break;

            default: 

                currentState = WAIT_FOR_SWITCH_PRESS;
                break;
        }
    }   
}

/**
 * @brief user ISR function for TMR2 
 * @param none
 * @return none
*/
void TMR2_UserInterruptHandler(void) 
{
    isSwitchPressed = true; 
}