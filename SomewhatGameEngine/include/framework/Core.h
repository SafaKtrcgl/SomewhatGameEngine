#pragma once

#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace SomewhatGameEngine
{
	//TODO: Development purposes only
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	template<typename T>
	using Set = std::unordered_set<T>;

	template<typename keyType, typename valueType, typename predicate = std::less<keyType>>
	using Map = std::map<keyType, valueType, predicate>;

	template<typename keyType, typename valueType, typename hasher = std::hash<keyType>>
	using Dictionary = std::unordered_map<keyType, valueType, hasher>;
}