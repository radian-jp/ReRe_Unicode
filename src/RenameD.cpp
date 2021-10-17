// RenameD.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "Rename.h"
#include "RenameD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
extern CRenameApp theApp;
/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Stc_Version;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_Stc_Version = _T("");
	//}}AFX_DATA_INIT
	m_Stc_Version = CCommon::GetVersion();// �o�[�W�����l��
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STC_VERSION, m_Stc_Version);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenameDlg �_�C�A���O

CRenameDlg::CRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRenameDlg)
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenameDlg)
	DDX_Control(pDX, IDC_SPN_CNVTRIMPOS, m_Spn_CnvTrimPos);
	DDX_Control(pDX, IDC_SPN_CNVTRIMLEN, m_Spn_CnvTrimLen);
	DDX_Control(pDX, IDC_SPN_CNVCUTPOS, m_Spn_CnvCutPos);
	DDX_Control(pDX, IDC_SPN_CNVCUTLEN, m_Spn_CnvCutLen);
	DDX_Control(pDX, IDC_EDT_CNVCUTLEN, m_Edt_CnvCutLen);
	DDX_Control(pDX, IDC_EDT_CNVCUTPOS, m_Edt_CnvCutPos);
	DDX_Control(pDX, IDC_LST_RENLIST, m_Lst_RenList);
	DDX_Control(pDX, IDC_EDT_RENSTR, m_Edt_RenStr);
	DDX_Control(pDX, IDC_EDT_CNVTRIMPOS, m_Edt_CnvTrimPos);
	DDX_Control(pDX, IDC_EDT_CNVTRIMLEN, m_Edt_CnvTrimLen);
	DDX_Control(pDX, IDC_EDT_CNVREPBFR, m_Edt_CnvRepBfr);
	DDX_Control(pDX, IDC_EDT_CNVREPAFT, m_Edt_CnvRepAft);
	DDX_Control(pDX, IDC_EDT_ADDEXT, m_Edt_AddExt);
	DDX_Control(pDX, IDC_CHK_ADDSUBDIR, m_Chk_AddSubDir);
	DDX_Control(pDX, IDC_LSC_FILE, m_Lsc_File);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRenameDlg, CDialog)
	//{{AFX_MSG_MAP(CRenameDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_DELSEL, OnBtnDelsel)
	ON_BN_CLICKED(IDC_BTN_ADDDIR, OnBtnAdddir)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSC_FILE, OnItemchangedLscFile)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_DELALL, OnBtnDelall)
	ON_BN_CLICKED(IDC_CHK_ADDSUBDIR, OnChkAddsubdir)
	ON_EN_CHANGE(IDC_EDT_ADDEXT, OnChangeEdtAddext)
	ON_EN_CHANGE(IDC_EDT_CNVREPAFT, OnChangeEdtCnvrepaft)
	ON_EN_CHANGE(IDC_EDT_CNVREPBFR, OnChangeEdtCnvrepbfr)
	ON_EN_CHANGE(IDC_EDT_CNVTRIMLEN, OnChangeEdtCnvtrimlen)
	ON_EN_CHANGE(IDC_EDT_CNVTRIMPOS, OnChangeEdtCnvtrimpos)
	ON_BN_CLICKED(IDC_RDO_CNVCASENONE, OnRdoCnvcasenone)
	ON_BN_CLICKED(IDC_RDO_CNVCASELOW, OnRdoCnvcaselow)
	ON_BN_CLICKED(IDC_RDO_CNVCASEUP, OnRdoCnvcaseup)
	ON_EN_CHANGE(IDC_EDT_RENSTR, OnChangeEdtRenstr)
	ON_LBN_SELCHANGE(IDC_LST_RENLIST, OnSelchangeLstRenlist)
	ON_EN_CHANGE(IDC_EDT_CNVCUTLEN, OnChangeEdtCnvcutlen)
	ON_EN_CHANGE(IDC_EDT_CNVCUTPOS, OnChangeEdtCnvcutpos)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenameDlg ���b�Z�[�W �n���h��

BOOL CRenameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	m_Spn_CnvTrimPos.SetRange(0, 999);
	m_Spn_CnvTrimLen.SetRange(0, 999);
	m_Spn_CnvCutPos.SetRange(0, 999);
	m_Spn_CnvCutLen.SetRange(0, 999);

	// �X�e�[�^�X�a�`�q�쐬
	m_StatusBar.Create(this);
	static UINT Indicators[] = { 0 };
	m_StatusBar.SetIndicators(Indicators, sizeof(Indicators) / sizeof(Indicators[0]) );

	m_Lsc_File.Init();

	m_Chk_AddSubDir.SetCheck(m_Lsc_File.m_AddSubDir);
	m_Edt_AddExt.SetWindowText(m_Lsc_File.m_AddExt);
	m_Edt_CnvTrimPos.SetWindowText(CCommon::FmtStr(L"%d", m_Lsc_File.m_CnvTrimPos) );
	m_Edt_CnvTrimLen.SetWindowText(CCommon::FmtStr(L"%d", m_Lsc_File.m_CnvTrimLen) );
	m_Edt_CnvCutPos.SetWindowText(CCommon::FmtStr(L"%d", m_Lsc_File.m_CnvCutPos) );
	m_Edt_CnvCutLen.SetWindowText(CCommon::FmtStr(L"%d", m_Lsc_File.m_CnvCutLen) );
	m_Edt_CnvRepBfr.SetWindowText(m_Lsc_File.m_CnvRepBfr);
	m_Edt_CnvRepAft.SetWindowText(m_Lsc_File.m_CnvRepAft);

	( (CButton *)GetDlgItem(
		CFileListCtrl::C_CASE_NONE == m_Lsc_File.m_CnvCase ?
			IDC_RDO_CNVCASENONE :
		CFileListCtrl::C_CASE_LOW == m_Lsc_File.m_CnvCase ?
			IDC_RDO_CNVCASELOW :
		CFileListCtrl::C_CASE_UP == m_Lsc_File.m_CnvCase ?
			IDC_RDO_CNVCASEUP :
			IDC_RDO_CNVCASENONE) )->SetCheck(1);

	// ���l�[���ݒ��ݒ�
	{
		for (int i = 0 ; ; i++)
		{
			CString RenStr = theApp.GetProfileString(L"Option", CCommon::FmtStr(L"RenStr%d", i), L"");
			if ("" == RenStr) break;

			int No = m_Lst_RenList.AddString(RenStr.Mid(RenStr.Find(':') + 1) );

			// �R�����g���J�b�g
			int Pos = RenStr.Find(':');
			if (0 <= Pos) RenStr = RenStr.Left(Pos);
			RenStr.TrimLeft();
			RenStr.TrimRight();
			RenStr.Replace(L"\t", L"");

			m_RenList.SetAtGrow(No, RenStr);

			m_Lst_RenList.SetItemData(No, No);
		}
	}

	LoadWindowPlacement(this, "Main");

	ReSize();

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CRenameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CRenameDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CRenameDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
	CDialog::OnCancel();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	ReSize();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnClose() 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	SaveWindowPlacement(this, "Main");
	
	CDialog::OnClose();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnBtnStart() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������

	CWaitCursor WaitCursor;

	m_StatusBar.SetWindowText(L"");

	int Max = m_Lsc_File.GetItemCount();

	if ("" == m_Lsc_File.m_RenStr) return;

	// ���l�[���`�F�b�N
	{
		CMapStringToPtr DupCheck;

		for (int No = 0 ; Max > No ; No++)
		{
			int Idx = m_Lsc_File.GetItemData(No);

			CString FileName = m_Lsc_File.m_Lists[Idx].m_Item[CFileListCtrl::FL_NAME];

			CString NewFileName = m_Lsc_File.m_Lists[Idx].m_Item[CFileListCtrl::FL_NEWNAME];
			NewFileName = FileName.Left(FileName.ReverseFind('\\') + 1) + NewFileName;

			if (FileName != NewFileName)
			{
				if (_waccess(FileName, 0) )
				{
					::AfxMessageBox(CCommon::FmtStr(CCommon::ResStr(IDS_FILENOTFOUND), FileName) );
					return;
				}

				if (!_waccess(NewFileName, 0) &&
					FileName.CompareNoCase(NewFileName) )
				{
					::AfxMessageBox(CCommon::FmtStr(CCommon::ResStr(IDS_FILEEXIST), NewFileName) );
					return;
				}

				void *Dummy;
				if (DupCheck.Lookup(NewFileName, Dummy) )
				{
					::AfxMessageBox(CCommon::FmtStr(CCommon::ResStr(IDS_FILEDUPLICATE), NewFileName) );
					return;
				}
			}

			DupCheck[NewFileName] = 0;
		}
	}

	// ���l�[��
	m_SrcRenameFiles.RemoveAll();
	m_DstRenameFiles.RemoveAll();
	{
		for (int No = 0 ; Max > No ; No++)
		{
			int Idx = m_Lsc_File.GetItemData(No);

			CString FileName = m_Lsc_File.m_Lists[Idx].m_Item[CFileListCtrl::FL_NAME];

			CString NewFileName = m_Lsc_File.m_Lists[Idx].m_Item[CFileListCtrl::FL_NEWNAME];
			NewFileName = FileName.Left(FileName.ReverseFind('\\') + 1) + NewFileName;

			if (FileName != NewFileName)
			{
				CFile::Rename(FileName, NewFileName);
			}

			m_SrcRenameFiles.Add(FileName);
			m_DstRenameFiles.Add(NewFileName);
		}

	}

	// �t�@�C�������Đݒ�
	{
		m_Lsc_File.DelAll();
		for (int i = 0 ; m_DstRenameFiles.GetSize() > i ; i++)
		{
			m_Lsc_File.Add(m_DstRenameFiles[i]);
		}
		m_Lsc_File.Rename();
	}

	m_StatusBar.SetWindowText(CCommon::ResStr(IDS_RENAMECOMPLETE) );
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnBtnUndo() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if (0 >= m_SrcRenameFiles.GetSize() ) return;

	CWaitCursor WaitCursor;

	m_StatusBar.SetWindowText(L"");

	// ���l�[��
	{
		for (int i = 0 ; m_SrcRenameFiles.GetSize() > i ; i++)
		{
			if (m_DstRenameFiles[i] != m_SrcRenameFiles[i])
			{
				CFile::Rename(m_DstRenameFiles[i], m_SrcRenameFiles[i]);
			}
		}
	}

	// �t�@�C�������Đݒ�
	{
		m_Lsc_File.DelAll();
		for (int i = 0 ; m_SrcRenameFiles.GetSize() > i ; i++)
		{
			m_Lsc_File.Add(m_SrcRenameFiles[i]);
		}
		m_Lsc_File.Rename();
	}
	
	m_SrcRenameFiles.RemoveAll();
	m_DstRenameFiles.RemoveAll();

	m_StatusBar.SetWindowText(CCommon::ResStr(IDS_RENAMECOMPLETE) );
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnBtnAdddir() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	static CString DefaultDirName;

	CString DirName = CCommon::SelectDirectory(*this, false, DefaultDirName);
	if ("" == DirName) return;
	DefaultDirName = DirName;

	CWaitCursor WaitCursor;

	m_Lsc_File.AddDirFiles(DirName);
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnBtnDelsel() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Lsc_File.DelSel();

	UpdateStatusBar();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnBtnDelall() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Lsc_File.DelAll();

	UpdateStatusBar();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnSelchangeLstRenlist() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	int No = m_Lst_RenList.GetCurSel();
	int Idx = m_Lst_RenList.GetItemData(No);

	m_Lsc_File.m_RenStr = m_RenList[Idx];

	m_Edt_RenStr.SetWindowText(m_Lsc_File.m_RenStr);
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtRenstr() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Edt_RenStr.GetWindowText(m_Lsc_File.m_RenStr);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvtrimpos() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if (!::IsWindow(m_Edt_CnvTrimPos) ) return;

	CString WkText;
	m_Edt_CnvTrimPos.GetWindowText(WkText);
	m_Lsc_File.m_CnvTrimPos = ::_wtoi(WkText);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvtrimlen() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if (!::IsWindow(m_Edt_CnvTrimLen) ) return;

	CString WkText;
	m_Edt_CnvTrimLen.GetWindowText(WkText);
	m_Lsc_File.m_CnvTrimLen = ::_wtoi(WkText);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvcutpos() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if (!::IsWindow(m_Edt_CnvCutPos) ) return;

	CString WkText;
	m_Edt_CnvCutPos.GetWindowText(WkText);
	m_Lsc_File.m_CnvCutPos = ::_wtoi(WkText);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvcutlen() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if (!::IsWindow(m_Edt_CnvCutLen) ) return;

	CString WkText;
	m_Edt_CnvCutLen.GetWindowText(WkText);
	m_Lsc_File.m_CnvCutLen = ::_wtoi(WkText);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvrepbfr() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Edt_CnvRepBfr.GetWindowText(m_Lsc_File.m_CnvRepBfr);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtCnvrepaft() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Edt_CnvRepAft.GetWindowText(m_Lsc_File.m_CnvRepAft);

	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnRdoCnvcasenone() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Lsc_File.m_CnvCase =
		1 == ( (CButton *)GetDlgItem(IDC_RDO_CNVCASENONE) )->GetCheck() ?
			CFileListCtrl::C_CASE_NONE :
		1 == ( (CButton *)GetDlgItem(IDC_RDO_CNVCASELOW) )->GetCheck() ?
			CFileListCtrl::C_CASE_LOW :
		1 == ( (CButton *)GetDlgItem(IDC_RDO_CNVCASEUP) )->GetCheck() ?
			CFileListCtrl::C_CASE_UP :
			CFileListCtrl::C_CASE_NONE;
	
	m_Lsc_File.Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnRdoCnvcaselow() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnRdoCnvcasenone();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnRdoCnvcaseup() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnRdoCnvcasenone();
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChkAddsubdir() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Lsc_File.m_AddSubDir = (1 == m_Chk_AddSubDir.GetCheck() );
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnChangeEdtAddext() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_Edt_AddExt.GetWindowText(m_Lsc_File.m_AddExt);
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::OnItemchangedLscFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateStatusBar();
	
	*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::ReSize()
{
	// �R���g���[�� �o�[�̍Ĕz�u
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	CRect CltRect;
	GetClientRect(CltRect);

	if (::IsWindow(m_StatusBar) )
	{
		CRect Rect;
		m_StatusBar.GetWindowRect(Rect);
		CltRect.bottom = max(CltRect.bottom - Rect.Height(), CltRect.top);
	}

	if (::IsWindow(m_Lsc_File) )
	{
		CRect Rect;
		m_Lsc_File.GetWindowRect(Rect);
		ScreenToClient(Rect);
		m_Lsc_File.MoveWindow(CRect(Rect.left, Rect.top, CltRect.right, CltRect.bottom) );
	}
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::UpdateStatusBar()
{
	m_StatusBar.SetWindowText(
		CCommon::FmtStr(CCommon::ResStr(IDS_STATUSMESSAGE), m_Lsc_File.GetItemCount(), m_Lsc_File.GetSelectedCount() ) );
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::SaveWindowPlacement(CWnd *pWnd, CString IniTitle)
{
	WINDOWPLACEMENT WindowPlacement;
	pWnd->GetWindowPlacement(&WindowPlacement);
	theApp.WriteProfileInt(L"Status", IniTitle + "_showCmd", WindowPlacement.showCmd);
	theApp.WriteProfileInt(L"Status", IniTitle + "_MinPosition_x", WindowPlacement.ptMinPosition.x);
	theApp.WriteProfileInt(L"Status", IniTitle + "_MinPosition_y", WindowPlacement.ptMinPosition.y);
	theApp.WriteProfileInt(L"Status", IniTitle + "_MaxPosition_x", WindowPlacement.ptMaxPosition.x);
	theApp.WriteProfileInt(L"Status", IniTitle + "_MaxPosition_y", WindowPlacement.ptMaxPosition.y);
	theApp.WriteProfileInt(L"Status", IniTitle + "_NormalPosition_left", WindowPlacement.rcNormalPosition.left);
	theApp.WriteProfileInt(L"Status", IniTitle + "_NormalPosition_top", WindowPlacement.rcNormalPosition.top);
	theApp.WriteProfileInt(L"Status", IniTitle + "_NormalPosition_right", WindowPlacement.rcNormalPosition.right);
	theApp.WriteProfileInt(L"Status", IniTitle + "_NormalPosition_bottom", WindowPlacement.rcNormalPosition.bottom);
}
/////////////////////////////////////////////////////////////////////////////
void CRenameDlg::LoadWindowPlacement(CWnd *pWnd, CString IniTitle)
{
	CRect DefaultRect;
	pWnd->GetWindowRect(DefaultRect);
	WINDOWPLACEMENT WindowPlacement;
	WindowPlacement.length = sizeof(WindowPlacement);
	WindowPlacement.flags = 0;
	WindowPlacement.showCmd =					theApp.GetProfileInt(L"Status", IniTitle + L"_showCmd", SW_SHOW);
	WindowPlacement.ptMinPosition.x =			theApp.GetProfileInt(L"Status", IniTitle + L"_MinPosition_x", -1);
	WindowPlacement.ptMinPosition.y =			theApp.GetProfileInt(L"Status", IniTitle + L"_MinPosition_y", -1);
	WindowPlacement.ptMaxPosition.x =			theApp.GetProfileInt(L"Status", IniTitle + L"_MaxPosition_x", -1);
	WindowPlacement.ptMaxPosition.y =			theApp.GetProfileInt(L"Status", IniTitle + L"_MaxPosition_y", -1);
	WindowPlacement.rcNormalPosition.left =		theApp.GetProfileInt(L"Status", IniTitle + L"_NormalPosition_left", DefaultRect.left);
	WindowPlacement.rcNormalPosition.top =		theApp.GetProfileInt(L"Status", IniTitle + L"_NormalPosition_top", DefaultRect.top);
	WindowPlacement.rcNormalPosition.right =	theApp.GetProfileInt(L"Status", IniTitle + L"_NormalPosition_right", DefaultRect.right);
	WindowPlacement.rcNormalPosition.bottom =	theApp.GetProfileInt(L"Status", IniTitle + L"_NormalPosition_bottom", DefaultRect.bottom);
	pWnd->SetWindowPlacement(&WindowPlacement);											   
}
/////////////////////////////////////////////////////////////////////////////










