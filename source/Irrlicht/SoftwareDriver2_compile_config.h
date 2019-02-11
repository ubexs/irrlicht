// Copyright (C) 2002-2012 Nikolaus Gebhardt / Thomas Alten
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __S_VIDEO_2_SOFTWARE_COMPILE_CONFIG_H_INCLUDED__
#define __S_VIDEO_2_SOFTWARE_COMPILE_CONFIG_H_INCLUDED__

#include "IrrCompileConfig.h"

// Generic Render Flags for burning's video rasterizer
// defined now in irrlicht compile config


#ifdef BURNINGVIDEO_RENDERER_BEAUTIFUL
	#define SOFTWARE_DRIVER_2_PERSPECTIVE_CORRECT
	#define SOFTWARE_DRIVER_2_SUBTEXEL
	#define SOFTWARE_DRIVER_2_BILINEAR
	#define SOFTWARE_DRIVER_2_LIGHTING
	#define SOFTWARE_DRIVER_2_USE_VERTEX_COLOR
	//#define SOFTWARE_DRIVER_2_USE_SEPARATE_SPECULAR_COLOR
	#define SOFTWARE_DRIVER_2_32BIT
	#define SOFTWARE_DRIVER_2_MIPMAPPING
	#define SOFTWARE_DRIVER_2_USE_WBUFFER
	#define SOFTWARE_DRIVER_2_TEXTURE_TRANSFORM
	#define SOFTWARE_DRIVER_2_TEXTURE_MAXSIZE		0
	//#define SOFTWARE_DRIVER_2_2D_AS_3D
#endif

//! Set Flags for Windows Mobile
#ifdef BURNINGVIDEO_RENDERER_CE
	#define SOFTWARE_DRIVER_2_PERSPECTIVE_CORRECT
	#define SOFTWARE_DRIVER_2_SUBTEXEL
	//#define SOFTWARE_DRIVER_2_BILINEAR
	//#define SOFTWARE_DRIVER_2_LIGHTING
	#define SOFTWARE_DRIVER_2_USE_VERTEX_COLOR
	#define SOFTWARE_DRIVER_2_16BIT
	#define SOFTWARE_DRIVER_2_MIPMAPPING
	#define SOFTWARE_DRIVER_2_USE_WBUFFER
	//#define SOFTWARE_DRIVER_2_TEXTURE_TRANSFORM
	#define SOFTWARE_DRIVER_2_TEXTURE_MAXSIZE		64
	#define BURNINGVIDEO_RENDERER_SCANLINE_MAG_MIN
#endif

#ifdef BURNINGVIDEO_RENDERER_FAST
	#define SOFTWARE_DRIVER_2_PERSPECTIVE_CORRECT
	#define SOFTWARE_DRIVER_2_SUBTEXEL
	//#define SOFTWARE_DRIVER_2_BILINEAR
	//#define SOFTWARE_DRIVER_2_LIGHTING
	#define SOFTWARE_DRIVER_2_USE_VERTEX_COLOR
	#define SOFTWARE_DRIVER_2_32BIT
	#define SOFTWARE_DRIVER_2_MIPMAPPING
	#define SOFTWARE_DRIVER_2_USE_WBUFFER
	#define SOFTWARE_DRIVER_2_TEXTURE_MAXSIZE		256
	#define BURNINGVIDEO_RENDERER_SCANLINE_MAG_MIN
#endif

#ifdef BURNINGVIDEO_RENDERER_ULTRA_FAST
	#define BURNINGVIDEO_RENDERER_FAST

	//#define SOFTWARE_DRIVER_2_PERSPECTIVE_CORRECT
	#define SOFTWARE_DRIVER_2_SUBTEXEL
	//#define SOFTWARE_DRIVER_2_BILINEAR
	//#define SOFTWARE_DRIVER_2_LIGHTING
	//#define SOFTWARE_DRIVER_2_USE_VERTEX_COLOR
	//#define SOFTWARE_DRIVER_2_32BIT
	#define SOFTWARE_DRIVER_2_MIPMAPPING
	#define SOFTWARE_DRIVER_2_USE_WBUFFER
	#define SOFTWARE_DRIVER_2_TEXTURE_MAXSIZE		128
	#define BURNINGVIDEO_RENDERER_SCANLINE_MAG_MIN
#endif

// Derivate flags

// texture format
#ifdef SOFTWARE_DRIVER_2_32BIT
	#define	BURNINGSHADER_COLOR_FORMAT	ECF_A8R8G8B8
#else
	#define	BURNINGSHADER_COLOR_FORMAT	ECF_A1R5G5B5
#endif

// mip mapping
#if defined ( SOFTWARE_DRIVER_2_MIPMAPPING )
	#if defined( BURNINGVIDEO_RENDERER_BEAUTIFUL )
		#define SOFTWARE_DRIVER_2_MIPMAPPING_MAX		12
		#define SOFTWARE_DRIVER_2_MIPMAPPING_SCALE      1
	#elif defined ( BURNINGVIDEO_RENDERER_CE )
		#define SOFTWARE_DRIVER_2_MIPMAPPING_MAX		4
		#define SOFTWARE_DRIVER_2_MIPMAPPING_SCALE      2
	#else
		#define SOFTWARE_DRIVER_2_MIPMAPPING_MAX		8
		#define SOFTWARE_DRIVER_2_MIPMAPPING_SCALE      1
	#endif
#else
	#define SOFTWARE_DRIVER_2_MIPMAPPING_MAX		1
	#define SOFTWARE_DRIVER_2_MIPMAPPING_SCALE      12
#endif

#ifndef REALINLINE
	#ifdef _MSC_VER
		#define REALINLINE __forceinline
	#else
		#define REALINLINE inline
	#endif
#endif

#endif
