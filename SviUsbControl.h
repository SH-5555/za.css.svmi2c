// SviUsbControl.h: CSviUsbControl �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_)
#define AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "SVI05API.h"

// [15/06/11] Avoid unsafe updating 
#define FPGA_SINGLE_AREA_SIZE (1024*512) // Bytes
#define FX3_SINGLE_AREA_SIZE (1024*512) // Bytes

using namespace std;

//SVIUSB2.0�h���C�o�ɑ΂��鑀������b�v���܂��B
class CSviUsbControl
{
public:
	bool close();
//	void SetSelBoardNo(int no);
//	ULONG ulSelBoardNo;
//	ULONG GetDeviceID(int no);
//	ULONG GetBoardNum();
	DWORD ScanBoard();
//	ULONG ulBoardNum;
//	ULONG ulBoardInfo[4];
	//�R���X�g���N�^
	CSviUsbControl();

	virtual ~CSviUsbControl();

	//SVI�h���C�o���I�[�v�����܂�
	bool open(void);

	//���������G���[�R�[�h���擾���܂��B�i�G���[�R�[�h�͏���������܂��B)
	DWORD getLastError(void);

	//�G���[�R�[�h�𕶎���ɕϊ����܂��B
	CString getLastErrorString(DWORD errorcode);

	//�J�������W�X�^�̐ݒ�(�T�u�A�h���X�w��L��)
	bool SetValue(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord);
	// �I�[�v���N���[�Y�͊O�ōs���ꍇ
	bool SetValue2(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord);

	//�J�������W�X�^�̎擾
	bool GetValue(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord, BOOL bRestart);
	// �I�[�v���N���[�Y�͊O�ōs���ꍇ
	bool GetValue2(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord, BOOL bRestart);
	// Read Access �̂�
	bool OneBlockRead(ULONG ulSlaveAdr, PUCHAR pRcvBuff, ULONG ulLen);

	// SPIROM�̒l���擾
	bool SetSVMSettingValue(ULONG ulLen, PUCHAR pRcvBuff);
	// SPIROM����l���擾
	bool GetSVMSettingValue(ULONG ulLen ,PUCHAR pRcvBuff);

	// SPIROM�ɂ���FX3�f�[�^���A�b�v�f�[�g
	bool SVMFx3Update(ULONG ulLen ,PUCHAR pRcvBuff);
	// FPGA��Update���s���܂�
	bool SVMFPGAUpdate(ULONG ulLen ,PUCHAR pRcvBuff);
	
	// [15/06/11
	bool SVMMultiUpdate(ULONG ulLen ,PUCHAR pRcvBuff);

	// SPIROM�ɂ���FX3�f�[�^���擾����
	bool SVMFX3BootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);
	// SPI�������ɂ���FPGA�̃u�[�g�p�f�[�^���擾���܂��B
	bool SVMFPGABootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);

	// [15/06/11]
	bool SVMMultiBootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);

	// FX3�̃o�[�W���������擾
	bool SVMVersionInfo(ULONG ulLen ,PUCHAR pRcvBuff);

	// [17/05/18] Write I2C Initialization Data
	bool WriteInitI2C(ULONG ulLen, PUCHAR pucSendBuf);

	// [17/05/18] Write I2C Initialization Data
	bool ReadInitI2C(ULONG ulLen, PUCHAR pucRcvBuf);
	bool CheckInitI2C();
		
	// [22/02/18] FPGA Register RW
	bool WriteFPGARegister(ULONG addr, ULONG value);
	bool ReadFPGARegister(ULONG addr, PULONG pValue);

private:

	// �P�u���b�N��M
	bool I2CBlockRead(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucRcvBuf, BOOL bWord);

	//�G���[�`�F�b�N�P�����iprivate)
	bool CSviUsbControl::checkLastError(void);

	//���^�[���R�[�h
	DWORD RC;

	// �P�u���b�N���M
	bool I2CBlockWrite(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucSendBuf, BOOL bWord);

	// SPIWrite�R�}���h���M
	bool SVMSettingWrite(ULONG ulLen, PUCHAR pucSendBuf);
	// SPIRead�R�}���h���M
	bool SVMSettingRead(ULONG ulLen, PUCHAR pucRcvBuf);

	// [15/09/02]
	int m_deviceIndex;
	// [18/07/31]
	int m_boardType;
public:
	void SetDeviceIndex(int index){
		m_deviceIndex = index;
	};
	void SetBoardType(int type){
		m_boardType = type;
	};
};

#endif // !defined(AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_)
