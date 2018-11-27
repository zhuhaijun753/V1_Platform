/****************************************************************************
* File Name : CanTp.c
*
* Modules : CAN Transport Layer source file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-25
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/

/*Include head files AREA*/
#include "CanTp.h"
#include "CanTp_Cfg_Table.h" /*The table only used by CanTp.C*/


/*Macro definition AREA*/




/*Variable declaration AREA*/
static CanTp_ProtocolControlUnitStruct_Type CanTp_ProtocolControlUnit;

/*Function implement AREA*/
/****************************************************************************
 * @function	CanTp_InitFunction
 * @brief  		init cantp parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_TP_EXTERN_API void CanTp_InitFunction(void)
{
	/*Init CanTp_RecvPduCtrInfo*/
	CanTp_RecvPduCtrInfo.ReqData = CanTp_RecvPudBuffer;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunction
 * @brief  		Indication the can to receive can message
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_NOT_OK;
	uint8 ret_subfunc = E_OK;

#if 1 /*Debug used*/
	static uint8 init_flag = 0x00;

	if(init_flag == 0x00)
	{
		CanTp_InitFunction();
		init_flag = 0x01;
	}
#endif

	/*Check the input pointer is NULL*/
	if(NULL == ptr_Data)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}


	CanTp_Debug_OutputInfo(_T("CanTp Notification Recv Data:\nCanChNo = %d,CanMsgId = 0x%lx,CanMsgDlc = %d,Data = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",	\
			ChNo,MsgId,Dlc,ptr_Data[0],ptr_Data[1],ptr_Data[2],ptr_Data[3],ptr_Data[4],ptr_Data[5],ptr_Data[6],ptr_Data[7]));


	/*Check the buffer is idle*/
	/*the buffer is in the used,the ecu will response NRC21*/

	switch(CommFunc_BitShiftRigth(ptr_Data[0],0x04) & 0x0F)
	{
		case CANTP_FRAME_TYPE_SF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv SF...\n"));
			CanTp_RxIndicationFunctionSF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_FF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv FF...\n"));
			CanTp_RxIndicationFunctionFF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_CF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv CF...\n"));
			CanTp_RxIndicationFunctionCF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_FC:
			CanTp_Debug_OutputInfo(_T("CanTp Recv FC...\n"));
			CanTp_RxIndicationFunctionFC(ChNo, MsgId, ptr_Data, Dlc);
			break;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionSF
 * @brief  		Indication the can transport to receive can message with single frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_NOT_OK;
	uint8 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*check diagnostic message id*/

	CanTp_RecvPduCtrInfo.RecvLockFlag = 0x01;
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_SF;
	CanTp_RecvPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*check diagnostic message data length*/
	DataLength = (uint8) (ptr_Data[0] & 0x0F);
	if((DataLength >= 1) && (DataLength <= 7))
	{
		CanTp_ProtocolDataUnitStruct_Type CanTp_DcmPdu;
		uint8 ReqDataArray[7];
		uint8 i = 0x00;

		CanTp_DcmPdu.ReqData = ReqDataArray;

		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = DataLength;
		memcpy(CanTp_RecvPduCtrInfo.ReqData, &ptr_Data[1], CanTp_RecvPduCtrInfo.RecvDataLength);

		CanTp_DcmPdu.BusChannel = ChNo;
		CanTp_DcmPdu.PduType = 0x00;
		CanTp_DcmPdu.ReqType = CanTp_RecvPduCtrInfo.ReqMsgType;
		CanTp_DcmPdu.DataLength = CanTp_RecvPduCtrInfo.TotalDataLength;
		memcpy(CanTp_DcmPdu.ReqData, CanTp_RecvPduCtrInfo.ReqData, CanTp_DcmPdu.DataLength);

		CanTp_Debug_OutputInfo(_T("Diag Info:BusChannel = %d,PduType = 0x%d,ReqType = 0x%x,DataLength = %d,ReqData : [",\
				CanTp_DcmPdu.BusChannel,CanTp_DcmPdu.PduType,CanTp_DcmPdu.ReqType,CanTp_DcmPdu.DataLength));
		for(i = 0x00; i<DataLength; i++)
		{
			CanTp_Debug_OutputInfo(_T("0x%x ",CanTp_DcmPdu.ReqData[i]));
		}
		CanTp_Debug_OutputInfo(_T("]\n"));

		/*notification to dcm modules*/

		ret = E_OK;
	}
	else
	{
		ret = E_PARAM_INVALID;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFF
 * @brief  		Indication the can transport to receive can message with first frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}


	CanTp_RecvPduCtrInfo.RecvLockFlag = 0x01;
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FF;
	CanTp_RecvPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*Get the message length*/
	DataLength = (uint16) ( ((ptr_Data[0] & 0x0F) << 8 ) | (ptr_Data[1]) );
	/*check diagnostic message data length*/
	if(DataLength > 7)
	{
		CanTp_RecvPduCtrInfo.SN = 0x01;
		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = 6;
		memcpy(CanTp_RecvPduCtrInfo.ReqData, &ptr_Data[2], CanTp_RecvPduCtrInfo.RecvDataLength);
		ret = E_OK;

		/*
		 * Send flow control frame
		 *
		 * add code
		 * */

	}
	else
	{
		CanTp_RecvPduCtrInfo.RecvLockFlag = 0x00;
		ret = E_MSG_FORMAT_ERROR;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionCF
 * @brief  		Indication the can transport to receive can message with consecutive frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionCF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;
	uint8 SequenceNumber = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Set the frame type flag*/
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_CF;

	/*Check the diagnostic message id*/
	/*if the consecutive frame id is not equal the first frame,ignore the message*/
	if(CanTp_RecvPduCtrInfo.MsgId != MsgId)
	{
		CanTp_RecvPduCtrInfo.RecvLockFlag = 0x00;
		ret = E_MSG_TYPE_ERROR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Get Sequence Number*/
	SequenceNumber = ptr_Data[0] & 0x0F;
	/*Check SN,and SN error handling*/
	if(SequenceNumber != CanTp_RecvPduCtrInfo.SN)
	{
		ret = E_WRONG_SN;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*SN Control*/
	CanTp_RecvPduCtrInfo.SN++;
	if(CanTp_RecvPduCtrInfo.SN > 0x0F)
	{
		CanTp_RecvPduCtrInfo.SN = 0x00;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the SN Range*/
	if(CanTp_RecvPduCtrInfo.SN == CanTp_ProtocolControlUnit.BS)
	{
		/*Send FC*/
	}
	else
	{
		/*Doing nothing*/
	}

	/*check diagnostic message data length*/
	if((CanTp_RecvPduCtrInfo.RecvDataLength + 7) >= CanTp_RecvPduCtrInfo.TotalDataLength)/*this frame is last frame message*/
	{
		memcpy((CanTp_RecvPduCtrInfo.ReqData + CanTp_RecvPduCtrInfo.RecvDataLength), \
				&ptr_Data[1], \
				(CanTp_RecvPduCtrInfo.TotalDataLength - CanTp_RecvPduCtrInfo.RecvDataLength));
		CanTp_RecvPduCtrInfo.RecvDataLength = CanTp_RecvPduCtrInfo.TotalDataLength;
		ret = E_OK;
	}
	else
	{
		memcpy((CanTp_RecvPduCtrInfo.ReqData + CanTp_RecvPduCtrInfo.RecvDataLength), \
					&ptr_Data[1], (0x07));
		CanTp_RecvPduCtrInfo.RecvDataLength = CanTp_RecvPduCtrInfo.RecvDataLength + 7;
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFC
 * @brief  		Indication the can transport to receive can message with Flow control frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFC(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Set the frame type flag*/
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FC;

	/*Check the diagnostic message id*/
	CanTp_ProtocolControlUnit.FS = ptr_Data[0] & 0X0F;
	CanTp_ProtocolControlUnit.BS = ptr_Data[1];
	CanTp_ProtocolControlUnit.STmin = ptr_Data[2];

	/*
	 * add code
	 *
	 * control strategy
	 * */

}

/****************************************************************************
 * @function	CanTp_WriteRecvBuffer
 * @brief  		write can message to cantp buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_WriteRecvBuffer(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_OK;


	return ret;
}

/****************************************************************************
 * @function	CanTp_ReadRecvBuffer
 * @brief  		read can message to cantp buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_ReadRecvBuffer(uint8* ptr_chno, uint16* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#endif
{
	uint8 ret = E_OK;


	return ret;
}

/*********************************File End*********************************/
