#include "Scene.h"

#include "Engine/Components/Component.h"
#include "Engine/Object/GameObject.h"

#include <algorithm>

namespace Bisang
{
	Scene::Scene(std::string sceneName, ResourceManager* resourceManager, InputManager* inputManager) :
		m_sceneName(sceneName), m_resourceManager(resourceManager), m_inputManager(inputManager) {
	}

	Scene::~Scene() = default;

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

		ProcessDestroyGameObjectQueue();   // 오브젝트 지연삭제 실행
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

	GameObject* Scene::CreateGameObject()
	{
		std::unique_ptr<GameObject> newObj = std::make_unique<GameObject>(this);
		GameObject* pNewObj = newObj.get();

		newObj->SetId(++m_GameObjectCount);
		m_gameObjects[newObj->GetId()] = std::move(newObj);

		return pNewObj;

	}

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

	void Scene::DestroyGameObject(uint64_t id)
	{
		if (m_gameObjects.find(id) == m_gameObjects.end())
			return;

		// 지연 삭제 큐 push
		m_destroyGameObjectQueue.push(id);
	}

	void Scene::ProcessDestroyGameObjectQueue()
	{
		// 지연 삭제 큐를 비우면서 오브젝트 제거 및 메모리 해제
		while (false == m_destroyGameObjectQueue.empty())
		{
			uint64_t id = m_destroyGameObjectQueue.front();
			m_gameObjects[id].reset();
			m_gameObjects.erase(id);
			m_destroyGameObjectQueue.pop();
		}
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

		// 렌더링 컴포넌트를 추가할 때마다 OrderInLayer 기준으로 오름차순 정렬
		std::sort(
			m_renderableComponents.begin(),
			m_renderableComponents.end(),
			[](const RenderableComponent* lhs,
				const RenderableComponent* rhs)
			{

				return lhs->GetOrderInLayer() < rhs->GetOrderInLayer();
			});
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
}