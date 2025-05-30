#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	enum ProjectileImgParam
	{
		PROJECTILE_IMAGEROW,
		PROJECTILE_IMAGE,
	};

	class ProjectileImageEvent
	{
	private:
		class ImgRow : public IntDLLEventTemplate<0x46E6FA, 7, 0, 0,
			0, REG_EAX, false, CONST_VAL(PROJECTILE_IMAGEROW), REG_ESI>
		{
		public:
			ImgRow(const char* str) : IntDLLEventTemplate() { Init(str); };
			ImgRow(int address) : IntDLLEventTemplate() { Init(address); };
		};
		class Img : public IntDLLEventTemplate<0x46E6C7, 5, 0, 0,
			0, MEM_ESP_ADD(0x2C), false, CONST_VAL(PROJECTILE_IMAGE), REG_ESI>
		{
		public:
			Img(const char* str) : IntDLLEventTemplate() { Init(str); };
			Img(int address) : IntDLLEventTemplate() { Init(address); };
		};
		ImgRow* img_row;
		Img* image;
	public:
		ProjectileImageEvent()
		{
			const char* str = "GetProjectileImage";
			img_row = new ImgRow(str);
			image = new Img(str);
		}
		ProjectileImageEvent(int address)
		{
			img_row = new ImgRow(address);
			image = new Img(address);
		}
		void end()
		{
			img_row->end();
			image->end();
		}
	};
}