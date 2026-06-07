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

                    // 블록 좌표 -> 화면(World) 좌표 변환
                    Vector2 worldPos =
                        m_transform->GetWorldPosition() +
                        m_blockMap->BlockToWorld(pos);
                   

                    RenderBlock renderBlock;

                    renderBlock.pos = pos;
                    renderBlock.blockId = block->blockId;
                    renderBlock.worldPos = worldPos;

                    // 아이소메트릭에서는 화면 아래쪽 블록을 나중에 그려야 함
                    renderBlock.sortY = worldPos.y;

                    // 같은 y값일 경우 높이로 추가 정렬
                    renderBlock.sortZ = z;

                    m_renderBlocks.push_back(renderBlock);
                }
            }
        }

        // 렌더링 순서 정렬
        std::sort(
            m_renderBlocks.begin(),
            m_renderBlocks.end(),
            [](const RenderBlock& a, const RenderBlock& b)
            {
                // 같은 y라면 낮은 층 먼저
                if (a.sortZ != b.sortZ)
                    return a.sortZ < b.sortZ;

                // 화면 위쪽 블록 먼저
                if (a.sortY != b.sortY)
                    return a.sortY < b.sortY;

                // 완전히 동일하면 BlockId 값 기준
                return static_cast<int>(a.blockId) <
                    static_cast<int>(b.blockId);
            }
        );

        // 정렬된 순서대로 DrawCall 생성
        for (const RenderBlock& renderBlock : m_renderBlocks)
        {
            auto iter = m_blockTextures.find(static_cast<int>(renderBlock.blockId));

            if (iter == m_blockTextures.end())
                continue;

            TextureResource* tr = iter->second.get();

            if (tr == nullptr)
                continue;

            auto size = tr->GetBitmap()->GetSize();

            RenderCommand rc = RenderCommand::CreateSpriteRC(
                tr,
                renderBlock.worldPos,
                Vector2(
                    static_cast<float>(size.width) * m_transform->GetScale().x,
                    static_cast<float>(size.height) * m_transform->GetScale().y
                ),
                0.0f,
                GetOrderInLayer(),
                renderBlock.worldPos.y,
                m_alpha
            );

            renderer->Submit(rc);
        }
    }
}