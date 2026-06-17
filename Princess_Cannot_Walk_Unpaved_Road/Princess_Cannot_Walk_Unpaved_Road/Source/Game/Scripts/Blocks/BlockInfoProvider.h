#pragma once

#include "Engine/Components/Script.h"
#include "BlockObjectInfoTable.h"

#include <memory>

namespace Bisang
{
	class BlockObjectInfoProvider : public Script
	{
	public:
		BlockObjectInfoProvider(GameObject* ownerObj) : Script(ownerObj) {}

		void Awake() override;
		void Start() override;

		BlockObjectInfoTable* GetTable()
		{
			return m_table.get();
		}

	private:
		std::unique_ptr<BlockObjectInfoTable> m_table;
	};
}