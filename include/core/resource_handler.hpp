#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

// Implementation of member functions
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    // Create a new resource
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();

    // Example load function; replace with actual resource loading logic
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        throw std::runtime_error("ResourceHolder::get - Resource not found");
    }
    return *(found->second);
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        throw std::runtime_error("ResourceHolder::get - Resource not found");
    }
    return *(found->second);
}

#endif // RESOURCEHOLDER_HPP
