//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: calcCheckSum.h
// Summary	: Calculating the check sum value
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************
#ifndef _CALCULATE_CHECK_SUM_H_
#define _CALCULATE_CHECK_SUM_H_

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
bool CalcCheckSum(uint8* pucBuffer, uint32 ulSize, uint8* ucCheckSum);

#endif // _CALCULATE_CHECK_SUM_H_
// EOF