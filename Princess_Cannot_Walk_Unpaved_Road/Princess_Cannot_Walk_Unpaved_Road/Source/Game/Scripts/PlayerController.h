#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	class Transform;
	class InputManager;
	class BlockMap;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;

		bool CanMoveTo(const Vector3& worldPos) const;

	private:
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		BlockMap* m_blockMap = nullptr;
		int playerZ = 1;

		Vector2 m_dir;
		float moveSpeed = 1000;
	};
}