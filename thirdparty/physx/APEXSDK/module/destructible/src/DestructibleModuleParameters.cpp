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
// Created: 2015.10.22 17:26:23

#include "DestructibleModuleParameters.h"
#include <string.h>
#include <stdlib.h>

using namespace NxParameterized;

namespace physx
{
namespace apex
{
namespace destructible
{

using namespace DestructibleModuleParametersNS;

const char* const DestructibleModuleParametersFactory::vptr =
    NxParameterized::getVptr<DestructibleModuleParameters, DestructibleModuleParameters::ClassAlignment>();

const physx::PxU32 NumParamDefs = 9;
static NxParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 3, 4, 5, 6, 7, 8,
};

#define TENUM(type) physx::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NxParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 8 },
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxDynamicChunkIslandCount), NULL, 0 }, // maxDynamicChunkIslandCount
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->sortFIFOByBenefit), NULL, 0 }, // sortFIFOByBenefit
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->validBoundsPadding), NULL, 0 }, // validBoundsPadding
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->maxChunkSeparationLOD), NULL, 0 }, // maxChunkSeparationLOD
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxActorCreatesPerFrame), NULL, 0 }, // maxActorCreatesPerFrame
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxChunkDepthOffset), NULL, 0 }, // maxChunkDepthOffset
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->massScale), NULL, 0 }, // massScale
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->scaledMassExponent), NULL, 0 }, // scaledMassExponent
};


bool DestructibleModuleParameters::mBuiltFlag = false;
NxParameterized::MutexType DestructibleModuleParameters::mBuiltFlagMutex;

DestructibleModuleParameters::DestructibleModuleParameters(NxParameterized::Traits* traits, void* buf, PxI32* refCount) :
	NxParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &DestructibleModuleParametersFactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

