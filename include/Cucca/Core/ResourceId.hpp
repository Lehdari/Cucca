/**
    Cucca Game Engine - Core - ResourceId.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-29
**/


#ifndef CUCCA_CORE_RESOURCEID_HPP
#define CUCCA_CORE_RESOURCEID_HPP


#include <string>


namespace Cucca {

    //  Structs and classes
    class ResourceId {
    public:
        ResourceId(void);
        ResourceId(const std::string& name);
        ResourceId(const char* name);
        ResourceId(const std::string& name, long id);
        ResourceId(const char* name, long id);

        bool operator==(const ResourceId& other);
        bool operator!=(const ResourceId& other);

        operator bool() const;

        void setName(const std::string& name);
        void setName(const char* name);
        void setId(long id);

        const std::string& name(void) const;
        const long id(void) const;

    private:
        std::string name_;
        long id_;
    };

} // namespace Cucca

namespace std {

    //  hash function specialization for ResourceId
    template <>
    struct hash<Cucca::ResourceId> {
        std::size_t operator()(const Cucca::ResourceId& resourceId) const {
            return (hash<std::string>()(resourceId.name()) >> 1) ^ (hash<int>()(resourceId.id()) << 1);
        }
    };

} // namespace std


#endif // CUCCA_CORE_RESOURCEID_HPP
