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

	void SpriteRenderer::SetSprite(std::shared_ptr<TextureResource> sprite)
	{
		// 리소스 세팅
		m_sprite = std::shared_ptr<TextureResource>(sprite);
		m_width = sprite->GetBitmap()->GetSize().width;
		m_height = sprite->GetBitmap()->GetSize().height;
	}

	void SpriteRenderer::DrawCall(Renderer* renderer)
	{
		RenderCommand rc;

		rc.orderInLayer = GetOrderInLayer();
		rc.position = m_transform->GetPosition();
		rc.size = Vector2(GetWidth(), GetHeight());
		rc.resource = m_sprite.get();
		rc.type = RenderCommandType::Sprite;
		rc.alpha = 1.0f;

		renderer->Submit(rc);
	}
}