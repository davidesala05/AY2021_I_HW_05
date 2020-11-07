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

#include "Global.h"

uint8_t flag_button = 0;
uint8_t data_rate = 0;
uint8_t reg = 0;

void Change_DataRate(uint8_t phase){

    data_rate = EEPROM_ReadByte((uint16)(EEPROM_ADDRESS));
    
    switch (phase){
        
        case INITIALIZATION :   
            break;
        
        case UPDATING :
            if (data_rate == MAX_DATA_RATE){
                data_rate = MIN_DATA_RATE;
            }
            else {
                data_rate++;
            }
            break;
            
        default :
            break;    
    }
    
    //read the old register now
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG1, 
                                &reg);    
    reg &= MASK_TO_ERASE;
    reg |= data_rate<<4;
    //write the new register now
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 reg);
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(data_rate,(uint16)(EEPROM_ADDRESS));
}

/* [] END OF FILE */
