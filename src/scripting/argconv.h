/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2011-2013  Matthias Gehre (M.Gehre@gmx.de)
    Copyright (C) 2024  mr b0nk 500 (b0nk@b0nk.xyz)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef SCRIPTING_ARGCONV_H
#define SCRIPTING_ARGCONV_H 1

#include "backends/geometry.h"
#include "scripting/flash/geom/Point.h"
#include "scripting/toplevel/ASString.h"
#include "scripting/toplevel/Boolean.h"
#include "scripting/toplevel/Error.h"
#include "scripting/toplevel/Number.h"
#include "swf.h"

/* Usage of ARG_UNPACK:
 * You have to use it within a ASFUNCTIONBODY_ATOM() { }, because it uses the implicit arguments 'args' and 'argslen'.
 * Standard usage is:
 * int32_t i;
 * bool b;
 * _NR<DisplayObject> o;
 * asAtom a = asAtomHandler::invalidAtom;
 * ARG_CHECK(ARG_UNPACK (i) (b) (o) (a));
 * which coerces the given arguments implicitly (according to ecma) to the types Integer, Boolean, DisplayObject and then puts them
 * into the given variables.
 * ATTENTION: The object 'o' is the same as the argument passed into the function, so changing it will be visible for the caller.
 *
 * A exception will be thrown if a type cannot be coerces implicitly or when not enough arguments are provided by the caller. A LOG_NOT_IMPLEMENTED
 * will be emitted if more than the unpacked arguments are provided by the caller.
 *
 * To specify default values, use the (var, defvalue) operator like
 * ARG_CHECK(ARG_UNPACK (i) (b,true) (o,NullRef) (a,asAtomHandler::nullAtom));
 * this will work as above if all arguments are supplied. When the second argument is not supplied, no error is thrown and
 * b is set to 'true'. If the third argument is not supplied, not error is thrown and o is set to NullRef. Note that you cannot
 * put a Null into DisplayObject, as Null derives directly from ASObject (i.e. Null is not a subclass DisplayObject).
 * If a 'null' value is provided for an Object type, it's reference is set to a NullRef.
 */

