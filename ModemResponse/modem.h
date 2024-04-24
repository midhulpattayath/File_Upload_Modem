//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: Modem.h
// Summary	: Modem Structure declaration
// Note		: None
// Author	: Midhul
// Date		: 22-04-24
//
//*****************************************************************************
#ifndef _MODEM_H_
#define _MODEM_H_

//******************************** Marcos *************************************

//******************************* Include Files *******************************
#include "common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Structure Declarations *************************
typedef struct __MODEM_RESPONSE
{
	uint8 ucResponseId;
	uint8 ucResponseStatus;
}_MODEM_RESPONSE;

//*********************** Inline Method Implementations ***********************

//***************************** Enumerations **********************************

//**************************** Function Prototype *****************************

#endif // _MODEM_H_
// EOF