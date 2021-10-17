#include "stdafx.h"
#include <io.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <afxtempl.h>
#include <afxmt.h>
#include "common.h"
/////////////////////////////////////////////////////////////////////////////
// �g���[�X
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
// �t�H�[�}�b�g
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::FmtStr(	// �t�H�[�}�b�g����
	const wchar_t *Format,				// �t�H�[�}�b�g
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
// ���\�[�X����
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ResStr(
	int ID)					// ID
{
	CString Str;
	Str.LoadString(ID);
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// �啶���ϊ�
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ToUpper(	// �ϊ���
	CString Str)						// �ϊ��O
{
	Str.MakeUpper();
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// �������ϊ�
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ToLower(	// �ϊ���
	CString Str)						// �ϊ��O
{
	Str.MakeLower();
	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// �����u��
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ReplaceStr(		// �ϊ���
	CString Str,							// �ϊ��O
	CString KeyNRep[][2],					// �u���L�[ & �u������
	int Num)								// �u����
{
	CString DummyKey(char(-1) );// ��������
	int i;

	for (i = 0 ; Num > i ; i++)
	{
		// �u���L�[�𖳌������ɒu��
		// ���u�������ɒu���L�[������ꍇ���l��
		Str.Replace(KeyNRep[i][0], DummyKey + char(i + 1) );
	}

	for (i = 0 ; Num > i ; i++)
	{
		// �u��
		Str.Replace(DummyKey + char(i + 1), KeyNRep[i][1]);
	}

	return Str;
}
/////////////////////////////////////////////////////////////////////////////
// �ݒ�t�@�C���f�B���N�g���ύX
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::ChgDirProfile(	// �ݒ�t�@�C����
	const wchar_t *ProfileName/* = 0*/,		// �ݒ�t�@�C������(0�̏ꍇ�͎���)
	bool ExeDir/* = true*/)					// = true EXE�t�@�C���̃f�B���N�g���ɕύX, = false �J�����g�f�B���N�g���ɕύX
{
	CString IniFileName;

	if (ExeDir)
	{
		// �ݒ�t�@�C�������s�t�@�C���̃f�B���N�g���ɕύX
		IniFileName = CCommon::GetModuleFileName();
		IniFileName = IniFileName.Left(IniFileName.ReverseFind('\\') + 1);
	}else
	{
		// �ݒ�t�@�C�������s���̃f�B���N�g���ɕύX
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
// ���s�t�@�C�����l��
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::GetModuleFileName()
{
	CString ModuleFileName;
	::GetModuleFileName(::GetModuleHandle(0), ModuleFileName.GetBuffer(1024), 1024);
	ModuleFileName.ReleaseBuffer();
	return ModuleFileName;
}
/////////////////////////////////////////////////////////////////////////////
// �o�[�W�����l��
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::GetVersion(		// �o�[�W���������i0.0.0.0�`���j
	const wchar_t *FileName/* = 0*/)			// �t�@�C�����i0�̏ꍇ�͎����j
{
	CString WkFileName;
	if (!FileName)
	{
		FileName = WkFileName = CCommon::GetModuleFileName();
	}

	// �t�@�C������o�[�W�������l��
	CByteArray FileVerSionInfo;
	{
		DWORD Dummy;
		DWORD Size;
		if (!(Size = ::GetFileVersionInfoSize(FileName, &Dummy) ) ) return "";

		FileVerSionInfo.SetSize(Size);
		if (!::GetFileVersionInfo( FileName, 0, FileVerSionInfo.GetSize(), FileVerSionInfo.GetData() ) ) return "";
	}

	// �o�[�W������񕶎��l��
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
// �f�B���N�g���I��
/////////////////////////////////////////////////////////////////////////////
static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		// �����t�H���_�ݒ�
		::SendMessage(hwnd, BFFM_SETSELECTION, true, lpData);
		break;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
/*static */CString CCommon::SelectDirectory(	// �I���f�B���N�g��
	HWND hWnd,									// �E�C���h�E
	bool OnlyLocal/* = false*/,					// ���[�J���̂�
	CString DefaltDir/* = ""*/,					// �f�t�H���g�f�B���N�g��
	CString Title/* = ""*/)						// �^�C�g��
{
	CString DirName;
	{
		BROWSEINFO BrowseInfo;
		{
			::memset(&BrowseInfo, 0, sizeof(BrowseInfo) );
			BrowseInfo.hwndOwner = hWnd;
			BrowseInfo.lpszTitle = Title;
			BrowseInfo.ulFlags =
				BIF_RETURNONLYFSDIRS |	// �f�B���N�g���̂ݑI��
				(OnlyLocal ? BIF_DONTGOBELOWDOMAIN : 0);// �l�b�g���[�N�Ȃ�
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
