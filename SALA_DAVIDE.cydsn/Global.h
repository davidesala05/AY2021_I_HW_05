/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef __GLOBAL_H_
    
    #define __GLOBAL_H_
    
    #include "cytypes.h"
    #include "project.h"
    #include "I2C_Interface.h"
    
    #define MASK_TO_ERASE 0b00001111
    #define MIN_DATA_RATE 0b0001
    #define MAX_DATA_RATE 0b0110
    
    #define INITIALIZATION 0
    #define UPDATING 1
    
    #define HEADER 0xA0
    #define TAIL 0xC0
    
    //EEPROM address
    #define EEPROM_ADDRESS 0x40008000
    //Device address
    #define LIS3DH_DEVICE_ADDRESS 0x18
    //CTRL_REG1
    #define LIS3DH_CTRL_REG1 0x20
    #define LIS3DH_CTRL_REG1_INIT 0b00000111
    //CTRL_REG4
    #define LIS3DH_CTRL_REG4 0x23
    #define LIS3DH_CTRL_REG4_HIGH_RESOLUTION 0b00001000
    //TEMP_CFG_REG
    #define LIS3DH_TEMP_CFG_REG 0x1F 
    #define LIS3DH_TEMP_CFG_REG_ADC_ENABLE 0b10000000
    //STATUS_REG_AUX
    #define STATUS_REG_AUX 0x07
    #define MASK_ADC_OVERRUN 0b10000000 //da verificare!!
    
    #define OUT_ADC1_L 0x08
    
    extern uint8_t flag_button;
    extern uint8_t data_rate;
    extern uint8_t reg;
    
    
    extern int16 DataOut;
    
    void Change_DataRate(uint8_t phase);
    
#endif


/* [] END OF FILE */
