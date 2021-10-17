#include "stdafx.h"
#include <io.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <afxtempl.h>
#include <afxmt.h>
#include "common.h"
/////////////////////////////////////////////////////////////////////////////
// トレース
/////////////////////////////////////////////////////////////////////////////
/*static */void CCommon::Trace(const wchar_t *Format, ...)
{
	CString FmtBuff;

	va_list args;
	va_start(args, Format);

	::_vsntprintf(FmtBuff.GetBuffer(1024), 1024, Format, args);
	FmtBuff.ReleaseBuffer();
	::OutputDebugString(FmtBuff);

	va_end(args);
}
/////////////////////////////////////////////////////////////////////////////
// フォーマット
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::FmtStr(	// フォーマット文字
	const wchar_t *Format,				// フォーマット
	...)
{
	CString Str;

	va_list VarList;
	va_start(VarList, Format);
	::_vsntprintf(Str.GetBuffer(4096), 4096, Format, VarList);
	Str.ReleaseBuffer();
	va_end(VarList);

	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// リソース文字
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ResStr(
	int ID)					// ID
{
	CString Str;
	Str.LoadString(ID);
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// 大文字変換
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ToUpper(	// 変換後
	CString Str)						// 変換前
{
	Str.MakeUpper();
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// 小文字変換
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ToLower(	// 変換後
	CString Str)						// 変換前
{
	Str.MakeLower();
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// 文字置換
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ReplaceStr(		// 変換後
	CString Str,							// 変換前
	CString KeyNRep[][2],					// 置換キー & 置換文字
	int Num)								// 置換数
{
	CString DummyKey(char(-1) );// 無効文字
	int i;

	for (i = 0 ; Num > i ; i++)
	{
		// 置換キーを無効文字に置換
		// ※置換文字に置換キーがある場合を考慮
		Str.Replace(KeyNRep[i][0], DummyKey + char(i + 1) );
	}

	for (i = 0 ; Num > i ; i++)
	{
		// 置換
		Str.Replace(DummyKey + char(i + 1), KeyNRep[i][1]);
	}

	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// 設定ファイルディレクトリ変更
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ChgDirProfile(	// 設定ファイル名
	const wchar_t *ProfileName/* = 0*/,		// 設定ファイル名称(0の場合は自動)
	bool ExeDir/* = true*/)					// = true EXEファイルのディレクトリに変更, = false カレントディレクトリに変更
{
	CString IniFileName;

	if (ExeDir)
	{
		// 設定ファイルを実行ファイルのディレクトリに変更
		IniFileName = CCommon::GetModuleFileName();
		IniFileName = IniFileName.Left(IniFileName.ReverseFind('\\') + 1);
	}else
	{
		// 設定ファイルを実行時のディレクトリに変更
		::GetCurrentDirectory(1024, IniFileName.GetBuffer(1024) );
		IniFileName.ReleaseBuffer();
		if (IniFileName.GetLength() && '\\' != IniFileName.Right(1) ) IniFileName += '\\';
	}

	IniFileName += (ProfileName ? ProfileName : ::AfxGetApp()->m_pszProfileName);
	::free( (void *)::AfxGetApp()->m_pszProfileName);
	::AfxGetApp()->m_pszProfileName = ::_wcsdup(IniFileName);

	return IniFileName;
}
/////////////////////////////////////////////////////////////////////////////
// 実行ファイル名獲得
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::GetModuleFileName()
{
	CString ModuleFileName;
	::GetModuleFileName(::GetModuleHandle(0), ModuleFileName.GetBuffer(1024), 1024);
	ModuleFileName.ReleaseBuffer();
	return ModuleFileName;
}
/////////////////////////////////////////////////////////////////////////////
// バージョン獲得
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::GetVersion(		// バージョン文字（0.0.0.0形式）
	const wchar_t *FileName/* = 0*/)			// ファイル名（0の場合は自分）
{
	CString WkFileName;
	if (!FileName)
	{
		FileName = WkFileName = CCommon::GetModuleFileName();
	}

	// ファイルからバージョン情報獲得
	CByteArray FileVerSionInfo;
	{
		DWORD Dummy;
		DWORD Size;
		if (!(Size = ::GetFileVersionInfoSize(FileName, &Dummy) ) ) return "";

		FileVerSionInfo.SetSize(Size);
		if (!::GetFileVersionInfo( FileName, 0, FileVerSionInfo.GetSize(), FileVerSionInfo.GetData() ) ) return "";
	}

	// バージョン情報文字獲得
	CString VersionStr;
	{
		UINT Dummy;

		DWORD *Translation;
		if (!::VerQueryValue(FileVerSionInfo.GetData(), L"\\VarFileInfo\\Translation", (void **)&Translation, &Dummy) ) return "";

		char *Version;
		CString SubBlock;
		SubBlock.Format(L"\\StringFileInfo\\%04x%04x\\FileVersion", LOWORD(*Translation), HIWORD(*Translation) );
		if (!::VerQueryValue(FileVerSionInfo.GetData(), SubBlock, (void **)&Version, &Dummy) ) return "";

		VersionStr = Version;
		VersionStr.Replace(',', '.');
		VersionStr.Replace(L" ", L"");
	}

	return VersionStr;
}
/////////////////////////////////////////////////////////////////////////////
// ディレクトリ選択
/////////////////////////////////////////////////////////////////////////////
static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		// 初期フォルダ設定
		::SendMessage(hwnd, BFFM_SETSELECTION, true, lpData);
		break;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::SelectDirectory(	// 選択ディレクトリ
	HWND hWnd,									// ウインドウ
	bool OnlyLocal/* = false*/,					// ローカルのみ
	CString DefaltDir/* = ""*/,					// デフォルトディレクトリ
	CString Title/* = ""*/)						// タイトル
{
	CString DirName;
	{
		BROWSEINFO BrowseInfo;
		{
			::memset(&BrowseInfo, 0, sizeof(BrowseInfo) );
			BrowseInfo.hwndOwner = hWnd;
			BrowseInfo.lpszTitle = Title;
			BrowseInfo.ulFlags =
				BIF_RETURNONLYFSDIRS |	// ディレクトリのみ選択
				(OnlyLocal ? BIF_DONTGOBELOWDOMAIN : 0);// ネットワークなし
			BrowseInfo.lpfn = BrowseCallbackProc;
			BrowseInfo.lParam = (LPARAM)DefaltDir.GetString();
		}

		ITEMIDLIST *pItemIDList = ::SHBrowseForFolder(&BrowseInfo);
		if (pItemIDList)
		{
			::SHGetPathFromIDList(pItemIDList, DirName.GetBuffer(MAX_PATH) );
			DirName.ReleaseBuffer();
		}
	}

	return DirName;
}
/////////////////////////////////////////////////////////////////////////////
