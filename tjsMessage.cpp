//---------------------------------------------------------------------------
/*
	TJS2 Script Engine
	Copyright (C) 2000 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// message management
//---------------------------------------------------------------------------
#include "tjsCommHead.h"

#include "tjsMessage.h"
#include "tjsHashSearch.h"

namespace TJS
{

//---------------------------------------------------------------------------
// tTJSMessageMapper class
//---------------------------------------------------------------------------
class tTJSMessageMapper
{
	std::unordered_map<ttstr,tTJSMessageHolder*,tTJSStringHash> Hash;
	tjs_uint RefCount;

public:
	tTJSMessageMapper() {;}
	~tTJSMessageMapper() {;}

	void Register(const tjs_char *name, tTJSMessageHolder *holder)
	{
		Hash[ttstr(name)] = holder;
	}

	void Unregister(const tjs_char *name)
	{
		Hash.erase(ttstr(name));
	}

	bool AssignMessage(const tjs_char *name, const tjs_char *newmsg)
	{
		auto search = Hash.find(ttstr(name));
		if (search != Hash.end()) {
			search->second->AssignMessage(newmsg);
			return true;
		}
		return false;
	}

	bool AssignMessage(const tjs_char *name, const tjs_char *newmsg, tjs_uint len)
	{
		auto search = Hash.find(ttstr(name));
		if(search!=Hash.end())
		{
			search->second->AssignMessage(newmsg,len);
			return true;
		}
		return false;
	}

	bool Get(const tjs_char *name, ttstr &str)
	{
		auto search = Hash.find(ttstr(name));
		if(search!=Hash.end())
		{
			str = (const tjs_char *)(*(search->second));
			return true;
		}
		return false;
	}

	ttstr CreateMessageMapString();

} static * TJSMessageMapper = NULL;
static int TJSMessageMapperRefCount = 0;
//---------------------------------------------------------------------------
ttstr tTJSMessageMapper::CreateMessageMapString()
{
	ttstr script;

	for (const auto& pair : Hash) {
		script += TJS_W("\tr(\"");
		script += pair.first.EscapeC();
		script += TJS_W("\", \"");
		script += ttstr(pair.second).EscapeC();
#ifdef TJS_TEXT_OUT_CRLF
		script += TJS_W("\");\r\n");
#else
		script += TJS_W("\");\n");
#endif
	}
	return script;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJSAddRefMessageMapper()
{
	if(TJSMessageMapper)
	{
		TJSMessageMapperRefCount++;
	}
	else
	{
		TJSMessageMapper = new tTJSMessageMapper;
		TJSMessageMapperRefCount = 1;
	}
}
//---------------------------------------------------------------------------
void TJSReleaseMessageMapper()
{
	if(TJSMessageMapper)
	{
		TJSMessageMapperRefCount--;
		if(TJSMessageMapperRefCount == 0)
		{
			delete TJSMessageMapper;
			TJSMessageMapper = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void TJSRegisterMessageMap(const tjs_char *name, tTJSMessageHolder *holder)
{
	if(TJSMessageMapper) TJSMessageMapper->Register(name, holder);
}
//---------------------------------------------------------------------------
void TJSUnregisterMessageMap(const tjs_char *name)
{
	if(TJSMessageMapper) TJSMessageMapper->Unregister(name);
}
//---------------------------------------------------------------------------
bool TJSAssignMessage(const tjs_char *name, const tjs_char *newmsg)
{
	if(TJSMessageMapper) return TJSMessageMapper->AssignMessage(name, newmsg);
	return false;
}
//---------------------------------------------------------------------------
ttstr TJSCreateMessageMapString()
{
	if(TJSMessageMapper) return TJSMessageMapper->CreateMessageMapString();
	return TJS_W("");
}
//---------------------------------------------------------------------------
ttstr TJSGetMessageMapMessage(const tjs_char *name)
{
	if(TJSMessageMapper)
	{
		ttstr ret;
		if(TJSMessageMapper->Get(name, ret)) return ret;
		return ttstr();
	}
	return ttstr();
}
//---------------------------------------------------------------------------
}

