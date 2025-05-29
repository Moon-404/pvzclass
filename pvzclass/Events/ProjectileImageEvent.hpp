#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	enum ProjectileImgParam
	{
		PROJECTILE_IMAGEROW,
		PROJECTILE_IMAGE,
		PROJECTILE_IMAGESIZE
	};

	class ProjectileImageEvent
	{
	private:
		class ImgRow : public IntDLLEventTemplate<0x46E6FA, 7, 0, 0,
			INT32_MIN, REG_EAX, false, CONST_VAL(PROJECTILE_IMAGEROW), REG_ESI>
		{
		public:
			ImgRow(const char* str) : IntDLLEventTemplate() { Init(str); };
			ImgRow(int address) : IntDLLEventTemplate() { Init(address); };
		};
		class Img : public IntDLLEventTemplate<0x46E6C7, 5, 0, 0,
			INT32_MIN, MEM_ESP_ADD(0x2C), false, CONST_VAL(PROJECTILE_IMAGE), REG_ESI>
		{
		public:
			Img(const char* str) : IntDLLEventTemplate() { Init(str); };
			Img(int address) : IntDLLEventTemplate() { Init(address); };
		};
		class ImageSize : public IntDLLEventTemplate<0x46E6D3, 6, 0, 0,
			INT32_MIN, MEM_ESP_ADD(0x30), false, CONST_VAL(PROJECTILE_IMAGESIZE), REG_ESI>
		{
		public:
			ImageSize(const char* str) : IntDLLEventTemplate() { Init(str); };
			ImageSize(int address) : IntDLLEventTemplate() { Init(address); };
		};
		ImgRow* img_row;
		Img* image;
		ImageSize* img_size;
	public:
		ProjectileImageEvent()
		{
			const char* str = "GetProjectileImage";
			img_row = new ImgRow(str);
			image = new Img(str);
			img_size = new ImageSize(str);
		}
		ProjectileImageEvent(int address)
		{
			img_row = new ImgRow(address);
			image = new Img(address);
			img_size = new ImageSize(address);
		}
		void end()
		{
			img_row->end();
			image->end();
			img_size->end();
		}
	};
}