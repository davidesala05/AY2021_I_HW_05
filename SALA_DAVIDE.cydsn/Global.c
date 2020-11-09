/* ========================================
 *
 * HEADER file where all the macros, global variables and function are declared
 * 
 * ========================================
*/

#include "Global.h"

/*Below all the global variables are initialized to 0*/
uint8_t flag_button = 0;
uint8_t flag_initialization = 0;
uint8_t data_rate = 0;
uint8_t reg = 0;
uint8_t data[6] = {0};
int16 dataX = 0;
int16 dataY = 0;
int16 dataZ = 0;
uint8_t Buffer[TRANSMIT_BUFFER_SIZE] = {0};


/******************************************/
/*        REGISTERS_START FUNCTION        */
/******************************************/

void Registers_Start(void){

    /*        REGISTERS INITIALIZATION        */
    
    /*Initialization of the LIS3DH_CTRL_REG1 register*/
    reg = LIS3DH_CTRL_REG1_INIT;
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1,
                                                   reg);
    if(error == ERROR){
        UART_PutString("Error occurred during I2C comm\r\n");  
    }
    /*Initialization of the LIS3DH_CTRL_REG4 register*/
    reg = LIS3DH_CTRL_REG4_INIT;
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG4,
                                         reg);
    if(error == ERROR){
        UART_PutString("Error occurred during I2C comm\r\n");  
    }
    /*Initialization of the LIS3DH_TEMP_CFG_REG register*/
    reg = LIS3DH_TEMP_CFG_REG_INIT;
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_TEMP_CFG_REG,
                                         reg);
    if(error == ERROR){
        UART_PutString("Error occurred during I2C comm\r\n");  
    }
    
    /*  DATARATE INITIALIZATION FROM EEPROM   */
    
    /*
    Below the EEPROM is started and read in the INITIALIZATION mode
    This allows to write the DATARATE that was previously present
    All the task are performed by the Change_DataRate function which
    is expressed in the Global.c file
    */
    
    EEPROM_Start();
    Change_DataRate(INITIALIZATION);
}

/******************************************/
/*        CHANGE_DATARATE FUNCTION        */
/******************************************/

/*Below the Change_DataRate function*/
void Change_DataRate(uint8_t phase){

    //The value saved in the EEPROM is read
    data_rate = EEPROM_ReadByte(EEPROM_ADDRESS);
    
    switch (phase){
        
        case INITIALIZATION : //In this case I don't want to increase the data_rate beacuse the initialization is required
            flag_initialization = 1; //This flag is used in the main to not increment the DATARATE at the POWER-ON of the system   
            break;
        
        case UPDATING : //In this case the data_rate is increased or reset to the initial value
            if (data_rate == MAX_DATA_RATE){ //If the DATARATE is the MAX admissible
                data_rate = MIN_DATA_RATE; //DATARATE reset to the starting value
            }
            else {
                data_rate++;
            }
            break;
            
        default :
            break;    
    }
    
    //Read the old register
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_CTRL_REG1, 
                                                  &reg);
    if(error == ERROR){
        UART_PutString("Error occurred during I2C comm\r\n");  
    }
    
    //The old ODR[3:0] bits of the data rate are erased
    reg &= MASK_TO_ERASE;
    //The new bits are saved
    reg |= (data_rate<<4); //The shift is necessary beacuse we have to modify the [7:4] bits
    //Write the new register
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 reg);
    //New data rate is saved to the EEPROM
    EEPROM_UpdateTemperature(); //Necessary before writing
    EEPROM_WriteByte(data_rate,EEPROM_ADDRESS);
}

/* [] END OF FILE */
