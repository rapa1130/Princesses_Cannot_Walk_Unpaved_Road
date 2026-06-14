// BlockInfoTable.h
#pragma once

#include "Game/Scripts/Blocks/BlockObjectInfo.h"

#include <unordered_map>

namespace Bisang
{
    class ResourceManager;

    class BlockObjectInfoTable
    {
    public:
        void Init(ResourceManager* resourceManager);

        void Register(const BlockObjectInfo& blockInfo);

        const BlockObjectInfo* Find(BlockId id) const;
        const BlockObjectInfo& Get(BlockId id) const;

        bool Contains(BlockId id) const;

    private:
        std::unordered_map<BlockId, BlockObjectInfo> m_blockInfos;
    };
}