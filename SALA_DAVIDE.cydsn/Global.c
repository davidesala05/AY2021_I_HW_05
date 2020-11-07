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

    //The value saved in the EEPROM is read
    data_rate = EEPROM_ReadByte((uint16)(0x40008000));
    
    switch (phase){
        
        case INITIALIZATION : //In this case I don't want to increase the data_rate beacuse the initialization is required
            break;
        
        case UPDATING : //In this case the data_rate is increased or reset to the initial value
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
    
    //Read the old register
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG1, 
                                &reg);    
    //The prior ODR[3:0] bits of the data rate are erased
    reg &= MASK_TO_ERASE;
    //The new bits are saved
    reg |= data_rate<<4; //The shift is necessary beacuse we have to modify the [7:4] bits
    //Write the new register
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 reg);
    //New data rate is saved to the EEPROM
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(data_rate,(uint16)(EEPROM_ADDRESS));
}

/* [] END OF FILE */
