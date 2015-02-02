/**
    Cucca Game Engine - Core - BinaryInitializer_File.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    BinaryInitializer_File is a initializer for Binary resources which
    loads the binary from external file.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-01
**/


#ifndef CUCCA_CORE_BINARYINITIALIZER_FILE_HPP
#define CUCCA_CORE_BINARYINITIALIZER_FILE_HPP


#include "ResourceInitializer.hpp"
#include "Binary.hpp"


namespace Cucca {

    CUCCA_RESOURCEINITIALIZER(BinaryInitializer_File, Binary) {
    public:
        BinaryInitializer_File(const std::string& fileName);

        void init(Binary& resource,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(Binary& resource);

    private:
        std::string fileName_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_BINARYINITIALIZER_FILE_HPP
