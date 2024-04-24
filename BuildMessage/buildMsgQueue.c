//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: buildMsgQueue.c
// Summary	: Create Msg Queue
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
#include "memoryManagement.h"
#include "fileUpload.h"
#include "modem.h"
#include "buildMsgQueue.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Build Upload Message Queue
// Inputs	: sUploadFile - Upload data
// Outputs	: psMsgQ - message Queue
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool buildUploadMsgQ(_FILE_UPLOAD sUploadFile, _MESSAGE_Q* psMsgQ)
{
	bool blReturn = false;

	if (NULL != psMsgQ)
	{
		psMsgQ->ulMesgSize = sizeof(sUploadFile.ucUploadId);

		do
		{
			if (false == allocMemory(&(psMsgQ->pucMsg), (sizeof(sUploadFile.ucUploadId) +
							sizeof(sUploadFile.ulPayLoadSize) + sUploadFile.ulPayLoadSize + 
									sizeof(sUploadFile.ucCheckSum))))
			{
				break;
			}

			memcpy(psMsgQ->pucMsg, &sUploadFile.ucUploadId, sizeof(sUploadFile.ucUploadId));
			memcpy((psMsgQ->pucMsg + psMsgQ->ulMesgSize), &(sUploadFile.ulPayLoadSize), sUploadFile.ulPayLoadSize);
			psMsgQ->ulMesgSize += sizeof(sUploadFile.ulPayLoadSize);

			if (sUploadFile.pucPayLoad != NULL)
			{
				memcpy((psMsgQ->pucMsg + psMsgQ->ulMesgSize), sUploadFile.pucPayLoad, sUploadFile.ulPayLoadSize);
				psMsgQ->ulMesgSize += sUploadFile.ulPayLoadSize;
			}

			blReturn = true;
		} while (0);
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Build Response Message Queue
// Inputs	: sModemResponse - modem response
// Outputs	: psMsgQ - message Queue
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool buildResponseMsgQ(_MODEM_RESPONSE sModemResponse, _MESSAGE_Q* psMsgQ)
{
	bool blReturn = false;

	if(NULL != psMsgQ)
	{
		do
		{
			if(false == allocMemory(&psMsgQ->pucMsg, (sizeof(sModemResponse.ucResponseId) +
							sizeof(sModemResponse.ucResponseStatus))))
			{
				break;
			}
			
			memcpy(psMsgQ->pucMsg, &sModemResponse.ucResponseId, sizeof(sModemResponse.ucResponseId));
			psMsgQ->ulMesgSize = sizeof(sModemResponse.ucResponseId);
			memcpy((psMsgQ->pucMsg + psMsgQ->ulMesgSize), &sModemResponse.ucResponseStatus, 
				sizeof(sModemResponse.ucResponseStatus));
			psMsgQ->ulMesgSize = sizeof(sModemResponse.ucResponseStatus);
			blReturn = true;
		} while (0);
	}

	return blReturn;
}