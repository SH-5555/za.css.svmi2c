#pragma once


// Targetへの駆動クロックを指定します。
enum CKIN{
	Target_CKINClock_54 = 0,		//　CKIN 54MHz
	Target_CKINClock_48,			//　CKIN 48MHz
};

// Targetへの駆動クロックの分周率を指定します
enum CKINDiv{
	Target_CKINDivide_One = 0,		//　分周率　1
	Target_CKINDivide_Half,			//　分周率　1/2
	Target_CKINDivide_Quarter,		// 分周率　1/4
	Target_CKINDivide_OneEighth,	// 分周率　1/8
};

// TargetのDCK取込み特性を設定します(TCB_CIP_SYNC_SIG_POL_DCK)
enum TARGETDCKEdgeID{
	Target_DCK_HighEdge = 0,		//　DCK（ピクセルクロック）を立ち上がりでサンプリング
	Target_DCK_LowEdge,				//　DCK（ピクセルクロック）を立ち下がりでサンプリング
};

// TargetのHsync取込み特性を設定します(TCB_CIP_SYNC_SIG_POL_HS)
enum TARGETPolHSID{
	Target_HS_PolLow = 0,			//　Hsync（水平同期）をLowアクティブでサンプリング
	Target_HS_PolHigh,				//　Hsync（水平同期）をHighアクティブ期間でサンプリング
};

// TargetのVsync取込み特性を設定します(TCB_CIP_SYNC_SIG_POL_VS)
enum TARGETPolVSID{
	Target_VS_PolLow = 0,			//　Vsync（水平同期）をLowアクティブでサンプリング
	Target_VS_PolHigh,				//　Vsync（水平同期）をHighアクティブ期間でサンプリング
};


enum CompressMode{
	Compress_One_Div = 0,
	Compress_Half_Div,
};

enum ColorSpace{
	Color_Yuv = 0,
	Color_Rgb,
};


enum BT656Mode{
	BT656_Separate = 0,
	BT656_Embedded,
};

enum CSSwapMode{
	CSSwap_UYVY_BGRG = 0,
	CSSwap_YUYV_GBGR,
	CSSwap_VYUY_RGBG,
	CSSwap_YVYU_GRGB,
};

enum DIPSwitch{
	DIPSwitch_None = 0,
	DIPSwitch_1,
	DIPSwitch_2,
	DIPSwitch_3,
	DIPSwitch_4,
	DIPSwitch_5,
	DIPSwitch_6,
	DIPSwitch_7,
	DIPSwitch_8,
};

#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
enum EndianMode{
	Endian_D3D2D1D0 = 0,
	Endian_D2D3D0D1,
	Endian_D1D0D3D2,
	Endian_D0D1D2D3,
};
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加

// SPIRomに保存するときの識別ID
enum SVMSettingInfoID{
	CKIN = 0x10,			// CKIN Out Select
	CKINDiv,				// CKIN Out Divide
	CompressMode,			// 1/2 Compress Mode
	ColorSpace,				// Color Space Select
	DVIMode,				// DVI Mode
	Size,					// Size For HDMI
	Fps,					// Frame Rate For HDMI
	TestMode,				// Test Color Pattern Mode
	BT656Mode,				// ITU_BT656 Mode
	PolartyDE,				// DE Signal Setting
	PolartyDCKEdge,			// Polarity Of Pixel Clock Edge
	PolartyHSync,			// Polarity Of H-Sync and DE
	PolartyVSync,			// Polarity Of V-Sync
	clkMode,				// 8bit 2CLKs Mode
	CSSwapMode,				// CS Swap Mode
	EndianMode,				// Byte Endian Mode add 2015.04.17 V1.0.1.0

	DEEnabled,				// [16/02/10] DE signal enabled / disabled
	Decimation,				// [16/02/19] Decimation 1/1, 1/2, 1/3, 1/4
	HDMIRange,				// [16/04/11] HDMI Range: Limited/Full
};


// SVMSetting情報サイズ設定
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
#define SVMSETTING_INFOSIZE 10 * 2
#else
#define SVMSETTING_INFOSIZE 9 * 2
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加



// SVM設定ファイル用
#define INI_KEY_CKIN "CKINOutSelect"
#define DEFAULT_CKIN Target_CKINClock_54

#define INI_KEY_CKINDIV "CKINOutDivide"
#define DEFAULT_CKINDIV Target_CKINDivide_One

#define INI_KEY_COMPRESS "1/2CompressMode"
#define DEFAULT_COMPRESS Compress_One_Div

