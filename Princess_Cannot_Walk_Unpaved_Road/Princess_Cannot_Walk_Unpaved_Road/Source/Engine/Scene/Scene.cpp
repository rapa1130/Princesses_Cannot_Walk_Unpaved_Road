#include "Scene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Components/Component.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Physics/Collision.h"
#include "Engine/Prefab/PrefabFactory.h"

#include <algorithm>
#include <iostream>

namespace Bisang
{
	Scene::Scene(std::string sceneName, GameContext* context)
		: m_sceneName(sceneName), m_context(context)
	{
		m_prefabFactory = m_context->prefabFactory;
	}

	Scene::~Scene() = default;

	//*************************************************
	// 생명주기
	//************************************************* 

	void Scene::Initialize()
	{
		// 게임 오브젝트 순회
		for (const auto& it : m_gameObjects)
		{
			// 오브젝트 소유 컴포넌트 순회
			for (const auto& jt : it.second->GetComponents())
			{
				Component* comp = jt.second.get();
				comp->Awake();
			}
		}
	}

	//*************************************************
	// 업데이트
	//************************************************* 

	void Scene::Update(float deltaTime)
	{
		// 게임 오브젝트 순회
		for (const auto& it : m_gameObjects)
		{
			// 오브젝트 소유 컴포넌트 순회
			for (const auto& jt : it.second->GetComponents())
			{
				Component* comp = jt.second.get();

				// 업데이트 비활성화 시 업데이트하지 않음
				if (false == comp->GetIsEnabled()) continue;

				// Start() 최초 1회 실행
				if (false == comp->GetIsStarted())
				{
					comp->Start();
					comp->SetIsStarted(true);
				}

				comp->Update(deltaTime);
			}
		}

		ProcessDeleteGameObjectQueue();   // 오브젝트 지연삭제 실행
		ProcessAddGameObjectQueue();      // 오브젝트 지연추가 실행
	}

	void Scene::FixedUpdate()
	{
		// 게임 오브젝트 순회
		for (const auto& it : m_gameObjects)
		{
			// 오브젝트 소유 컴포넌트 순회
			for (const auto& jt : it.second->GetComponents())
			{
				Component* comp = jt.second.get();

				// 업데이트 비활성화 시 업데이트하지 않음
				if (false == comp->GetIsEnabled()) continue;

				// Start() 최초 1회 실행
				if (false == comp->GetIsStarted())
				{
					comp->Start();
					comp->SetIsStarted(true);
				}

				comp->FixedUpdate();
			}
		}

		// 콜라이더 충돌검사
		// CheckCollisions();
	}

	//*************************************************
	// 렌더링
	//************************************************* 

	void Scene::Render(Renderer* renderer)
	{
		// 렌더링 컴포넌트 순회 ( 정렬되어있음 )
		for (RenderableComponent* rComp : m_renderableComponents)
		{
			// 렌더링 비활성화 시
			if (false == rComp->GetIsVisible()) continue;
      
			rComp->DrawCall(renderer);
		}
	}



	//*************************************************
	// 게임 오브젝트
	//************************************************* 
	//##########
	// 등록
	//##########
	GameObject* Scene::Instantiate(std::string prefabName)
	{
		std::unique_ptr<GameObject> obj = m_prefabFactory->Create(prefabName);
		if (obj == nullptr) return nullptr;
		GameObject* pObj = obj.get();
		m_addGameObjectQueue.push(std::move(obj));
		return pObj;
	}

	void Scene::AddGameObject(std::string prefabName)
	{
		std::unique_ptr<GameObject> obj = m_prefabFactory->Create(prefabName);
		if (obj == nullptr) return;
		AddGameObject(std::move(obj));
	}

	void Scene::AddGameObject(std::unique_ptr<GameObject> obj)
	{
		// 씬 등록 절차 수행
		RegisterToScene(obj.get());

		// 오브젝트 아이디 부여
		obj->SetId(++m_GameObjectCount);

		// 씬에 등록
		m_gameObjects[obj->GetId()] = std::move(obj);
	}

	void Scene::ProcessAddGameObjectQueue()
	{
		// 지연 추가 큐를 비우면서 오브젝트 등록
		while (false == m_addGameObjectQueue.empty())
		{
			AddGameObject(std::move(m_addGameObjectQueue.front()));
			m_addGameObjectQueue.pop();
		}
	}

	void Scene::RegisterToScene(GameObject* obj)
	{
		obj->SetScene(this);

		for (const auto& it : obj->GetComponents())
		{
			Component* comp = it.second.get();

			// 렌더러블 컴포넌트면 씬에 추가 등록
			RenderableComponent* rComp = dynamic_cast<RenderableComponent*>(comp);
			if (rComp)
			{
				AddRenderableComponent(rComp);
			}

			// 콜라이더 컴포넌트면 씬에 추가 등록
			//Collider* collider = dynamic_cast<Collider*>(comp);
			//if (collider)
			//{
			//	AddCollider(collider);
			//}
		}
	}

	//##########
	// 삭제
	//##########
	void Scene::DestroyGameObject(uint64_t id)
	{
		if (m_gameObjects.find(id) == m_gameObjects.end()) return;
		if (m_deleteGameObjectSet.find(id) != m_deleteGameObjectSet.end()) return;

		// 지연 삭제 큐 push
		m_deleteGameObjectQueue.push(id);

		// 지연 삭제 셋 insert
		m_deleteGameObjectSet.insert(id);
	}

