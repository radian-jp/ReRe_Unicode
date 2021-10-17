#ifndef __COMMON_H__
#define __COMMON_H__
/////////////////////////////////////////////////////////////////////////////
class CCommon
{
public:
	// �g���[�X
	static void Trace(const wchar_t *Format, ...);

	// �t�H�[�}�b�g
	static CString FmtStr(		// �t�H�[�}�b�g����
		const wchar_t *Format,		// �t�H�[�}�b�g
		...);

	// ���\�[�X����
	static CString ResStr(
		int ID);				// ID

	// �啶���ϊ�
	static CString ToUpper(		// �ϊ���
		CString Str);			// �ϊ��O

	// �������ϊ�
	static CString ToLower(		// �ϊ���
		CString Str);			// �ϊ��O

	// �����u��
	static CString ReplaceStr(		// �ϊ���
		CString Str,				// �ϊ��O
		CString KeyNRep[][2],		// �u���L�[ & �u������
		int Num);					// �u����

	// �ݒ�t�@�C���f�B���N�g���ύX
	static CString ChgDirProfile(		// �ݒ�t�@�C����
		const wchar_t *ProfileName = 0,	// �ݒ�t�@�C������(0�̏ꍇ�͎���)
		bool ExeDir = true);			// = true EXE�t�@�C���̃f�B���N�g���ɕύX, = false �J�����g�f�B���N�g���ɕύX

	// �o�[�W�����l��
	static CString GetVersion(			// �o�[�W���������i0.0.0.0�`���j
		const wchar_t *FileName = 0);		// �t�@�C�����i0�̏ꍇ�͎����j

	// ���s�t�@�C�����l��
	static CString GetModuleFileName();

	// �f�B���N�g���I��
	static CString CCommon::SelectDirectory(	// �I���f�B���N�g��
		HWND hWnd,								// �E�C���h�E
		bool OnlyLocal = false,					// ���[�J���̂�
		CString DefaltDir = "",					// �f�t�H���g�f�B���N�g��
		CString Title = "");					// �^�C�g��
};
/////////////////////////////////////////////////////////////////////////////
#endif
