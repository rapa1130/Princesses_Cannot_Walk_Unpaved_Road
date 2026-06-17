#include "RailTrackerPrefab.h"
#include "Game/Scripts/Map/RailManager.h"

namespace Bisang
{
    std::unique_ptr<GameObject> RailTrackerPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> tracker = std::make_unique<GameObject>();
        tracker.get()->SetName("RailTracker");

        tracker->AddComponent<RailManager>();
        
        return tracker;
    }
}