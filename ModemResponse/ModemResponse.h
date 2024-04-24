//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: Modem.h
// Summary	: Modem functions Header file
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************
#ifndef _MODEM_RESPONSE_H_
#define _MODEM_RESPONSE_H_

//******************************** Marcos *************************************

//******************************* Include Files *******************************
#include "common.h"
#include "buildMsgQueue.h"
#include "msgQueue.h"
#include "modem.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************

//**************************** Function Prototype *****************************
bool uploadModem(_MESSAGE_Q psUploadMsgQ, _MESSAGE_Q* psResPonseMsgQ);
bool modemResponse(_MODEM_RESPONSE* psResponse, _MESSAGE_Q psResPonseMsgQ);
bool modemSendInitMsg();

#endif // _MODEM_RESPONSE_H_
// EOF