//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: msgQeueu.h
// Summary	: Message Queue structure creation
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************
#ifndef _MSG_QUEUE_
#define _MSG_QUEUE_

//******************************** Marcos *************************************

//******************************* Include Files *******************************
#include "common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************
typedef struct __MESSAGE_Q
{
	uint8 ucMesgId;
	uint32 ulMesgSize;
	uint8* pucMsg;
}_MESSAGE_Q;

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************

//**************************** Function Prototype *****************************

#endif // _MSG_QUEUE_
// EOF