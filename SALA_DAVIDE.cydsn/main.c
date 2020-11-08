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
#include "stdio.h"

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
    
    
    Buffer[0] = HEADER;
    Buffer[TRANSMIT_BUFFER_SIZE-1] = TAIL;
    
    for(;;)
    {
        /* Place your application code here. */
        
        if (flag_button == 1){
            if(flag_initialization == 1){
                flag_initialization = 0;
                flag_button = 0;
            }
            else {
                Change_DataRate(UPDATING);
                flag_button = 0;
            }
        }
        
        I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                    STATUS_REG, 
                                    &reg);
        
        if (reg & MASK_ADC_OVERRUN){
        
            //campiona
            I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                             OUT_X_L,
                                             6,
                                             data);
            //trasformare in qualche modo
            dataX = (int16)((data[0] | (data[1]<<8)))>>4;
            dataY = (int16)((data[2] | (data[3]<<8)))>>4;
            dataZ = (int16)((data[4] | (data[5]<<8)))>>4;
            
            
            /*DataUnion.f = (float32)(dataX)*mg_TO_g*G*SENSITIVITY;
            Buffer[1] = (uint8_t)((DataUnion.l) >> 0 & 0xFF);
            Buffer[2] = (uint8_t)((DataUnion.l) >> 8 & 0xFF);
            Buffer[3] = (uint8_t)((DataUnion.l) >> 16 & 0xFF);
            Buffer[4] = (uint8_t)((DataUnion.l) >> 24 & 0xFF);
            
            DataUnion.f = (float32)(dataY)*mg_TO_g*G*SENSITIVITY;
            Buffer[5] = (uint8_t)((DataUnion.l) >> 0 & 0xFF);
            Buffer[6] = (uint8_t)((DataUnion.l) >> 8 & 0xFF);
            Buffer[7] = (uint8_t)((DataUnion.l) >> 16 & 0xFF);
            Buffer[8] = (uint8_t)((DataUnion.l) >> 24 & 0xFF);
            
            DataUnion.f = (float32)(dataZ)*mg_TO_g*G*SENSITIVITY;
            Buffer[9] = (uint8_t)((DataUnion.l) >> 0 & 0xFF);
            Buffer[10] = (uint8_t)((DataUnion.l) >> 8 & 0xFF);
            Buffer[11] = (uint8_t)((DataUnion.l) >> 16 & 0xFF);
            Buffer[12] = (uint8_t)((DataUnion.l) >> 24 & 0xFF);*/
            
            DataUnion.f = (float32)(dataX)*mg_TO_g*G*SENSITIVITY;
            Buffer[1] = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[2] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[3] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[4] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            
            DataUnion.f = (float32)(dataY)*mg_TO_g*G*SENSITIVITY;
            Buffer[5] = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[6] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[7] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[8] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            
            DataUnion.f = (float32)(dataZ)*mg_TO_g*G*SENSITIVITY;
            Buffer[9]  = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[10] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[11] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[12] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            
            
            UART_PutArray(Buffer,TRANSMIT_BUFFER_SIZE);
        }
    }
}

/* [] END OF FILE */
