
// rf4sd-mfcdlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "rf4sd-mfcdlg.h"
#include "rf4sd-mfcdlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Crf4sdmfcdlgDlg �Ի���




Crf4sdmfcdlgDlg::Crf4sdmfcdlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Crf4sdmfcdlgDlg::IDD, pParent)
	, m_filePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Crf4sdmfcdlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_fileNameList);
	DDX_Text(pDX, IDC_EDIT1, m_filePath);
}

BEGIN_MESSAGE_MAP(Crf4sdmfcdlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Crf4sdmfcdlgDlg::OnBnClickedChooseFilePath)
	ON_BN_CLICKED(IDC_BUTTON2, &Crf4sdmfcdlgDlg::OnBnClickedRecoverFileName)
END_MESSAGE_MAP()


// Crf4sdmfcdlgDlg ��Ϣ�������
//��ȡӦ�ó�������·��
CString Crf4sdmfcdlgDlg::GetExePath()
{
	CString m_FilePath;
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_FilePath.ReleaseBuffer();
	int m_iPosIndex;
	m_iPosIndex = m_FilePath.ReverseFind('\\');
	m_FilePath = m_FilePath.Left(m_iPosIndex);
	return m_FilePath;
}

BOOL Crf4sdmfcdlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//RecoverFileName4SkyDrive();
	m_filePath = GetExePath();
	m_filePath += '\\';
	UpdateData( FALSE );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

CString * Crf4sdmfcdlgDlg::SplitString(CString str, char split, int& iSubStrs)
{
	int iPos = 0; //�ָ��λ��
	int iNums = 0; //�ָ��������
	CString strTemp = str;
	CString strRight;
	//�ȼ������ַ���������
	while (iPos != -1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos + 1, str.GetLength());
		strTemp = strRight;
		iNums++;
	}
	if (iNums == 0) //û���ҵ��ָ��
	{
		//���ַ����������ַ�������
		iSubStrs = 1; 
		return NULL;
	}
	//���ַ�������
	iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//���Ӵ�
		strLeft = strTemp.Left(iPos);
		//���Ӵ�
		strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}

void Crf4sdmfcdlgDlg::Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)  
{  
	int len=lstrlen(strIn);  
	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);  
	wchar_t* pUnicode;  
	pUnicode=new wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);  
	BYTE * pTargetData = NULL;  
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);  
	pTargetData=new BYTE[targetLen+1];  
	memset(pTargetData,0,targetLen+1);  
	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);  
	lstrcpy(strOut,(char*)pTargetData);  
	delete pUnicode;  
	delete pTargetData;  
}  

void Crf4sdmfcdlgDlg::RecoverFileName4SkyDrive()
{
	CString folderPath( m_filePath ); 

	CFile fileInput;
	CString fileListName = folderPath + "Encoding Errors.txt" ;
	fileInput.Open( fileListName, CFile::modeRead | CFile::typeText );
	int nSizeFile = fileInput.GetLength();

	const int nSize = 10240;
	char pbuf[nSize];
	UINT nBytesRead = fileInput.Read( pbuf, nSize );
	pbuf[nSizeFile] = '\0' ;

	char pbufANSI[nSize];
	Convert( pbuf, pbufANSI, CP_UTF8, CP_ACP );

	CString nameList( pbufANSI );
#if 1
	// ����ǰ3��
	int nLineSkip = 3;
	int nPos =0;
	while(nLineSkip--)
	{
		nPos = nameList.Find( '\n', 0);
		nameList = nameList.Mid( nPos+1, nameList.GetLength() );
	}
#else
	nameList = nameList.Mid( 1, nameList.GetLength() );
#endif
	nameList.Replace("\r\r\n", " ");

	int nNameCount = 0;
	CString* pNameListSplit = SplitString( nameList, ' ', nNameCount );

	for ( int i=0;i<nNameCount; i++ )
	{
		m_fileNameList.AddString( pNameListSplit[i] );
	}

	for ( int i=0;i<nNameCount; i+=3 )
	{
		if( pNameListSplit[i].IsEmpty() )
			continue;
		
		CString newFileName = folderPath + pNameListSplit[i] ;

		CString oldFileName = folderPath + pNameListSplit[i+2];

		if ( newFileName.GetAt(0) != ' ' && oldFileName.GetAt(0) != ' ' )
		{
			BOOL bResult = MoveFileEx( oldFileName, newFileName, MOVEFILE_COPY_ALLOWED );
			if (bResult==0)
			{
				int nError = GetLastError();
				bResult = nError ;
			}
		}
	}

	delete[] pNameListSplit;

	fileInput.Close();

	DeleteFile( fileListName );
}

void Crf4sdmfcdlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Crf4sdmfcdlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Crf4sdmfcdlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Crf4sdmfcdlgDlg::OnBnClickedChooseFilePath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	BROWSEINFO stInfo = {NULL};
	LPCITEMIDLIST pIdlst;
	TCHAR szPath[MAX_PATH];
	stInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	stInfo.lpszTitle= "��ѡ��·��:";
	pIdlst = SHBrowseForFolder(&stInfo);
	if(!pIdlst) return ;
	if(!SHGetPathFromIDList(pIdlst, szPath)) return;

	m_filePath = szPath;
	m_filePath += '\\';
	UpdateData( FALSE );
}


void Crf4sdmfcdlgDlg::OnBnClickedRecoverFileName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );
	m_filePath += '\\';

	RecoverFileName4SkyDrive();

}
