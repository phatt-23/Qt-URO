//
// Created by phatt on 4/7/25.
//

#pragma once

#include "QtWidgets.h"


class IService : QObject {
    Q_OBJECT
public:
    IService() {}
    ~IService() override {}
};


template <typename T>
concept RefDerivedFromIService = requires
{
    typename T::element_type;
    requires std::derived_from<typename T::element_type, IService>;
};


