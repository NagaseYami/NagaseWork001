#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "object3dpolygon.h"
#include "objectattractionparticle.h"
#include "objectparticle.h"
#include "camera.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"

void TestScene2::Init()
{
	Camera::SetMainCamera(&m_Camera);
	ObjectAttractionParticle * pParticle = new ObjectAttractionParticle();
	pParticle->Init();
	/*ObjectParticle * pPart = new ObjectParticle();
	pPart->Init();*/

}

void TestScene2::Update()
{
}

void TestScene2::Uninit()
{
	Object::UninitAll();
}
#endif // _DEBUG