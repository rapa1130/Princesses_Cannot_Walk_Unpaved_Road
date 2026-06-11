#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include <string>
#include <cstdint>
#include <vector>
#include <cstddef>
#include <functional>
#include "Engine/Core/GameContext.h"

namespace Bisang
{
	class RenderableComponent;
    class Collider;
	class GameObject;
    class Renderer;
    class IPrefab;
    

	class Scene
	{
    public:

        /**
         * @brief 씬을 생성한다.
         *
         * 씬 이름과 엔진 매니저들을 저장한다.
         *
         * @param[in] sceneName 씬 이름
         * @param[in] context 씬에서 필요한 각종 매니저들
         */
        Scene(std::string sceneName, GameContext* context);

        /**
         * @brief 씬을 소멸한다.
         */
        virtual ~Scene();

        std::string GetSceneName() { return m_sceneName; }

        /**
        * @brief 프리팹으로 게임 오브젝트 생성을 예약한다. [지연 생성]
        *
        * @param[in] prefabName 프리팹 팩토리에 등록된 프리팹 이름
        *
        */

        ResourceManager* GetResourceManager() { return m_context->resourceManager; }
        InputManager* GetInputManager() { return m_context->inputManager; }


        //*************************************************
        // 생명주기
        //************************************************* 

        /**
         * @brief 씬 진입 시 초기화 작업을 수행한다.
         *
         * 초기 상태를 설정한다.
         */
        virtual void Initialize() = 0;

        /**
         * @brief 씬 종료 시 정리 작업을 수행한다.
         *
         * 씬이 사용하던 자원을 정리하고
         * 종료 처리를 수행한다.
         */
        virtual void Finalize() = 0;

        /**
         * @brief 씬을 구성한다.
         *
         * 씬에 필요한 게임 오브젝트와 컴포넌트를 생성한다.
         */
        virtual void Setup() = 0;

        /**
         * @brief 씬 진입 시 호출된다.
         */
        virtual void OnEnter() = 0;

        /**
         * @brief 씬 종료 시 호출된다.
         */
        virtual void OnExit() = 0;


        //*************************************************
        // 업데이트
        //************************************************* 

        /**
         * @brief 모든 컴포넌트의 Update를 수행한다.
         *
         * 활성화된 컴포넌트에 대해 Start를 최초 1회 호출한 뒤
         * Update를 수행한다.
         *
         * @param[in] deltaTime 이전 프레임과의 시간 간격(초)
         */
        void Update(float deltaTime);

        /**
         * @brief 모든 컴포넌트의 FixedUpdate를 수행한다.
         *
         * 활성화된 컴포넌트에 대해 Start를 최초 1회 호출한 뒤
         * FixedUpdate를 수행한다.
         */
        void FixedUpdate();


        //*************************************************
        // 렌더링
        //************************************************* 

        /**
         * @brief 모든 렌더링 컴포넌트를 렌더링한다.
         */
        void Render(Renderer* renderer);


        //*************************************************
        // 게임 오브젝트
        //************************************************* 
        //##########
        // 등록
        //##########
        /**
         * @brief 게임 오브젝트를 씬에 등록한다. [지연 등록]
         *
         * @param[in] prefabName 프리팹 이름
         *
         * @return GameObject* 게임 오브젝트 포인터
         */
        GameObject* Instantiate(std::string prefabName);

        /**
         * @brief 게임 오브젝트를 씬에 등록한다. [즉시 등록]
         *
         * @param[in] obj 게임 오브젝트 유니크 포인터
         *
         */
        void AddGameObject(std::unique_ptr<GameObject> obj);

        /**
         * @brief 게임 오브젝트를 씬에 등록한다. [즉시 등록]
         *
         * @param[in]  prefabName 프리팹 팩토리에 등록된 프리팹 이름
         *
         */
        void AddGameObject(std::string prefabName);

        /**
         * @brief 오브젝트 씬 등록 절차를 수행한다.
         *
         * @param[in] obj 등록할 오브젝트 포인터
         *
         */
        void RegisterToScene(GameObject* obj);

        /**
         * @brief 지연 추가 큐를 처리한다.
         *
         * 추가 예정 게임 오브젝트를 추가한다.
         */
        void ProcessAddGameObjectQueue();

        //##########
        // 삭제
        //##########
        /**
         * @brief 게임 오브젝트 삭제를 예약한다. [지연 삭제]
         *
         * 즉시 삭제하지 않고 지연 삭제 큐에 등록한다.
         *
         * @param[in] id 삭제할 게임 오브젝트 ID
         */
        void DestroyGameObject(uint64_t id);

