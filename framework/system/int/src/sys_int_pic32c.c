/*******************************************************************************
  Interrupt System Service

  Company:
    Microchip Technology Inc.

  File Name:
    sys_int_pic32c.c

  Summary:
    Interrupt System Service APIs.

  Description:
    This file contains functions related to the Interrupt System Service for PIC32
    devices.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#include "system/int/sys_int.h"

volatile bool g_interrupt_enabled;

// *****************************************************************************
// *****************************************************************************
// Section: Function Definitions
// *****************************************************************************
// *****************************************************************************


/******************************************************************************

  Function:
    void SYS_INT_Initialize ( void )

  Summary:
    Configures and initializes the interrupt sub-system.

  Description:
    This function appropriately configures and initializes the interrupt sub-system
    for the current system design.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
  <code>
  SYS_INT_Initialize();
  </code>

  Remarks:
    This function is not implemented in the System Interrupt library.  It is
    implemented by the board support package (using the processor-specific
    interrupt peripheral library) because it requires knowledge of the specific
    interrupt requirements for each system.
*/

void SYS_INT_Initialize ( void )

{
    g_interrupt_enabled = false;
    NVIC_SetPriorityGrouping( 0x00 );
}

//*******************************************************************************
/*  Function:
     SYS_INT_PROCESSOR_STATUS  SYS_INT_StatusGetAndDisable ( void )

  Summary:
    Disables interrupts to the processor and return the previous status.
    
  Description:
    This function disables interrupts to the processor at the top level. This
    function can be called to prevent any source from being able to generate an
    interrupt. It returns the processor status (which includes global interrupt
    status and Interrupt Priority status) before disabling the interrupts.

  Remarks:
    See sys_int.h file for more details.
*/

SYS_INT_PROCESSOR_STATUS  SYS_INT_StatusGetAndDisable ( void )
{   
      SYS_INT_PROCESSOR_STATUS processorStatus = true;
      
      processorStatus = g_interrupt_enabled;
      __disable_irq();
	  __DMB();
	  g_interrupt_enabled = false;
      
      return processorStatus;
}

//*******************************************************************************
/* Function:
    void SYS_INT_StatusRestore ( SYS_INT_PROCESSOR_STATUS processorStatus )

  Summary:
    Restores the processor status.

  Description:
    This function sets the processor status based on the 32 bit value passed as 
    a parameter. 0th bit of the status is for Master Interrupt status.

  Remarks:
    See sys_int.h file for more details.
*/

void SYS_INT_StatusRestore ( SYS_INT_PROCESSOR_STATUS processorStatus )
{
    if( processorStatus )
    {
        SYS_INT_Enable();
    }
}

//*******************************************************************************
/*  Function:
     void SYS_INT_Enable ( void )

  Summary:
    Enables global interrupts to the processor.
    
  Description:
    This function enables interrupts to the processor at the top level, allowing
    any currently enabled source to generate an interrupt.  This function must be
    called before any source will be able to generate an interrupt.

  Remarks:
        See sys_int.h file for more details.
*/

void SYS_INT_Enable ( void )
{
    g_interrupt_enabled = true; 
    __DMB();                    
    __enable_irq();             
}

// *****************************************************************************
/*  Disable the generation of interrupts to the CPU

  Summary:
     Disables all interrupts

  Description:
     This function disables all interrupts.

  Remarks:
    This API will be depricated soon. Use "SYS_INT_StatusGetAndDisable" instead.
 */

bool SYS_INT_Disable( void )
{
    SYS_INT_PROCESSOR_STATUS processorStatus;

    /* Save the processor status and then Disable the global interrupt */
    processorStatus = SYS_INT_StatusGetAndDisable();

    /* return the interrupt status */
    return (bool)(processorStatus & 0x01);
}

// *****************************************************************************
/* Function:
    bool SYS_INT_SourceDisable ( INT_SOURCE source )

  Summary:
    Disables the interrupt source.

  Description:
    This routine disables the given source from generating interrupts the 
    processor when events occur.It returns the interrupt source enable/disable 
	status before disabling the interrupt source.

  Remarks:
    See sys_int.h file for more details.
 */


bool SYS_INT_SourceDisable ( INT_SOURCE source )
{   
    bool intSrcStatus = true;
    SYS_INT_PROCESSOR_STATUS processorStatus;
    
    processorStatus = SYS_INT_StatusGetAndDisable();
    
    intSrcStatus    = SYS_INT_SourceIsEnabled( source );
    
    NVIC_DisableIRQ( source );

    SYS_INT_StatusRestore( processorStatus );
    
    /* return the source status */
    return intSrcStatus;
}

/*******************************************************************************
 End of File
*/


