
// rf4sd-mfcdlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Crf4sdmfcdlgApp:
// �йش����ʵ�֣������ rf4sd-mfcdlg.cpp
//

class Crf4sdmfcdlgApp : public CWinApp
{
public:
	Crf4sdmfcdlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Crf4sdmfcdlgApp theApp;