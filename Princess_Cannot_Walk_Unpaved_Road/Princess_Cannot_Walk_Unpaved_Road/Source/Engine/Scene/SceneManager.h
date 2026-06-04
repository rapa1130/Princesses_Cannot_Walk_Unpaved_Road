#pragma once

#include "Engine/Scene/Scene.h"

#include <string>
#include <unordered_map>
#include <memory>
#include <type_traits>

namespace Bisang
{
	class ResourceManager;
	class InputManager;

	/**
	 * @brief 씬을 생성 및 관리하는 클래스
	 *
	 * 씬의 등록, 시작 씬 설정, 씬 전환 및
	 * 현재 활성화된 씬의 업데이트와 렌더링을 담당한다.
	 */
	class SceneManager
	{
	public:
		/**
		 * @brief SceneManager를 생성한다.
		 *
		 * @param[in] resourceManager 리소스 관리자
		 * @param[in] inputManager 입력 관리자
		 */
		SceneManager(ResourceManager* resourceManager, InputManager* inputManager) :
			m_resourceManager(resourceManager), m_inputManager(inputManager)
		{
		}

		/**
		 * @brief 새로운 씬을 등록한다.
		 *
		 * 지정한 타입의 씬을 생성하여 등록한다.
		 * 동일한 이름의 씬이 이미 존재하는 경우 등록하지 않는다.
		 *
		 * @tparam T 생성할 씬 타입
		 * @param[in] sceneName 등록할 씬 이름
		 */
		template <typename T>
		void AddScene(const std::string& sceneName)
		{
			static_assert(std::is_base_of_v<Scene, T>,
				"T must inherit from Scene");

			if (m_scenes.find(sceneName) != m_scenes.end())
			{
				return;
			}

			m_scenes[sceneName] = std::make_unique<T>(
				sceneName,
				m_resourceManager,
				m_inputManager
			);
		}

		/**
		 * @brief 현재 활성화된 씬의 이름을 반환한다.
		 *
		 * @return 현재 씬 이름
		 */
		const std::string& GetCurrentSceneName() const
		{
			return m_currentSceneName;
		}

		/**
		 * @brief 시작 씬을 설정한다.
		 *
		 * 게임 시작 시 최초로 사용할 씬을 지정한다.
		 *
		 * @param[in] sceneName 시작 씬 이름
		 */
		void SetStartScene(const std::string& sceneName);

		/**
		 * @brief 현재 씬을 다른 씬으로 전환한다.
		 *
		 * 기존 씬의 OnExit()를 호출한 뒤
		 * 새로운 씬의 SetupScene()과 OnEnter()를 호출한다.
		 *
		 * @param[in] sceneName 전환할 씬 이름
		 */
		void ChangeScene(const std::string& sceneName);

		/**
		 * @brief 현재 씬 Setup(), OnEnter() 실행
		 */
		void InitCurrentScene();

		/**
		 * @brief 현재 씬을 구성한다.
		 *
		 * 씬에 필요한 게임 오브젝트와 컴포넌트를 생성한다.
		 */
		void SetupScene();

		/**
		 * @brief 현재 씬의 고정 프레임 업데이트를 수행한다.
		 */
		void FixedUpdate();

		/**
		 * @brief 현재 씬의 프레임 업데이트를 수행한다.
		 *
		 * @param[in] deltaTime 이전 프레임과의 시간 간격(초)
		 */
		void Update(float deltaTime);

		/**
		 * @brief 현재 씬을 렌더링한다.
		 */
		void Render();

	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;

		Scene* m_currentScene = nullptr;
		std::string m_currentSceneName;

		ResourceManager* m_resourceManager = nullptr;
		InputManager* m_inputManager = nullptr;
	};
}