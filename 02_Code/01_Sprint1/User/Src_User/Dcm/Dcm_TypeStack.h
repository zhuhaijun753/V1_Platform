/****************************************************************************
* File Name : Dcm_TypeStack.h
*
* Modules : Diagnostic Communication management Layer head file
*
* Summary : 1.The file define use data type in diagnostic communication layer.
*
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-10
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef _DCM_TYPESTACK_H_
#define _DCM_TYPESTACK_H_

/*Include head files AREA*/
/*
 * Negative Response Code (NRC) definition and values
 * Reference <<ISO 14229-1 2013>>.
 * */
#define DCM_NRC_PR				(0x00)	/*positiveResponse*/
#define DCM_NRC_GR				(0x10)  /*generalReject*/
#define DCM_NRC_SNS				(0x11)  /*serviceNotSupported*/
#define DCM_NRC_SFNS			(0x12)  /*sub-functionNotSupported*/
#define DCM_NRC_IMLOIF			(0x13)  /*incorrectMessageLengthOrInvalidFormat*/
#define DCM_NRC_RTL				(0x14)  /*responseTooLong*/
#define DCM_NRC_BRR				(0x21)  /*busyRepeatRequest*/
#define DCM_NRC_CNC				(0x22)  /*conditionsNotCorrect*/
#define DCM_NRC_RSE				(0x24)  /*requestSequenceError*/
#define DCM_NRC_NRFSC			(0x25)  /*noResponseFromSubnetComponent*/
#define DCM_NRC_FPEORA			(0x26)  /*FailurePreventsExecutionOfRequestedAction*/
#define DCM_NRC_ROOR			(0x31)  /*requestOutOfRange*/
#define DCM_NRC_SAD				(0x33)  /*securityAccessDenied*/
#define DCM_NRC_IK				(0x35)  /*invalidKey*/
#define DCM_NRC_ENOA			(0x36)  /*exceedNumberOfAttempts*/
#define DCM_NRC_RTDNE			(0x37)  /*requiredTimeDelayNotExpired*/
#define DCM_NRC_UDNA			(0x70)  /*uploadDownloadNotAccepted*/
#define DCM_NRC_TDS				(0x71)  /*transferDataSuspended*/
#define DCM_NRC_GPF				(0x72)  /*generalProgrammingFailure*/
#define DCM_NRC_WBSC			(0x73)  /*wrongBlockSequenceCounter*/
#define DCM_NRC_RCRRP			(0x78)  /*requestCorrectlyReceived-ResponsePending*/
#define DCM_NRC_SFNISAS			(0x7E)  /*sub-functionNotSupportedInActiveSession*/
#define DCM_NRC_SNSIAS			(0x7F)  /*serviceNotSupportedInActiveSession*/
#define DCM_NRC_RPMTH			(0x81)  /*rpmTooHigh*/
#define DCM_NRC_RPMTL			(0x82)  /*rpmTooLow*/
#define DCM_NRC_EIR				(0x83)  /*engineIsRunning*/
#define DCM_NRC_EINR			(0x84)  /*engineIsNotRunning*/
#define DCM_NRC_ERTTL			(0x85)  /*engineRunTimeTooLow*/
#define DCM_NRC_TEMPTH			(0x86)  /*temperatureTooHigh*/
#define DCM_NRC_TEMPTL			(0x87)  /*temperatureTooLow*/
#define DCM_NRC_VSTH			(0x88)  /*vehicleSpeedTooHigh*/
#define DCM_NRC_VSTL			(0x89)  /*vehicleSpeedTooLow*/
#define DCM_NRC_TPTH			(0x8A)  /*throttle/PedalTooHigh*/
#define DCM_NRC_TPTL			(0x8B)  /*throttle/PedalTooLow*/
#define DCM_NRC_TRNIN			(0x8C)  /*transmissionRangeNotInNeutral*/
#define DCM_NRC_TRNIG			(0x8D)  /*transmissionRangeNotInGear*/
#define DCM_NRC_BSNC			(0x8F)  /*brakeSwitch(es)NotClosed (Brake Pedal not pressed or not applied)*/
#define DCM_NRC_SLNIP			(0x90)  /*shifterLeverNotInPark*/
#define DCM_NRC_TCCL			(0x91)  /*torqueConverterClutchLocked*/
#define DCM_NRC_VTH				(0x92)  /*voltageTooHigh*/
#define DCM_NRC_VTL				(0x93)  /*voltageTooLow*/

