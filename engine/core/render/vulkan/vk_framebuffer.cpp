#include "engine/core/Util/PathUtil.h"
#include "interface/Renderer.h"
#include "vk_render_view.h"
#include "vk_framebuffer.h"
#include "vk_renderer.h"

namespace Echo
{
    static VKFramebuffer* g_current = nullptr;

    VKFramebuffer::VKFramebuffer(ui32 id, ui32 width, ui32 height)
        : FrameBuffer(id, width, height)
    {
        createVkCommandBuffer();
        createVkRenderPass();
    }

    VKFramebuffer::~VKFramebuffer()
    {
    }

    VKFramebuffer* VKFramebuffer::current()
    {
        return g_current;
    }

    void VKFramebuffer::attach(Attachment attachment, RenderView* renderView)
    {
        m_views[(ui8)attachment] = renderView;
    }

    bool VKFramebuffer::begin(bool isClearColor, const Color& bgColor, bool isClearDepth, float depthValue, bool isClearStencil, ui8 stencilValue)
    {
        g_current = this;

        VkCommandBufferBeginInfo commandBufferBeginInfo = {};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        commandBufferBeginInfo.pNext = nullptr;
        commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        commandBufferBeginInfo.pInheritanceInfo = nullptr;

        if (VK_SUCCESS == vkBeginCommandBuffer(m_vkCommandBuffer, &commandBufferBeginInfo))
        {
            // clear
            VkClearColorValue clearColor = { Renderer::BGCOLOR.r, Renderer::BGCOLOR.g, Renderer::BGCOLOR.b, Renderer::BGCOLOR.a };
            VkClearValue clearValue = {};
            clearValue.color = clearColor;

            VkImageSubresourceRange imageRange = {};
            imageRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageRange.levelCount = 1;
            imageRange.layerCount = 1;

            vkCmdClearColorImage(m_vkCommandBuffer, getVkColorImage(), VK_IMAGE_LAYOUT_GENERAL, &clearColor, 1, &imageRange);    

            return true;
        }

        EchoLogError("vulkan begin command buffer failed.");
        return false;
    }

    bool VKFramebuffer::end()
    {
        return true;
    }

    void VKFramebuffer::onSize(ui32 width, ui32 height)
    {
        m_width = width;
        m_height = height;

        for (RenderView* colorView : m_views)
        {
            if (colorView)
                colorView->onSize(width, height);
        }

        // view port
        m_vkViewport.x = 0.f;
        m_vkViewport.y = 0.0f;
        m_vkViewport.width = m_width;
        m_vkViewport.height = m_height;
        m_vkViewport.minDepth = 0.f;
        m_vkViewport.maxDepth = 1.f;

        m_vkViewportStateCreateInfo = {};
        m_vkViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        m_vkViewportStateCreateInfo.viewportCount = 1;
        m_vkViewportStateCreateInfo.pViewports = &m_vkViewport;
        m_vkViewportStateCreateInfo.scissorCount = 0;
        m_vkViewportStateCreateInfo.pScissors = nullptr;
    }

    void VKFramebuffer::createVkRenderPass()
    {
        VKRenderer* vkRenderer = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());

        VkAttachmentReference attachRef = {};
        attachRef.attachment = 0;
        attachRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpassDesc = {};
        subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDesc.colorAttachmentCount = 1;
        subpassDesc.pColorAttachments = &attachRef;

        VkAttachmentDescription attachDesc = {};
        //attachDesc.format = ;
        attachDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachDesc.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkRenderPassCreateInfo renderPassCreateInfo = {};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = 1;
        renderPassCreateInfo.pAttachments = &attachDesc;
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subpassDesc;

