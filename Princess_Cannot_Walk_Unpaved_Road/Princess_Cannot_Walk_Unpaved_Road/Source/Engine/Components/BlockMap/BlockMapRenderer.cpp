#include "BlockMapRenderer.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Components/Transform.h"
#include "Engine/Resource/TextureResource.h"

#include <algorithm>

namespace Bisang
{
    BlockMapRenderer::BlockMapRenderer(GameObject* ownerObj, Scene* scene)
        : RenderableComponent(ownerObj, scene)
    {
        ResourceManager* rm = GetResourceManager();
        if (rm != nullptr)
        {
            m_blockTextures[static_cast<int>(BlockId::Grass)] =
                rm->LoadTexture(L"Assets/Textures/GrassBlock.png");
            m_blockTextures[static_cast<int>(BlockId::Dirt)] =
                rm->LoadTexture(L"Assets/Textures/Dirt.png");
            m_blockTextures[static_cast<int>(BlockId::Water)] =
                rm->LoadTexture(L"Assets/Textures/Water.png");
            m_blockTextures[static_cast<int>(BlockId::Rock)] =
                rm->LoadTexture(L"Assets/Textures/Rock.png");
            m_blockTextures[static_cast<int>(BlockId::Clay)] =
                rm->LoadTexture(L"Assets/Textures/Clay.png");
            m_blockTextures[static_cast<int>(BlockId::Tree)] =
                rm->LoadTexture(L"Assets/Textures/Tree.png");
        }
    }

    void BlockMapRenderer::DrawCall(Renderer* renderer)
    {
        // Transform 없으면 월드 위치를 계산할 수 없음
        if (m_transform == nullptr)
        {
            return;
        }

        // 렌더링할 BlockMap이 지정되지 않은 경우
        if (m_blockMap == nullptr)
        {
            return;
        }

        // 렌더링 비활성화 상태
        if (!GetIsVisible())
            return;

        // 이전 프레임 데이터 제거
        m_renderBlocks.clear();

        // 맵 전체 순회
        for (int z = 0; z < m_blockMap->GetHeight(); z++)
        {
            for (int y = 0; y < m_blockMap->GetDepth(); y++)
            {
                for (int x = 0; x < m_blockMap->GetWidth(); x++)
                {
                    Int3 pos;
                    pos.x = x;
                    pos.y = y;
                    pos.z = z;

                    const Block* block = m_blockMap->GetBlock(pos);

                    // 맵 범위를 벗어났거나 블록 데이터가 없는 경우
                    if (block == nullptr)
                        continue;

                    // 빈 블록은 렌더링하지 않음
                    if (block->blockId == BlockId::Empty)
                        continue;

                    RenderBlock renderBlock;

                    renderBlock.pos = pos;
                    renderBlock.blockId = block->blockId;
                    renderBlock.worldPos = m_blockMap->BlockToWorld(pos);

                    m_renderBlocks.push_back(renderBlock);
                }
            }
        }


        // 정렬된 순서대로 DrawCall 생성
        for (const RenderBlock& renderBlock : m_renderBlocks)
        {
            auto iter = m_blockTextures.find(static_cast<int>(renderBlock.blockId));

            if (iter == m_blockTextures.end())
                continue;

            TextureResource* textureResource = iter->second.get();

            if (textureResource == nullptr)
                continue;

            auto size = textureResource->GetBitmap()->GetSize();

            RenderCommand rc = RenderCommand::CreateSpriteRC(
                GetLayer(),
                renderBlock.worldPos,
                textureResource,
                renderBlock.worldPos + textureResource->GetPivot(),
                Vector2(
                    static_cast<float>(size.width) * m_transform->GetScale().x,
                    static_cast<float>(size.height) * m_transform->GetScale().y
                ),
                0.0f,
                m_alpha
            );

            renderer->Submit(rc);
        }
    }
}