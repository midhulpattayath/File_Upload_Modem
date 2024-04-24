//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: main.c
// Summary	: Starting of file upload task
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
// #include "fileOperation.h"
#include "Fileupload.h"
// #include "memoryManagement.h"
// #include "modem.h"
// #include "calcCheckSum.h"
// #include "buildMsgQueue.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Starting of the file upload task
// Inputs	: Nil
// Outputs	: Nil
// Return	: return 0
// Notes	: Nil
//*****************************************************************************
int main()
{
	if(true == uploadFile())
	{
		printf("\n File Transfer Completed........");
	}

	return 0;
}