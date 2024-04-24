//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: FileUpload.h
// Summary	: FileUpload functions implimentaion
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "FileUpload.h"
#include "buildMsgQueue.h"
#include "calcCheckSum.h"
#include "fileOperation.h"
#include "common.h"
#include "modemResponse.h"
#include "memoryManagement.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Calculating read file size
// Inputs	: Nil
// Outputs	: pulFileSize - File size
// 				pucFileReadSize - File read size
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool calCulateUploadSize(uint32* pulFileSize, uint32* pucFileReadSize)
{
	bool blReturn = false;

	if((NULL != pucFileReadSize) && (NULL != pulFileSize))
	{
		if(*pulFileSize > FILE_UPLOAD_MAX_SIZE)
		{
			*pucFileReadSize = FILE_UPLOAD_MAX_SIZE;
		}
		else
		{
			*pucFileReadSize = *pulFileSize;
		}

		*pulFileSize -= FILE_UPLOAD_MAX_SIZE;
		blReturn = true;
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: File upload
// Inputs	: Nil
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool uploadFile()
{
	bool blReturn = false;
	uint32 ulFileSize = 0;
	FILE* spFile = NULL;

	do
	{
		if(false == openFile(&spFile))
		{
			printf("\n File open failed");
			break;
		}
		
		if(false == readLength(spFile, &ulFileSize))
		{
			printf("\n Read length failed");
			break;
		}
		
		if(false == processFileBuffer(spFile, &ulFileSize))
		{
			printf("\n File upload failed");
			break;
		}

		closeFile(spFile);
	} while (0);

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: upload to modem
// Inputs	: psFile - File pointer
//			pulFileSize - read size
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool processFileBuffer(FILE *psFile, uint32* pulFileSize)
{
	bool blReturn = false;
	bool blModemInit = false;
	_FILE_UPLOAD sUploadFile = {0};
	_MESSAGE_Q sUploadMessageQ = {0};
	_MESSAGE_Q sModemResonseQ = {0};
	_MODEM_RESPONSE sModemResponse = {0};

	if((NULL != psFile) && (NULL != pulFileSize))
	{
		blModemInit = modemSendInitMsg();

		while(true == blModemInit)
		{
			sUploadMessageQ.ucMesgId = eUploadModem;
			sUploadFile.ucUploadId = eUploadingId;

			if(false == calCulateUploadSize(pulFileSize, &sUploadFile.ulPayLoadSize))
			{
				printf("\n Size calculation failed");
				break;
			}

			if(false == allocMemory(&sUploadFile.pucPayLoad, sUploadFile.ulPayLoadSize))
			{
				printf("\n Memory allocation failed");
				break;
			}

			if(false == readFileData(psFile, sUploadFile.pucPayLoad, sUploadFile.ulPayLoadSize))
			{
				printf("\n File read failed");
				break;
			}

			if(false == buildUploadMsgQ(sUploadFile, &sUploadMessageQ))
			{
				printf("\n parse Buffer build failed");
				break;
			}

			if(false == CalcCheckSum(sUploadMessageQ.pucMsg, sUploadMessageQ.ulMesgSize, &sUploadFile.ucCheckSum))
			{
				printf("\n parse Buffer build failed");
				break;
			}

			// Adding check sum to the msg data
			memcpy((sUploadMessageQ.pucMsg + sUploadMessageQ.ulMesgSize), &sUploadFile.ucCheckSum,
				 sizeof(sUploadFile.ucCheckSum));
			sUploadMessageQ.ulMesgSize += sizeof(sUploadFile.ucCheckSum);

			if(false == uploadModem(sUploadMessageQ, &sModemResonseQ))
			{
				printf("\n Upload modem failed");
				break;
			}

			if(false == modemResponse(&sModemResponse, sModemResonseQ))
			{
				printf("\n Modem response failed");
				break;
			}

			if((sModemResponse.ucResponseStatus != eUploadResponseSuccess) ||
				 (sModemResponse.ucResponseId != sUploadFile.ucUploadId))
			{
				printf("\n Modem response Not match");
				break;
			}

			freeMemory(sUploadFile.pucPayLoad);
			freeMemory(sUploadMessageQ.pucMsg);
			freeMemory(sModemResonseQ.pucMsg);

			if(sUploadFile.ulPayLoadSize != FILE_UPLOAD_MAX_SIZE)
			{
				printf("\n Completed file transfer");
				blReturn = true;
				break;
			}
		}
	}

	return blReturn;
}
