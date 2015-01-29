/**
    Cucca Game Engine - Core - ResourceId.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-29
**/


#include "../../include/Core/ResourceId.hpp"


using namespace Cucca;


//  Member definitions
ResourceId::ResourceId(void) :
    name_(""),
    id_(-1)
{}

ResourceId::ResourceId(const std::string& name) :
    name_(name),
    id_(-1)
{}

ResourceId::ResourceId(const char* name) :
    name_(name),
    id_(-1)
{}

ResourceId::ResourceId(const std::string& name, long id) :
    name_(name),
    id_(id)
{}

ResourceId::ResourceId(const char* name, long id) :
    name_(name),
    id_(id)
{}

bool ResourceId::operator==(const ResourceId& other) {
    return name_ == other.name_ && id_ == other.id_;
}

bool ResourceId::operator!=(const ResourceId& other) {
    return !(*this == other);
}

ResourceId::operator bool() const {
    return name_.size() != 0;
}

void ResourceId::setName(const std::string& name) {
    name_ = name;
}

void ResourceId::setName(const char* name) {
    name_ = std::string(name);
}

void ResourceId::setId(long id) {
    id_ = id;
}

const std::string& ResourceId::name(void) const {
    return name_;
}

const long ResourceId::id(void) const {
    return id_;
}
