#include "PortalParticle.h"

#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/Transform.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Math/Math.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"
#include "Engine/Core/Layer.h"

#include <iostream>

namespace Bisang
{
	void PortalParticle::Start()
	{
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
		m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();

		m_transform->SetScale({ 0.5,0.5 });
		
		m_worldPos = m_blockMap->BlockToWorld(m_pos);
		m_transform->SetPosition(m_worldPos);

		CreateParticle();
	}
	void PortalParticle::Update(float dT)
	{
		m_worldPos = m_blockMap->BlockToWorld(m_pos);
		m_t += dT * m_speed;
			
		if (m_t >= 1.0f)
		{
				
			m_t -= 1.0f;
		}

		Vector2 offset = Vector2::Lerp(m_startOffset, m_endOffset, m_t);
		m_transform->SetPosition(m_worldPos + offset);
		m_spriteRenderer->SetColor({ 0,0,0,sinf(m_t * 3.141592) });
	}
	void PortalParticle::SetRisingSpeed(float speed)
	{
		m_risingSpeed = speed;
	}
	float PortalParticle::GetRisingSpeed() const
	{
		return m_risingSpeed;
	}
	void PortalParticle::CreateParticle()
	{
		ResourceManager* resourceManager = m_ownerObj->GetScene()->GetResourceManager();
		m_spriteRenderer->SetSprite(resourceManager->LoadTexture(L"Assets/Textures/Effect/ProtalParticle.png"));
		m_spriteRenderer->SetLayer(Layer::Highlight);

		m_t = (float)rand() / RAND_MAX;

		float minusOneToPlusOne = 2 * ((float)rand() / RAND_MAX) - 1;
		float randX = minusOneToPlusOne * m_randRadius;
		minusOneToPlusOne = 2 * ((float)rand() / RAND_MAX) - 1;
		float randY = minusOneToPlusOne * m_randRadius;
		m_startOffset = Vector2(randX, randY);
		m_endOffset = m_startOffset - Vector2(0, m_risingDistance);
		m_speed = ((float)rand() / RAND_MAX) * m_risingSpeed / 2 + m_risingSpeed / 2;
		m_alphaPhase = 1.0f;
	}
}