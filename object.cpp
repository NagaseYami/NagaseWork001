#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "object.h"

vector<Object*> Object::m_pManager;

Object::Object()
{
	m_pManager.push_back(this);
}

void Object::FixedUpdateAll()
{
	for (auto itr = m_pManager.begin(); itr != m_pManager.end();)
	{
		Object * pObj = *itr;
		if (pObj->isDestory() != true)
		{
			pObj->FixedUpdate();
			itr++;
		}
		else
		{
			pObj->Uninit();
			delete pObj;
			itr = m_pManager.erase(itr);
		}
	}
}

void Object::UpdateAll()
{
	for (auto itr = m_pManager.begin(); itr != m_pManager.end();)
	{
		Object * pObj = *itr;
		if (pObj->isDestory() != true)
		{
			pObj->Update();
			itr++;
		}
		else
		{
			pObj->Uninit();
			delete pObj;
			itr = m_pManager.erase(itr);
		}
	}
}

void Object::LateUpdateAll()
{
	for (auto itr = m_pManager.begin(); itr != m_pManager.end();)
	{
		Object * pObj = *itr;
		if (pObj->isDestory() != true)
		{
			pObj->LateUpdate();
			itr++;
		}
		else
		{
			pObj->Uninit();
			delete pObj;
			itr = m_pManager.erase(itr);
		}
	}
}

void Object::DrawAllBackBufferObject()
{
	auto pDevice = Renderer::GetDevice();
	auto copy = m_pManager;
	sort(copy.begin(), copy.end(), [](Object* const &a, Object* const &b) { return a->m_Layer < b->m_Layer; });

	for (auto itr = copy.begin(); itr != copy.end(); itr++)
	{
		Object * pObj = *itr;
		if (!pObj->m_isRenderTarget)
		{
			pObj->Draw();
		}		
	}
			
}

void Object::UninitAll()
{
	for (auto itr = m_pManager.begin(); itr != m_pManager.end(); itr++)
	{
		Object * pObj = *itr;
		pObj->Uninit();
		delete pObj;
	}
	m_pManager.clear();
}

bool Object::isDestory() const
{
	return m_bDestory;
}

void Object::DestoryFlag(bool flag)
{
	m_bDestory = false;
}