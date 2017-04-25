/* 
 * File:   pic32mx_btad_buttons.c
 * Author: C16105
 *
 * Created on September 19, 2014, 10:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "meb2_buttons.h"


#define LONG_PRESS_DELAY                10 // 1s

APP_AUDIOPLAYER *appDataPtr;
static unsigned int mNewButtonState;
static unsigned int mButtonState;
static uint8_t  mButtonEvent = 0;

void APP_ButtonInit(void)
{
    mButtonState = APP_READ_BUTTON_PORTS();

    mRepeatButton = INVALID_BUTTON;
    mRepeatCount = 0;
    mButtonEvent = 0;
    
    appDataPtr = APP_GetAppDataInstance();
}

void APP_ButtonTask(void)
{
    unsigned int newState = mNewButtonState;
    unsigned int changed;
    bool intStatus;

    if (mButtonEvent == 1)
    {
        intStatus = SYS_INT_Disable();
        {
            mButtonEvent = 0;
            newState = mNewButtonState;
            changed = mButtonState ^ newState;
        }
        if(intStatus) SYS_INT_Enable();

        if (changed & APP_BUTTON1_PIN)
        {
            if ((newState & APP_BUTTON1_PIN) == 0)
            {
                //DOWN
                APP_OnButtonEvent(APP_BUTTON1,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON1;
                    mRepeatCount = 0;
                }
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON1)
                {
                    APP_OnButtonEvent(APP_BUTTON1,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
//                else
//                {
//                    APP_OnButtonEvent(APP_BUTTON1,false,0);
//                }
                
            }
        }
        if (changed & APP_BUTTON2_PIN)
        {
            if ((newState & APP_BUTTON2_PIN) == 0)
            {
                APP_OnButtonEvent(APP_BUTTON2,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON2;
                    mRepeatCount = 0;
                }
                
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON2)
                {
                    APP_OnButtonEvent(APP_BUTTON2,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
//                else
//                {
//                    APP_OnButtonEvent(APP_BUTTON2,false,0);
//                }
            }
        }
        if (changed & APP_BUTTON3_PIN)
        {
            if ((newState & APP_BUTTON3_PIN) == 0)
            {
                APP_OnButtonEvent(APP_BUTTON3,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON3;
                    mRepeatCount = 0;
                }
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON3)
                {
                    APP_OnButtonEvent(APP_BUTTON3,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
//                else
//                {
//                    APP_OnButtonEvent(APP_BUTTON3,false,0);
//                }
            }
        }
        
        mButtonState = newState;
    }
}

// pass the mRepeatButton to this function
int8_t APP_ButtonGetState(int8_t  button){
    if(button == INVALID_BUTTON)
        return -1;
    int8_t ret = -1;
    switch(button){
        case APP_BUTTON1:
            ret = BSP_SwitchStateGet(BSP_SWITCH_1);
            break;
        case APP_BUTTON2:
            ret = BSP_SwitchStateGet(BSP_SWITCH_2);
            break;
        case APP_BUTTON3:
            ret = BSP_SwitchStateGet(BSP_SWITCH_3);
            break;
       
        default:
            break;
    }
    return ret;
}

void APP_OnButtonEvent(uint8_t button, bool bButtonClosed, int32_t repeatCount)
{
    switch (button)
    {
        // *****************************************************************************
        // Button S1: UP
        // *****************************************************************************
        case APP_BUTTON1:
            if(bButtonClosed)
            {
                if(repeatCount >= LONG_PRESS_DELAY)
                {
                    // every 100ms send a ff command
//                    if((repeatCount - LONG_PRESS_DELAY) % 100 == 0)
                    {
                        appDataPtr->pressCMD = PLAYER_CMD_FAST_FORWARD;
//                        APP_PlayerCommand ( PLAYER_CMD_FAST_FORWARD );
                    }
                }
                
            }else
            {
                // Short press on SW3
                if(repeatCount < LONG_PRESS_DELAY)
                {
                    APP_PlayerCommand ( PLAYER_CMD_NEXT_FILE );
                }else{
                    // reset FF/RW step
                    APP_ResetPlayerFileAdvanceStep();
                }
            }
            
            break;
            
        case APP_BUTTON2:
            if(bButtonClosed)
            {
            }else
            {
                APP_PlayerCommand ( PLAYER_CMD_PLAY_PAUSE );
            }
            
            break;
            
        case APP_BUTTON3:
            if(bButtonClosed)
            {
                if(repeatCount >= LONG_PRESS_DELAY)
                {
                    // every 100ms
                    {
                        appDataPtr->pressCMD = PLAYER_CMD_REWIND;
//                        APP_PlayerCommand ( PLAYER_CMD_REWIND );
                    }
                }
                
            }else
            {
                // Short press on SW3
                if(repeatCount < LONG_PRESS_DELAY)
                {
                    APP_PlayerCommand ( PLAYER_CMD_PREV_FILE );
                }else{
                    // resume playing
                    APP_SetPlayerPlay(true);
                    // reset FF/RW step
                    APP_ResetPlayerFileAdvanceStep();
                }
            }
            break;
            
        default:
            break;
    }
    
}

void buttons_handleInterrupt(unsigned int newButtonState)
{
    // Remember new buttons state
    mNewButtonState = newButtonState;
    mButtonEvent = 1;
}