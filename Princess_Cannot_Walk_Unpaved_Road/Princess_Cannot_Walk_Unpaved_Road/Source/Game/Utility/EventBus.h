#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace Bisang
{
    class EventBus
    {
    public:
        using ListenerId = std::size_t;

        template <typename EventT>
        ListenerId Subscribe(std::function<void(const EventT&)> callback)
        {
            const ListenerId id = ++m_nextId;

            auto wrapper = [callback](const void* event)
                {
                    callback(*static_cast<const EventT*>(event));
                };

            m_listeners[typeid(EventT)].push_back({ id, wrapper });
            return id;
        }

        template <typename EventT>
        void Publish(const EventT& event)
        {
            auto it = m_listeners.find(typeid(EventT));
            if (it == m_listeners.end())
                return;

            for (auto& listener : it->second)
            {
                listener.callback(&event);
            }
        }

        template <typename EventT>
        void Unsubscribe(ListenerId id)
        {
            auto it = m_listeners.find(typeid(EventT));
            if (it == m_listeners.end())
                return;

            auto& listeners = it->second;

            listeners.erase(
                std::remove_if(
                    listeners.begin(),
                    listeners.end(),
                    [id](const Listener& listener)
                    {
                        return listener.id == id;
                    }),
                listeners.end());
        }

    private:
        struct Listener
        {
            ListenerId id;
            std::function<void(const void*)> callback;
        };

        ListenerId m_nextId = 0;
        std::unordered_map<std::type_index, std::vector<Listener>> m_listeners;
    };
}