#if !defined(AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_)
#define AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3d9.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////////////
//
namespace DuiLib{

/////////////////////////////////////////////////////////////////////////////////////
//
	typedef enum __ANIM_TEXTURE_TYPE	//������Դ��ʽ
	{
		TEXTURE_CAPTURE,				//�������Խ�ͼ
		TEXTURE_FILE					//���������ļ�
	}ANIM_TEXTURE_TYPE;

// 	typedef enum __INTERPOLATE_TYPE 	//��ֵ���㷽ʽ
// 	{
// 		INTERPOLATE_LINEAR, 			//���Բ�ֵ
// 		INTERPOLATE_COS,				//cos��ֵ
// 		INTERPOLATE_SIN					//sin��ֵ
// 	}INTERPOLATE_TYPE;

	typedef enum __ANIM_SPEED_TYPE  	// ���ٷ�ʽ
	{
		SPEED_LINEAR,					// ֱ��,����
		SPEED_PARABOLA,					// ������, �Ż�����(�Ż�Ч����̫����)
		SPEED_HYPERBOLA					// ˫����, �Ż�����(�Ż�Ч���Ƚ�����)
	}ANIM_SPEED_TYPE;

class UILIB_API CAnimJobUI
{
	friend class CAnimationSpooler;
private:
	static const RECT s_cEmptyRect;

	DWORD m_dwStartTick;     			//������ʼʱ��
	DWORD m_dwDuration;		 			//����ʱ��
	
	POINT m_ptStartCenter;				//������ʼ���ĵ�
	POINT m_ptXYtrans;					//��������ʼ��ƫ����
	float m_fStartZtrans;				//z��ƫ����,�൱�ڷŴ���С����,�ᱻ�����ֵ,��ʼ��
	float m_fEndZtrans;					//z��ƫ����,�൱�ڷŴ���С����,�ᱻ�����ֵ,��ֹ��

	COLORREF m_clrBack;					//������ʱԴ����ı�����ɫ
	int m_iAlpha;						//͸����
	
	float m_fRotateVecX;				//��ת��X����
	float m_fRotateVecY;				//��ת��Y����
	float m_fRotateVecZ;				//��ת��Z����
	float m_fRotateAngle;   			//��ת�Ƕ�,�Զ�Ϊ��λ

	ANIM_TEXTURE_TYPE m_eTexFormType;	//������Դ��ʽ
	RECT m_rcCaptureSrc;				//��ͼʱ������Դ����,TEXTURE_CAPTUREʱ��Ч
	CStdString m_strImgPath;			//�ļ��ṩ�������ļ�·��,TEXTURE_FILEʱ��Ч
	LPDIRECT3DTEXTURE9 m_pTexture;		//����
	HDC m_hMaskDC;
	HBITMAP m_hMaskBmp;
	HDC m_hDestDC;
	HBITMAP m_hDestBmp;
	bool m_bUseMaskBk;

	ANIM_SPEED_TYPE m_eSpeedType;		//���ٷ�ʽ
	bool m_bDrawBack;					//�ڱ������
	bool m_bCullFace;					//�Ƿ��޳�����,��Ӧ�������D3DRS_CULLMODE

	bool m_bBeforePaint;	 			//�Ƿ����ػ�֮ǰ��ȡ����
	bool m_bClip;			 			//�Ƿ�Գ�����Χ�Ķ������вü�
	RECT m_rcClip;			 			//�ü�����,����ֻ����������򲥷�,ֻ��m_bClipΪtrueʱ��Ч

	bool m_bIsCompleted;	 			//�ö�����ִ�����˻���ȡ����
	UINT m_uCallBackMsg;	 			//����ִ������ʹ���Ϣ,ֻ�д���WM_USER����Ϣ�Żᱻ����,lParam���س�ʼ���Ǵ����ֵ,wParam ��ʾ�Ƿ�ִ�����
	LPVOID m_pMsgCallBackData;			//��ʼ��ʱ�����ָ��
public:
	CAnimJobUI(const CAnimJobUI& src);
	CAnimJobUI(
		DWORD dwStartTick,
		DWORD dwDuration,
		POINT ptStartCenter,
		POINT ptXYtrans,
		float fStartZtrans = 1.0f,
		float fEndZtrans = 1.0f,
		bool bBeforePaint = false,
		bool bClip = false,
		RECT rcClip = s_cEmptyRect,
		RECT rcCaptureSrc = s_cEmptyRect,
 		UINT uCallBackMsg = WM_USER,
		LPVOID pMsgCallBackData = NULL);
	~CAnimJobUI();
public:
	void SetRotateInfo(float fRotateAngle,float fRotateVecX,float fRotateVecY,float fRotateVecZ);
	void SetBkColor(COLORREF clrBack);
	void SetAlpha(int iAlpha);
	void SetSpeedType(ANIM_SPEED_TYPE eSpeedType);
	void SetTextureFromFile(CStdString strImgPath);
	void SetDrawMode(bool bDrawBack,bool bCullFace);
	void SetUseMaskBk();
private:
	bool InitBkInfo(HWND hWnd);
	bool InitDestInfo(HDC hDC);
	bool AdjustTargetTexture(HWND hWnd);
};

class UILIB_API CAnimationSpooler
{
protected:
	struct CUSTOMVERTEX								   //�Զ��嶥�㻺������ʽ
	{
		FLOAT x, y, z;
		FLOAT rhw;
		DWORD color;
		FLOAT tu, tv;
	};
	typedef CUSTOMVERTEX CUSTOMVERTEXRECT[4];

	HWND m_hWnd;										//Ŀ�괰��
	bool m_bIsAnimating;								//�Ƿ����ڻ�����
	bool m_bIsInitialized;								//�Ƿ��ʼ��
	CStdPtrArray m_aJobs;								//���涯������
	D3DFORMAT m_clrFormat;
	LPDIRECT3D9 m_pD3D;									//D3D
	LPDIRECT3DDEVICE9 m_p3DDevice;						//D3D�豸
	LPDIRECT3DSURFACE9 m_p3DSurface;					//D3D����������
public:
	CAnimationSpooler();
	~CAnimationSpooler();

	bool Init(HWND hWnd);
	bool PrepareAnimation();
	bool Render();

	bool IsInitialized();
	bool IsAnimating() const;
	bool IsJobsEmpty() const;
	bool AddJob(CAnimJobUI* pJob);
	void RemoveJobs();
protected:

	COLORREF TranslateColor(LPDIRECT3DSURFACE9 pSurface, COLORREF clr) const;
	bool SetColorKey(LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DSURFACE9 pSurface, int iTexX,int iTexY,COLORREF clrColorKey);

	bool PrepareJob_Flat(CAnimJobUI* pJob);
	bool RenderJob_Flat(CAnimJobUI* pJob, LPDIRECT3DSURFACE9 pSurface, DWORD dwTick);

	bool MakeTexture(CAnimJobUI* pJob);
	bool CaptureSurface();

// 	double CAnimationSpooler::LinearInterpolate(double y1, double y2, double fPrecent);
// 	double CAnimationSpooler::CosineInterpolate(double y1, double y2, double fPrecent);
};
}
#endif // !defined(AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_)

