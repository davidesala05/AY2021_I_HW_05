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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    EEPROM_Start();
    Change_DataRate(INITIALIZATION);
    

    for(;;)
    {
        /* Place your application code here. */
        
        if (flag_button){
            Change_DataRate(UPDATING);
            flag_button = 0;
        }
    }
}

/* [] END OF FILE */
