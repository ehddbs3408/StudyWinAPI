#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	return false;
}

void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)GROUP_TYPE::END; Row++)
	{
		for (UINT Col = Row; Col < (UINT)GROUP_TYPE::END; Col++)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((GROUP_TYPE)Row, (GROUP_TYPE)Col);
			}
		}
	}
}

void CollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// ���� ���� ������ �ΰ�, ū ���� ��(��Ʈ)�� ����.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	if (Col < Row)
	{
		Row = (UINT)_eRight;
		Col = (UINT)_eLeft;
	}
	// üũ�� �̹� �Ǿ��ִٸ�?
	if (m_arrCheck[Row] &= (1<<Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

void CollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter; 
	
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j]) // �ڱ� �ڽ� �浹
				continue;

			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			// �浹������? ����.
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert({ ID.ID, false });
				iter = m_mapColInfo.find(ID.ID);
			}
			// �浹�ϴ°ų�?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹��
				if (iter->second)
				{
					pLeftCol->StayCollision(pRightCol);
					pRightCol->StayCollision(pLeftCol);
				}
				// ������ �ƴѵ� ����� �浹���̾�.
				else
				{
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}

			// �浹 ���ϴ�?
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}

}