//
// Created by phatt on 4/7/25.
//

#ifndef STDLIB_H
#define STDLIB_H

// STD LIBRARY
//
// Created by phatt on 2/8/25.
//

#include <format>
#include <iomanip>
#include <iostream>
#include <print>
#include <sstream>
#include <sstream>

#include <filesystem>
#include <fstream>
#include <ios>

#include <exception>
#include <source_location>
#include <stdexcept>

#include <memory>
#include <ranges>
#include <regex>
#include <span>
#include <thread>
#include <utility>

#include <algorithm>
#include <functional>
#include <optional>

#include <cfloat>
#include <cstdint>

#include <iterator>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <any>
#include <variant>

// SMART POINTERS

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
Ref<T> CreateRef(T* ptr)
{
    return std::make_shared<T>(ptr);
}

template<typename T, typename... Args>
Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
Scope<T> CreateScope(T* ptr)
{
    return std::make_unique<T>(ptr);
}


#endif //STDLIB_H
