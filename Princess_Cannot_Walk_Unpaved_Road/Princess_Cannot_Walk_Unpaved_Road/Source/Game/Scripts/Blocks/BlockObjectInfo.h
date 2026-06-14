#pragma once

#include "Game/Scripts/Blocks/BlockId.h"

#include <memory>

namespace Bisang
{
    class TextureResource;

    enum class BlockObjectKind
    {
        Terrain,   // 땅, 물
        Material,  // 재료
        Tool       // 곡괭이, 도끼
    };

    enum class ToolType
    {
        None,
        Pickaxe,
        Axe,
        Roller
    };

    struct MineableData
    {
        int maxHp;
        ToolType requiredTool;
        BlockId dropBlockId;
        int count;
    };

    struct BlockObjectInfo
    {
        BlockId id;                                 // 블럭 아이디
        BlockObjectKind kind;                       // 종류
        std::shared_ptr<TextureResource> texture;   // 텍스처
        bool isSolid = false;                       // 통과할 수 있는지\

        bool isPickable = false;                    // 집을 수 있는지
        ToolType toolType = ToolType::None;         // 도구 타입
        const MineableData* mineable = nullptr;     // 캐기 정보
        int orderInZ = 0;
    };
}
