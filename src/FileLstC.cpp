// FileLstC.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Rename.h"
#include "FileLstC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
static int g_ColTitleID[CFileListCtrl::FL_MAX] =
{
	IDS_FILELISTCOL_NAME,
	IDS_FILELISTCOL_NEWNAME,
	IDS_FILELISTCOL_DATE,
	IDS_FILELISTCOL_SIZE,
	IDS_FILELISTCOL_TYPE
};
/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl

CFileListCtrl::CFileListCtrl() :
m_AddSubDir(false),
m_CnvTrimPos(0),
m_CnvTrimLen(0),
m_CnvCutPos(0),
m_CnvCutLen(0),
m_CnvCase(C_CASE_NONE),
m_ListSerialNo(0),
m_SortCol(0),
m_SortCnd(1)
{
}

CFileListCtrl::~CFileListCtrl()
{
}


BEGIN_MESSAGE_MAP(CFileListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFileListCtrl)
	ON_WM_DROPFILES()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl メッセージ ハンドラ
void CFileListCtrl::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

	CWaitCursor WaitCursor;
	
	int Max = ::DragQueryFile(hDropInfo, -1, 0, 0);

	for (int i = 0 ; Max > i ; i++)
	{
		CString FileName;
		::DragQueryFile(hDropInfo, i, FileName.GetBuffer(1024), 1024);
		FileName.ReleaseBuffer();

		CFileStatus FileStatus;
		CFile::GetStatus(FileName, FileStatus);

		if (CFile::directory & FileStatus.m_attribute)
		{
			AddDirFiles(FileName, false);
		}else
		{
			Add(FileName);
		}
	}

	::DragFinish(hDropInfo);

	Sort(m_SortCol, m_SortCnd);

	CListCtrl::OnDropFiles(hDropInfo);
}
/////////////////////////////////////////////////////////////////////////////
static int CALLBACK CompareFuncStr(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	void **SortParam = (void **)lParamSort;

	CMap<int , int, CFileListCtrl::CList, CFileListCtrl::CList&> &Lists =
		*(CMap<int, int, CFileListCtrl::CList, CFileListCtrl::CList&> *)SortParam[0];

	int Col = (int)SortParam[1];
	bool Asc = (0 < Col);
	Col = ::abs(Col) - 1;

	CString &Cmp1 = Lists[Asc ? lParam1 : lParam2].m_Item[Col];
	CString &Cmp2 = Lists[Asc ? lParam2 : lParam1].m_Item[Col];
	return Cmp1.CompareNoCase(Cmp2);
}
/////////////////////////////////////////////////////////////////////////////
static int CALLBACK CompareFuncVal(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	void **SortParam = (void **)lParamSort;

	CMap<int , int, CFileListCtrl::CList, CFileListCtrl::CList&> &Lists =
		*(CMap<int, int, CFileListCtrl::CList, CFileListCtrl::CList&> *)SortParam[0];

	int Col = (int)SortParam[1];
	bool Asc = (0 < Col);
	Col = ::abs(Col) - 1;

	CString &Cmp1 = Lists[Asc ? lParam1 : lParam2].m_Item[Col];
	CString &Cmp2 = Lists[Asc ? lParam2 : lParam1].m_Item[Col];
	return ::_wtoi(Cmp1) - ::_wtoi(Cmp2);
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	Sort(pNMListView->iSubItem, m_SortCol != pNMListView->iSubItem ? 1 : m_SortCnd * -1);
	
	*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVCUSTOMDRAW *pNmLvCustomDraw = (NMLVCUSTOMDRAW *)pNMHDR;

    switch(pNmLvCustomDraw->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	    // Request prepaint notifications for each item.
	    *pResult = CDRF_NOTIFYITEMDRAW;
	    break;

    case CDDS_ITEMPREPAINT: // Requested notification
		{
			int No = pNmLvCustomDraw->nmcd.dwItemSpec;
			int Idx = GetItemData(No);

			CString FileName = m_Lists[Idx].m_Item[FL_NAME];
			FileName = FileName.Mid(FileName.ReverseFind('\\') + 1);

			CString NewFileName = m_Lists[Idx].m_Item[FL_NEWNAME];

			if ("" != NewFileName && FileName != NewFileName)
			{
				pNmLvCustomDraw->clrText = RGB(86, 0, 255);
				pNmLvCustomDraw->clrTextBk = RGB(255, 255, 255);
			}else
			{
				pNmLvCustomDraw->clrText = RGB(0, 0, 0);
				pNmLvCustomDraw->clrTextBk = RGB(255, 255, 255);
			}
		}

	    *pResult = CDRF_DODEFAULT;
	    break;
	}
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::Init()
{
	// ドロップを許可
	DragAcceptFiles();

	// リストコントロールの設定
	SetExtendedStyle(
		LVS_EX_FULLROWSELECT		// １行選択
		/*| LVS_EX_GRIDLINES*/);	// グリッドライン

	// カラムタイトル
	InsertColumn(FL_NAME, CCommon::ResStr(g_ColTitleID[FL_NAME]), LVCFMT_LEFT, 200);
	InsertColumn(FL_NEWNAME, CCommon::ResStr(g_ColTitleID[FL_NEWNAME]), LVCFMT_LEFT, 150);
	InsertColumn(FL_DATE, CCommon::ResStr(g_ColTitleID[FL_DATE]), LVCFMT_LEFT, 130);
	InsertColumn(FL_SIZE, CCommon::ResStr(g_ColTitleID[FL_SIZE]), LVCFMT_RIGHT, 80);
	InsertColumn(FL_TYPE, CCommon::ResStr(g_ColTitleID[FL_TYPE]), LVCFMT_LEFT, 40);

	Sort(m_SortCol, m_SortCnd);
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::AddDirFiles(CString DirName, bool Sorting/* = ture*/)
{
	if (DirName.ReverseFind('\\') != DirName.GetLength() - 1) DirName += '\\';

	CFileFind FileFind;
	if (!FileFind.FindFile(DirName + "*.*") ) return;

	bool Next;
	do
	{
		Next = (false != FileFind.FindNextFile() );

		if (!FileFind.IsDirectory() )
		{
			Add(FileFind.GetFilePath() );
		}else
		if (m_AddSubDir && !FileFind.IsDots() )
		{
			AddDirFiles(FileFind.GetFilePath(), false);
		}
	}while (Next);

	if (Sorting) Sort(m_SortCol, m_SortCnd);
}
/////////////////////////////////////////////////////////////////////////////
bool CFileListCtrl::Add(CString FileName)
{
	// 拡張子チェック
	if ("" != m_AddExt)
	{
		CString AddExt = m_AddExt;
		if ('.' != AddExt[0]) AddExt = '.' + AddExt;

		if (AddExt.CompareNoCase(FileName.Right(min(AddExt.GetLength(), FileName.GetLength() ) ) ) )
		{
			return false;
		}
	}

	// 重複チェック
	void *Dummy;
	if (m_DupCheck.Lookup(FileName, Dummy) )
	{
		return false;
	}

	CFileStatus FileStatus;
	CFile::GetStatus(FileName, FileStatus);

	CString Ext;
	{
		int Pos = FileName.ReverseFind('.') + 1;
		if (0 < Pos && FileName.ReverseFind('\\') < Pos)
		{
			Ext = FileName.Mid(Pos);
		}
	}

	int Idx = GetItemCount();
	int No;
	if (0 > (No = InsertItem(Idx, L"" ) ) ) ::AfxThrowMemoryException();

	CList List;
	List.m_Item[FL_NAME] = FileName;
	List.m_Item[FL_DATE] = FileStatus.m_mtime.Format("%Y/%m/%d %H:%M:%S");
	List.m_Item[FL_SIZE] = CCommon::FmtStr(L"%u", FileStatus.m_size);
	List.m_Item[FL_TYPE] = Ext;

	SetItemText(No, FL_NAME, List.m_Item[FL_NAME]);
	SetItemText(No, FL_DATE, List.m_Item[FL_DATE]);
	SetItemText(No, FL_SIZE, CnvComma(List.m_Item[FL_SIZE]) );
	SetItemText(No, FL_TYPE, List.m_Item[FL_TYPE]);

	SetItemData(No, m_ListSerialNo);

	m_Lists[m_ListSerialNo] = List;
	m_ListSerialNo++;

	m_DupCheck[FileName] = 0;

	return true;
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::DelSel()
{
	for (POSITION Pos = GetFirstSelectedItemPosition() ; Pos ; Pos = GetFirstSelectedItemPosition() )
	{
		int No = GetNextSelectedItem(Pos);
		int Idx = GetItemData(No);

		DeleteItem(No);
		m_DupCheck.RemoveKey(m_Lists[Idx].m_Item[FL_NAME]);
		m_Lists.RemoveKey(Idx);
	}

	Rename();
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::DelAll()
{
	DeleteAllItems();
	m_Lists.RemoveAll();
	m_DupCheck.RemoveAll();
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::Rename()
{
	CWaitCursor WaitCursor;

	int Pos;

	int Max = GetItemCount();
	int NoWidth = CCommon::FmtStr(L"%d", Max).GetLength();

	for (int No = 0 ; Max > No ; No++)
	{
		int Idx = GetItemData(No);

		CString PathName = m_Lists[Idx].m_Item[FL_NAME];

		Pos = PathName.ReverseFind('\\');
		CString DirName = PathName.Left(Pos + 1);
		CString FileName = CnvFileNameFilter(PathName.Mid(Pos + 1) );

		Pos = FileName.ReverseFind('.');
		if (0 > Pos) Pos = FileName.GetLength();
		CString FileTitle = FileName.Left(Pos);
		CString FileExt = FileName.Mid(Pos);

		// 置換キー & 置換文字
		CString KeyNRep[][2] =
		{
			"%%", "%",		// ※必ず先頭
			"%f", FileName,
			"%t", FileTitle,
			"%e", FileExt,
			"%n", CCommon::FmtStr(L"%0*d", NoWidth, No)
		};
		int KeyNRepNum = sizeof(KeyNRep) / sizeof(KeyNRep[0]);

		// 文字置換
		CString NewFileName = CCommon::ReplaceStr(m_RenStr, KeyNRep, KeyNRepNum);
		NewFileName.Replace('\\','#');
		NewFileName.Replace('/', '#');
		NewFileName.Replace(':', '#');
		NewFileName.Replace(',', '#');
		NewFileName.Replace(';', '#');
		NewFileName.Replace('*', '#');
		NewFileName.Replace('?', '#');
		NewFileName.Replace('"', '#');
		NewFileName.Replace('<', '#');
		NewFileName.Replace('>', '#');
		NewFileName.Replace('|', '#');
	
		SetItemText(No, FL_NEWNAME, m_Lists[Idx].m_Item[FL_NEWNAME] = NewFileName);
	}

	Invalidate();
	UpdateWindow();
}
/////////////////////////////////////////////////////////////////////////////
void CFileListCtrl::Sort(int Col, int Cnd)
{
	CWaitCursor WaitCursor;

	LVCOLUMN LvColumn;
	CString WkText;

	if (m_SortCol != Col || m_SortCnd != Cnd)
	{
		// カラムタイトルに以前のソートマークをクリア
		::memset(&LvColumn, 0, sizeof(LvColumn) );
		WkText = CCommon::ResStr(g_ColTitleID[m_SortCol]);
		LvColumn.mask = LVCF_TEXT;
		LvColumn.pszText = (LPWSTR)WkText.GetString();
		LvColumn.cchTextMax = ::wcslen(LvColumn.pszText);
		SetColumn(m_SortCol, &LvColumn);
	}

	// カラムタイトルにソートマークを設定
	::memset(&LvColumn, 0, sizeof(LvColumn) );
	LvColumn.mask = LVCF_TEXT;
	CString ColTitle =
		CCommon::ResStr(g_ColTitleID[Col]) +
		' ' +
		CCommon::ResStr(0 < Cnd ? IDS_FILELISTSORT_ASC : IDS_FILELISTSORT_DESC); 
	LvColumn.pszText = (LPWSTR)ColTitle.GetString();
	LvColumn.cchTextMax = ::wcslen(LvColumn.pszText);
	SetColumn(Col, &LvColumn);

	m_SortCol = Col;
	m_SortCnd = Cnd;

	void *SortParam[] =
	{
		&m_Lists,
		(void *)(int(m_SortCol + 1) * m_SortCnd)
	};

	SortItems(
		FL_SIZE != m_SortCol ? CompareFuncStr : CompareFuncVal,
		(DWORD)SortParam);

	Rename();
}
/////////////////////////////////////////////////////////////////////////////
CString CFileListCtrl::CnvFileNameFilter(CString FileName)
{
	if (0 < m_CnvTrimLen)
	{
		int Pos = max(0, min(m_CnvTrimPos, FileName.GetLength() ) );
		int Len = min(m_CnvTrimLen, FileName.GetLength() - Pos);
		FileName = FileName.Mid(Pos, Len);
	}

	if (0 < m_CnvCutLen)
	{
		int Pos = max(0, min(m_CnvCutPos, FileName.GetLength() ) );
		int Len = min(m_CnvCutLen, FileName.GetLength() - Pos);
		FileName = FileName.Left(Pos) + FileName.Mid(Pos + Len);
	}

	if ("" != m_CnvRepBfr)
	{
		FileName.Replace(m_CnvRepBfr, m_CnvRepAft);
	}

	switch (m_CnvCase)
	{
	case C_CASE_NONE:
		break;
	case C_CASE_LOW:
		FileName.MakeLower();
		break;
	case C_CASE_UP:
		FileName.MakeUpper();
		break;
	}

	return FileName;
}
/////////////////////////////////////////////////////////////////////////////
CString CFileListCtrl::CnvComma(CString NumText)
{
	for (int i = NumText.GetLength() - 3 ; 0 < i ; i -= 3)
	{
		NumText = NumText.Left(i) + ',' + NumText.Mid(i);
	}

	return NumText;
}
/////////////////////////////////////////////////////////////////////////////
