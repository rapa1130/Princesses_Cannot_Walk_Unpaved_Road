#include "SceneManager.h"

namespace Bisang
{
	void SceneManager::SetStartScene(const std::string& sceneName)
	{
		if (m_scenes.find(sceneName) == m_scenes.end()) return;
		m_currentScene = m_scenes[sceneName].get();
		m_currentSceneName = sceneName;
	}

	void SceneManager::InitCurrentScene()
	{
		m_currentScene->Setup();
		m_currentScene->Initialize();
	}

	void SceneManager::ChangeScene()
	{
		if (false == m_hasPendingSceneChange) return;
		m_hasPendingSceneChange = false;

		auto it = m_scenes.find(m_pendingSceneName);
		if (it == m_scenes.end()) return;

		if (m_currentScene)
		{
			m_currentScene->Finalize();
		}

		m_currentScene = it->second.get();
		m_currentSceneName = m_pendingSceneName;

		m_currentScene->Setup();
		m_currentScene->Initialize();
	}

	void SceneManager::RequestChangeScene(const std::string& sceneName)
	{
		m_pendingSceneName = sceneName;
		m_hasPendingSceneChange = true;
	}

	void SceneManager::FixedUpdate()
	{
		if (!m_currentScene) return;
		m_currentScene->FixedUpdate();
	}

	void SceneManager::Update(float deltaTime)
	{
		if (!m_currentScene) return;
		m_currentScene->Update(deltaTime);
	}

	void SceneManager::Render()
	{
		if (!m_currentScene) return;
		m_currentScene->Render(m_renderer);
	}
	Scene* SceneManager::GetCureentScene() const
	{
		return m_currentScene;
	}
}