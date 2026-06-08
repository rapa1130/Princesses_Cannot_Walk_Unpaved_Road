#pragma once
#include <typeindex>
#include"Engine/Renderer/IRenderable.h"

namespace Bisang
{
	class GameObject;
	class Transform;
	class Scene;
	class Renderer;
	class ResourceManager;

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

		ResourceManager* GetResourceManager(); 

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

	class Transform;

	class RenderableComponent : public Component, public IRenderable
	{
	public:
		RenderableComponent(GameObject* Owner, Scene* scene); 

		virtual ~RenderableComponent() = default;


		virtual void DrawCall(Renderer* renderer) = 0;

		int GetLayer() const { return m_Layer; }
		void SetLayer(int order) { m_Layer = order; }

		bool GetIsVisible() const { return m_isVisible; }
		void SetIsVisible(bool on) { m_isVisible = on; }

		Transform* GetTransform() const { return m_transform; }

	protected:
		Transform* m_transform;

	private:
		int m_Layer = 0;   // 레이어 (작을 수록 빨리 렌더링)
		bool m_isVisible = true;   // 렌더링 여부
	};
}