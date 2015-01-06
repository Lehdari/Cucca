/**
    Cucca Game Engine - Core - StorageVector.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceManager class defines an interface for managing resources.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-01
**/


#ifndef CUCCA_CORE_STORAGEVECTOR_HPP
#define CUCCA_CORE_STORAGEVECTOR_HPP


#include <initializer_list>


namespace Cucca {

    template<typename T, typename... Args>
    class StorageVector { };

    template<typename T, unsigned S, typename... Args>
    class StorageVector<T, S, Args...> {
    public:
        StorageVector(std::initializer_list<StorageVector<T, Args...>> list) :
            data_(list)
        {}

        StorageVector(void) {};

        StorageVector<T, Args...>& operator[](unsigned n) {
            return data_[n];
        }

    private:
        StorageVector<T, Args...> data_[S];
    };

    template<typename T>
    class StorageVector<T, unsigned S> {
    public:
        StorageVector(std::initializer_list<T> list) :
            data_(list)
        {}

        StorageVector(void) {};

        T& operator[](unsigned n) {
            return data_[n];
        }

    private:
        T data_[S];
    };

} // namespace Cucca


#endif // CUCCA_CORE_STORAGEVECTOR_HPP
