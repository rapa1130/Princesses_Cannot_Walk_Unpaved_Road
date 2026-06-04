#include "SpriteRenderer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	SpriteRenderer::SpriteRenderer(GameObject* ownerObj, Scene* scene) :
		RenderableComponent(ownerObj, scene),
		m_transform(m_ownerObj->GetComponent<Transform>())
	{
	}

	float SpriteRenderer::GetWidth() const
	{
		return m_width * m_transform->GetScale().x;
	}

	float SpriteRenderer::GetHeight() const
	{
		return m_height * m_transform->GetScale().y;
	}

	void SpriteRenderer::SetSprite(Sprite* sprite)
	{
		// 리소스 세팅
		m_sprite = sprite;
	}

	void SpriteRenderer::DrawCall()
	{
		// 렌더러에 드로우콜
	}
}