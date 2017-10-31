#ifndef TASKS_SOUNDS_H_
#define TASKS_SOUNDS_H_

#include "driverlib.h"

#include "../libs/FatFs/diskio.h"

//****************************************************************************
//
// \brief Provides functions to play sound effects
//
//****************************************************************************

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

//#define MCP4725_ADDR 0x60
//#define MCP4725_DAC_REG 0x40

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

/*!
 * Play sound effect file
 *
 * \param[in] p_file sound file to play
 *
 * \return FRESULT enum (0 = OK)
 *
 */
DRESULT playSoundEffect(const char* p_file);

#endif // TASKS_SOUNDS_H_
