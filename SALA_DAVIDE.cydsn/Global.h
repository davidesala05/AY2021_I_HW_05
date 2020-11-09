/* ========================================
 *
 * HEADER file where all the macros, global variables and function are declared
 * 
 * ========================================
*/

#ifndef __GLOBAL_H_
    
    #define __GLOBAL_H_
    
    #include "cytypes.h"
    #include "project.h"
    #include "I2C_Interface.h"
    
    //MASK and macro used in the Change_DataRate function
    #define MASK_TO_ERASE 0b00001111
    #define MIN_DATA_RATE 0b00000001
    #define MAX_DATA_RATE 0b00000110
    //Macro used for the conversion
    #define G           9.80665
    #define SENSITIVITY 2 //Because the FS is +-4g
    #define mg_TO_g     0.001
    //Phase used in the Change_DataRate function
    #define INITIALIZATION 0
    #define UPDATING       1
    //Sizes of the BUFFER used to send the values
    #define BUFFER_SIZE 4*3 //4(the byte of a float32) * 3(the variables)
    #define TRANSMIT_BUFFER_SIZE 1+BUFFER_SIZE+1
    //TAIL and HEADER added to BUFFER
    #define HEADER 0xA0
    #define TAIL   0xC0
    
    /*Below all the registers and MASKs used in the main*/
    
    //EEPROM address
    #define EEPROM_ADDRESS           0x00
    //Device address
    #define LIS3DH_DEVICE_ADDRESS    0x18
    //CTRL_REG0
    #define LIS3DH_CTRL_REG0         0x1E
    #define LIS3DH_CTRL_REG0_INIT    0b00010000
    //CTRL_REG1
    #define LIS3DH_CTRL_REG1         0x20
    #define LIS3DH_CTRL_REG1_INIT    0b00000111
    //CTRL_REG4
    #define LIS3DH_CTRL_REG4         0x23
    #define LIS3DH_CTRL_REG4_INIT    0b00011000
    //TEMP_CFG_REG
    #define LIS3DH_TEMP_CFG_REG      0x1F 
    #define LIS3DH_TEMP_CFG_REG_INIT 0b10000000
    //STATUS_REG_AUX
    #define STATUS_REG               0x27
    
    /*
    MASK used to read the registers
    at the sampling frequency (DATARATE)
    */
    #define MASK_DATA_AVAILABLE      0b00001000
    
    /* OUT_X_L --> starting point for the MultiRead */
    #define OUT_X_L 0x28
    
    /*Below all the flags and variables are declared*/
    
    extern uint8_t flag_button;//Used to take track of the pression of the BUTTON
    extern uint8_t flag_initialization; //Used to not change the DATARATE at the POWER-ON of the system
    extern uint8_t data_rate; //Used to increment and save the DATARATE
    extern uint8_t reg; //Used to save the register to be READ or WRITE
    extern uint8_t reg_STATUS_REG; //Used to save the STATUS_REG register in the main
    extern uint8_t data[6]; //Used to save the acceleration values READ by the MULTIREAD
    extern int16   dataX; //Used to store the X-axis acceleration in 16bit
    extern int16   dataY; //Used to store the Y-axis acceleration in 16bit
    extern int16   dataZ; //Used to store the Z-axis acceleration in 16bit

    extern uint8_t Buffer[TRANSMIT_BUFFER_SIZE]; //The BUFFER used to send the values by UART
    
    /*
    Function called at the beginning of the main
    and used to initialized all the registers
    */
    void Registers_Start(void);
    
    /*Function used to change or initialize the DATARATE*/
    void Change_DataRate(uint8_t phase);
    
    /*
    Below the UNION used to store the values after the conversion in 32bit is declared
    - DataUnion.f is used to stored the float32 value
    - DataUnion.l is used to extract the byte to saved in Buffer[i]
    */
    union FloatUnion {
        float32 f;
        uint32_t l;
    }DataUnion;
    
#endif


/* [] END OF FILE */