        /**
         * @brief 게임 오브젝트를 삭제한다. [즉시 삭제]
         *
         * 삭제 예정 게임 오브젝트를 제거하고 메모리를 해제한다.
         */
        void DeleteGameObject(uint64_t id);

        /**
         * @brief 지연 삭제 큐를 처리한다.
         *
         * 삭제 예정 게임 오브젝트를 제거하고 메모리를 해제한다.
         */
        void ProcessDeleteGameObjectQueue();

        /**
         * @brief 오브젝트 씬 삭제 절차를 수행한다.
         *
         * @param[in] obj 삭제할 오브젝트 id
         *
         */
        void UnregisterFromScene(uint64_t id);

        //##########
        // 조회
        //##########
        /**
         * @brief ID로 게임 오브젝트를 조회한다.
         *
         * @param[in] id 게임 오브젝트 ID
         *
         * @return 조회된 게임 오브젝트
         * @return 존재하지 않을 경우 nullptr
         */
        GameObject* GetGameObject(uint64_t id);

        /**
         * @brief 이름으로 게임 오브젝트를 조회한다.
         *
         * @param[in] name 게임 오브젝트 이름
         *
         * @return 조회된 게임 오브젝트
         * @return 존재하지 않을 경우 nullptr
         */
        GameObject* FindGameObjectByName(std::string name);


        //*************************************************
        // 렌더링 컴포넌트
        //************************************************* 
        /**
         * @brief 렌더링 컴포넌트를 등록한다.
         *
         * 이미 등록된 컴포넌트는 중복 등록되지 않는다.
         * 등록 후 OrderInLayer 기준으로 정렬된다.
         *
         * @param[in] component 등록할 렌더링 컴포넌트
         */
        void AddRenderableComponent(RenderableComponent* component);

        /**
         * @brief 렌더링 컴포넌트 등록을 해제한다.
         *
         * @param[in] component 제거할 렌더링 컴포넌트
         */
        void RemoveRenderableComponent(RenderableComponent* component);


        //*************************************************
        // 콜라이더 컴포넌트
        //************************************************* 
         /** @brief 콜라이더 컴포넌트를 등록한다.
         *
         * 이미 등록된 컴포넌트는 중복 등록되지 않는다.
         *
         * @param[in] collider 등록할 콜라이더 컴포넌트
         */
        void AddCollider(Collider* collider);

        /**
         * @brief 콜라이더 컴포넌트 등록을 해제한다.
         *
         * @param[in] collider 제거할 콜라이더 컴포넌트
         */
        void RemoveCollider(Collider* collider);
        
        /**
         * @brief 등록된 콜라이더들을 순회하면서 충돌 처리를 한다.
         */
        void CheckCollisions();


	protected:
		std::string m_sceneName = "";                   // 씬이름

        GameContext* m_context = nullptr;              
        PrefabFactory* m_prefabFactory = nullptr;

		//*************************************************
		// 게임 오브젝트 관리
		//************************************************* 
		uint64_t m_GameObjectCount = 0;                                            // 오브젝트 개수, ID에 사용
		std::unordered_map<uint64_t, std::unique_ptr<GameObject>> m_gameObjects;   // 오브젝트 맵
        std::queue<std::unique_ptr<GameObject>> m_AddGameObjectQueue;              // 지연 추가 오브젝트
		std::queue<uint64_t> m_DeleteGameObjectQueue;                              // 지연 삭제 오브젝트


		//*************************************************
		// 렌더링 컴포넌트
		//************************************************* 
		std::vector<RenderableComponent*> m_renderableComponents;   // 렌더링 컴포넌트 ( 레이어 순서 오름차순 정렬 되어있음 )

        //*************************************************
        // 콜라이더
        //************************************************* 
        struct CollisionPair
        {
            Collider* lhs;
            Collider* rhs;

            CollisionPair(Collider* a, Collider* b)
            {
                if (std::less<Collider*>{}(a, b))
                {
                    lhs = a;
                    rhs = b;
                }
                else
                {
                    lhs = b;
                    rhs = a;
                }
            }

            bool operator==(const CollisionPair& other) const
            {
                return lhs == other.lhs &&
                    rhs == other.rhs;
            }
        };

        struct CollisionPairHash
        {
            size_t operator()(const CollisionPair& pair) const
            {
                size_t h1 = std::hash<Collider*>()(pair.lhs);
                size_t h2 = std::hash<Collider*>()(pair.rhs);

                return h1 ^ (h2 << 1);
            }
        };

        std::vector<Collider*> m_colliders;
        std::unordered_set<CollisionPair, CollisionPairHash> m_prevCollisions;
        std::unordered_set<CollisionPair, CollisionPairHash> m_currentCollisions;
	};

}