        if(VK_SUCCESS != vkCreateRenderPass(vkRenderer->getVkDevice(), &renderPassCreateInfo, nullptr, &m_vkRenderPass))
        {
            EchoLogError("vulkan create render pass failed.");
        }
    }

    void VKFramebuffer::createVkFramebuffer()
    {
        VKRenderView* colorView = ECHO_DOWN_CAST<VKRenderView*>(m_views[ui8(Attachment::Color0)]);
        if(colorView)
        {
            VKRenderer* vkRenderer  = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());
            VkImageView vkImageView = colorView->getVkImageView();

            VkFramebufferCreateInfo fbCreateInfo = {};
            fbCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fbCreateInfo.renderPass = m_vkRenderPass;
            fbCreateInfo.attachmentCount = 1;
            fbCreateInfo.pAttachments = &vkImageView;
            fbCreateInfo.width = m_width;
            fbCreateInfo.height = m_height;
            fbCreateInfo.layers = 1;

            if(VK_SUCCESS != vkCreateFramebuffer(vkRenderer->getVkDevice(), &fbCreateInfo, NULL, &m_vkFramebuffer))
            {
                EchoLogError("vulkan create frame buffer failed");
            }
        }
    }

    void VKFramebuffer::createVkCommandBuffer()
    {
        VKRenderer* vkRenderer = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());

        VkCommandBufferAllocateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.commandPool = vkRenderer->getVkCommandPool();
        createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        createInfo.commandBufferCount = 1;

        if (VK_SUCCESS != vkAllocateCommandBuffers(vkRenderer->getVkDevice(), &createInfo, &m_vkCommandBuffer))
        {
            EchoLogError("vulkan create command buffer failed");
        }
    }

    void VKFramebuffer::submitCommandBuffer()
    {
        vkEndCommandBuffer(m_vkCommandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_vkCommandBuffer;

        if (VK_SUCCESS != vkQueueSubmit(VKRenderer::instance()->getVkGraphicsQueue(), 1, &submitInfo, nullptr))
        {
            EchoLogError("vulkan queue submit failed");
        }
    }

    VKFramebufferOffscreen::VKFramebufferOffscreen(ui32 id, ui32 width, ui32 height)
        : VKFramebuffer(id, width, height)
    {
    }

    VKFramebufferOffscreen::~VKFramebufferOffscreen()
    {
    }

    bool VKFramebufferOffscreen::begin(bool clearColor, const Color& backgroundColor, bool clearDepth, float depthValue, bool clearStencil, ui8 stencilValue)
    {
        VKFramebuffer::begin(clearColor, backgroundColor, clearDepth, depthValue, clearStencil, stencilValue);

        return true;
    }

    bool VKFramebufferOffscreen::end()
    {
        return true;
    }

    void VKFramebufferOffscreen::onSize(ui32 width, ui32 height)
    {
        m_width = width;
        m_height = height;
    }

    VKFramebufferWindow::VKFramebufferWindow(ui32 width, ui32 height, void* handle)
        : VKFramebuffer(0, width, height)
    {
        createVkSurface(handle);

        createSwapChain(VKRenderer::instance()->getVkDevice());

        createImageViews(VKRenderer::instance()->getVkDevice());

        vkGetDeviceQueue(VKRenderer::instance()->getVkDevice(), VKRenderer::instance()->getPresentQueueFamilyIndex(m_vkWindowSurface), 0, &m_vkPresentQueue);

        onSize(width, height);
    }

    VKFramebufferWindow::~VKFramebufferWindow()
    {
        vkDestroySurfaceKHR(VKRenderer::instance()->getVkInstance(), m_vkWindowSurface, nullptr);
    }

    bool VKFramebufferWindow::begin(bool clearColor, const Color& backgroundColor, bool clearDepth, float depthValue, bool clearStencil, ui8 stencilValue)
    {
        VKFramebuffer::begin(clearColor, backgroundColor, clearDepth, depthValue, clearStencil, stencilValue);

        vkAcquireNextImageKHR(VKRenderer::instance()->getVkDevice(), m_vkSwapChain, Math::MAX_UI64, VKRenderer::instance()->getImageAvailableSemaphore(), VK_NULL_HANDLE, &m_imageIndex);



        return true;
    }

    bool VKFramebufferWindow::end()
    {
        submitCommandBuffer();

        present();

        return true;
    }

    void VKFramebufferWindow::onSize(ui32 width, ui32 height)
    {
        VKFramebuffer::onSize(width, height);
    }

    void VKFramebufferWindow::createVkSurface(void* handle)
    {
        // create window surface
#ifdef ECHO_PLATFORM_WINDOWS
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.hwnd = (HWND)handle;
        createInfo.hinstance = GetModuleHandle(nullptr);

        // create surface
        if (VK_SUCCESS != vkCreateWin32SurfaceKHR(VKRenderer::instance()->getVkInstance(), &createInfo, nullptr, &m_vkWindowSurface))
        {
            EchoLogError("Vulkan Renderer failed to create window surface!");
        }
#elif defined(ECHO_PLATFORM_ANDROID)
        VkAndroidSurfaceCreateInfoKHR createInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.window = AndroidGetApplicationWindow();
        if (VK_SUCCESS != vkCreateAndroidSurfaceKHR(m_vkInstance, &createInfo, nullptr, &m_vkWindowSurface))
        {
            EchoLogError("Vulkan Renderer failed to create window surface!");
        }
#endif
    }

    void VKFramebufferWindow::present()
    {
        VkPresentInfoKHR present;
        present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        present.pNext = nullptr;
        present.swapchainCount = 1;
        present.pSwapchains = &m_vkSwapChain;
        present.pImageIndices = &m_imageIndex;
        present.pWaitSemaphores = nullptr;
        present.waitSemaphoreCount = 0;
        present.pResults = nullptr;

        if (VK_SUCCESS != vkQueuePresentKHR(m_vkPresentQueue, &present))
        {
            EchoLogError("vulkan present failed");
        }
    }

    void VKFramebufferWindow::createSwapChain(VkDevice vkDevice)
    {
        VKRenderer* vkRenderer = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());

        // surface capabilities
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkRenderer->getVkPhysicalDevice(), m_vkWindowSurface, &surfaceCapabilities);

        // present mode
        ui32 presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(vkRenderer->getVkPhysicalDevice(), m_vkWindowSurface, &presentModeCount, nullptr);

        vector<VkPresentModeKHR>::type presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(vkRenderer->getVkPhysicalDevice(), m_vkWindowSurface, &presentModeCount, &presentModes[0]);

        // swap chain extent
        VkExtent2D swapChainExtent = surfaceCapabilities.currentExtent;

        // surface format
        VkSurfaceFormatKHR surfaceFormat = pickSurfaceSupportFormat();

        // The FIFO present mode is guaranteed by the spec to be supported
        // Also note that current Android driver only supports FIFO
        VkPresentModeKHR swapChainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

        // Detemine the number of VkImage's to use in the swap chain.
        ui32 desiredNumberOfSwapChainImages = surfaceCapabilities.minImageCount;

        // surface transform bit
        VkSurfaceTransformFlagBitsKHR presentTransform = surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR : surfaceCapabilities.currentTransform;

        // Find a supported composite alpha mode 
        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        // Queue family indices
        ui32 queueFamilyIndices[2] = { vkRenderer->getGraphicsQueueFamilyIndex(), vkRenderer->getPresentQueueFamilyIndex(m_vkWindowSurface) };

        // Swap chain info
        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.surface = m_vkWindowSurface;
        createInfo.minImageCount = desiredNumberOfSwapChainImages;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = { swapChainExtent.width, swapChainExtent.height };
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        createInfo.preTransform = presentTransform;
        createInfo.imageArrayLayers = 1;
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.presentMode = swapChainPresentMode;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
        createInfo.clipped = VK_TRUE;
        createInfo.compositeAlpha = compositeAlpha;

        // queue family index config
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
        if (queueFamilyIndices[0] != queueFamilyIndices[1])
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }

        if (vkCreateSwapchainKHR(vkDevice, &createInfo, nullptr, &m_vkSwapChain) != VK_SUCCESS)
        {
            EchoLogError("Failed to create vulkan swap chain!");
        }
    }

    void VKFramebufferWindow::createImageViews(VkDevice vkDevice)
    {
        VKRenderer* vkRenderer = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());

        // image count
        ui32 swapChainImageCount = 0;
        vkGetSwapchainImagesKHR(vkDevice, m_vkSwapChain, &swapChainImageCount, nullptr);

        // Vk image
        m_vkSwapChainImages.resize(swapChainImageCount);
        vkGetSwapchainImagesKHR(vkDevice, m_vkSwapChain, &swapChainImageCount, &m_vkSwapChainImages[0]);

        // create ImageViews
        m_vkSwapChainImageViews.resize(swapChainImageCount);
        for (size_t i = 0; i < m_vkSwapChainImageViews.size(); i++)
        {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = m_vkSwapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = VK_FORMAT_B8G8R8A8_UNORM;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(vkDevice, &createInfo, nullptr, &m_vkSwapChainImageViews[i]) != VK_SUCCESS)
            {
                EchoLogError("Failed to create image views!");
            }
        }
    }

    VkSurfaceFormatKHR VKFramebufferWindow::pickSurfaceSupportFormat()
    {
        VKRenderer* vkRenderer = ECHO_DOWN_CAST<VKRenderer*>(Renderer::instance());

        ui32 formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(vkRenderer->getVkPhysicalDevice(), m_vkWindowSurface, &formatCount, nullptr);

        vector<VkSurfaceFormatKHR>::type surfaceFormats(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(vkRenderer->getVkPhysicalDevice(), m_vkWindowSurface, &formatCount, &surfaceFormats[0]);

        return surfaceFormats[0];
    }
}