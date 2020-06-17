#include <iostream>
#include <map>
#include <memory>
#include <utility>   
#pragma once

using namespace std;
template <class K, class V>
class CachedMap {

public:
	CachedMap() {
		//std::map<K, std::shared_ptr<V>> CachedMap::map1;
		//std::map<K, std::weak_ptr<V>> CachedMap::map2;
	}
	CachedMap(K k, V v)
	{
		shared_ptr<V> Sp= make_shared<V>(v);
		weak_ptr<V> Wp=Sp;
		map1[k] = Sp;
		map2[k] = Wp;

	}

	void erase(const K& key)
	{
		for (auto const& val : map1)
		{
			if (val.first == key) {
				
				map1.erase(val.first);
				cout << "deleted!" << endl;
				return;
			}
		}

		throw "ObjectNotExistException";

	}
	void add(const K& key, const V& value)
	{
		for (const auto& val : map1)
		{
			if (val.first == key) {
				throw "DuplicateKeyException";
				
			}
		}

		shared_ptr<V> Sp = make_shared<V>(value);
		map1[key] = Sp;
		


	}

	shared_ptr<V> get(const K& key)
	{
		
		for (const auto& val : map2)
		{
			weak_ptr<V> sec = val.second;
			if (val.first == key) {
				if (sec.expired())
					return sec.lock();
				map2.erase(key);
				return nullptr;
			}

		}
		for (const auto& val : map1)
		{
			weak_ptr<V> sec = val.second;
			if (val.first == key) {
				map2[key] = val.second;
				return sec.lock();
			}
		}

		return nullptr;


	}
private:
	std::map<K, std::shared_ptr<V>> map1;
	std::map<K, std::weak_ptr<V>> map2;
	

};

