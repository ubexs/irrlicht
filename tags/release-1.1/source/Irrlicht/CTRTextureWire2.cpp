// Copyright (C) 2002-2006 Nikolaus Gebhardt/Alten Thomas
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "ITriangleRenderer2.h"

// compile flag for this file

#undef USE_Z
#undef IPOL_Z
#undef CMP_Z
#undef WRITE_Z

#undef IPOL_W
#undef CMP_W
#undef WRITE_W

#undef SUBTEXEL

#undef IPOL_C
#undef IPOL_T0
#undef IPOL_T1

// define render case

#define USE_Z
#define IPOL_Z
#define CMP_Z
#define WRITE_Z

//#define SUBTEXEL

//#define IPOL_W
//#define CMP_W
//#define WRITE_W

//#define IPOL_C
#define IPOL_T0
//#define IPOL_T1

// apply global override

#ifndef SOFTWARE_DRIVER_2_PERSPECTIVE_CORRECT
	#undef IPOL_W
#endif

#ifndef SOFTWARE_DRIVER_2_SUBTEXEL
	#undef SUBTEXEL
#endif


namespace irr
{

namespace video
{

class CTRTextureWire2 : public ITriangleRenderer2
{
public:

	//! constructor
	CTRTextureWire2(IZBuffer2* zbuffer);

	//! draws an indexed triangle list
	virtual void drawTriangle ( const s4DVertex *a,const s4DVertex *b,const s4DVertex *c );
	virtual void drawLine ( const s4DVertex *a,const s4DVertex *b);



private:
	void renderAlphaLine ( const s4DVertex *a,const s4DVertex *b ) const;
	void renderLine ( const s4DVertex *a,const s4DVertex *b ) const;

};

//! constructor
CTRTextureWire2::CTRTextureWire2(IZBuffer2* zbuffer)
: ITriangleRenderer2(zbuffer)
{
	#ifdef _DEBUG
	setDebugName("CTRTextureWire2");
	#endif
}



/*!
*/
void CTRTextureWire2::renderLine ( const s4DVertex *a,const s4DVertex *b ) const
{
	
	int pitch0 = SurfaceWidth << VIDEO_SAMPLE_GRANULARITY;
	int pitch1 = SurfaceWidth << 2;

	int aposx = (int) a->Pos.x;
	int aposy = (int) a->Pos.y;
	int bposx = (int) b->Pos.x;
	int bposy = (int) b->Pos.y;

	int dx = bposx - aposx;
	int dy = bposy - aposy;

	int c;
	int m;
	int d = 0;
	int run;

	tVideoSample *dst;
#ifdef IPOL_Z
	TZBufferType2 *z;
#endif

	int xInc0 = 1 << VIDEO_SAMPLE_GRANULARITY;
	int yInc0 = pitch0;

	int xInc1 = 4;
	int yInc1 = pitch1;

	tVideoSample color;
	tFixPoint r0, g0, b0;

	getSample_color ( r0, g0, b0, a->Color );
	color = fix_to_color ( r0, g0, b0 );

	color = fix_to_color ( r0, g0, b0 );

	if ( dx < 0 )
	{
		xInc0 = - ( 1 << VIDEO_SAMPLE_GRANULARITY);
		xInc1 = -4;
		dx = -dx;
	}

	if ( dy > dx )
	{
		swap_xor ( dx, dy );
		swap_xor ( xInc0, yInc0 );
		swap_xor ( xInc1, yInc1 );
	}

	dst = (tVideoSample*) ( (u8*) lockedSurface + ( aposy * pitch0 ) + (aposx << VIDEO_SAMPLE_GRANULARITY ) );
#ifdef IPOL_Z
	z = (TZBufferType2*) ( (u8*) lockedZBuffer + ( aposy * pitch1 ) + (aposx << 2 ) );
#endif

	c = dx << 1;
	m = dy << 1;

#ifdef IPOL_Z
	f32 slopeZ = (b->Pos.z - a->Pos.z);
	if (dx )
		slopeZ /= (f32) dx;
	f32 dataZ = a->Pos.z;
#endif

	run = dx;
	while ( run )
	{
#ifdef CMP_Z
		if ( *z >= dataZ )
#endif
		{
			*dst = color;

#ifdef WRITE_Z
			*z = dataZ;
#endif
		}

		dst = (tVideoSample*) ( (u8*) dst + xInc0 );	// x += xInc
#ifdef IPOL_Z
		z = (TZBufferType2*) ( (u8*) z + xInc1 );
#endif

		d += m;
		if ( d > dx )
		{
			dst = (tVideoSample*) ( (u8*) dst + yInc0 );	// y += yInc
#ifdef IPOL_Z
			z = (TZBufferType2*) ( (u8*) z + yInc1 );
#endif
			d -= c;
		}
		run -= 1;
#ifdef IPOL_Z
		dataZ += slopeZ;
#endif
	}

}

void CTRTextureWire2::drawTriangle ( const s4DVertex *a,const s4DVertex *b,const s4DVertex *c )
{
	sScanLineData line;

	// query access to TexMaps

	// sort on height, y
	if ( a->Pos.y > b->Pos.y ) swapVertices(&a, &b);
	if ( a->Pos.y > c->Pos.y ) swapVertices(&a, &c);
	if ( b->Pos.y > c->Pos.y ) swapVertices(&b, &c);


	lockedSurface = (tVideoSample*)RenderTarget->lock();

#ifdef USE_Z
	lockedZBuffer = ZBuffer->lock();
#endif

	renderLine ( a, b );
	renderLine ( b, c );
	renderLine ( a, c );

	RenderTarget->unlock();

#ifdef USE_Z
	ZBuffer->unlock();
#endif

}


void CTRTextureWire2::drawLine ( const s4DVertex *a,const s4DVertex *b)
{

	// query access to TexMaps

	// sort on height, y
	if ( a->Pos.y > b->Pos.y ) swapVertices(&a, &b);

	lockedSurface = (tVideoSample*)RenderTarget->lock();

#ifdef USE_Z
	lockedZBuffer = ZBuffer->lock();
#endif

	renderLine ( a, b );
	RenderTarget->unlock();

#ifdef USE_Z
	ZBuffer->unlock();
#endif

}




//! creates a flat triangle renderer
ITriangleRenderer2* createTriangleRendererTextureGouraudWire2(IZBuffer2* zbuffer)
{
	return new CTRTextureWire2(zbuffer);
}


} // end namespace video
} // end namespace irr


