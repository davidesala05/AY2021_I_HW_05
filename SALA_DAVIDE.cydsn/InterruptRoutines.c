/* ========================================
 *
 * ISR of the BUTTON
 * 
 * ========================================
*/

#include "InterruptRoutines.h"

CY_ISR(Custom_BUTTON_ISR){

    flag_button = 1; //Flag used in the main to call the funciton used to change the DATARATE
}

/* [] END OF FILE */