	void Scene::DeleteGameObject(uint64_t id)
	{
		// 씬 등록 해제 절차 실행
		UnregisterFromScene(id);

		// 씬에서 삭제
		m_gameObjects.erase(id);
	}

	void Scene::ProcessDeleteGameObjectQueue()
	{
		// 지연 삭제 큐를 비우면서 오브젝트 제거 및 메모리 해제
		while (false == m_deleteGameObjectQueue.empty())
		{
			uint64_t id = m_deleteGameObjectQueue.front();
			m_deleteGameObjectQueue.pop();
			m_deleteGameObjectSet.erase(id);

			DeleteGameObject(id);
		}
	}

	void Scene::UnregisterFromScene(uint64_t id)
	{
		GameObject* obj = m_gameObjects[id].get();
		
		for (const auto& it : obj->GetComponents())
		{
			Component* comp = it.second.get();

			if (auto* rComp = dynamic_cast<RenderableComponent*>(comp))
			{
				RemoveRenderableComponent(rComp);
			}

			//if (auto* collider = dynamic_cast<Collider*>(comp))
			//{
			//	RemoveCollider(collider);
			//}
		}

	}

	//##########
	// 조회
	//##########
	GameObject* Scene::GetGameObject(uint64_t id)
	{
		auto it = m_gameObjects.find(id);
		if (it == m_gameObjects.end())
		{
			return nullptr;
		}

		return it->second.get();
	}
	GameObject* Scene::FindGameObjectByName(std::string name)
	{
		for (const auto& it : m_gameObjects)
		{
			if (name == it.second->GetName())
			{
				return it.second.get();
			}
		}
		return nullptr;
	}

	//*************************************************
	// 렌더링 컴포넌트
	//************************************************* 

	void Scene::AddRenderableComponent(RenderableComponent* component)
	{
		if (component == nullptr)
			return;

		auto iter = std::find(
			m_renderableComponents.begin(),
			m_renderableComponents.end(),
			component);

		if (iter != m_renderableComponents.end())
			return;

		m_renderableComponents.push_back(component);
	}

	void Scene::RemoveRenderableComponent(RenderableComponent* component)
	{
		if (component == nullptr)
			return;

		// 렌더링 컴포넌트 순회 돌면서 탐색
		auto iter = std::find(
			m_renderableComponents.begin(),
			m_renderableComponents.end(),
			component);

		// 렌더링 컴포넌트 리스트에서 제거
		if (iter != m_renderableComponents.end())
		{
			m_renderableComponents.erase(iter);
		}
	}

	//*************************************************
	// 콜라이더 컴포넌트
	//************************************************* 

	void Scene::CheckCollisions()
	{
		m_currentCollisions.clear();

		for (size_t i = 0; i < m_colliders.size(); ++i)
		{
			Collider* lhs = m_colliders[i];

			if (lhs == nullptr)
				continue;

			if (false == lhs->GetIsEnabled())
				continue;

			for (size_t j = i + 1; j < m_colliders.size(); ++j)
			{
				Collider* rhs = m_colliders[j];

				if (rhs == nullptr)
					continue;

				if (false == rhs->GetIsEnabled())
					continue;
				                                                                
				CollisionPair pair(lhs, rhs);

				if (Collision::Check(lhs, rhs))
				{
					m_currentCollisions.insert(pair);

					if (m_prevCollisions.find(pair) == m_prevCollisions.end())
					{
						lhs->OnCollisionEnter(rhs);
						rhs->OnCollisionEnter(lhs);
					}
					else
					{
						lhs->OnCollisionStay(rhs);
						rhs->OnCollisionStay(lhs);
					}
				}
			}
		}

		for (const CollisionPair& pair : m_prevCollisions)
		{
			if (m_currentCollisions.find(pair) == m_currentCollisions.end())
			{
				if (pair.lhs != nullptr && pair.rhs != nullptr)
				{
					pair.lhs->OnCollisionExit(pair.rhs);
					pair.rhs->OnCollisionExit(pair.lhs);
				}
			}
		}

		m_prevCollisions = m_currentCollisions;
	}

	void Scene::AddCollider(Collider* collider)
	{
		if (collider == nullptr)
			return;

		auto iter = std::find(
			m_colliders.begin(),
			m_colliders.end(),
			collider);

		if (iter != m_colliders.end())
			return;

		m_colliders.push_back(collider);
	}

	void Scene::RemoveCollider(Collider* collider)
	{
		if (collider == nullptr)
			return;

		auto iter = std::find(
			m_colliders.begin(),
			m_colliders.end(),
			collider);

		if (iter == m_colliders.end())
			return;

		*iter = m_colliders.back();
		m_colliders.pop_back();

		for (auto it = m_prevCollisions.begin();
			it != m_prevCollisions.end();)
		{
			if (it->lhs == collider || it->rhs == collider)
				it = m_prevCollisions.erase(it);
			else
				++it;
		}

		for (auto it = m_currentCollisions.begin();
			it != m_currentCollisions.end();)
		{
			if (it->lhs == collider || it->rhs == collider)
				it = m_currentCollisions.erase(it);
			else
				++it;
		}
	}


}