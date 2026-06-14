#pragma once
#include "Engine/Components/Script.h"

#include "Game/Scripts/Blocks/BlockObjectInfo.h"

#include <memory>

namespace Bisang
{
	class TextureResource;

	class PlayerStatus : public Script
	{
	public:
		PlayerStatus(GameObject* ownerObj) : Script(ownerObj) {}

		void EquipTool(ToolType tool, std::shared_ptr<TextureResource> texture)
		{
			m_equippedTool = tool;
			m_toolTexture = texture;
		}

		void UnequipTool()
		{
			m_equippedTool = ToolType::None;
			m_toolTexture = nullptr;
		}

		ToolType GetToolType() { return m_equippedTool; }
		std::shared_ptr<TextureResource> GetToolTexture() { return m_toolTexture; }

	private:
		ToolType m_equippedTool = ToolType::None;
		std::shared_ptr<TextureResource> m_toolTexture;
	};
}
