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
// Created: 2015.10.22 17:26:30

#ifndef HEADER_DestructibleActorParam_0p3_h
#define HEADER_DestructibleActorParam_0p3_h

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

namespace DestructibleActorParam_0p3NS
{

struct GroupsMask_Type;
struct LODWeights_Type;
struct ShapeDescFlags_Type;
struct ShapeDescTemplate_Type;
struct ContactPairFlag_Type;
struct ActorDescFlags_Type;
struct ActorDescTemplate_Type;
struct BodyDescFlags_Type;
struct BodyDescTemplate_Type;
struct DestructibleDepthParameters_Type;
struct DestructibleParametersFlag_Type;
struct DestructibleParameters_Type;

struct STRING_DynamicArray1D_Type
{
	NxParameterized::DummyStringStruct* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct DestructibleDepthParameters_DynamicArray1D_Type
{
	DestructibleDepthParameters_Type* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct DestructibleDepthParameters_Type
{
	bool TAKE_IMPACT_DAMAGE;
	bool IGNORE_POSE_UPDATES;
	bool IGNORE_RAYCAST_CALLBACKS;
	bool IGNORE_CONTACT_CALLBACKS;
	bool USER_FLAG_0;
	bool USER_FLAG_1;
	bool USER_FLAG_2;
	bool USER_FLAG_3;
};
struct GroupsMask_Type
{
	bool useGroupsMask;
	physx::PxU32 bits0;
	physx::PxU32 bits1;
	physx::PxU32 bits2;
	physx::PxU32 bits3;
};
struct DestructibleParametersFlag_Type
{
	bool ACCUMULATE_DAMAGE;
	bool DEBRIS_TIMEOUT;
	bool DEBRIS_MAX_SEPARATION;
	bool CRUMBLE_SMALLEST_CHUNKS;
	bool ACCURATE_RAYCASTS;
	bool USE_VALID_BOUNDS;
};
struct ShapeDescFlags_Type
{
	bool NX_TRIGGER_ON_ENTER;
	bool NX_TRIGGER_ON_LEAVE;
	bool NX_TRIGGER_ON_STAY;
	bool NX_SF_VISUALIZATION;
	bool NX_SF_DISABLE_COLLISION;
	bool NX_SF_FEATURE_INDICES;
	bool NX_SF_DISABLE_RAYCASTING;
	bool NX_SF_POINT_CONTACT_FORCE;
	bool NX_SF_FLUID_DRAIN;
	bool NX_SF_FLUID_DISABLE_COLLISION;
	bool NX_SF_FLUID_TWOWAY;
	bool NX_SF_DISABLE_RESPONSE;
	bool NX_SF_DYNAMIC_DYNAMIC_CCD;
	bool NX_SF_DISABLE_SCENE_QUERIES;
	bool NX_SF_CLOTH_DRAIN;
	bool NX_SF_CLOTH_DISABLE_COLLISION;
	bool NX_SF_CLOTH_TWOWAY;
	bool NX_SF_SOFTBODY_DRAIN;
	bool NX_SF_SOFTBODY_DISABLE_COLLISION;
	bool NX_SF_SOFTBODY_TWOWAY;
};
struct ShapeDescTemplate_Type
{
	ShapeDescFlags_Type flags;
	physx::PxU16 collisionGroup;
	GroupsMask_Type groupsMask;
	physx::PxU16 materialIndex;
	physx::PxF32 density;
	physx::PxF32 skinWidth;
	physx::PxU64 userData;
	physx::PxU64 name;
};
struct ContactPairFlag_Type
{
	bool NX_IGNORE_PAIR;
	bool NX_NOTIFY_ON_START_TOUCH;
	bool NX_NOTIFY_ON_END_TOUCH;
	bool NX_NOTIFY_ON_TOUCH;
	bool NX_NOTIFY_ON_IMPACT;
	bool NX_NOTIFY_ON_ROLL;
	bool NX_NOTIFY_ON_SLIDE;
	bool NX_NOTIFY_FORCES;
	bool NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD;
	bool NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD;
	bool NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD;
	bool NX_NOTIFY_CONTACT_MODIFICATION;
};
struct LODWeights_Type
{
	physx::PxF32 maxDistance;
	physx::PxF32 distanceWeight;
	physx::PxF32 maxAge;
	physx::PxF32 ageWeight;
	physx::PxF32 bias;
};
struct BodyDescFlags_Type
{
	bool NX_BF_DISABLE_GRAVITY;
	bool NX_BF_FILTER_SLEEP_VEL;
	bool NX_BF_ENERGY_SLEEP_TEST;
	bool NX_BF_VISUALIZATION;
};
struct BodyDescTemplate_Type
{
	BodyDescFlags_Type flags;
	physx::PxF32 wakeUpCounter;
	physx::PxF32 linearDamping;
	physx::PxF32 angularDamping;
	physx::PxF32 maxAngularVelocity;
	physx::PxF32 CCDMotionThreshold;
	physx::PxF32 sleepLinearVelocity;
	physx::PxF32 sleepAngularVelocity;
	physx::PxU32 solverIterationCount;
	physx::PxF32 sleepEnergyThreshold;
	physx::PxF32 sleepDamping;
	physx::PxF32 contactReportThreshold;
};
struct ActorDescFlags_Type
{
	bool NX_AF_DISABLE_COLLISION;
	bool NX_AF_DISABLE_RESPONSE;
	bool NX_AF_LOCK_COM;
	bool NX_AF_FLUID_DISABLE_COLLISION;
	bool NX_AF_CONTACT_MODIFICATION;
	bool NX_AF_FORCE_CONE_FRICTION;
	bool NX_AF_USER_ACTOR_PAIR_FILTERING;
};
struct ActorDescTemplate_Type
{
	ActorDescFlags_Type flags;
	physx::PxF32 density;
	physx::PxU16 actorCollisionGroup;
	physx::PxU16 dominanceGroup;
	ContactPairFlag_Type contactReportFlags;
	physx::PxU16 forceFieldMaterial;
	physx::PxU64 userData;
	physx::PxU64 name;
	physx::PxU64 compartment;
};
struct DestructibleParameters_Type
{
	physx::PxF32 damageThreshold;
	physx::PxF32 damageToRadius;
	physx::PxF32 damageCap;
	physx::PxF32 forceToDamage;
	physx::PxF32 impactVelocityThreshold;
	physx::PxF32 materialStrength;
	physx::PxF32 damageToPercentDeformation;
	physx::PxF32 deformationPercentLimit;
	physx::PxU32 minimumFractureDepth;
	physx::PxI32 debrisDepth;
	physx::PxU32 essentialDepth;
	physx::PxF32 debrisLifetimeMin;
	physx::PxF32 debrisLifetimeMax;
	physx::PxF32 debrisMaxSeparationMin;
	physx::PxF32 debrisMaxSeparationMax;
	physx::PxBounds3 validBounds;
	physx::PxF32 maxChunkSpeed;
	DestructibleParametersFlag_Type flags;
	physx::PxF32 fractureImpulseScale;
	physx::PxU16 dynamicChunkDominanceGroup;
	GroupsMask_Type dynamicChunksGroupsMask;
};

struct ParametersStruct
{

	NxParameterized::DummyStringStruct crumbleEmitterName;
	NxParameterized::DummyStringStruct dustEmitterName;
	physx::PxMat34Legacy globalPose;
	physx::PxVec3 scale;
	bool dynamic;
	physx::PxU32 supportDepth;
	bool formExtendedStructures;
	bool useAssetDefinedSupport;
	bool useWorldSupport;
	physx::PxF32 massScaleExponent;
	bool renderStaticChunksSeparately;
	STRING_DynamicArray1D_Type overrideSkinnedMaterialNames;
	STRING_DynamicArray1D_Type overrideStaticMaterialNames;
	DestructibleParameters_Type destructibleParameters;
	DestructibleDepthParameters_DynamicArray1D_Type depthParameters;
	ShapeDescTemplate_Type shapeDescTemplate;
	ActorDescTemplate_Type actorDescTemplate;
	BodyDescTemplate_Type bodyDescTemplate;

};

static const physx::PxU32 checksum[] = { 0xf78aa4ca, 0x62e8ff0b, 0x6b3dcc04, 0xe44d2726, };

} // namespace DestructibleActorParam_0p3NS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class DestructibleActorParam_0p3 : public NxParameterized::NxParameters, public DestructibleActorParam_0p3NS::ParametersStruct
{
public:
	DestructibleActorParam_0p3(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~DestructibleActorParam_0p3();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("DestructibleActorParam");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const physx::PxU32 ClassVersion = ((physx::PxU32)0 << 16) + (physx::PxU32)3;

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
		bits = 8 * sizeof(DestructibleActorParam_0p3NS::checksum);
		return DestructibleActorParam_0p3NS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const DestructibleActorParam_0p3NS::ParametersStruct& parameters(void) const
	{
		DestructibleActorParam_0p3* tmpThis = const_cast<DestructibleActorParam_0p3*>(this);
		return *(static_cast<DestructibleActorParam_0p3NS::ParametersStruct*>(tmpThis));
	}

	DestructibleActorParam_0p3NS::ParametersStruct& parameters(void)
	{
		return *(static_cast<DestructibleActorParam_0p3NS::ParametersStruct*>(this));
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

class DestructibleActorParam_0p3Factory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(DestructibleActorParam_0p3), DestructibleActorParam_0p3::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, DestructibleActorParam_0p3::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class DestructibleActorParam_0p3");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(DestructibleActorParam_0p3)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, DestructibleActorParam_0p3)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, DestructibleActorParam_0p3::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, DestructibleActorParam_0p3::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class DestructibleActorParam_0p3");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of DestructibleActorParam_0p3 here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (DestructibleActorParam_0p3*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (DestructibleActorParam_0p3::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (DestructibleActorParam_0p3::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (DestructibleActorParam_0p3::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (DestructibleActorParam_0p3::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