namespace lightspark
{

template<class T>
class ArgumentConversionAtom
{
public:
	static T toConcrete(ASWorker* wrk,asAtom obj,const T& v);
	static T toConcreteNoRefcount(ASWorker* wrk,asAtom obj,const T& v)
	{
		return toConcrete(wrk,obj,v);
	}
	static void toAbstract(asAtom& ret, ASWorker* wrk,const T& val);
	static void cleanupOldValue(T& oldval);
	static T failValue();
};

template<>
class ArgumentConversionAtom<asAtom>
{
public:
	static asAtom toConcrete(ASWorker* wrk,asAtom obj,const asAtom& v)
	{
		if(asAtomHandler::isNull(obj))
			return asAtomHandler::nullAtom;
		if(asAtomHandler::isUndefined(obj))
			return asAtomHandler::undefinedAtom;
		if(asAtomHandler::isValid(v) && !asAtomHandler::isNull(v) && !asAtomHandler::isUndefined(v) && !asAtomHandler::checkArgumentConversion(v,obj))
		{
			createError<ArgumentError>(wrk,kCheckTypeFailedError,
									  asAtomHandler::toObject(obj,wrk)->getClassName(),
									  "?"); // TODO
			return asAtomHandler::invalidAtom;
		}
		asAtomHandler::localNumberToGlobalNumber(wrk,obj);
		ASATOM_ADDSTOREDMEMBER(obj);
		return obj;
	}
	static void toAbstract(asAtom& ret, ASWorker* wrk,asAtom val)
	{
		if(asAtomHandler::isInvalid(val))
			asAtomHandler::setNull(ret);
		else
		{
			ASATOM_INCREF(val);
			ret = val;
		}
	}
	static asAtom failValue() { return asAtomHandler::invalidAtom; }
	// special case for ARG_UNPACK: no incRef is needed for asAtoms
	static asAtom toConcreteNoRefcount(ASWorker* wrk,asAtom obj,const asAtom& v)
	{
		if(asAtomHandler::isNull(obj))
			return asAtomHandler::nullAtom;
		if(asAtomHandler::isUndefined(obj))
			return asAtomHandler::undefinedAtom;
		if(asAtomHandler::isValid(v) && !asAtomHandler::isNull(v) && !asAtomHandler::isUndefined(v) && !asAtomHandler::checkArgumentConversion(v,obj))
		{
			createError<ArgumentError>(wrk,kCheckTypeFailedError,
									  asAtomHandler::toObject(obj,wrk)->getClassName(),
									  "?"); // TODO
			return asAtomHandler::invalidAtom;
		}
		return obj;
	}
	static void cleanupOldValue(asAtom& oldval)
	{
		ASATOM_REMOVESTOREDMEMBER(oldval);
	}
};

template<class T>
class ArgumentConversionAtom<NullableRef<T>>
{
public:
	static NullableRef<T> toConcrete(ASWorker* wrk,asAtom obj,const NullableRef<T>& v)
	{
		if(asAtomHandler::isNull(obj))
			return NullRef;
		if(asAtomHandler::isUndefined(obj))
			return NullRef;

		if(!asAtomHandler::is<T>(obj))
		{
			createError<ArgumentError>(wrk,kCheckTypeFailedError,
												  asAtomHandler::getClass(obj,wrk->getSystemState())->getQualifiedClassName(),
												  Class<T>::getClass(wrk->getSystemState())->getQualifiedClassName());
			return NullRef;
		}
		T* o = asAtomHandler::toObject(obj,wrk)->as<T>();
		o->incRef();
		return _MNR(o);
	}
	static void toAbstract(asAtom& ret, ASWorker* /*wrk*/,const NullableRef<T>& val)
	{
		if(val.isNull())
			asAtomHandler::setNull(ret);
		else
		{
			val->incRef();
			ret = asAtomHandler::fromObject(val.getPtr());
		}
	}
	static NullableRef<T> toConcreteNoRefcount(ASWorker* wrk,asAtom obj,const NullableRef<T>& v)
	{
		return toConcrete(wrk,obj,v);
	}
	static NullableRef<T> failValue() { return NullRef; }
	static void cleanupOldValue(NullableRef<T>& oldval)
	{
	}
};

template<>
class ArgumentConversionAtom<NullableRef<ASObject>>
{
public:
	static NullableRef<ASObject> toConcrete(ASWorker* wrk,asAtom obj,const NullableRef<ASObject>& v)
	{
		ASObject* o = asAtomHandler::toObject(obj,wrk);
		o->incRef();
		return _MNR(o);
	}
	static void toAbstract(asAtom& ret, ASWorker* /*wrk*/,const NullableRef<ASObject>& val)
	{
		if(val.isNull())
			asAtomHandler::setNull(ret);
		else
		{
			val->incRef();
			ret = asAtomHandler::fromObject(val.getPtr());
		}
	}
	static NullableRef<ASObject> toConcreteNoRefcount(ASWorker* wrk,asAtom obj,const NullableRef<ASObject>& v)
	{
		return toConcrete(wrk,obj,v);
	}
	static NullableRef<ASObject> failValue() { return NullRef; }
	static void cleanupOldValue(NullableRef<ASObject>& oldval)
	{
	}
};

template<>
inline number_t lightspark::ArgumentConversionAtom<number_t>::toConcrete(ASWorker* wrk,asAtom obj,const number_t& v)
{
	return asAtomHandler::getNumber(wrk,obj);
}
template<>
inline number_t lightspark::ArgumentConversionAtom<number_t>::failValue() { return 0; }

template<>
inline void lightspark::ArgumentConversionAtom<number_t>::cleanupOldValue(number_t& oldvalue) {}

template<>
inline bool lightspark::ArgumentConversionAtom<bool>::toConcrete(ASWorker* wrk,asAtom obj,const bool& v)
{
	return asAtomHandler::Boolean_concrete(obj);
}
template<>
inline bool lightspark::ArgumentConversionAtom<bool>::failValue() { return false; }

template<>
inline void lightspark::ArgumentConversionAtom<bool>::cleanupOldValue(bool& oldvalue) {}

template<>
inline uint32_t lightspark::ArgumentConversionAtom<uint32_t>::toConcrete(ASWorker* wrk,asAtom obj,const uint32_t& v)
{
	return asAtomHandler::getUInt(wrk,obj);
}
template<>
inline uint32_t lightspark::ArgumentConversionAtom<uint32_t>::failValue() { return 0; }
template<>
inline void lightspark::ArgumentConversionAtom<uint32_t>::cleanupOldValue(uint32_t& oldvalue) {}

template<>
inline int32_t lightspark::ArgumentConversionAtom<int32_t>::toConcrete(ASWorker* wrk,asAtom obj,const int32_t& v)
{
	return asAtomHandler::toInt(obj);
}
template<>
inline int32_t lightspark::ArgumentConversionAtom<int32_t>::failValue() { return 0; }

template<>
inline void lightspark::ArgumentConversionAtom<int32_t>::cleanupOldValue(int32_t& oldvalue) {}

template<>
inline int64_t lightspark::ArgumentConversionAtom<int64_t>::toConcrete(ASWorker* wrk,asAtom obj,const int64_t& v)
{
	return asAtomHandler::toInt64(obj);
}
template<>
inline int64_t lightspark::ArgumentConversionAtom<int64_t>::failValue() { return 0; }

template<>
inline void lightspark::ArgumentConversionAtom<int64_t>::cleanupOldValue(int64_t& oldvalue) {}

template<>
inline tiny_string lightspark::ArgumentConversionAtom<tiny_string>::toConcrete(ASWorker* wrk,asAtom obj,const tiny_string& v)
{
	return asAtomHandler::toString(obj,wrk);
}
template<>
inline tiny_string lightspark::ArgumentConversionAtom<tiny_string>::failValue() { return ""; }

template<>
inline void lightspark::ArgumentConversionAtom<tiny_string>::cleanupOldValue(tiny_string& oldvalue) {}

template<>
inline RGB lightspark::ArgumentConversionAtom<RGB>::toConcrete(ASWorker* wrk,asAtom obj,const RGB& v)
{
	return RGB(asAtomHandler::getUInt(wrk,obj));
}
template<>
inline RGB lightspark::ArgumentConversionAtom<RGB>::failValue() { return RGB(); }
template<>
inline void lightspark::ArgumentConversionAtom<RGB>::cleanupOldValue(RGB& oldvalue) {}

template<>
inline AS3KeyCode lightspark::ArgumentConversionAtom<AS3KeyCode>::toConcrete(ASWorker* wrk,asAtom obj,const AS3KeyCode& v)
{
	return AS3KeyCode(asAtomHandler::getUInt(wrk,obj));
}
template<>
inline AS3KeyCode lightspark::ArgumentConversionAtom<AS3KeyCode>::failValue() { return AS3KEYCODE_UNKNOWN; }
template<>
inline void lightspark::ArgumentConversionAtom<AS3KeyCode>::cleanupOldValue(AS3KeyCode& oldvalue) {}

template<>
inline Vector2f lightspark::ArgumentConversionAtom<Vector2f>::toConcrete(ASWorker* wrk, asAtom obj, const Vector2f& v)
{
	bool needsAS3 = wrk->needsActionScript3();
	auto swfVersion = wrk->AVM1getSwfVersion();
	if (needsAS3 || asAtomHandler::is<Point>(obj))
	{
		auto point = asAtomHandler::as<Point>(obj);
		return Vector2f(point->getX(), point->getY());
	}
	else if (asAtomHandler::isObject(obj))
	{
		auto _obj = asAtomHandler::getObjectNoCheck(obj);
		asAtom x = asAtomHandler::undefinedAtom;
		asAtom y = asAtomHandler::undefinedAtom;

		multiname m(nullptr);
		m.name_type=multiname::NAME_STRING;
		m.isAttribute = false;

		m.name_s_id=wrk->getSystemState()->getUniqueStringId("x");
		_obj->getVariableByMultiname(x, m, GET_VARIABLE_OPTION::NONE, wrk);
		m.name_s_id=wrk->getSystemState()->getUniqueStringId("y");
		_obj->getVariableByMultiname(y, m, GET_VARIABLE_OPTION::NONE, wrk);

		return Vector2f
		(
			asAtomHandler::AVM1toNumber(x, swfVersion),
			asAtomHandler::AVM1toNumber(y, swfVersion)
		);
	}
	auto _default = asAtomHandler::AVM1toNumber(asAtomHandler::undefinedAtom, swfVersion);
	return Vector2f(_default, _default);
}
template<>
inline Vector2f lightspark::ArgumentConversionAtom<Vector2f>::failValue()
{
	auto _default = Number::NaN;
	return Vector2f(_default, _default);
}
template<>
inline void lightspark::ArgumentConversionAtom<Vector2f>::cleanupOldValue(Vector2f& oldvalue) {}

template<>
inline void lightspark::ArgumentConversionAtom<int32_t>::toAbstract(asAtom& ret, ASWorker* wrk,const int32_t& val)
{
	asAtomHandler::setInt(ret,wrk,val);
}

template<>
inline void lightspark::ArgumentConversionAtom<uint32_t>::toAbstract(asAtom& ret, ASWorker* wrk,const uint32_t& val)
{
	asAtomHandler::setUInt(ret,wrk,val);
}

template<>
inline void lightspark::ArgumentConversionAtom<number_t>::toAbstract(asAtom& ret, ASWorker* wrk,const number_t& val)
{
	asAtomHandler::setNumber(ret,wrk,val);
}

template<>
inline void lightspark::ArgumentConversionAtom<bool>::toAbstract(asAtom& ret, ASWorker* wrk,const bool& val)
{
	asAtomHandler::setBool(ret,val);
}

template<>
inline void lightspark::ArgumentConversionAtom<tiny_string>::toAbstract(asAtom& ret, ASWorker* wrk,const tiny_string& val)
{
	ret = asAtomHandler::fromObject(abstract_s(wrk,val));
}

template<>
inline void lightspark::ArgumentConversionAtom<RGB>::toAbstract(asAtom& ret, ASWorker* wrk,const RGB& val)
{
	asAtomHandler::setUInt(ret,wrk,val.toUInt());
}

template<>
inline void lightspark::ArgumentConversionAtom<AS3KeyCode>::toAbstract(asAtom& ret, ASWorker* wrk,const AS3KeyCode& val)
{
	asAtomHandler::setUInt(ret,wrk,val);
}

template<>
inline void lightspark::ArgumentConversionAtom<Vector2f>::toAbstract(asAtom& ret, ASWorker* wrk, const Vector2f& val)
{
	ret = asAtomHandler::fromObject(Class<Point>::getInstanceS(wrk, val.x, val.y));
}
#define ARG_CHECK(u) if (u.isInvalid()) return;
#ifndef NDEBUG
#define ARG_UNPACK ArgUnpackAtom(wrk,args,argslen,true,false)
#define ARG_UNPACK_NO_ERROR ArgUnpackAtom(wrk,args,argslen,false,false)
#define ARG_UNPACK_MORE_ALLOWED ArgUnpackAtom(wrk,args,argslen,true,true)
#define ARG_UNPACK_NO_ERROR_MORE_ALLOWED ArgUnpackAtom(wrk,args,argslen,false,true)
#else
#define ARG_UNPACK ArgUnpackAtom(wrk,args,argslen,true)
#define ARG_UNPACK_NO_ERROR ArgUnpackAtom(wrk,args,argslen,false)
#define ARG_UNPACK_MORE_ALLOWED ArgUnpackAtom(wrk,args,argslen,true)
#define ARG_UNPACK_NO_ERROR_MORE_ALLOWED ArgUnpackAtom(wrk,args,argslen,false)
#endif
class ArgUnpackAtom
{
private:
	ASWorker* wrk;
	asAtom* args;
	int argslen;
	bool invalid;
	bool canError;
#ifndef NDEBUG
	bool moreAllowed;
#endif
public:
#ifndef NDEBUG
	ArgUnpackAtom(ASWorker* _w,asAtom* _args, int _argslen, bool _canError, bool _moreAllowed) : wrk(_w),args(_args), argslen(_argslen),invalid(false), canError(_canError), moreAllowed(_moreAllowed)
#else
	ArgUnpackAtom(ASWorker* _w,asAtom* _args, int _argslen, bool _canError) : wrk(_w),args(_args), argslen(_argslen),invalid(false), canError(_canError)
#endif
	{
		
	}
	bool isInvalid() const { return invalid; }

	template<class T> ArgUnpackAtom& operator()(T& v)
	{
		if(argslen == 0)
		{
			v = ArgumentConversionAtom<T>::failValue();
			if (canError)
				createError<ArgumentError>(wrk,kWrongArgumentCountError, "object", "?", "?");
			invalid=true;
		}
		if(!invalid)
		{
			v = ArgumentConversionAtom<T>::toConcreteNoRefcount(wrk,args[0],v);
			args++;
			argslen--;
		}
		return *this;
	}
	template<class T, class TD> ArgUnpackAtom& operator()(T& v,const TD& defvalue)
	{
		if(argslen > 0)
		{
			v = ArgumentConversionAtom<T>::toConcreteNoRefcount(wrk,args[0],v);
			args++;
			argslen--;
		}
		else
		{
			v = defvalue;
		}
		return *this;
	}

#ifndef NDEBUG
	~ArgUnpackAtom()
	{
		if(argslen > 0 && !moreAllowed)
			LOG(LOG_NOT_IMPLEMENTED,"Not all arguments were unpacked");
	}
#endif
};

}
#endif /* SCRIPTING_ARGCONV_H */
