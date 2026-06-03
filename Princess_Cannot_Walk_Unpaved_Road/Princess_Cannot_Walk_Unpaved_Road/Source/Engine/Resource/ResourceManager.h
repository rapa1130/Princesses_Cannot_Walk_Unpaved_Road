#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <type_traits>

namespace Bisang
{
    class IResource;

    /**
     * @brief 게임 리소스를 로드하고 관리하는 매니저 클래스.
     *
     * 리소스 타입과 파일 경로를 기준으로 리소스를 캐싱한다.
     * 이미 로드된 리소스는 재사용하며, 동일한 리소스의 중복 로드를 방지한다.
     */
    class ResourceManager
    {
    public:

        /**
         * @brief 지정한 경로의 리소스를 로드한다.
         *
         * 이미 동일한 타입과 경로의 리소스가 로드되어 있으면
         * 기존 리소스를 반환한다.
         *
         * @tparam T 로드할 리소스 타입
         * @param[in] path 리소스 파일 경로
         *
         * @return 로드된 리소스 객체
         * @return 로드 실패 시 nullptr
         */
        template<typename T>
        std::shared_ptr<T> Load(const std::wstring& path);

        /**
         * @brief 이미 로드된 리소스를 가져온다.
         *
         * 리소스를 새로 로드하지 않으며,
         * 캐시에 존재하는 리소스만 반환한다.
         *
         * @tparam T 조회할 리소스 타입
         * @param[in] path 리소스 파일 경로
         *
         * @return 리소스 객체
         * @return 존재하지 않으면 nullptr
         */
        template<typename T>
        std::shared_ptr<T> Get(const std::wstring& path);

        /**
         * @brief 모든 리소스를 제거한다.
         *
         * ResourceManager가 보유한 모든 리소스 캐시를 비운다.
         * 다른 곳에서 참조 중인 shared_ptr이 없다면 리소스는 해제된다.
         */
        void Clear()
        {
            m_resources.clear();
        }

    private:

        /**
         * @brief 타입별 리소스 캐시.
         *
         * 1차 키 : 리소스 타입
         * 2차 키 : 리소스 파일 경로
         * 값 : 리소스 객체
         */
        std::unordered_map<
            std::type_index,
            std::unordered_map<std::wstring, std::shared_ptr<IResource>>
        > m_resources;
    };

    template<typename T>
    std::shared_ptr<T> ResourceManager::Load(const std::wstring& path)
    {
        static_assert(std::is_base_of_v<IResource, T>,
            "T must inherit from IResource");

        auto type = std::type_index(typeid(T));
        auto& resourceMap = m_resources[type];

        auto iter = resourceMap.find(path);
        if (iter != resourceMap.end())
        {
            return std::static_pointer_cast<T>(iter->second);
        }

        auto resource = std::make_shared<T>();

        if (!resource->LoadFromFile(path))
        {
            return nullptr;
        }

        resourceMap[path] = resource;
        return resource;
    }

    template<typename T>
    std::shared_ptr<T> ResourceManager::Get(const std::wstring& path)
    {
        static_assert(std::is_base_of_v<IResource, T>,
            "T must inherit from IResource");

        auto type = std::type_index(typeid(T));
        auto typeIter = m_resources.find(type);

        if (typeIter == m_resources.end())
        {
            return nullptr;
        }

        auto& resourceMap = typeIter->second;
        auto iter = resourceMap.find(path);

        if (iter == resourceMap.end())
        {
            return nullptr;
        }

        return std::static_pointer_cast<T>(iter->second);
    }
}