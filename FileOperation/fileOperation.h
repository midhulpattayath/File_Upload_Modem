//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: fileOperation.h
// Summary	: File operations
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************
#ifndef _FILE_OPERATION_
#define _FILE_OPERATION_

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
bool readFileData(FILE *psFile, uint8 *pucPayload, uint32 ulSize);
bool readLength(FILE *psFile, uint32* pulFileSize);
bool openFile(FILE **psFile);
void closeFile(FILE *psFile);

#endif // _FILE_OPERATION_
// EOF