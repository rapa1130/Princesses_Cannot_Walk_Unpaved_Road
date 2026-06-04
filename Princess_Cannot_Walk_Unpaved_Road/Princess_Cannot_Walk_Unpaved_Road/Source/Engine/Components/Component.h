#pragma once
#include <typeindex>
#include"Engine/Renderer/IRenderable.h"
#include"Engine/Renderer/Renderer.h"

namespace Bisang
{
	class Scene;
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* ownerObj, Scene* scene) : m_ownerObj(ownerObj), m_scene(scene) {}
		virtual ~Component() = default;

		std::type_index GetTypeIndex() { return m_typeIndex; }
		void SetTypeIndex(std::type_index typeIndex) { m_typeIndex = typeIndex; }

		virtual void Initialize() {}

		virtual void Start() {}
		virtual void Update(float dT) {}
		virtual void FixedUpdate() {}


		bool GetIsEnabled() { return m_isEnabled; }
		void SetIsEnabled(bool b) { m_isEnabled = b; }
		bool GetIsStarted() { return m_isStarted; }
		void SetIsStarted(bool b) { m_isStarted = b; }

		void SetOwner(GameObject* ownerObj) { m_ownerObj = ownerObj; }
		GameObject* GetOwner() const { return m_ownerObj; }

	protected:
		std::type_index m_typeIndex = typeid(Component);

		Scene* m_scene = nullptr;           // 소속 씬
		GameObject* m_ownerObj = nullptr;   // 주인 오브젝트

		bool m_isEnabled = true;    // 업데이트 실행 여부
		bool m_isStarted = false;   // Start() 실행 여부
	};


	//*************************************************
	// 렌더링 컴포넌트
	//************************************************* 

	class RenderableComponent : public Component, public IRenderable
	{
	public:
		RenderableComponent(GameObject* Owner, Scene* scene) : Component(Owner, scene) {}
		virtual ~RenderableComponent() = default;

		virtual void DrawCall(Renderer* renderer) override
		{
			renderer->Sumbit();
		}

		int GetOrderInLayer() const { return m_orderInLayer; }
		void SetOrderInLayer(int order) { m_orderInLayer = order; }
		bool GetIsVisible() const { return m_isVisible; }
		void SetIsVisible(bool on) { m_isVisible = on; }


	private:
		int m_orderInLayer = 0;    // 렌더링 순서 (작을 수록 빨리 렌더링)
		bool m_isVisible = true;   // 렌더링 여부
	};
}