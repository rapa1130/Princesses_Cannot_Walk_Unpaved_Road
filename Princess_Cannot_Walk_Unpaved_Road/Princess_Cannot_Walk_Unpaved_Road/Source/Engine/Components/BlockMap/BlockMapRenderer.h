#pragma once
#include "BlockMap.h"

#include "Engine/Components/Component.h"

#include "Game/Scripts/Blocks/BlockObjectInfoTable.h"

#include <memory>
#include <vector>
#include <unordered_map>

namespace Bisang
{
    class Renderer;
    class TextureResource;
    class BlockObjectInfoTable;

    class BlockMapRenderer : public RenderableComponent
    {
    public:
        BlockMapRenderer(GameObject* ownerObj);

        virtual void DrawCall(Renderer* renderer) override;

        void SetBlockMap(BlockMap* blockMap) { m_blockMap = blockMap; }
        BlockMap* GetBlockMap() const { return m_blockMap; }

        float GetAlpha() const { return m_alpha; }
        void SetAlpha(float alpha) { m_alpha = alpha; }

        void SetBlockObjectInfoTable(BlockObjectInfoTable* table)
        {
            m_blockObjectInfoTable = table;
        }

    private:
        struct RenderBlock
        {
            Int3 pos;
            int id;
            Vector3 worldPos;
            TextureResource* texture;
            int orderInZ;
        };

    private:
        BlockMap* m_blockMap = nullptr;
        std::vector<RenderBlock> m_renderBlocks;
        BlockObjectInfoTable* m_blockObjectInfoTable;
        float m_alpha = 1.0f;
    };
}