//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: FileUpload.h
// Summary	: FileUpload functions Header file
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************
#ifndef _FILE_UPLOAD_H_
#define _FILE_UPLOAD_H_

//******************************** Marcos *************************************
#define FILE_UPLOAD_FILE_NAME				("hai.txt")
#define FILE_UPLOAD_ONE_BYTE_MAX_VALUE		(0xFF)
#define FILE_UPLOAD_FILE_OPEN_END			(2)
#define FILE_UPLOAD_ONE						(1)
#define FILE_UPLOAD_OPEN_READ_MODE			("rb")
#define FILE_UPLOAD_MAX_SIZE				(50)

//******************************* Include Files *******************************
#include "common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************

typedef struct __FILE_UPLOAD
{
	uint8 ucUploadId;
	uint32 ulPayLoadSize;
	uint8* pucPayLoad;
	uint8 ucCheckSum;
}_FILE_UPLOAD;

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************
typedef enum __UPLOAD_STATUS
{
	eUploadResponseSuccess,
	eUploadResponseFail,
	eUploadInitId,
	eUploadingId = 0x01,
	eUploadFailId = 0x03,
	eUploadModem = 0x00,
	eModemResponse = 0x01
}_UPLOAD_STATUS;

//**************************** Function Prototype *****************************
bool uploadFile();
bool processFileBuffer(FILE *psFile, uint32* pulFileSize);
bool calCulateUploadSize(uint32* pulFileSize, uint32* pucFileReadSize);

#endif // _FILE_UPLOAD_H_
// EOF