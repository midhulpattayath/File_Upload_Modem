//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: memoryManagement.h
// Summary	: Memeory Operations
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************
#ifndef _MEMORY_MANAGMENT_H_
#define _MEMORY_MANAGMENT_H_

//******************************** Marcos *************************************

//******************************* Include Files *******************************
#include "common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************

//**************************** Function Prototype *****************************
bool allocMemory(uint8 **pucAllocBuffer, uint32 ulSize);
void freeMemory(uint8 *pucMemoryAddress);

#endif // _MEMORY_MANAGMENT_H_
// EOF