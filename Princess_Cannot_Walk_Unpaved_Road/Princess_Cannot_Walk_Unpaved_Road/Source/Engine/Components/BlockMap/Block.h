#pragma once
#include <memory>

namespace Bisang
{
	class TextureResource;

	class Block
	{
	public:
		Block(int id, bool isSolid, std::shared_ptr< TextureResource> textureResource) : m_id(id), m_isSolid(isSolid), m_textrueResource(textureResource) {}
		int GetId() { return m_id; }
		bool GetIsSolid() { return m_isSolid; }
		TextureResource* GetTextureResource() { return m_textrueResource.get(); }

	private:
		int m_id = 0;                                                    // 블럭 ID
		bool m_isSolid = true;                                           // 막혀있는 블럭인가?
		std::shared_ptr< TextureResource> m_textrueResource = nullptr;   // 블럭 텍스처 리소스
	};
}