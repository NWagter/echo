#ifndef __ECHO_GEOMDEF_H__
#define __ECHO_GEOMDEF_H__

#include "engine/core/Math/MathLib.h"

namespace Echo
{
	enum CullState
	{
		CS_INSIDE,
		CS_OUTSIDE,
		CS_INTERSECT,
	};

	struct HitInfo
	{
	public:
		bool				bHit;			// Did the ray hit an object?
		Vector3	 			hitPos;		// World coordinates of intersection
		Vector3				normal;			// Normal at hit point

		Real				beta;			// being used to get weight of hitting triangle
		Real				gamma;			// being used to get weight of hitting triangle

	public:
		HitInfo()
			: bHit(false)
			, hitPos(Vector3::INVALID)
			, normal(Vector3::INVALID)
			, beta(0.0)
			, gamma(0.0)
		{
		}
	};

}

#endif