//---------------------------------------------------------------------------
/*
	TJS2 Script Engine
	Copyright (C) 2000 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Math.RandomGenerator implementation
//---------------------------------------------------------------------------

#ifndef tjsRandomGeneratorH
#define tjsRandomGeneratorH

#include <random>
#include "tjsNative.h"


namespace TJS
{
//---------------------------------------------------------------------------
class tTJSNI_RandomGenerator : public tTJSNativeInstance
{
public:
	tTJSNI_RandomGenerator();
    ~tTJSNI_RandomGenerator();
private:
	std::mt19937_64 *Generator;

public:
	iTJSDispatch2 * Serialize();

	void Randomize(tTJSVariant ** param, tjs_int numparams);
	double Random();
	tjs_uint32 Random32();
	tjs_int64 Random63();
	tjs_int64 Random64();
};
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
class tTJSNC_RandomGenerator : public tTJSNativeClass
{
public:
	tTJSNC_RandomGenerator();

	static tjs_uint32 ClassID;

private:
	tTJSNativeInstance *CreateNativeInstance();
};
//---------------------------------------------------------------------------
} // namespace TJS

#endif
