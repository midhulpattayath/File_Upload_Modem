//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: buildMsgQueue.h
// Summary	: Message Qeueu operations
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************
#ifndef _BUILD_MSG_QUEUE_H_
#define _BUILD_MSG_QUEUE_H_

//******************************** Marcos *************************************

//******************************* Include Files *******************************
#include "common.h"
#include "msgQueue.h"
#include <stdio.h>
#include "fileUpload.h"
#include "modem.h"
#include "modemResponse.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************

//**************************** Function Prototype *****************************
bool buildUploadMsgQ(_FILE_UPLOAD sUploadFile, _MESSAGE_Q* psMsgQ);
bool buildResponseMsgQ(_MODEM_RESPONSE sModemResponse, _MESSAGE_Q* psMsgQ);

#endif // _BUILD_MSG_QUEUE_H_
// EOF