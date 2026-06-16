#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Renderer/Color.h"
#include "Engine/Math/Int3.h"
#include "Game/Scripts/Blocks/BlockId.h"

namespace Bisang
{
    class GameObject;
    class BlockMap;
    class SpriteRenderer;
    class Transform;
    class ResourceManager;
    class BlockObjectInfoTable;

    class Highlighter : public Script
    {
    public:
        Highlighter(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;

        void SetHighlightBlock(const Int3& blockPos, BlockId blockID);

    private:
        Bisang::Color m_overlayColor;

        Int3 m_targetPosition;
        BlockId m_targetBlockID = BlockId::Empty;


        SpriteRenderer* m_spriteRenderer = nullptr;
        BlockMap* m_blockMap = nullptr;
        Transform* m_transform = nullptr;
        ResourceManager* m_resourceManager = nullptr;
        BlockObjectInfoTable* m_infoTable = nullptr;

    };
}