//---------------------------------------------------------------------------
/*
	TJS2 Script Engine
	Copyright (C) 2000 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// An Implementation of Hash Searching
//---------------------------------------------------------------------------
#ifndef HashSearchH
#define HashSearchH

#include "tjs.h"

#define TJS_HS_DEFAULT_HASH_SIZE 64
#define TJS_HS_HASH_USING	0x1
#define TJS_HS_HASH_LV1	0x2

// #define TJS_HS_DEBUG_CHAIN  // to debug chain algorithm

namespace TJS
{
struct tTJSStringHash {
	std::size_t operator()(const TJS::tTJSString &str) const {
		return std::hash<std::wstring>()(str.c_str());
	}
};

template<class Key, class T, class Hash = std::hash<Key> >
class HashCache : public std::unordered_map<Key, T, Hash> {
	typedef std::unordered_map<Key, T, Hash> inherited;
	tjs_uint MaxCount;

public:
	explicit HashCache(tjs_uint maxcount) { MaxCount = maxcount; }

	void Add(const Key &key, const T &value) {
		this->insert_or_assign(key,value);
		while (this->size() > MaxCount) {
			this->erase(this->begin());
		}
	}
};

//---------------------------------------------------------------------------
} // namespace TJS
//---------------------------------------------------------------------------

#endif

