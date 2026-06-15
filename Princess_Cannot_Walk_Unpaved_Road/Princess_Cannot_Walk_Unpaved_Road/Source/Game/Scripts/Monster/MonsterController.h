#pragma once
#include "Engine/Components/Script.h"
namespace Bisang
{
	class BlockMap;
	class Transform;

	class MonsterController : public Script
	{
	public:
		MonsterController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

	private:
		BlockMap* m_blockMap = nullptr;
		Transform* m_transform = nullptr;
	};


}