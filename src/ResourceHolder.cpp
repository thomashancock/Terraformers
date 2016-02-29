#include "ResourceHolder.hpp"

/* Public Member Functions */

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id
) {
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id
) const {
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(
	Identifier id,
	const std::string& filename,
	const Parameter& secondParam
) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam)) { // Texture loaded here
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

/* Private Member Functions */