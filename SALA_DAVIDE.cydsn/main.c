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
#include "project.h"
#include "Global.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Start();
    isr_BUTTON_StartEx(Custom_BUTTON_ISR);
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    reg = LIS3DH_CTRL_REG1_INIT;
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 reg);
    reg = LIS3DH_CTRL_REG4_HIGH_RESOLUTION;
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 reg);
    reg = LIS3DH_TEMP_CFG_REG_ADC_ENABLE;
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_TEMP_CFG_REG,
                                 reg);
    
    
    EEPROM_Start();
    Change_DataRate(INITIALIZATION);
    
    
    
    
    uint8_t data[6];
    

    for(;;)
    {
        /* Place your application code here. */
        
        if (flag_button){
            Change_DataRate(UPDATING);
            flag_button = 0;
        }
        
        I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                STATUS_REG_AUX, 
                                &reg);
        if (reg & MASK_ADC_OVERRUN){
            //campiona
            I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                             OUT_ADC1_L,
                                             6,
                                             data);
            //trasformare in qualche modo
            
            //mandare alla uart in qualche modo
        }
    }
}

/* [] END OF FILE */
