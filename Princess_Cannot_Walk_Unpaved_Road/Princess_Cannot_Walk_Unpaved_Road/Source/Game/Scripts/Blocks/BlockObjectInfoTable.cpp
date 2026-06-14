// BlockInfoTable.cpp
#include "BlockObjectInfoTable.h"

#include "Engine/Resource/ResourceManager.h"

#include <cassert>

namespace Bisang
{
    void BlockObjectInfoTable::Init(ResourceManager* resourceManager)
    {
        static MineableData rockMineable
        {
            5,
            ToolType::Pickaxe,
            BlockId::Rock,
            1
        };

        BlockObjectInfo empty;
        empty.id = BlockId::Empty;
        empty.kind = BlockObjectKind::Terrain;
        empty.isSolid = false;
        Register(empty);

        BlockObjectInfo grass;
        grass.id = BlockId::Grass;
        grass.kind = BlockObjectKind::Terrain;
        grass.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/GrassBlock.png");
        grass.isSolid = true;
        Register(grass);

        BlockObjectInfo dirt;
        dirt.id = BlockId::Dirt;
        dirt.kind = BlockObjectKind::Terrain;
        dirt.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Dirt.png");
        dirt.isSolid = true;
        Register(dirt);

        BlockObjectInfo water;
        water.id = BlockId::Water;
        water.kind = BlockObjectKind::Terrain;
        water.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Water.png");
        water.isSolid = false;
        Register(water);

        BlockObjectInfo rock;
        rock.id = BlockId::Rock;
        rock.kind = BlockObjectKind::Terrain;
        rock.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Rock.png");
        rock.isSolid = true;
        rock.mineable = &rockMineable;
        Register(rock);

        BlockObjectInfo clay;
        clay.id = BlockId::Clay;
        clay.kind = BlockObjectKind::Material;
        clay.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Clay.png");
        clay.isSolid = true;
        Register(clay);

        BlockObjectInfo tree;
        tree.id = BlockId::Tree;
        tree.kind = BlockObjectKind::Material;
        tree.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Tree.png");
        tree.isSolid = true;
        tree.mineable = &rockMineable;
        Register(tree);

        BlockObjectInfo orcTree;
        orcTree.id = BlockId::OrcTree;
        orcTree.kind = BlockObjectKind::Material;
        orcTree.texture = resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/OrcTree.png");
        orcTree.isSolid = true;
        orcTree.mineable = &rockMineable;
        Register(orcTree);

        BlockObjectInfo axe;
        axe.id = BlockId::Axe;
        axe.kind = BlockObjectKind::Tool;
        axe.toolType = ToolType::Axe;
        axe.texture = resourceManager->LoadTexture(L"Assets/Textures/Tools/Axe/Axe_Front.png");
        Register(axe);

        BlockObjectInfo pickAxe;
        pickAxe.id = BlockId::PickAxe;
        pickAxe.kind = BlockObjectKind::Tool;
        pickAxe.toolType = ToolType::Pickaxe;
        pickAxe.texture = resourceManager->LoadTexture(L"Assets/Textures/Tools/PickAxe/PickAxe_Left.png");
        Register(pickAxe);


    }

    void BlockObjectInfoTable::Register(const BlockObjectInfo& blockInfo)
    {
        m_blockInfos[blockInfo.id] = blockInfo;
    }

    const BlockObjectInfo* BlockObjectInfoTable::Find(BlockId id) const
    {
        auto it = m_blockInfos.find(id);
        if (it == m_blockInfos.end())
            return nullptr;

        return &it->second;
    }

    const BlockObjectInfo& BlockObjectInfoTable::Get(BlockId id) const
    {
        const BlockObjectInfo* info = Find(id);
        assert(info != nullptr);
        return *info;
    }

    bool BlockObjectInfoTable::Contains(BlockId id) const
    {
        return m_blockInfos.find(id) != m_blockInfos.end();
    }
}