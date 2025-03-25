#pragma once

// [15/12/08] コンストラクタでのコピー禁止！
class CSettingDataManager
{
public:
	CSettingDataManager(void);
	~CSettingDataManager(void);

	void SetToDefault(void);

	int ReadFromSPIBuf(const UCHAR* pData, int dataSize);
	int SetToSPIBuf(UCHAR* pData, int dataSize);

	UCHAR* GetDataBuf(){
		return m_data;
	}
private:
	UCHAR m_data[512];

public:
	struct sConventionalData{
		sConventionalData(){
			ckin = 0;			
			ckinDiv = 0;		
			color = 0;			
			bt656 = 0;			
			deMode = 0;				
			edge = 0;			
			hsync = 0;			
			vsync = 0;		
			csSwap = 0;		
			csEndian = 3;	
			deEnabled = 0;
			decimation = 0;
			hdmiRange = 0;
		};
		BYTE ckin;			///< @brief	CKIN Out Select
		BYTE ckinDiv;		///< @brief	CKIN Out Divide
		BYTE color;			///< @brief	Color Space Select
		BYTE bt656;			///< @brief	ITU BT.656 Mode(SAV/EAV)
		BYTE deMode;		///< @brief	DE Signal Setting
		BYTE edge;			///< @brief	Polarity of Pixel Clock Edge 
		BYTE hsync;			///< @brief	Polarity of H-Sync and DE
		BYTE vsync;			///< @brief	Polarity of V-Sync
		BYTE csSwap;		///< @brief	CS Swap Mode
		BYTE csEndian;		///< @brief	Endian Mode
		BYTE deEnabled;

		BYTE decimation; // [16/02/19]
		BYTE hdmiRange; // [16/04/11]
	}m_conventionalData;

	struct sUVCData{
		sUVCData(){
			width = 1280;
			height = 720;
			colorid = 0;
			deviceid = 0;
			fps = "30";
		}
		int height, width, colorid;
		CString fps;
		int deviceid;
	}m_uvcData;

	struct sClippingData{
		sClippingData(){
			x0 = y0 = 0;
			width = height = 8191;
			enable = 0;
		}
		int x0;
		int width;
		int y0;
		int height;
		int enable;
	}m_clippingData;

	unsigned char m_svoData[256]; // VPO Register Custom Value
public:
	sConventionalData* GetConventionalData(){
		return &m_conventionalData;
	}
	sUVCData* GetUVCData(){
		return &m_uvcData;
	}
	sClippingData* GetClippingData(){
		return &m_clippingData;
	}
	int GetColorGUID(int idx, unsigned char* pGuid, char* name, int nameSize);
};
