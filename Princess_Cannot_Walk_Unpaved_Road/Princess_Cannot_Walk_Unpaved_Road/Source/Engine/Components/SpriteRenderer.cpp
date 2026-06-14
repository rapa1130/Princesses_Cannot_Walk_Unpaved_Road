#include "SpriteRenderer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/Debug.h"
#include "Engine/Resource/TextureResource.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"

namespace Bisang
{
	SpriteRenderer::SpriteRenderer(GameObject* ownerObj) :
		RenderableComponent(ownerObj)
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
		if (sprite == nullptr)
		{
			m_sprite = nullptr;
			return;
		}

		// 리소스 세팅
		m_sprite = std::shared_ptr<TextureResource>(sprite);
		m_width = sprite->GetBitmap()->GetSize().width;
		m_height = sprite->GetBitmap()->GetSize().height;
	}

	void SpriteRenderer::DrawCall(Renderer* renderer)
	{
		if (m_sprite == nullptr) return;

		RenderCommand rc = RenderCommand::CreateSpriteRC(
			GetLayer(),
			m_transform->GetWorldPosition(),
			m_sprite.get(),
			m_transform->GetWorldPosition() + m_sprite->GetPivot(),
			Vector2(GetWidth(), GetHeight()),
			m_transform->GetRotation(),
			m_alpha
		);

		renderer->Submit(rc);
	}
}