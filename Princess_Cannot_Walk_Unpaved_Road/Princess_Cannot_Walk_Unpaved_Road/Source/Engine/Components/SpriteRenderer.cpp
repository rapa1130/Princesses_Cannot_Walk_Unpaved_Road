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
		// 리소스 세팅
		m_sprite = std::shared_ptr<TextureResource>(sprite);
		m_width = sprite->GetBitmap()->GetSize().width;
		m_height = sprite->GetBitmap()->GetSize().height;
	}

	void SpriteRenderer::SetSprite(const std::wstring& path)
	{
		ResourceManager* resourceManager = GetResourceManager();
		if (resourceManager == nullptr)
		{
			DEBUG_ERROR_LOCATION("ResourceManager is nullptr");
			return;
		}
		m_sprite = resourceManager->LoadTexture(path);
		if (m_sprite == nullptr)
		{
			DEBUG_ERROR_LOCATION("Fail to Load Sprite Texture");
			return;
		}
		m_width = m_sprite->GetBitmap()->GetSize().width;
		m_height = m_sprite->GetBitmap()->GetSize().height;
	}

	void SpriteRenderer::DrawCall(Renderer* renderer)
	{
		RenderCommand rc = RenderCommand::CreateSpriteRC(
			GetLayer(),
			m_transform->GetPosition(),
			m_sprite.get(),
			m_transform->GetPosition() + m_sprite->GetPivot(),
			Vector2(GetWidth(), GetHeight()),
			m_transform->GetRotation(),
			m_alpha
		);

		renderer->Submit(rc);
	}
}