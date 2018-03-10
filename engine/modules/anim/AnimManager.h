#ifndef __ECHO_ANIMMANAGER_H__
#define __ECHO_ANIMMANAGER_H__

#include "engine/core/Resource/ResourceManager.h"

namespace Echo
{
	class Animation;
	class AnimBlender;
	class Skeleton;


	class AnimManager : public ResourceManager
	{
		__DeclareSingleton(AnimManager);

	public:
		AnimManager();
		virtual ~AnimManager();

		// 创建动画
		Animation* createAnim(const String& name, bool isManual=false);

		// 创建动画混合器
		AnimBlender* createAnimBlender(Skeleton* pSkel);

		// 根据ID获取动画混合器
		AnimBlender* getAnimBlender(ui32 id);

		// 销毁动画混合器
		void destroyAnimBlenders(AnimBlender** blenders, int num);

	protected:
		Resource*	createImpl(const String& name, bool isManual);
		
	private:
		std::map<ui32, AnimBlender*>	 m_animBlenders;		// 动画混合
	};
}

#endif
