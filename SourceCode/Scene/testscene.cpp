#include "../Object/objectattractionparticle.h"
#include "testscene.h"

void TestScene::Init()
{
	Camera::SetMainCamera(&m_Camera);
	ObjectAttractionParticle * pParticle = new ObjectAttractionParticle();
	pParticle->Init();
}

void TestScene::Update()
{
}

void TestScene::Uninit()
{
	Object::UninitAll();
}