#define INI_KEY_COLOR "ColorSpaceSelect"
#define DEFAULT_COLOR Color_Yuv

#define INI_KEY_BT656 "ITU_BT656Mode"
#define DEFAULT_BT656 BT656_Separate

#define INI_KEY_EDGE "PolarityOfPixelClockEdge"
#define DEFAULT_EDGE Target_DCK_HighEdge

#define INI_KEY_HSYNC "PolarityOfH-SyncandDE"
#define DEFAULT_HSYNC Target_HS_PolLow

#define INI_KEY_VSYNC "PolarityOfV-Sync"
#define DEFAULT_VSYNC Target_VS_PolLow

#define INI_KEY_CSSWAP "CSSwapMode"
#define DEFAULT_CSSWAP CSSwap_UYVY_BGRG

#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
#define INI_KEY_ENDIAN "CSSwapMode"
#define DEFAULT_ENDIAN Endian_D0D1D2D3
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加


#define INI_KEY_WIDTH	"UVC_Width"
#define DEFAULT_WIDTH	1280
#define INI_KEY_HEIGHT	"UVC_Height"
#define DEFAULT_HEIGHT	720
#define INI_KEY_FPS		"UVC_FPS"
#define DEFAULT_FPS		"30"
#define INI_KEY_COLORGUID	"UVC_Color"
#define DEFAULT_COLORGUID	-1

class SVMSettingInfo
{
public:
	SVMSettingInfo(void);
	~SVMSettingInfo(void);

	SVMSettingInfo(const SVMSettingInfo &obj);

	BYTE GetCkinOutSelect(void);
	void SetCkinOutSelect(BYTE val);
	BYTE GetCkinOutDivide(void);
	void SetCkinOutDivide(BYTE val);
	BYTE GetColorSpaceSelect(void);
	void SetColorSpaceSelect(BYTE val);
	BYTE GetBT686Mode(void);
	void SetBT686Mode(BYTE val);
	BYTE GetDeSignalSetting(void);
	void SetDeSignalSetting(BYTE val);
	BYTE GetPolarityClockEdge(void);
	void SetPolarityClockEdge(BYTE val);
	BYTE GetPolarityHsync(void);
	void SetPolarityHsync(BYTE val);
	BYTE GetPolarityVsync(void);
	void SetPolarityVsync(BYTE val);
	BYTE GetCSSwapMode(void);
	void SetCSSwapMode(BYTE val);
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
	BYTE GetEndianMode(void);
	void SetEndianMode(BYTE val);
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加

	int GetUVCHeight(){
		return height;
	}
	void SetUVCHeight(int val){
		height = val;
	}

	int GetUVCWidth(){
		return width;
	}
	void SetUVCWidth(int val){
		width = val;
	}

	const CString& GetUVCFPS(){
		return fps;
	}
	void SetUVCFPS(const char* val){
		fps = val;
	}

	int GetUVCColorIdx(){
		return colorid;
	}
	void SetUVCColorIdx(int val){
		colorid = val;
	}

	int GetUVCDeviceID(){
		return deviceid;
	}
	void SetUVCDeviceID(int val){
		deviceid = val;
	}

	BOOL GetIniFilePath(void);
	BOOL GetIniFileData(void);
	BOOL SetIniFileData(void);

	int GetColorGUID(int idx, unsigned char* pGuid, char* name, int nameSize);

private:
	BYTE ckin;			///< @brief	CKIN Out Select
	BYTE ckinDiv;		///< @brief	CKIN Out Divide
	BYTE color;			///< @brief	Color Space Select
	BYTE bt656;			///< @brief	ITU BT.656 Mode(SAV/EAV)
	BYTE de;			///< @brief	DE Signal Setting
	BYTE edge;			///< @brief	Polarity of Pixel Clock Edge 
	BYTE hsync;			///< @brief	Polarity of H-Sync and DE
	BYTE vsync;			///< @brief	Polarity of V-Sync
	BYTE csSwap;		///< @brief	CS Swap Mode
#if 1 // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え
	BYTE csEndian;		///< @brief	Endian Mode
#endif // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え
	//iniファイル用
	TCHAR	AppPath[MAX_PATH];		///< @brief アプリケーションパス
	CString AppName;				///< @brief アプリケーション名
	CString IniFileFullPath;		///< @brief Iniファイルのフルパス

	int height, width, colorid;
	CString fps;
	int deviceid;
};
