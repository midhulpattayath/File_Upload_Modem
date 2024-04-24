//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: memoryManagement.c
// Summary	: Memory operations
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
#include "memoryManagement.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Alloacting memory space
// Inputs	: ulSize - allocating size
// Outputs	: pucAllocBuffer - Allocating buffer
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool allocMemory(uint8 **pucAllocBuffer, uint32 ulSize)
{
	bool blReturn = false;

	if((NULL != pucAllocBuffer) && (ulSize != 0))
	{
		*pucAllocBuffer = (char*)malloc(ulSize);

		if(NULL != *pucAllocBuffer)
		{
			blReturn = true;
		}
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Dealloacting memory space
// Inputs	: pucAllocBuffer - Allocating buffer
// Outputs	: Nil
// Return	: Nil
// Notes	: Nil
//*****************************************************************************
void freeMemory(uint8 *pucMemoryAddress)
{
	free(pucMemoryAddress);
}