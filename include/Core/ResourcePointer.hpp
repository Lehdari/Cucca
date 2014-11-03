/**
    Cucca Game Engine - Core - ResourcePointer.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourcePointer is a shared smart pointer used in cooperation with
    ResourceManager. It provides an out of references callback to
    ResourceManager upon destruction.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-03
**/


#ifndef CUCCA_CORE_RESOURCEPOINTER_HPP
#define CUCCA_CORE_RESOURCEPOINTER_HPP


#include <iostream> // TEMP


namespace Cucca {

    template<typename ResourceIdType_T>
    class ResourceManager;

    template<typename ResourceType_T, typename ResourceIdType_T>
    class ResourcePointer {
    public:
        ResourcePointer(ResourceType_T* resource,
                        const ResourceIdType_T& resourceId,
                        ResourceManager<ResourceIdType_T>* resourceManager,
                        void (ResourceManager<ResourceIdType_T>::*outOfReferences)(const ResourceIdType_T&),
                        unsigned* referenceCount);
        ResourcePointer(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer);
        ResourcePointer(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer);
        ~ResourcePointer(void);

        ResourcePointer<ResourceType_T, ResourceIdType_T>& operator=(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer);
        ResourcePointer<ResourceType_T, ResourceIdType_T>& operator=(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer);

    private:
        ResourceType_T* resource_;
        ResourceIdType_T resourceId_;

        ResourceManager<ResourceIdType_T>* resourceManager_;
        void (ResourceManager<ResourceIdType_T>::*outOfReferences_)(const ResourceIdType_T&);

        unsigned* referenceCount_;
    };


    //  Member definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(ResourceType_T* resource,
                                                                       const ResourceIdType_T& resourceId,
                                                                       ResourceManager<ResourceIdType_T>* resourceManager,
                                                                       void (ResourceManager<ResourceIdType_T>::*outOfReferences)(const ResourceIdType_T& resourceId),
                                                                       unsigned* referenceCount) :
        resource_(resource),
        resourceId_(resourceId),
        resourceManager_(resourceManager),
        outOfReferences_(outOfReferences),
        referenceCount_(referenceCount)
    {
        ++*referenceCount_;
        std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer) :
        resource_(resourcePointer.resource_),
        resourceId_(resourcePointer.resourceId_),
        resourceManager_(resourcePointer.resourceManager_),
        outOfReferences_(resourcePointer.outOfReferences_),
        referenceCount_(resourcePointer.referenceCount_)
    {
        ++*referenceCount_;
        std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer) :
        resource_(resourcePointer.resource_),
        resourceId_(resourcePointer.resourceId_),
        resourceManager_(resourcePointer.resourceManager_),
        outOfReferences_(resourcePointer.outOfReferences_),
        referenceCount_(resourcePointer.referenceCount_)
    {
        resourcePointer.resource_ = nullptr;
        resourcePointer.resourceManager_ = nullptr;
        resourcePointer.referenceCount_ = nullptr;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::~ResourcePointer(void) {
        if (resource_) {
            if (--*referenceCount_ == 0)
                (resourceManager_->*outOfReferences_)(resourceId_);
            else // TEMP
                std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP
        }
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>& ResourcePointer<ResourceType_T, ResourceIdType_T>::operator=(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer) {
        if (--*referenceCount_ == 0)
            (resourceManager_->*outOfReferences_)(resourceId_);
        else // TEMP
            std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP

        resource_ = resourcePointer.resource_;
        resourceId_ = resourcePointer.resourceId_;
        resourceManager_ = resourcePointer.resourceManager_;
        outOfReferences_ = resourcePointer.outOfReferences_;
        referenceCount_ = resourcePointer.referenceCount_;
        ++*referenceCount_;
        std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP

        return *this;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>& ResourcePointer<ResourceType_T, ResourceIdType_T>::operator=(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer) {
        if (--*referenceCount_ == 0)
            (resourceManager_->*outOfReferences_)(resourceId_);
        else // TEMP
            std::cout << "Resource " << resourceId_ << " reference count: " << *referenceCount_ << std::endl; // TEMP

        resource_ = resourcePointer.resource_;
        resourceId_ = resourcePointer.resourceId_;
        resourceManager_ = resourcePointer.resourceManager_;
        outOfReferences_ = resourcePointer.outOfReferences_;
        referenceCount_ = resourcePointer.referenceCount_;

        resourcePointer.resource_ = nullptr;
        resourcePointer.resourceManager_ = nullptr;
        resourcePointer.referenceCount_ = nullptr;

        return *this;
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEPOINTER_HPP