DestructibleModuleParameters::~DestructibleModuleParameters()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void DestructibleModuleParameters::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NxParameterized::Traits* traits = mParameterizedTraits;
	physx::PxI32* refCount = mRefCount;
	void* buf = mBuffer;

	this->~DestructibleModuleParameters();

	NxParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NxParameterized::DefinitionImpl* DestructibleModuleParameters::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NxParameterized::DefinitionImpl* DestructibleModuleParameters::getParameterDefinitionTree(void) const
{
	DestructibleModuleParameters* tmpParam = const_cast<DestructibleModuleParameters*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NxParameterized::ErrorType DestructibleModuleParameters::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NxParameterized::ErrorType DestructibleModuleParameters::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void DestructibleModuleParameters::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<DestructibleModuleParameters::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void DestructibleModuleParameters::freeParameterDefinitionTable(NxParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void DestructibleModuleParameters::buildTree(void)
{

	physx::PxU32 allocSize = sizeof(NxParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NxParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(static_cast<void*>(ParamDefTable), 0, allocSize);

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		NX_PARAM_PLACEMENT_NEW(ParamDefTable + i, NxParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "This class is used for initializing the NxModuleDestructible.", true);
		ParamDefTable[0].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="maxDynamicChunkIslandCount"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("maxDynamicChunkIslandCount", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "The maximum number of dynamic NxActors that will be allowed to be active per NxApexScene. A value of 0 (the default) is interpreted as no limit.", true);
		ParamDefTable[1].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="sortFIFOByBenefit"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("sortFIFOByBenefit", TYPE_BOOL, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Instead of keeping the maxCount youngest, use maxCount largest benefit if this is true.", true);
		ParamDefTable[2].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="validBoundsPadding"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("validBoundsPadding", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "The padding applied to the combined scene valid bounds and NxDestructible actor bounds.  The final combined and passed bounds is used to cull NxActors", true);
		ParamDefTable[3].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="maxChunkSeparationLOD"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("maxChunkSeparationLOD", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("max", physx::PxU64(1), true);
		HintTable[1].init("min", physx::PxU64(0), true);
		ParamDefTable[4].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[4];
		static Hint* HintPtrTable[4] = { &HintTable[0], &HintTable[1], &HintTable[2], &HintTable[3], };
		HintTable[0].init("longDescription", "Chunk islands are destroyed after this time or separation from their origins.  This parameter sets the lifetimes and max separations within their min-max ranges.  The valid range is [0,1].  Default is 0.5.", true);
		HintTable[1].init("max", physx::PxU64(1), true);
		HintTable[2].init("min", physx::PxU64(0), true);
		HintTable[3].init("shortDescription", "Every destructible asset defines a min and max lifetime, and maximum separation distance for its chunks.", true);
		ParamDefTable[4].setHints((const NxParameterized::Hint**)HintPtrTable, 4);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="maxActorCreatesPerFrame"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("maxActorCreatesPerFrame", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Lets the user throttle the number of SDK actor creates per frame (per scene) due to destruction, as this can be quite costly. The default is 0xffffffff (unlimited).", true);
		ParamDefTable[5].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="maxChunkDepthOffset"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("maxChunkDepthOffset", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "If maxChunkDepthOffset = 0, all chunks can be fractured.  If maxChunkDepthOffset = 1, the highest level (smallest) chunks are eliminated, etc.  This prevents too many chunks from being formed.  In other words, the higher maxChunkDepthOffset, the lower the LOD.", true);
		HintTable[1].init("shortDescription", "Effectively eliminates the higher level (smaller) chunks from NxDestructibleAssets (see NxDestructibleAsset).", true);
		ParamDefTable[6].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="massScale"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("massScale", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Used with scaledMassExponent for scaling dynamic chunk masses.\nThe 'real' mass m of a chunk is calculated by the destructible actor's density multiplied by\nthe total volume of the chunk's (scaled) collision shapes.  The mass used in\nthe simulation is massScale*pow(m/massScale,scaledMassExponent).  Values less than 1 have the\neffect of reducing the ratio of different masses.  The closer scaledMassExponent is to zero, the\nmore the ratio will be 'flattened.'  This helps PhysX converge when there is a very large number\nof interacting rigid bodies (such as a pile of destructible chunks).\nValid range: (0,infinity).  Default = 1.0.\n", true);
		HintTable[1].init("shortDescription", "Used with scaledMassExponent for scaling dynamic chunk masses.", true);
		ParamDefTable[7].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="scaledMassExponent"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("scaledMassExponent", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Used with massScale for scaling dynamic chunk masses.\nThe 'real' mass m of a chunk is calculated by the destructible actor's density multiplied by\nthe total volume of the chunk's (scaled) collision shapes.  The mass used in\nthe simulation is massScale*pow(m/massScale,scaledMassExponent).  Values less than 1 have the\neffect of reducing the ratio of different masses.  The closer scaledMassExponent is to zero, the\nmore the ratio will be 'flattened.'  This helps PhysX converge when there is a very large number\nof interacting rigid bodies (such as a pile of destructible chunks).\nValid range: (0,1].  Default = 0.5.\n", true);
		HintTable[1].init("shortDescription", "Used with massScale for scaling dynamic chunk masses.", true);
		ParamDefTable[8].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[8];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(3);
		Children[3] = PDEF_PTR(4);
		Children[4] = PDEF_PTR(5);
		Children[5] = PDEF_PTR(6);
		Children[6] = PDEF_PTR(7);
		Children[7] = PDEF_PTR(8);

		ParamDefTable[0].setChildren(Children, 8);
	}

	mBuiltFlag = true;

}
void DestructibleModuleParameters::initStrings(void)
{
}

void DestructibleModuleParameters::initDynamicArrays(void)
{
}

void DestructibleModuleParameters::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	maxDynamicChunkIslandCount = physx::PxU32(0);
	sortFIFOByBenefit = bool(false);
	validBoundsPadding = physx::PxF32(0);
	maxChunkSeparationLOD = physx::PxF32(0.5);
	maxActorCreatesPerFrame = physx::PxU32(PX_MAX_U32);
	maxChunkDepthOffset = physx::PxU32(0);
	massScale = physx::PxF32(1);
	scaledMassExponent = physx::PxF32(0.5);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void DestructibleModuleParameters::initReferences(void)
{
}

void DestructibleModuleParameters::freeDynamicArrays(void)
{
}

void DestructibleModuleParameters::freeStrings(void)
{
}

void DestructibleModuleParameters::freeReferences(void)
{
}

} // namespace destructible
} // namespace apex
} // namespace physx
