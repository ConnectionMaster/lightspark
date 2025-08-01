/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2025  Ludger Krämer <dbluelle@onlinehome.de>

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

#ifndef SCRIPTING_ABC_OPTIMIZED_SETPROPERTY_H
#define SCRIPTING_ABC_OPTIMIZED_SETPROPERTY_H 1

#include "scripting/abcutils.h"
#include "scripting/abctypes.h"

namespace lightspark
{
void abc_setPropertyStaticName(call_context* context);
void abc_setPropertyStaticName_constant_constant(call_context* context);
void abc_setPropertyStaticName_local_constant(call_context* context);
void abc_setPropertyStaticName_constant_local(call_context* context);
void abc_setPropertyStaticName_local_local(call_context* context);
void abc_setPropertyInteger(call_context* context);
void abc_setPropertyInteger_constant_constant_constant(call_context* context);
void abc_setPropertyInteger_constant_local_constant(call_context* context);
void abc_setPropertyInteger_constant_constant_local(call_context* context);
void abc_setPropertyInteger_constant_local_local(call_context* context);
void abc_setPropertyInteger_local_constant_constant(call_context* context);
void abc_setPropertyInteger_local_local_constant(call_context* context);
void abc_setPropertyInteger_local_constant_local(call_context* context);
void abc_setPropertyInteger_local_local_local(call_context* context);
void abc_setPropertyIntegerVector_constant_constant_constant(call_context* context);
void abc_setPropertyIntegerVector_constant_local_constant(call_context* context);
void abc_setPropertyIntegerVector_constant_constant_local(call_context* context);
void abc_setPropertyIntegerVector_constant_local_local(call_context* context);
void abc_setPropertyIntegerVector_local_constant_constant(call_context* context);
void abc_setPropertyIntegerVector_local_local_constant(call_context* context);
void abc_setPropertyIntegerVector_local_constant_local(call_context* context);
void abc_setPropertyIntegerVector_local_local_local(call_context* context);
}

#endif /* SCRIPTING_ABC_OPTIMIZED_SETPROPERTY_H */
