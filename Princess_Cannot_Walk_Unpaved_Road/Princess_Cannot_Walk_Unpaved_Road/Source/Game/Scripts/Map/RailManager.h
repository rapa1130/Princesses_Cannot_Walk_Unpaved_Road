#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

#include "Engine/Components/BlockMap/BlockObject.h"
#include "Game/Scripts/Blocks/BlockId.h"
#include "Game/Scripts/Map/BlockMapGenerator.h"

#include <vector>

namespace Bisang
{
    class BlockMap;
    class BlockMapGenerator;

    struct RailPath
    {
        std::vector<Int3> positions;
    };

    class RailManager : public Script
    {
    public:
        RailManager(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void FindInitialPath();

    private:
        BlockMap* m_blockMap = nullptr;
        BlockMapGenerator* m_blockMapGen = nullptr;

        std::vector<RailPath> paths;
    };
}
