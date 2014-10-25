/**
    Cucca Game Engine - Core - ResourceBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceBase class acts as a base class for templated Resources.
    It has a type identifier system similar to Node class. @see Node.hpp

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-26
**/


#ifndef CUCCA_CORE_RESOURCEBASE_HPP
#define CUCCA_CORE_RESOURCEBASE_HPP


namespace Cucca {
    class ResourceBase {
    public:
        //  Standard constructors/destructors
        ResourceBase(void) :
            resourceType_(-1)
            {}
        virtual ~ResourceBase(void) {}

        //  Get resource type. Will return -1 if no resource is stored.
        int getResourceType(void) const;

        //  Resource type id system. Similar to the one in the Node class.
        template<typename ResourceType_T>
        static int getResourceTypeId(void) {
            static unsigned numResourceTypes__ = 0;
            static int resourceTypeId__ = numResourceTypes__++;
            return resourceTypeId__;
        }

    protected:
        /*  Template constructor
            Constructors cannot be called with template parameters, that's why
            an argument is required for automatic deduction. */
        template<typename ResourceType_T>
        ResourceBase(const ResourceType_T& resource) :
            resourceType_(getResourceTypeId<ResourceType_T>())
            {}

        //  Stored resource type identifier
        int resourceType_;
    };
}


#endif // CUCCA_CORE_RESOURCEBASE_HPP
