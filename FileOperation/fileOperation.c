//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: fileOperation.c
// Summary	: file operations
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
#include "fileUpload.h"
#include "fileOperation.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

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
// Notes	: Nil
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
// Purpose	: Close file
// Inputs	: psFile - Close file structure pointer
// Outputs	: Nil
// Return	: Nil
// Notes	: Nil
//*****************************************************************************
void closeFile(FILE *psFile)
{
	fclose(psFile);
}