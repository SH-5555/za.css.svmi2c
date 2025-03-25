#ifndef INC_SVI05API
#define INC_SVI05API

#ifdef SVI05API_EXPORTS
#define SVI05API_API extern "C" __declspec(dllexport)
#else
#define SVI05API_API extern "C" __declspec(dllimport)
#endif

#ifdef SVI05API_EXPORTS
class __declspec(dllexport) CSVI05API {
public:
	CSVI05API(void);
};
#else
class __declspec(dllimport) CSVI05API {
public:
	CSVI05API(void);
};
#endif

// �T�|�[�g�E���C�u�����E�G���[�R�[�h��`
#define	SVI05API_RET_NORMAL				0x1
#define	SVI05API_RET_ERROR_DEVICE		0xe0000000
#define	SVI05API_RET_ERROR_DEVOPEN		0xf0000001
#define	SVI05API_RET_ERROR_MULTIOPEN	0xf0000002
#define	SVI05API_RET_ERROR_NOOPEN		0xf0000003
#define	SVI05API_RET_ERROR_PARAMETER	0xf0000004
#define	SVI05API_RET_ERROR_COM			0xf0000005
#define	SVI05API_RET_ERROR_NOIDLE		0xf0000006
#define	SVI05API_RET_ERROR_FMUPDATE_T	0xf0000007
#define	SVI05API_RET_ERROR_FPUPDATE_T	0xf0000008
#define	SVI05API_RET_ERROR_GSTS2_T		0xf0000009
#define	SVI05API_RET_ERROR_MDATA_T		0xf000000a
#define	SVI05API_RET_ERROR_SVI			0xf1000000

// SVI05API_GetStatus() �p�����[�^�p��`
#define SVI_STS_SUCCESS        0x0001  // ����I��
#define SVI_STS_FRAMEPENDING   0x0002  // ����I�� (�ۗ��t���[��/�f�[�^����)
#define SVI_STS_CAPCANCELED    0x0003  // ����I�� (�L���v�`�������~���ꂽ)
#define SVI_STS_BUSY           0x0011  // �r�W�[�ŃR�}���h�����s�ł��Ȃ�
#define SVI_STS_RECOVERYMODE   0x0012  // ���J�o���[���[�h�̂��߃R�}���h�����s�ł��Ȃ�
#define SVI_STS_I2CACTIVE      0x0013  // I2C�R���g���[���A�N�e�B�u
#define SVI_STS_CMD_INVALID    0x0101  // �R�}���h���s���ł���
#define SVI_STS_PRM_INVALID    0x0102  // �p�����[�^���s���ł���
#define SVI_STS_SEQ_INVALID    0x0103  // �p�P�b�g�̔��s�V�[�P���X���s���ł���
#define SVI_STS_CAM_POWER_OFF  0x0104  // �J�����d��OFF�ł���
#define SVI_STS_I2C_ACKTIMEOUT 0x0601  // I2C�ŃX���[�u�����ACK����M�ł����^�C���A�E�g����������
#define SVI_STS_I2C_PRETIMEOUT 0x0602  // I2C�Ńv���^�C���A�E�g����������
#define SVI_STS_I2C_POSTTIMEOUT 0x0603 // I2C�Ń|�X�g�^�C���A�E�g����������
#define SVI_STS_USB_ERROR      0x0C01  // USB�ʐM���ɃG���[����������
#define SVI_STS_UPDATE_INVALID 0x0E01  // ���W���[���f�[�^���s���ł���
#define SVI_STS_FROMERS_ERROR  0x0E02  // �t���b�V���������[�̏����Ɏ��s����
#define SVI_STS_FROMWT_ERROR   0x0E03  // �t���b�V���������[�̏������݂Ɏ��s����
#define SVI_STS_INTERNAL_ERROR 0x0F01  // �����G���[����������
#define SVI_STS_RESOURCE_ERROR 0x0F02  // �������\�[�X���s�����ď��������s�ł��Ȃ�

#define	SVI_STS_ERR_MASK			0xF00
#define	SVI05API_GETSTATUS_STS_OK	SVI_STS_SUCCESS

#define SVM_FPGAFW_ADRESS		0x0			// FPGA�u�[�g�f�[�^�i�[��A�h���X
#define SVM_FX3FW_ADRESS		0x100000	// Fx3�t�@�[���E�F�A�i�[��A�h���X

#define SVM_SETTINGINFO_ADRESS	0x1F0000	// SVMSetting���̊i�[��A�h���X
#define SVM_SPIMAX_ADRESS		0xFFFFFF	// SVMSetting���̊i�[��A�h���X

#if 1 // 2015.04.16 V1.0.1.0 SVM-03/SVM-03U���ݑΉ�
#define SVM03U_SETTINGINFO_ADRESS	0x1F0000	// SVM-03U:SVMSetting���̊i�[��A�h���X
#define SVM03U_FPGAFW_ADRESS		0x80000		// SVM-03U:FPGA�u�[�g�f�[�^�i�[��A�h���X
#define SVM03U_FX3FW_ADRESS			0x180000	// SVM-03U:Fx3�t�@�[���E�F�A�i�[��A�h���X
#endif // 2015.04.16 V1.0.1.0 SVM-03/SVM-03U���ݑΉ�

#define SVM_SSID_SPI			0xE7		// SSID-SPI-ROM�ւ̃A�N�Z�X���[�h�w��
#define SVM_SSID_EXTTARGET		0x00		// SSID-�O���^�[�Q�b�g�A�N�Z�X���[�h���w��
#define SVM_SSID_FPGA			0x99		// SSID��FPGA�A�N�Z�X���[�h�w��
#define SVM_SSID_UARTDEBUG		0xDB		// SSID��UART�f�o�b�N���[�h�w��
#define SVM_SSID_NOSSID			0x42		// SSID��SPI�p�P�b�g�ɕt�����Ȃ����[�h���w��

#define SVM_FX3CMD_I2CREAD		0x00		// FX3��I2CRead�̃R�}���h�𔭍s
#define SVM_FX3CMD_I2CWRITE		0x01		// FX3��I2CWrite�̃R�}���h�𔭍s
#define SVM_FX3CMD_I2C2BREAD	0x02		// FX3��I2C2ByteRead�̃R�}���h�𔭍s
#define SVM_FX3CMD_SPIREAD		0x03		// FX3��SPIRead�̃R�}���h�𔭍s
#define SVM_FX3CMD_SPIWRITE		0x04		// FX3��SPIWrite�̃R�}���h�𔭍s
#define SVM_FX3CMD_FWUPDAT		0x05		// SPIROM�ɂ���FX3�f�[�^���A�b�v�f�[�g
#define SVM_FX3CMD_FWUPDAT_CHECK 0x06		// SPIROM�ɂ���Update���擾
#define SVM_FX3CMD_FX3VERSIONINFO	0xF0	// FX3�̃o�[�W�������m�F

// SVI05API_Open() �p�����[�^�p��`
#define	SVI05API_APP_WHO_REC	1L
#define	SVI05API_APP_WHO_CTL	2L

SVI05API_API void  SVI05API_Init( void );
SVI05API_API DWORD SVI05API_Open(ULONG ulAppWho, int deviceIndex);
SVI05API_API DWORD SVI05API_OpenEx(ULONG ulAppWho, int deviceIndex, int boardIndex);
SVI05API_API DWORD SVI05API_I2CBlockWrite(ULONG ulSlaveAdr, ULONG ulSubdr, ULONG ulLen, PUCHAR pucSendBuf, BOOL bWord);
SVI05API_API DWORD SVI05API_I2CBlockRead(ULONG  ulSlaveAdr, ULONG ulSubdr, ULONG ulLen, PUCHAR	pucRcvBuf, BOOL bWord);

// [17/01/05]
SVI05API_API DWORD SVI05API_I2COneBlockWrite(ULONG ulSlaveAdr, ULONG ulLen, ULONG ulWriteMode, PUCHAR pucSendBuf);
SVI05API_API DWORD SVI05API_I2COneBlockRead(ULONG  ulSlaveAdr, ULONG ulLen, ULONG ulReadMode, PUCHAR pucRcvBuf);

SVI05API_API DWORD SVI05API_GetVersion( char *pcVerBuf );
SVI05API_API DWORD SVI05API_Close(ULONG ulAppWho);
SVI05API_API void  SVI05API_End( void );
SVI05API_API DWORD SVI05API_SPIRead (UCHAR ucCommdId, UCHAR ucSSId,ULONG ulAddress,ULONG ulLen,PUCHAR pucSendBuf);
SVI05API_API DWORD SVI05API_SPIWrite (UCHAR ucCommdId, UCHAR ucSSId,ULONG ulAddress,ULONG ulLen,PUCHAR pucSendBuf);
SVI05API_API DWORD SVI05API_SVMSettingRead (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMSettingWrite (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMVersionInfo (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMSPIBootMemUpdate (ULONG ulAddress, ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMFX3Update (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMFPGAUpdate (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMSPIBootMemRead (ULONG ulAddress, ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMFX3BootMemRead (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVMFPGABootMemRead (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SPIFpgaRead (UCHAR ucCommdId, UCHAR ucSSId,ULONG ulAddress,ULONG ulLen,PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SPIFpgaWrite (UCHAR ucCommdId, UCHAR ucSSId,ULONG ulAddress,ULONG ulLen,PUCHAR pucSendBuf);

#if 1 // 2015.04.16 V1.0.1.0 SVM-03/SVM-03U���ݑΉ�
SVI05API_API DWORD SVI05API_SVM03USettingRead (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVM03USettingWrite (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVM03UFX3Update (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVM03UFPGAUpdate (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVM03UFX3BootMemRead (ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_SVM03UFPGABootMemRead (ULONG ulLen, PUCHAR pucRcvBuf);
#endif // 2015.04.16 V1.0.1.0 SVM-03/SVM-03U���ݑΉ�

//SVI05API_API DWORD SVI05API_SettingRead (ULONG offset,  ULONG ulLen, PUCHAR pucRcvBuf);
//SVI05API_API DWORD SVI05API_SettingWrite (ULONG offset, ULONG ulLen, PUCHAR pucRcvBuf);
SVI05API_API DWORD SVI05API_Update (ULONG offset, ULONG ulLen, PUCHAR pucRcvBuf);

#endif