/*
 * diagnostic services Identifier definition and values
 * Reference <<ISO 14229-1 2013>>.
 * */
#define DCM_SID_DSC				(0x10)  /*DiagnosticSessionControl*/
#define DCM_SID_ER				(0x11)	/*ECUReset*/
#define DCM_SID_CDTCI			(0x14)	/*ClearDiagnosticInformation*/
#define DCM_SID_RDTCI			(0x19)	/*ReadDTCInformation*/
#define DCM_SID_RDBI			(0x22)	/*ReadDataByIdentifier*/
#define DCM_SID_RMBA			(0x23)	/*ReadMemoryByAddress*/
#define DCM_SID_RSDBI			(0x24)	/*ReadScalingDataByIdentifier*/
#define DCM_SID_SA				(0x27)	/*SecurityAcces*/
#define DCM_SID_CC				(0x28)	/*CommunicationControl*/
#define DCM_SID_RDBPI			(0x2A)	/*ReadDataByPeriodicIdentifier*/
#define DCM_SID_DDDI			(0x2C)	/*DynamicallyDefineDataIdentifier*/
#define DCM_SID_WDBI			(0x2E)	/*WriteDataByIdentifier*/
#define DCM_SID_IOCBI			(0x2F)	/*InputOutputControlByIdentifier*/
#define DCM_SID_RC				(0x31)	/*RoutineControl*/
#define DCM_SID_RD				(0x34)	/*RequestDownload*/
#define DCM_SID_RU				(0x35)	/*RequestUpload*/
#define DCM_SID_TD				(0x36)	/*TransferData*/
#define DCM_SID_RTE				(0x37)	/*RequestTransferExit*/
#define DCM_SID_RFT				(0x38)	/*RequestFileTransfer*/
#define DCM_SID_WMBA			(0x3D)	/*WriteMemoryByAddress*/
#define DCM_SID_TP				(0x3E)	/*TesterPresent*/
#define DCM_SID_ATP				(0x83)	/*AccessTimingParameter*/
#define DCM_SID_SDT				(0x84)	/*SecuredDataTransmission*/
#define DCM_SID_CDTCS			(0x85)	/*ControlDTCSetting*/
#define DCM_SID_ROE				(0x86)	/*ResponseOnEvent*/
#define DCM_SID_LC				(0x87)	/*LinkControl*/

/*
 * DTC Format Identifier definition
 * Reference <<ISO 14229-1 2013>>.
 * */
/*This parameter value identifies the DTC format reported by the server as defined in ISO 15031-6 specification.*/
#define DCM_DTCFI_SAE_J2012_DA_00	(0x00)
/*This parameter value identifies the DTC format reported by the server as defined in this table by the parameter DTCAndStatusRecord.*/
#define DCM_DTCFI_ISO_14229_1		(0x01)
/*This parameter value identifies the DTC format reported by the server as defined in SAE J1939-73.*/
#define DCM_DTCFI_SAE_J1939_73		(0x02)
/*This parameter value identifies the DTC format reported by the server as defined in ISO 11992-4 specification.*/
#define DCM_DTCFI_ISO_11992_4		(0x03)
/*This parameter value identifies the DTC format reported by the server as defined in ISO 27145-2 specification.*/
#define DCM_DTCFI_SAE_J2012_DA_04	(0x04)

/*
 * DTC Groups Information Definition
 * Reference <<ISO 15031-6 2005>>
 * */
#define DCM_DTCGI_EMISSION			(0x000000)
#define DCM_DTCGI_POWERTRAIN		(0x100000)
#define DCM_DTCGI_CHASSIS			(0x200000)
#define DCM_DTCGI_BODY				(0x800000)
#define DCM_DTCGI_NETWORK			(0xC00000)
#define DCM_DTCGI_ALLGROUPS			(0xFFFFFF)

/*
 * Dtc Groups Types definition
 * */
#define DCM_DTCGT_EMISSION			(0x0)
#define DCM_DTCGT_POWERTRAIN		(0x1)
#define DCM_DTCGT_CHASSIS			(0x2)
#define DCM_DTCGT_BODY				(0x3)
#define DCM_DTCGT_NETWORK			(0x4)
#define DCM_DTCGT_ALLGROUPS			(0x5)
#define DCM_DTCGT_EACHDTCS			(0x6)

/*
 * function Execution result value definition
 * */
#define DCM_E_OK					(0x00)
#define DCM_E_NOT_OK				(0x01)






#endif /* _DCM_TYPESTACK_H_ */