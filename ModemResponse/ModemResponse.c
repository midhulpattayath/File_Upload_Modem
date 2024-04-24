//************************ File Upload Task ***********************************
// Copyright (c) 2024 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File		: modemResponse.c
// Summary	: Modem response Operations
// Note		: None
// Author	: Midhul
// Date		: 23-04-24
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "common.h"
#include "fileUpload.h"
#include "calcCheckSum.h"
#include "buildMsgQueue.h"
#include "modemResponse.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Global Constants ******************************

//****************************** Local Functions ******************************

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Read Modem Response
// Inputs	: psResPonseMsgQ - response Queue
// Outputs	: psResponse - modem Response
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool modemResponse(_MODEM_RESPONSE* psResponse, _MESSAGE_Q psResPonseMsgQ)
{
	bool blReturn = false;

	if(NULL != psResponse)
	{
		psResponse->ucResponseId = *(psResPonseMsgQ.pucMsg);
		psResponse->ucResponseStatus = *(psResPonseMsgQ.pucMsg + 
				sizeof(psResponse->ucResponseId));
		blReturn = true;
	}

	return blReturn;
}

//***************************** FUNCTION_HEADER *******************************
// Purpose	: Upload payload to modem
// Inputs	: psUploadMsgQ - upload message queue
// Outputs	: psResPonseMsgQ - modem response msg queue
// Return	: true if success
// Notes	: Nil
//*****************************************************************************
bool uploadModem(_MESSAGE_Q psUploadMsgQ, _MESSAGE_Q* psResPonseMsgQ)
{
	bool blReturn = false;
	uint8 ucCheckSum = 0;
	_MODEM_RESPONSE sModemResponse = {0};

	if(NULL != psResPonseMsgQ)
	{
		if(psUploadMsgQ.ucMesgId == eUploadModem)
		{
			do
			{
				if (false == CalcCheckSum(psUploadMsgQ.pucMsg, 
								psUploadMsgQ.ulMesgSize, &ucCheckSum))
				{
					break;
				}

				printf("\n Check Sum is : %x", ucCheckSum);

				if (ucCheckSum == 0)
				{
					blReturn = true;
				}
			} while (0);
		}

		psResPonseMsgQ->ucMesgId = eModemResponse;
		sModemResponse.ucResponseId = *psUploadMsgQ.pucMsg;

		if(true == blReturn)
		{
			sModemResponse.ucResponseStatus = eUploadResponseSuccess;
		}
		else
		{
			sModemResponse.ucResponseStatus = eUploadResponseFail;
		}

		blReturn = buildResponseMsgQ(sModemResponse, psResPonseMsgQ);
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
	bool blReturn = false;
	_FILE_UPLOAD sUploadFile = {0};
	_MESSAGE_Q sModemUploadQ = {0};
	_MESSAGE_Q sModemResPonseMsgQ = {0};
	_MODEM_RESPONSE sModemResponse = {0};

	sUploadFile.ucUploadId = eUploadInitId;
	sUploadFile.ulPayLoadSize = 0;

	do
	{
		if(false == buildUploadMsgQ(sUploadFile, &sModemUploadQ))
		{
			break;
		}

		sModemUploadQ.ucMesgId = eUploadModem;

		if(false == CalcCheckSum(sModemUploadQ.pucMsg, sModemUploadQ.ulMesgSize,
					 &sUploadFile.ucCheckSum))
		{
			break;
		}

		// Adding checksum to msg
		memcpy((sModemUploadQ.pucMsg + sModemUploadQ.ulMesgSize), &sUploadFile.ucCheckSum, 
				sizeof(sUploadFile.ucCheckSum));
		sModemUploadQ.ulMesgSize += sizeof(sUploadFile.ucCheckSum);

		if(false == uploadModem(sModemUploadQ, &sModemResPonseMsgQ))
		{
			printf("\n Failed to upload");
			break;
		}

		if(false == modemResponse(&sModemResponse, sModemResPonseMsgQ))
		{
			break;
		}

		if((sModemResponse.ucResponseId == eUploadInitId) &&
			 (sModemResponse.ucResponseStatus == eUploadResponseSuccess))
		{
			printf("\n Upload Started.... ");
			blReturn = true;
		}
	} while (0);
	
	return blReturn;
}