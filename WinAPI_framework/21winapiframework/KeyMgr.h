#pragma once
struct tKeyInfo
{
	KEY_STATE	eState; // Ű ���°�
	bool				bPrevCheck;//���������� ���ȴ��� ����
};

class KeyMgr
{
private:
	vector<tKeyInfo> m_vecKey;
public:
	SINGLE(KeyMgr);
private:
	KeyMgr();
	~KeyMgr();
public:
	void	Init();
	void Update();
};

