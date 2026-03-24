#pragma once
#include "Core.hpp"

namespace PT
{
class Application;

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void Update() = 0;
    virtual void OnEvent(class Event& event) = 0;
    virtual void UpdateGUI() = 0;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

    PT_INLINE void SetID(TypeIDptr id)
    {
        m_id = id;
    }

    [[nodiscard]] PT_INLINE constexpr TypeIDptr GetIDptr()
    {
        return m_id;
    }

private:
    TypeIDptr m_id;
};

class LayerStack
{
public:
    template<typename TLayer>
    PT_INLINE std::weak_ptr<TLayer> GetLayer()
    {
        const auto layer = std::find_if(m_layers.begin(), m_layers.end(),
            [](const auto& layer)
            {
                return layer->GetIDptr() == GetTypeIDptr<TLayer>();
            }
        );

        if(layer != m_layers.end())
        {
            return static_pointer_cast<TLayer>(*layer);
        }
        return {};
    }

    template<typename TLayer, typename ... TArgs>
    PT_INLINE std::shared_ptr<TLayer> AddLayer(TArgs&&... args)
    {
        const std::weak_ptr<Layer> layer = GetLayer<TLayer>();

        if(layer.lock())
        {
            CORE_LOG_WARNING("Trying to add an existing layer to the app");
            return nullptr;
        }

        std::shared_ptr<TLayer> createdLayer{ std::make_shared<TLayer>(std::forward<TArgs>(args)...) };
        createdLayer->SetID(GetTypeIDptr<TLayer>());
        createdLayer->OnAttach();
        m_layers.push_back(createdLayer);
        return createdLayer;
    }

    template<typename TLayer>
    PT_INLINE void RemoveLayer()
    {
        m_layers.erase(std::remove_if(m_layers.begin(), m_layers.end(),
            [](const auto& layer)
            {
                bool isRemove = layer->GetIDptr() == GetTypeIDptr<TLayer>();
                if(isRemove)
                {
                    layer->OnDetach();
                }
                return isRemove;
            }
        ));
    }

    PT_INLINE void ClearLayers()
    {
        for(auto layer = m_layers.rbegin(); layer != m_layers.rend(); layer++)
        {
            layer->get()->OnDetach();
        }

        m_layers.clear();
    }

    PT_INLINE std::vector<std::shared_ptr<Layer>>& GetLayers()
    {
        return m_layers;
    }

private:
    std::vector<std::shared_ptr<Layer>> m_layers;
};

}
