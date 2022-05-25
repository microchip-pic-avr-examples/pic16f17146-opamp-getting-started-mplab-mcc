
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with OPAMP configurations on PIC16F17146 Microcontroller

## Introduction

Operational amplifier (OPA) module is a powerful analog peripheral available in PIC16F17146 family of microcontrollers. The OPA module comes with an internal resistor ladder, which can be used to create a non-inverting or inverting amplifier with no external components required. An internal mux can set the OPA module into unity gain without an external jumper wire. The OPA module also has the option for an external configuration, where the user can use externally placed components to build a custom amplifier configuration. This code example is designed to switch between and demonstrate the 4 configurations: Unity Gain, Non-Inverting Amplifier, Inverting Amplifier, and External Pin Connections.

## Related Documentation

- [TB3280: Using Operational Amplifiers in PIC16 and PIC18](https://www.microchip.com/DS90003280)
- [TB3279: Optimizing Internal Operational Amplifiers for Analog Signal Conditioning](https://www.microchip.com/DS90003279)
- [AN3521: Analog Sensor Measurement and Acquisition](https://www.microchip.com/DS00003521)
- [PIC16F17146 Data Sheet](https://www.microchip.com/DS40002343)


## Software Used

- MPLAB® X IDE [6.00 or newer](https://www.microchip.com/mplab/mplab-x-ide)
- Microchip XC8 Compiler [2.35 or newer](https://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) [5.1.1 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
- Microchip PIC16F1xxxx Series Device Support (DFP) [1.13.178 or newer](https://packs.download.microchip.com/)

## Hardware Used

-	PIC16F17146 Curiosity Nano Board
-	Signal Source
-	Parts for an external operational amplifier configuration (resistors, capacitors, etc.)

## Setup

#### Internal Configurations Wiring

##### Pin Table
| Pin | Name          | Function
| --- | ------------- | ---
| RA2 | OPA1IN        | Input
| RC2 | OPA1OUT       | OPA Module Output
| RC0 | S1            | Pushbutton Switch
| RB7 | EUSART TX     | EUSART TX pin
| RB5 | EUSART RX     | EUSART RX pin

![setup](images/setup.png)

| Wire   | Name         | Function
| ---    | -------------| ---
| Blue   | OPA1IN       | Input to the Operational Amplifier. Connected to a signal source.
| Yellow | OPA1OUT      | Output of the Operational Amplifier
| Black  | GND          | Ground

These modes of operation (unity gain, non-inverting, and inverting) utilize the internal resistor ladder or unity gain override of the OPA module. No external parts are needed for these modes. The internal pin-selection multiplexer is used with each configuration to set RA2 to be the signal input.

*Note: The internal configuration wiring is the setup used for Unity gain, Non-Inverting and Inverting configuration labs. For external configuration, setup will vary based on custom design.*

#### External Configuration Wiring

##### Pin Table
| Pin | Name          | Function
| --- | ------------- | ---
| RA2 | OPA1IN2+      | Non-Inverting Input
| RC3 | OPA1IN1-      | Inverting Input
| RC2 | OPA1OUT       | OPA Module Output
| RC0 | S1            | Pushbutton Switch
| RB7 | EUSART TX     | EUSART TX pin
| RB5 | EUSART RX     | EUSART RX pin

For the external configuration, the internal feedback network is disabled, and both inputs of the operational amplifier are connected to I/O pins. In this mode, the OPA module on the device acts like a discrete single-supply operational amplifier.

This type of configuration is recommended when the internal resistor ladder is not precise enough or the circuit desired is not possible using the internal resistor ladder (E.g., Summing Amplifier).

#### I/O Cautions
The device will be permanently damaged by voltages above Vdd and below Vss. Do not apply these levels to any I/O on the device. Please consult the device datasheet for more information.

## Operation

This code example demonstrates 4 basic configurations of the OPA module - Unity Gain, Non-Inverting, Inverting, and External.

Pressing S1 on the Curiosity Nano board switches to the next OPA configuration.

The current OPA configuration is displayed on the PC terminal when switching through the labs. Microcontroller sends data to the PC with baud rate of 9600 using UART with the help of virtual serial port feature of the on-board debugger.


| Configuration                        | Output function
| -----------------------------------  | -----
| Unity Gain                           | Vout = Vin
| Non-Inverting Amplifier              | Vout = 2 x Vin
| Inverting Amplifier<sup>*</sup>      | Vout = Vdd - Vin
| External                             | Dependent on Configuration


*Note: The impedance of the input source affects the transfer function. For best results, the impedance of the source should be very low.*

#### Unity Gain
![unity-gain-schematic](images/unity-gain-schematic.png)

In unity gain, the OPA module acts as a voltage buffer, tracking the input signal with the output for a gain of 1. This is most useful for sensitive signals that have a full-scale range, such as resistive voltage dividers.

![unity-gain-output](images/unity-gain-output.png)

The code snippet below is an example of configuring the OPA module in unity gain. In this example, OPA module is configured to operate in Unity gain mode in software by setting Unity Gain Enable (UG) bit

```
void ConfigureOPA_UnityGain (void)
{
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
```

#### Non-Inverting Amplifier
![non-inverting-schematic](images/non-inverting-schematic.png)

The non-inverting amplifier produces an output greater than the input signal, with the gain in this configuration being R2/R1 + 1. In this code example, the internal resistor ladder is used to generate a gain of 2, however other gain options are available on the internal resistor ladder.

![non-inverting-output](images/non-inverting-output.png)

The code snippet below is an example of configuring the OPA module as a non-inverting amplifier.

```
void ConfigureOPA_NonInverting(uint8_t gain)
{
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
```

#### Inverting Amplifier
![inverting-schematic](images/inverting-schematic.png)

The inverting amplifier produces an output that is inverted from the input. Since the OPA module is a single-supply device, the output must be level-shifted for correct operation. Vbias is used to level-shift the output of the operational amplifier in this configuration, with the level set to (1 + R2/R1) * Vbias. The level-shifted gain of this setup is equal to -R2/R1. In this code example, Vdd/2 is set as Vbias and the internal resistor ladder is used to generate a gain of -1, however other gain options are available on the internal resistor ladder.

![inverting-output](images/inverting-output.png)

*Note: The scale for output (yellow) has been increased to 1V/div from 500mV/div.*

The code snippet below is a example of configuring the OPA module as an inverting amplifier.

```
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
```

#### External Op-amp Configuration

![external-schematic](images/external-schematic.png)

In this configuration, the gain of OPA module is controlled using external components. The input sources to OPA module are connected to the I/O pins. The non-inverting input source of the OPA module is selected using the OPA module Non-Inverting Input Channel Selection (PCH) bits and can be connected to an external input pin (OPAxIN+). The Positive Source Selection (PSS) bits are used to select from the available OPA non-inverting input pins for the device. Similarly, the inverting input source of the OPA module is selected using the OPA module inverting Input Channel Selection (NCH) bits and can be connected to an external input pin (OPAxIN-). The Negative Source Selection (NSS) bits are used to select from
the available inverting OPA input pins for the device. The code snippet below is a example of configuring the gain of OPA module externally.
```
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
```
## Peripheral Configuration
This section explains how to configure the peripherals using MPLAB X IDE with MCC plugin for recreation of the project.

Refer [Software Used](https://github.com/microchip-pic-avr-examples/pic16f17146-opamp-getting-started-mplab-mcc#software-used) section to install required tools to recreate the project.

Additional Links: [MCC Melody Technical Reference](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=MCC.MELODY.INTRODUCTION&redirect=true)

##### Peripheral Configuration Summary
|    Module                  |    Configuration                                                                                                                                                                                                                                                                                                                                |    Usage                                      |
|--------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------|
|    Clock Control           |    Clock Source   - HFINTOSC<br>   HF Internal Clock – 4 MHz<br>   Clock Divider - 4                                                                                                                                                                                                                                                            |    System clock      
|    EUSART1                 |  *UART1 Driver*<br>Requested Baudrate –   9600 <br> UART PLIB Selector - EUSART1<br><br> *EUSART1 PLIB* <br>    Enable Redirect   STDIO to EUSART    <br>Enable   Receive<br>  Enable Transmit<br>   Enable Serial   Port                                                                                                                                                                          |    Send data to PC   terminal <br>   <br>     |
|    OPA1                    |    Enable OPA1<br>   Enable Charge   Pump <br>     <br>Op Amp   Configuration- Unity Gain Buffer<br>    <br>Positive   Channel – OPA1IN+  <br>Positive Source   Selection – OPA1IN2+   <br>Positive   Reference – VDD                                                                                         |                                               |
|    TMR2                    |    Enable Timer<br>   <br>Control Mode   - Monostable<br>   External   Reset Source - T2INPPS pin<br>   Start/Reset   Option - Start on rising edge on TMR2_ers<br>     <br>Clock Source   - LFINTOSC<br>   Prescaler -   1:128<br>      Timer Period   - 100 ms<br>    <br>Enable   Interrupt    |    Switch denouncing                          |

##### Peripheral Configuration using MCC

###### Clock control
![clock-control](images/clock-control.png)

###### UART1 Driver
![uart1](images/uart1.png)

###### EUSART1 PLIB
![eusart1](images/eusart1.png)

*Note: The on-board debugger present on curiosity nano board has a virtual serial port (CDC) is connected to EUSART on the PIC16F17146 and provides an easy way to communicate with the target application through terminal software. Refer curiosity nano board user guide for more details.*

###### OPA1
*All OPA configuration used in this example are generated separately using MCC as MCC can generate only single configuration at a time. All OPA1_Initialize() functions generated separately are then added in opa_setup.c file.*

![opa1](images/opa1.png)

###### TMR2
![tmr2](images/tmr2.png)

###### Pins
![pins](images/pins.png)

###### Pin Grid View
![pins-grid-view](images/pins-grid-view.png)

## Summary
The OPA module in the PIC16F17146 family is a configurable analog peripheral that can be used in several ways. Each configuration has a specific use case that can aid in signal acquisition applications through an internal connection with the ADCC. Other analog peripherals can also utilize the OPA module to unlock new use cases, for instance, the DAC output can be mirrored or tracked in output level through the module. The 4 configurations shown in this code example are the tip of the iceberg - most of the op-amp circuits can be implemented using the OPA module.
