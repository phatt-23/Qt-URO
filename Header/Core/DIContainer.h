//
// Created by phatt on 4/7/25.
//

#ifndef DICONTAINER_H
#define DICONTAINER_H


#include "IService.h"
#include "StdLib.h"


/// Dependency Injection Container
/// supporting only singleton services.
class DIContainer final
{
public:
    DIContainer() = default;
    ~DIContainer() = default;

    template <typename RefType>
    requires std::derived_from<typename RefType::element_type, IService>
    void AddSingleton(RefType service)
    {
        using ServiceType = typename RefType::element_type;
        const char* key = typeid(ServiceType).name();
        m_Services[key] = std::static_pointer_cast<IService>(service);
    }

    template <typename ServiceType>
    requires std::derived_from<ServiceType, IService>
    Ref<ServiceType> GetService()
    {
        const char* key = typeid(ServiceType).name();  // or hash_code()
        return std::static_pointer_cast<ServiceType>(m_Services[key]);
    }

private:
    // is string just for easier debug, could just be a hash_code of a typeid
    std::unordered_map<std::string, Ref<IService>> m_Services;
};



#endif //DICONTAINER_H
