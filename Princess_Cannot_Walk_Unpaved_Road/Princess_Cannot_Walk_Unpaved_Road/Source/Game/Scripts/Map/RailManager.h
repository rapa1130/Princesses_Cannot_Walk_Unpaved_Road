#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

#include "Engine/Components/BlockMap/BlockObject.h"
#include "Game/Scripts/Blocks/BlockId.h"
#include "Game/Scripts/Map/BlockMapGenerator.h"

#include <vector>

#define DIRECTION_COUNT 4

namespace Bisang
{
    class BlockMap;
    class GameManager;


    class RailManager : public Script
    {
    public:
        RailManager(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;
        void FindInitialPath();
        void FindPathFrom(const Int3& pos);

        int GetNowRailPathSize() const;
        bool HasRailPathAt(int index) const;
        const Int3& GetRailPathof(int index) const;


    private:
        bool FindAdjacent(Int3& outAdj, const Int3& inPos) const;
        bool IsAlreadyPath(const Int3& pos) const;


        BlockMap* m_blockMap = nullptr;
        GameManager* m_gM = nullptr;

        std::vector<Int3> m_railPaths;

        const int m_findDirX[DIRECTION_COUNT] = {-1,0,1,0};
        const int m_findDiry[DIRECTION_COUNT] = {0,1,0,-1};
    };
}
