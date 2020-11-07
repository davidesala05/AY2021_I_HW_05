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
    
    #define EEPROM_ADDRESS 0x40008000
    #define LIS3DH_DEVICE_ADDRESS 0x18
    #define LIS3DH_CTRL_REG1 0x20
    
    extern uint8_t flag_button;
    extern uint8_t data_rate;
    extern uint8_t ctrl_reg1;
    
    void Change_DataRate(uint8_t phase);
    
#endif


/* [] END OF FILE */
