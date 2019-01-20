#include "engine/core/log/Log.h"
#include "RenderTargetManager.h"
#include "Material.h"
#include "engine/core/main/Engine.h"
#include "interface/ShaderProgram.h"
#include "interface/Texture.h"
#include <algorithm>

namespace Echo
{
	RenderTargetManager::RenderTargetManager()
		:  m_currentRenderTarget( RTI_End )
	{
	}

	RenderTargetManager::~RenderTargetManager()
	{
		for( RenderTargetMap::iterator bit = m_renderTargets.begin(); bit != m_renderTargets.end();  )
		{
			EchoSafeDelete( bit->second, RenderTarget);
			m_renderTargets.erase(bit ++);
		}
	}

	RenderTargetManager* RenderTargetManager::instance()
	{
		static RenderTargetManager* inst = EchoNew(RenderTargetManager);
		return inst;
	}

	bool RenderTargetManager::initialize()
	{
		RenderTarget::Options option;
		option.depth = true;
		RenderTarget* defautRT = Renderer::instance()->createRenderTarget(RTI_DefaultBackBuffer, Renderer::instance()->getScreenWidth(), Renderer::instance()->getScreenHeight(), Renderer::instance()->getBackBufferPixelFormat(), option);
		if (defautRT)
		{
			m_renderTargets.insert(RenderTargetMap::value_type(RTI_DefaultBackBuffer, defautRT));

			return true;
		}

		EchoLogError("EchoNew( RTI_DefaultBackBuffer ) Failed !");
		return false;
	}

	void RenderTargetManager::destroyRenderTargetByID(ui32 _id)
	{
		RenderTargetMap::iterator fit = m_renderTargets.find( _id );

		if( fit == m_renderTargets.end() )
		{
			EchoLogError( "Could not found RenderTarget[%d]", _id );
			return;
		}

		EchoSafeDelete(fit->second, RenderTarget);
		m_renderTargets.erase(fit);
	}

	bool RenderTargetManager::beginRenderTarget( ui32 id,bool _clearColor, const Color& _backgroundColor, bool _clearDepth, float _depthValue, bool _clearStencil, ui8 stencilValue, ui32 rbo)
	{
		EchoAssert( id != RTI_End );
		RenderTarget* pRT = getRenderTargetByID( id);
        if(pRT)
        {
            RenderTarget* pUsingRT = m_currentRenderTarget != RTI_End ? getRenderTargetByID(m_currentRenderTarget) : 0;
            pRT->m_isFrameBufferChange = m_currentRenderTarget != id ? true : false;
            if( m_currentRenderTarget == RTI_End )
            {
                pRT->m_isViewportChange = true;
            }
            else if( pUsingRT && ( pUsingRT->width() != pRT->width() || pUsingRT->height() != pRT->height() ) )
            {
                pRT->m_isViewportChange = true;
            }
            else
            {
                pRT->m_isViewportChange = false;
            }
            
            m_currentRenderTarget = id;
            Renderer::instance()->dirtyTexSlot();
            
            return getRenderTargetByID(id)->beginRender(_clearColor, _backgroundColor, _clearDepth, _depthValue, _clearStencil, stencilValue);
        }

        return false;
	}

	void RenderTargetManager::onScreensizeChanged( ui32 _width, ui32 _height)
	{
		for (RenderTargetMap::iterator bit = m_renderTargets.begin(); bit != m_renderTargets.end(); ++bit)
		{
			RenderTarget* pRenderTarget = bit->second;
			if (pRenderTarget)
			{
				switch (pRenderTarget->id())
				{
				case RTI_DefaultBackBuffer: pRenderTarget->onResize(_width, _height); break;
				}
			}
		}
	}

	RenderTarget* RenderTargetManager::createRenderTarget(ui32 _id, ui32 _width, ui32 _height, PixelFormat _pixelFormat, RenderTarget::Options option)
	{
		RenderTargetMap::iterator iter = m_renderTargets.find(_id);
		if (iter != m_renderTargets.end())
		{
			EchoLogError("Rendertarget [%d] is already created.", _id);
			return iter->second;
		}

		if (_pixelFormat == PF_RGBA16_FLOAT && !Renderer::instance()->getDeviceFeatures().supportHFColorBf1())
		{
			_pixelFormat = PF_RGBA8_UNORM;
			EchoLogInfo("Device could not support PF_RGBA16_FLOAT(GL_EXT_color_buffer_half_float) use PF_RGBA8_UNORM!(Rendertarget[%d])",_id);
		}

		RenderTarget* pNewRenderTarget = Renderer::instance()->createRenderTarget(_id, _width, _height, _pixelFormat, option);

		if (!pNewRenderTarget)
		{
			EchoLogError("Allocate RenderTarget Failed !");
			return NULL;
		}

		if (!pNewRenderTarget->create())
		{
			EchoLogError("RenderTarget::create Failed !");
			EchoSafeDelete(pNewRenderTarget, RenderTarget);
			return NULL;
		}

		m_renderTargets.insert(RenderTargetMap::value_type(_id, pNewRenderTarget));

		return pNewRenderTarget;
	}

	RenderTarget* RenderTargetManager::getRenderTargetByID(ui32 _id)
	{
		RenderTargetMap::iterator fit = m_renderTargets.find(_id);
		if (fit != m_renderTargets.end())
			return fit->second;

		//EchoLogError("Could not found RenderTarget[%d]", _id);
		return nullptr;
	}

	bool RenderTargetManager::endRenderTarget(ui32 _id)
	{
		if(m_currentRenderTarget == _id);
        {
            RenderTarget* renderTarget = getRenderTargetByID(_id);
            if(renderTarget)
                return renderTarget->endRender();
        }
        
        return false;
	}
	
	bool RenderTargetManager::invalidate(ui32 _id, bool invalidateColor, bool invalidateDepth, bool invalidateStencil)
	{
		//EchoAssert( m_inUsingRenderTarget = RTI_End );

		//return getRenderTargetByID(_id)->invalidateFrameBuffer(invalidateColor, invalidateDepth, invalidateStencil);
		return true;
	}
}
