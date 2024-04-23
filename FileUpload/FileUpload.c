//************************ CHAT APPLICATION **********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: FileUpload.c
// Summary	: FileUpload functions implimentaions
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "FileUpload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//******************************* Local Types *********************************

//***************************** Local Constants *******************************


//***************************** Local Variables *******************************

//***************************** Global Constants *******************************

//****************************** Local Functions ******************************
bool openFile(FILE **psFile);
bool modemSendInitMsg();
bool processFileBuffer(FILE *psFile, uint32* pulFileSize);
bool CalcCheckSum(_FILE_UPLOAD* sUploadFile);
bool allocMemory(uint8 **pucAllocBuffer, uint32 ulSize);
bool findCheckSum(uint8* pucBuffer, uint32 ulSize, uint8* ucCheckSum);
bool readFileData(FILE *psFile, uint8 *pucPayload, uint32 ulSize);
bool readLength(FILE *psFile, uint32* pulFileSize);
bool uploadModem(_FILE_UPLOAD psUploadData);
bool modemResponse(_MODEM_RESPONSE* psResponse, _UPLOAD_STATUS eUploadId);
bool calCulateUploadSize(uint32* pulFileSize, uint32* pucFileReadSize);

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Open the Upload File 
// Inputs	: Nil
// Outputs	: psFile - file open structure double pointer
// Return	: true if successful opned
// Notes	: Nil
//*****************************************************************************
bool openFile(FILE **psFile)
{
	bool blReturn = false;

	if(NULL != psFile)
	{
		*psFile = fopen(FILE_UPLOAD_FILE_NAME, FILE_UPLOAD_OPEN_READ_MODE);

		if(NULL != *psFile)
		{
			blReturn = true;
		}
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Read file length
// Inputs	: psFile - open file structure pointer
// Outputs	: pulFileSize - pointer to get length
// Return	: true if success
// Notes		: Nil
//*****************************************************************************
bool readLength(FILE *psFile, uint32* pulFileSize)
{
	bool blReturn = false;

	if((NULL != psFile) && (NULL != pulFileSize))
	{
		fseek(psFile, 0, FILE_UPLOAD_FILE_OPEN_END);
		*pulFileSize = ftell(psFile);
		fseek(psFile, 0, 0);
		blReturn = true;
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: upload Data to modem
// Inputs	: psUploadData - upload file
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool uploadModem(_FILE_UPLOAD psUploadData)
{
	bool blReturn = true;
	uint16 unIndex = 0;

	printf("\n Upload Id %x", psUploadData.ucUploadId);
	
	if(psUploadData.ucUploadId != eUploadInitId)
	{
		printf("\n Upload payload Size %lx", psUploadData.ulPayLoadSize);
		printf("\n Payload data : ");

		for(unIndex = 0; unIndex < psUploadData.ulPayLoadSize; unIndex++)
		{
			printf("%x ", psUploadData.pucPayLoad[unIndex]);
		}

		printf("\n Check Sum :  %x", psUploadData.ucCheckSum);
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Read Modem Response
// Inputs	: ulUploadSize - upload Size
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool modemResponse(_MODEM_RESPONSE* psResponse, _UPLOAD_STATUS eUploadId)
{
	bool blReturn = false;

	if(NULL != psResponse)
	{
		if((eUploadId == eUploadingId) || (eUploadId == eUploadInitId))
		{
			psResponse->ucResponseId = eUploadId;
			psResponse->ucResponseStatus = eUploadResponseSuccess;
		}
		else
		{
			psResponse->ucResponseId = eUploadFailId;
			psResponse->ucResponseStatus = eUploadResponseFail;
		}

		blReturn = true;
	}

	return blReturn;
}

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
// Purpose	: Alloacting memory space
// Inputs	: ulSize - allocating size
// Outputs	: pucAllocBuffer - Allocating buffer
// Return	: true if success
// Notes		: Nil
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
// Purpose	: Read data from file
// Inputs	: psFile - File pointer
//				pulSize - read size
// Outputs	: pucPayload - read buffer
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool readFileData(FILE *psFile, uint8 *pucPayload, uint32 ulSize)
{
	bool blReturn = false;

	if((NULL != psFile) && (NULL != pucPayload))
	{
		fread(pucPayload, ulSize, FILE_UPLOAD_ONE, psFile);
		blReturn = true;
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: File upload
// Inputs	: Nil
// Outputs	: Nil
// Return	: true if success
// Notes		: Nil
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
		
		if(false == modemSendInitMsg())
		{
			printf("\n Upload Init failed");
			break;
		}
		
		if(false == processFileBuffer(spFile, &ulFileSize))
		{
			printf("\n File upload failed");
			break;
		}

		fclose(spFile);
	} while (0);
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: upload to modem
// Inputs	: psFile - File pointer
//					pulFileSize - read size
// Outputs	: Nil
// Return	: true if success
// Notes		: Nil
//*****************************************************************************
bool processFileBuffer(FILE *psFile, uint32* pulFileSize)
{
	bool blReturn = false;
	_FILE_UPLOAD sUploadFile = {0};
	_MODEM_RESPONSE sModemResponse = {0};

	if((NULL != psFile) && (NULL != pulFileSize))
	{
		while(1)
		{
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

			if(false == CalcCheckSum(&sUploadFile))
			{
				printf("\n Check Sum failed");
				break;
			}

			// if(false == uploadModem(sUploadFile))
			// {
			// 	printf("\n Upload modem failed");
			// 	break;
			// }

			if(false == modemResponse(&sModemResponse, sUploadFile.ucUploadId))
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

			free(sUploadFile.pucPayLoad);

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

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Sent Upload Start msg to Modem
// Inputs	: Nil
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool modemSendInitMsg()
{
	bool blReturn = true;
	_FILE_UPLOAD sUploadFile = {0};
	_MODEM_RESPONSE sModemResponse = {0};

	sUploadFile.ucUploadId = eUploadInitId;
	sUploadFile.ulPayLoadSize = 0;

	do
	{
		if(false == uploadModem(sUploadFile))
		{
			break;
		}

		if(false == modemResponse(&sModemResponse, sUploadFile.ucUploadId))
		{
			break;
		}

		if((sModemResponse.ucResponseId == eUploadInitId) &&
			 (sModemResponse.ucResponseStatus == eUploadResponseSuccess))
		{
			blReturn = true;
		}
	} while (0);
	
	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Sent Upload Start msg to Modem
// Inputs	: Nil
// Outputs	: Nil
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool CalcCheckSum(_FILE_UPLOAD *sUploadFile)
{
	bool blReturn = false;
	uint32 ulUploadSize = 0;
	uint8* pucPayload = NULL;

	if(NULL != sUploadFile)
	{
		ulUploadSize += sizeof(sUploadFile->ucUploadId);

		do
		{
			if(false == allocMemory(&pucPayload, sizeof(sUploadFile->ucUploadId) + 
						sizeof(sUploadFile->ulPayLoadSize) + sUploadFile->ulPayLoadSize))
			{
				break;
			}

			memcpy(pucPayload, sUploadFile->ucUploadId, sizeof(sUploadFile->ucUploadId));
			memcpy((pucPayload + ulUploadSize), sUploadFile->pucPayLoad, sUploadFile->ulPayLoadSize);
			ulUploadSize += sizeof(sUploadFile->ulPayLoadSize);
			memcpy((pucPayload + ulUploadSize), sUploadFile->pucPayLoad, sUploadFile->ulPayLoadSize);
			ulUploadSize += sUploadFile->ulPayLoadSize;

			if(false == findCheckSum(pucPayload, ulUploadSize, &sUploadFile->ucCheckSum))
			{
				break;
			}

			free(pucPayload);
			blReturn = true;
		} while (0);
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Calculating Check Sum
// Inputs	: pucBuffer - payload buffer
// 				ulSize - payload size
// Outputs	: ucCheckSum - check sum 
// Return	: true if success
// Notes		: Nil
//*****************************************************************************
bool findCheckSum(uint8* pucBuffer, uint32 ulSize, uint8* ucCheckSum)
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

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Starting of the program
// Inputs	: Nil
// Outputs	: Nil
// Return	: Nil
// Notes	: Nil
//*****************************************************************************
int main()
{
	uploadFile();
}