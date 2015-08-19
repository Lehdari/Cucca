/**
    Cucca Game Engine - Core - ResourcePointer.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    ResourcePointer is a shared smart pointer used in cooperation with
    ResourceManager. Its main purpose is to enable ResourceManager to
    perform garbage collection.

    In addition to get() member function it also provides overloads for
    asterisk(*) and arrow(->) operators to gain access to the Resource
    itself.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#ifndef CUCCA_CORE_RESOURCEPOINTER_HPP
#define CUCCA_CORE_RESOURCEPOINTER_HPP


namespace Cucca {

    //  Forward declarations
    class ResourceId;

    template<typename ResourceIdType_T>
    class ResourceManager;


    //  Structs/classes
    template<typename ResourceType_T, typename ResourceIdType_T = ResourceId>
    class ResourcePointer {
    public:
        ResourcePointer(void);
        ResourcePointer(ResourceType_T* resource,
                        const ResourceIdType_T& resourceId,
                        ResourceManager<ResourceIdType_T>* resourceManager,
                        void (ResourceManager<ResourceIdType_T>::*outOfReferences)(ResourcePointer<ResourceType_T, ResourceIdType_T>&),
                        int* referenceCount);
        ResourcePointer(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer);
        ResourcePointer(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer);
        ~ResourcePointer(void);

        ResourcePointer<ResourceType_T, ResourceIdType_T>& operator=(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer);
        ResourcePointer<ResourceType_T, ResourceIdType_T>& operator=(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer);

        ResourceType_T& operator*(void);
        ResourceType_T* operator->(void);
        const ResourceType_T* operator->(void) const;

        //  get resource pointer
        ResourceType_T* get(void);
        //  get resource id
        const ResourceIdType_T& getId(void);

        //  unload / reload the resource
        void unload(void);
        void reload(void);

    private:
        ResourceType_T* resource_;
        ResourceIdType_T resourceId_;

        ResourceManager<ResourceIdType_T>* resourceManager_;
        void (ResourceManager<ResourceIdType_T>::*outOfReferences_)(ResourcePointer<ResourceType_T, ResourceIdType_T>&);

        int* referenceCount_;
    };


    //  Member definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(void) :
        resource_(nullptr),
        resourceId_(),
        resourceManager_(nullptr),
        outOfReferences_(nullptr),
        referenceCount_(nullptr)
    {}

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(ResourceType_T* resource,
                                                                       const ResourceIdType_T& resourceId,
                                                                       ResourceManager<ResourceIdType_T>* resourceManager,
                                                                       void (ResourceManager<ResourceIdType_T>::*outOfReferences)(ResourcePointer<ResourceType_T, ResourceIdType_T>&),
                                                                       int* referenceCount) :
        resource_(resource),
        resourceId_(resourceId),
        resourceManager_(resourceManager),
        outOfReferences_(outOfReferences),
        referenceCount_(referenceCount)
    {
        if (referenceCount_)
            ++*referenceCount_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::ResourcePointer(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer) :
        resource_(resourcePointer.resource_),
        resourceId_(resourcePointer.resourceId_),
        resourceManager_(resourcePointer.resourceManager_),
        outOfReferences_(resourcePointer.outOfReferences_),
        referenceCount_(resourcePointer.referenceCount_)
    {
        if (referenceCount_)
            ++*referenceCount_;
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
        resourcePointer.outOfReferences_ = nullptr;
        resourcePointer.referenceCount_ = nullptr;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>::~ResourcePointer(void) {
        if (resource_ && --*referenceCount_ == 0) // note: can go to negative values
            (resourceManager_->*outOfReferences_)(*this);
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>& ResourcePointer<ResourceType_T, ResourceIdType_T>::operator=(const ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer) {
        if (resource_ && --*referenceCount_ == 0) // note: can go to negative values
            (resourceManager_->*outOfReferences_)(*this);

        resource_ = resourcePointer.resource_;
        resourceId_ = resourcePointer.resourceId_;
        resourceManager_ = resourcePointer.resourceManager_;
        outOfReferences_ = resourcePointer.outOfReferences_;
        referenceCount_ = resourcePointer.referenceCount_;

        if (referenceCount_)
            ++*referenceCount_;

        return *this;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T>& ResourcePointer<ResourceType_T, ResourceIdType_T>::operator=(ResourcePointer<ResourceType_T, ResourceIdType_T>&& resourcePointer) {
        if (resource_ && --*referenceCount_ == 0) // note: can go to negative values
            (resourceManager_->*outOfReferences_)(*this);

        resource_ = resourcePointer.resource_;
        resourceId_ = resourcePointer.resourceId_;
        resourceManager_ = resourcePointer.resourceManager_;
        outOfReferences_ = resourcePointer.outOfReferences_;
        referenceCount_ = resourcePointer.referenceCount_;

        resourcePointer.resource_ = nullptr;
        resourcePointer.resourceManager_ = nullptr;
        resourcePointer.outOfReferences_ = nullptr;
        resourcePointer.referenceCount_ = nullptr;

        return *this;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourceType_T& ResourcePointer<ResourceType_T, ResourceIdType_T>::operator*(void) {
        return *resource_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourceType_T* ResourcePointer<ResourceType_T, ResourceIdType_T>::operator->(void) {
        return resource_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    const ResourceType_T* ResourcePointer<ResourceType_T, ResourceIdType_T>::operator->(void) const {
        return resource_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    ResourceType_T* ResourcePointer<ResourceType_T, ResourceIdType_T>::get(void) {
        return resource_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    const ResourceIdType_T& ResourcePointer<ResourceType_T, ResourceIdType_T>::getId(void) {
        return resourceId_;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    void ResourcePointer<ResourceType_T, ResourceIdType_T>::unload(void) {
        if (resource_ && --*referenceCount_ == 0) // note: can go to negative values
            (resourceManager_->*outOfReferences_)(*this);

        resource_ = nullptr;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    void ResourcePointer<ResourceType_T, ResourceIdType_T>::reload(void) {
        *this = resourceManager_->getResource(resourceId_);
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEPOINTER_HPP
