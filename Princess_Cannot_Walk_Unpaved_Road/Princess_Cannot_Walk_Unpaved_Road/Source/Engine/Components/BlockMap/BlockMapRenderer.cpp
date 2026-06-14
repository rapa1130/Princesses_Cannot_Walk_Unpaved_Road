#include "BlockMapRenderer.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Components/Transform.h"
#include "Engine/Resource/TextureResource.h"

#include "Game/Scripts/Blocks/BlockObjectInfoTable.h"

#include <algorithm>

namespace Bisang
{
    BlockMapRenderer::BlockMapRenderer(GameObject* ownerObj)
        : RenderableComponent(ownerObj)
    {
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

                    int block = m_blockMap->GetBlock(pos);

                    // 맵 범위를 벗어났거나 블록 데이터가 없는 경우
                    if (block == -1) continue;
                    
                    int id = block;

                    RenderBlock renderBlock;
                    renderBlock.pos = pos;
                    renderBlock.id = id;
                    renderBlock.worldPos = m_blockMap->BlockToWorld(pos);
                    renderBlock.texture = m_blockObjectInfoTable->Get(BlockId(id)).texture.get();

                    m_renderBlocks.push_back(renderBlock);
                }
            }
        }


        // 정렬된 순서대로 DrawCall 생성
        for (const RenderBlock& renderBlock : m_renderBlocks)
        {
            TextureResource* textureResource = renderBlock.texture;
            if (textureResource == nullptr) continue;

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