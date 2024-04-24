//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: calcCheckSum.c
// Summary	: Calculate Check Sum value
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
#include "fileUpload.h"
#include "calcCheckSum.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Calculating Check Sum
// Inputs	: pucBuffer - payload buffer
// 			ulSize - payload size
// Outputs	: ucCheckSum - check sum 
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool CalcCheckSum(uint8* pucBuffer, uint32 ulSize, uint8* ucCheckSum)
{
	bool blReturn = false;
	uint16 unCheckSum = 0;
	uint8* pucData = (uint8*)&unCheckSum;
	uint32 ulIndex = 0;

	if((NULL != pucBuffer) && (NULL != ucCheckSum))
	{
		for(ulIndex = 0; ulIndex < ulSize; ulIndex++)
		{
			unCheckSum += pucBuffer[ulIndex];

			while(unCheckSum > FILE_UPLOAD_ONE_BYTE_MAX_VALUE)
			{
				unCheckSum = (*pucData) + *(pucData + FILE_UPLOAD_ONE);
			}
		}

		*ucCheckSum = (uint8) unCheckSum;
		*ucCheckSum = ~(*ucCheckSum);
		blReturn = true;
	}

	return blReturn;
}