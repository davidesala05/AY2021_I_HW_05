/* ========================================
 *
 * FIFTH ASSIGNMENT
 * DAVIDE SALA
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

    /* Starting the components */
    I2C_Peripheral_Start();
    UART_Start();
    isr_BUTTON_StartEx(Custom_BUTTON_ISR);
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    /*
    The function used to initialize all the registers
    and the datarate from the EEPROM is called
    */
    Registers_Start(); //See Global.c file
    
    /*HEADER and TAIL added to the BUFFER*/
    Buffer[0] = HEADER;
    Buffer[TRANSMIT_BUFFER_SIZE-1] = TAIL;
    
    ErrorCode error;
    
    for(;;)
    {
        /******************************************/
        /*            BUTTON PRESSION             */
        /******************************************/
        
        /*
        If the BUTTON is pressed the new DATARATE is uploaded
        both to the register and to the EEPROM
        */
        if (flag_button == 1){ //Flag set in the ISR of the BUTTON
            if(flag_initialization == 1){ //This allows to not enter an the POWER-ON of the system
                flag_initialization = 0;
                flag_button = 0;
            }
            else { //If is not the initialization of the system
                Change_DataRate(UPDATING); //The function is called in the UPDATING mode
                flag_button = 0;
            }
        }
        
        /******************************************/
        /*           STATUS_REG READING           */
        /******************************************/
        
        /*
        The STATUS_REG is read in order to control
        in an OVERRUN of both the registers occur
        */
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                            STATUS_REG, 
                                            &reg_STATUS_REG);
        if(error == ERROR){
            UART_PutString("Error occurred during I2C comm\r\n");  
        }
        
        /******************************************/
        /*                SAMPLING                */
        /******************************************/
        
        /*
        Below there is the condition that is verified
        at a DATARATE frequency when the new data are
        available
        */
        if (reg_STATUS_REG & MASK_DATA_AVAILABLE){
        
            /*
            The new data are read by the contiguous
            registers and saved in the variable
            */
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                     OUT_X_L,
                                                     6,
                                                     data);
            if(error == ERROR){
                UART_PutString("Error occurred during I2C comm\r\n");  
            }            

            /*
            Data are transformed in int16 and divided by the corresponding axes
            Each of the three data is expressed as two’s complement left-justified,
            so a shift by 4 bits is required
            */
            dataX = (int16)((data[0] | (data[1]<<8)))>>4;
            dataY = (int16)((data[2] | (data[3]<<8)))>>4;
            dataZ = (int16)((data[4] | (data[5]<<8)))>>4;
            
            /*
            Below the Data is transformed in m/s2 and in float32
            DataUnion is an UNION declared in the Glocal.h file
            - DataUnion.f is used to stored the float32 value
            - DataUnion.l is used to extract the byte to saved in Buffer[i]
            
            The conversion in made by a sensitivity expressed in the datasheet,
            the gravity constant and the conversion from "millig" to "g"
            */
 
            //X-axis
            DataUnion.f = (float32)(dataX)*mg_TO_g*G*SENSITIVITY;
            Buffer[1] = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[2] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[3] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[4] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            //X-axis
            DataUnion.f = (float32)(dataY)*mg_TO_g*G*SENSITIVITY;
            Buffer[5] = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[6] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[7] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[8] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            //Z-axis
            DataUnion.f = (float32)(dataZ)*mg_TO_g*G*SENSITIVITY;
            Buffer[9]  = (uint8_t)((DataUnion.l & 0xFF000000) >> 24);
            Buffer[10] = (uint8_t)((DataUnion.l & 0x00FF0000) >> 16);
            Buffer[11] = (uint8_t)((DataUnion.l & 0x0000FF00) >> 8);
            Buffer[12] = (uint8_t)((DataUnion.l & 0x000000FF) >> 0);
            
            /*The BUFFER is sent by the UART*/
            UART_PutArray(Buffer,TRANSMIT_BUFFER_SIZE);
        }
    }
}

/* [] END OF FILE */
