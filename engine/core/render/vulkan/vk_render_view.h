#pragma once

#include "base/render_view.h"
#include "vk_render_base.h"

namespace Echo
{
	class VKRenderView : public RenderView
	{
	public:
        VKRenderView(ui32 width, ui32 height, PixelFormat pixelFormat);
		virtual ~VKRenderView();

        // on resize
        virtual void onSize(ui32 width, ui32 height) override;

	public:
		// get vk image view
		VkImageView getVkImageView() { return m_vkImageView; }

	private:
		// mapping vk format
		void mappingVkFormat();

		// create vulkan image
		void createVkImage();

		// create vulkan image view
		void createVkImageView();

    private:
        VkFormat        m_vkFormat;
        VkImage         m_vkImage = VK_NULL_HANDLE;
        VkDeviceMemory  m_vkMemory;
        VkImageView     m_vkImageView = VK_NULL_HANDLE;
	};
}
