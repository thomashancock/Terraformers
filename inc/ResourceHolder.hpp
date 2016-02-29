#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <cassert>

template <typename Resource, typename Identifier> 
class ResourceHolder{
	public:
		Resource& get(
			Identifier id
		);
		const Resource& get(
			Identifier id
		) const;

		template <typename Parameter>
		void load(
			Identifier id,
			const std::string& filename,
			const Parameter& secondParam
		);

	private:
		std::map<Identifier,std::unique_ptr<Resource>> m_resourceMap;
};

#endif /* RESOURCEHOLDER_H */