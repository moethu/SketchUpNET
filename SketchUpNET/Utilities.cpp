/*

SketchUpNET - a C++ Wrapper for the Trimble(R) SketchUp(R) C API
Copyright(C) 2015, Autor: Maximilian Thumfart

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/initialize.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/layer.h>
#include <msclr/marshal.h>
#include <vector>
#include <SketchUpAPI/model/typed_value.h>
#include "Color.h"
#include "Vector.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public class Utilities
	{
		public:

		static System::String^ GetLayerName(SULayerRef layer)
		{
			SUStringRef layername = SU_INVALID;
			SUStringCreate(&layername);
			SULayerGetName(layer, &layername);
			System::String^ name = GetString(layername);

			return name;
		}


		static System::String^ GetString(SUStringRef name)
		{
			size_t name_length = 0;
			SUStringGetUTF8Length(name, &name_length);
			if (name_length == 0) return System::String::Empty;
			
			char* name_utf8 = new char[name_length +1];
			SUStringGetUTF8(name, name_length+1, name_utf8, &name_length);
			
			return gcnew System::String(name_utf8, 0, name_length, System::Text::Encoding::UTF8);
		}

		static const char* ToString(System::String^ value)
		{
			array<unsigned char>^ bytes = System::Text::Encoding::UTF8->GetBytes(value);
			char* result = new char[bytes->Length + 1];
			result[bytes->Length] = 0;
			int i = 0;
			for each(unsigned char c in bytes) {
				result[i++] = c;
			}
			return result;
		}

		static const char* ToCharArray(SUStringRef name)
		{
			size_t name_length = 0;
			SUStringGetUTF8Length(name, &name_length);
			char* name_utf8 = new char[name_length + 1];
			SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
			return name_utf8;
		}

		static Object^ ToObject(SUTypedValueRef tvref) {
			SUTypedValueType t;
			SUTypedValueGetType(tvref, &t);
			switch (t)
			{
			case SUTypedValueType_Empty:
				return NULL;
				break;
			case SUTypedValueType_Byte:
				char valueByte;
				SUTypedValueGetByte(tvref, &valueByte);
				return valueByte;
				break;
			case SUTypedValueType_Short:
				Int16 valueShort;
				SUTypedValueGetInt16(tvref, &valueShort);
				return valueShort;
				break;
			case SUTypedValueType_Int32:
				Int32 valueInt;
				SUTypedValueGetInt32(tvref, &valueInt);
				return valueInt;
				break;
			case SUTypedValueType_Float:
				float valueFloat;
				SUTypedValueGetFloat(tvref, &valueFloat);
				return valueFloat;
				break;
			case SUTypedValueType_Double:
				double valueDouble;
				SUTypedValueGetDouble(tvref, &valueDouble);
				return valueDouble;
				break;
			case SUTypedValueType_Bool:
				bool valueBool;
				SUTypedValueGetBool(tvref, &valueBool);
				return valueBool;
				break;
			case SUTypedValueType_Color:
				SUColor valueColor;
				SUTypedValueGetColor(tvref, &valueColor);
				return Color::FromSU(valueColor);
				break;
			case SUTypedValueType_Time:
				return NULL;
				break;
			case SUTypedValueType_String:
				SUStringRef str;
				SUTypedValueGetString(tvref, &str);
				return GetString(str);
				break;
			case SUTypedValueType_Vector3D:
				return NULL;
				break;
			case SUTypedValueType_Array:
				return NULL;
				break;
			default:
				return NULL;
				break;
			}
		}


	};




}