/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


// This file was generated by NxParameterized/scripts/GenParameterized.pl
// Created: 2015.10.22 17:26:19

#ifndef HEADER_BufferU8x2_h
#define HEADER_BufferU8x2_h

#include "NxParametersTypes.h"

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
#include "NxParameterized.h"
#include "NxParameters.h"
#include "NxParameterizedTraits.h"
#include "NxTraitsInternal.h"
#endif

namespace physx
{
namespace apex
{

#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())

namespace BufferU8x2NS
{

struct U8x2_Type;

struct U8x2_DynamicArray1D_Type
{
	U8x2_Type* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct U8x2_Type
{
	physx::PxU8 x;
	physx::PxU8 y;
};

struct ParametersStruct
{

	U8x2_DynamicArray1D_Type data;

};

static const physx::PxU32 checksum[] = { 0x9857276c, 0xc24be4d6, 0x1aee732c, 0xf8979343, };

} // namespace BufferU8x2NS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class BufferU8x2 : public NxParameterized::NxParameters, public BufferU8x2NS::ParametersStruct
{
public:
	BufferU8x2(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~BufferU8x2();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("BufferU8x2");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const physx::PxU32 ClassVersion = ((physx::PxU32)0 << 16) + (physx::PxU32)0;

	static physx::PxU32 staticVersion(void)
	{
		return ClassVersion;
	}

	physx::PxU32 version(void) const
	{
		return(staticVersion());
	}

	static const physx::PxU32 ClassAlignment = 8;

	static const physx::PxU32* staticChecksum(physx::PxU32& bits)
	{
		bits = 8 * sizeof(BufferU8x2NS::checksum);
		return BufferU8x2NS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const BufferU8x2NS::ParametersStruct& parameters(void) const
	{
		BufferU8x2* tmpThis = const_cast<BufferU8x2*>(this);
		return *(static_cast<BufferU8x2NS::ParametersStruct*>(tmpThis));
	}

	BufferU8x2NS::ParametersStruct& parameters(void)
	{
		return *(static_cast<BufferU8x2NS::ParametersStruct*>(this));
	}

	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle) const;
	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle);

	void initDefaults(void);

protected:

	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void);
	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void) const;


	virtual void getVarPtr(const NxParameterized::Handle& handle, void*& ptr, size_t& offset) const;

private:

	void buildTree(void);
	void initDynamicArrays(void);
	void initStrings(void);
	void initReferences(void);
	void freeDynamicArrays(void);
	void freeStrings(void);
	void freeReferences(void);

	static bool mBuiltFlag;
	static NxParameterized::MutexType mBuiltFlagMutex;
};

class BufferU8x2Factory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(BufferU8x2), BufferU8x2::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, BufferU8x2::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class BufferU8x2");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(BufferU8x2)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, BufferU8x2)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, BufferU8x2::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, BufferU8x2::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class BufferU8x2");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of BufferU8x2 here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (BufferU8x2*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (BufferU8x2::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (BufferU8x2::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (BufferU8x2::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (BufferU8x2::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
