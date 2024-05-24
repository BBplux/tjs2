//---------------------------------------------------------------------------
/*
	TJS2 Script Engine
	Copyright (C) 2000-2005	 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Math.RandomGenerator implementation
//---------------------------------------------------------------------------
#include "tjsCommHead.h"


#include "tjsError.h"
#include "tjsRandomGenerator.h"
#include "tjsDictionary.h"
#include "tjsLex.h"


namespace TJS
{

//---------------------------------------------------------------------------
// tTJSNI_RandomGenerator : TJS Native Instance : RandomGenerator
//---------------------------------------------------------------------------
tTJSNI_RandomGenerator::tTJSNI_RandomGenerator()
{
	// C++ constructor
	Generator = NULL;
}
//---------------------------------------------------------------------------
tTJSNI_RandomGenerator::~tTJSNI_RandomGenerator()
{
	// C++ destructor
	if(Generator) delete Generator;
}
//---------------------------------------------------------------------------
void tTJSNI_RandomGenerator::Randomize(tTJSVariant **param, tjs_int numparams) {
	if (numparams == 0) {
		std::random_device rd;
		if (Generator) delete Generator, Generator = NULL;
		Generator = new std::mt19937_64(rd());
	} else if (numparams >= 1) {
		if (param[0]->Type() == tvtObject) {
			std::random_device rd;
			if (Generator) delete Generator, Generator = NULL;
			Generator = new std::mt19937_64(rd());
		} else {
			tjs_uint64 n = (tjs_int64) *param[0];
			if (Generator) delete Generator, Generator = NULL;
			Generator = new std::mt19937_64(n);
		}
	}
}
//---------------------------------------------------------------------------
iTJSDispatch2 * tTJSNI_RandomGenerator::Serialize()
{
	return NULL;
}
//---------------------------------------------------------------------------
double tTJSNI_RandomGenerator::Random()
{
	// returns double precision random value x, x is in 0 <= x < 1
	if(!Generator) return 0;
	std::uniform_real_distribution<double> dis(0, 1);
	return dis(*Generator);

}
//---------------------------------------------------------------------------
tjs_uint32 tTJSNI_RandomGenerator::Random32()
{
	// returns 63 bit integer random value
	if(!Generator) return 0;
	std::uniform_int_distribution<tjs_uint32> dis;
	return dis(*Generator);
}
//---------------------------------------------------------------------------
tjs_int64 tTJSNI_RandomGenerator::Random63()
{
	// returns 63 bit integer random value
	if(!Generator) return 0;
	std::uniform_int_distribution<tjs_int64> dis;
	return dis(*Generator);
}
//---------------------------------------------------------------------------
tjs_int64 tTJSNI_RandomGenerator::Random64()
{
	// returns 64 bit integer random value
	if(!Generator) return 0;
	std::uniform_int_distribution dis(std::numeric_limits<tjs_int64>::min(), std::numeric_limits<tjs_int64>::max());
	return dis(*Generator);
}
//---------------------------------------------------------------------------













//---------------------------------------------------------------------------
// tTJSNC_RandomGenerator : TJS Native Class : RandomGenerator
//---------------------------------------------------------------------------
tjs_uint32 tTJSNC_RandomGenerator::ClassID = (tjs_uint32)-1;
tTJSNC_RandomGenerator::tTJSNC_RandomGenerator() :
	tTJSNativeClass(TJS_W("RandomGenerator"))
{
	// class constructor

	TJS_BEGIN_NATIVE_MEMBERS(/*TJS class name*/RandomGenerator)
	TJS_DECL_EMPTY_FINALIZE_METHOD
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator,
	/*TJS class name*/ RandomGenerator)
{
	_this->Randomize(param, numparams);

	return TJS_S_OK;
}
TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/RandomGenerator)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/randomize)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	_this->Randomize(param, numparams);

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/randomize)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/random)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	// returns 53-bit precision random value x, x is in 0 <= x < 1

	if(result)
		*result = _this->Random();
	else
		_this->Random(); // discard result

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/random)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/random32)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	// returns 32-bit precision integer value x, x is in 0 <= x <= 4294967295

	if(result)
		*result = (tjs_int64)_this->Random32();
	else
		_this->Random32(); // discard result

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/random32)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/random63)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	// returns 63-bit precision integer value x, x is in 0 <= x <= 9223372036854775807

	if(result)
		*result = _this->Random63();
	else
		_this->Random63(); // discard result

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/random63)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/random64)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	// returns 64-bit precision integer value x, x is in
	// -9223372036854775808 <= x <= 9223372036854775807

	if(result)
		*result = _this->Random64();
	else
		_this->Random64(); // discard result

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/random64)
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/serialize)
{
	TJS_GET_NATIVE_INSTANCE(/*var. name*/_this, /*var. type*/tTJSNI_RandomGenerator);

	if(result)
	{
		iTJSDispatch2 * dsp = _this->Serialize();
		*result = tTJSVariant(dsp, dsp);
		dsp->Release();
	}

	return TJS_S_OK;
}
TJS_END_NATIVE_METHOD_DECL(/*func. name*/serialize)
//----------------------------------------------------------------------
	TJS_END_NATIVE_MEMBERS
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
tTJSNativeInstance *tTJSNC_RandomGenerator::CreateNativeInstance()
{
	return new tTJSNI_RandomGenerator();
}
//---------------------------------------------------------------------------
} // namespace TJS

//---------------------------------------------------------------------------

