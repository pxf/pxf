#ifndef _PXF_GRAPHICS_QUADBATCH_H_
#define _PXF_GRAPHICS_QUADBATCH_H_

#include <Pxf/Math/Vector.h>
#include <Pxf/Graphics/DeviceResource.h>

namespace Pxf
{
	namespace Graphics
	{
		class Device;

		//! Abstract class for quad primitive batches (2D rendering tool)
		class QuadBatch : public DeviceResource
		{
		public:
			QuadBatch(Device* _pDevice)
				: DeviceResource(_pDevice)
			{}

			virtual void SetColor(float r, float g, float b) = 0;
			virtual void SetColor(Math::Vec3f* c) = 0;
            virtual void SetAlpha(float a) = 0;
			virtual void SetTextureSubset(float tl_u, float tl_v, float br_u, float br_v) = 0;
			virtual void SetRotation(float angle) = 0; // Rotate following quad around its own axis
			virtual void Rotate(float angle) = 0; // Rotate coord system
            virtual void Translate(float x, float y) = 0; // Translate coord system
            virtual void LoadIdentity() = 0; // Reset coord system
			virtual void SetDepth(float d) = 0;

			virtual void Reset() = 0;
			virtual void AddFreeform(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) = 0;
			virtual void AddTopLeft(float x, float y, float w, float h) = 0;
			virtual void AddCentered(float x, float y, float w, float h) = 0;
			virtual void AddCentered(float x, float y, float w, float h, float rotation) = 0;
			virtual void Draw() = 0;
		};
	} // Graphics
} // Pxf

#endif // _PXF_GRAPHICS_QUADBATCH_H_