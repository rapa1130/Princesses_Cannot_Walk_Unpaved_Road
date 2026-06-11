#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Components/Collider/Collider.h"
#include "Engine/Scene/Scene.h"

#include <unordered_map>
#include <set>
#include <string>
#include <typeindex>
#include <memory>
#include <type_traits>
#include <vector>
#include <cstdint>

namespace Bisang
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		/**
		 * @brief 컴포넌트를 추가한다.
		 *
		 * 동일한 타입의 컴포넌트가 이미 존재할 경우
		 * 기존 컴포넌트를 반환한다.
		 *
		 * RenderableComponent를 상속받은 경우
		 * 씬의 렌더링 목록에도 등록된다.
		 *
		 * @tparam T 추가할 컴포넌트 타입
		 *
		 * @return 생성되거나 기존에 존재하던 컴포넌트
		 */
		template <typename T>
		T* AddComponent()
		{
			if (m_components.find(typeid(T)) != m_components.end())
			{
				return static_cast<T*>(m_components[typeid(T)].get());
			}

			std::unique_ptr<T> newComp = std::make_unique<T>(this);
			T* pNewComp = newComp.get();

			newComp->SetTypeIndex(typeid(T));
			m_components[typeid(T)] = std::move(newComp);

			return pNewComp;
		}

		/**
		 * @brief 지정한 타입의 컴포넌트를 조회한다.
		 *
		 * @tparam T 조회할 컴포넌트 타입
		 *
		 * @return 조회된 컴포넌트
		 * @return 존재하지 않을 경우 nullptr
		 */
		template <typename T>
		T* GetComponent()
		{
			auto it = m_components.find(typeid(T));

			if (it == m_components.end())
			{
				return nullptr;
			}

			return static_cast<T*>(it->second.get());
		}

		Scene* GetScene() const { return m_scene; }
		void SetScene(Scene* scene) { m_scene = scene; }

		void SetId(uint64_t id) { m_id = id; }
		uint64_t GetId() { return m_id; }

		void SetName(std::string name) { m_name = name; }
		std::string GetName() { return m_name; }


		GameObject* GetParent() { return m_parent; }
		void SetParent(GameObject* parent)
		{
			m_parent = parent;
			parent->AddChild(this);
		}
		void ClearParent() { m_parent = nullptr; }
		void AddChild(GameObject* child) { m_children.insert(child); }
		void RemoveChild(GameObject* child) { m_children.erase(child); }

		bool GetIsPendingDestroy() { return m_isPendingDestroy; }
		void SetIsPendingDestroy(bool b) { m_isPendingDestroy = b; }

		const auto& GetComponents() const { return m_components; }

	private:
		Scene* m_scene = nullptr;           // 소속 씬
		uint64_t m_id = 0;                  // 오브젝트 id
		std::string m_name = "NewObject";   // 오브젝트 이름

		GameObject* m_parent = nullptr;     // 부모 오브젝트
		std::set<GameObject*> m_children;   // 자식 오브젝트

		bool m_isPendingDestroy = false;    // 지연 삭제 예정 여부

		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;   // 소유 컴포넌트
		std::vector<RenderableComponent*> m_renderableComponents;                       // 소유 컴포넌트 중 렌더링 가능 컴포넌트
	};
}
