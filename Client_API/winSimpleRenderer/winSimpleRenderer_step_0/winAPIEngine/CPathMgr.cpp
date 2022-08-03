#include "CPathMgr.h"
#include "framework.h"



SINGLETON_DEFINITION(CPathMgr)

CPathMgr::CPathMgr()
{
	mPaths.clear();
}

CPathMgr::~CPathMgr()
{
	mPaths.clear();
}

bool CPathMgr::Create()
{
	//���� ������ �ִ� ��η� ��ڴ�
	//(���� ���������� �������� ���丮(����)�� ������ ��ü��θ� ��´�)

	wchar_t tStrPath[MAX_PATH] = { 0 };

	GetModuleFileName(nullptr, tStrPath, MAX_PATH);

	/*WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);*/


	int tCount = lstrlen(tStrPath); // ���ڿ��� ���̸� ���Ѵ�
	for (int ti = tCount - 1; ti >= 0; --ti)
	{
		// "/" �������� ���� ������
		// "\\" �����쿡���� ����������
		if ('/' == tStrPath[ti] || '\\' == tStrPath[ti])
		{
			//���� �̶�� �����ϰ� ���캸��
			//				c"\ryu\t.exe
			//
			//������ �Ѱ����� 12��
			// ù�ε����� 0, �������ε����� 11
			//�ڿ������� �˻��ؼ� ó�� �߰��� \ �� �ε��� 6
			// 6 + 1 = 7 �ε��� ���ں���
			// MAX_PATH(260)  -  (6+1)



			//�޸� ���� �Լ� : ������ ������ �ش� �޸𸮸� ä���
			memset(tStrPath + (ti + 1), 0, sizeof(wchar_t) * (MAX_PATH - (ti + 1)));

			break;
		}
	}

	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);


	//���� ������ �ִ� ��ü��θ� ROOT_PATH�� ����Ͽ���
	mPaths.insert(make_pair(ROOT_PATH, tStrPath));



	return true;
}

bool CPathMgr::MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey)
{
	const wchar_t* tpBasePath = FindPath(tStrBaseKey);

	if (!tpBasePath)
	{
		return false;
	}

	wstring tStrPath;

	if (tpBasePath)
	{
		tStrPath = tpBasePath; // ����ȯ c��Ÿ�� ���ڿ� --> wstring Ÿ��
	}


	tStrPath = tStrPath + tpPath + L'\\';


	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath.c_str());
	OutputDebugString(szTemp);


	mPaths.insert(make_pair(tStrKey, tStrPath));


	return true;
}

const wchar_t* CPathMgr::FindPath(const string& tStrKey)
{
	unordered_map<string, wstring>::iterator tItor;

	tItor = mPaths.find(tStrKey);

	if (mPaths.end() == tItor)
	{
		return nullptr;
	}


	//c��Ÿ�� ���ڿ��� ����
	return tItor->second.c_str();
}