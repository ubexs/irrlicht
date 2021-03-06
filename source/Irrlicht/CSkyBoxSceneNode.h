// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef IRR_C_SKY_BOX_SCENE_NODE_H_INCLUDED
#define IRR_C_SKY_BOX_SCENE_NODE_H_INCLUDED

#include "ISceneNode.h"
#include "S3DVertex.h"

namespace irr
{
namespace scene
{

	// Skybox, rendered with zbuffer turned off, before all other nodes.
	class CSkyBoxSceneNode : public ISceneNode
	{
	public:

		//! constructor
		CSkyBoxSceneNode(video::ITexture* top, video::ITexture* bottom, video::ITexture* left,
			video::ITexture* right, video::ITexture* front, video::ITexture* back,
			ISceneNode* parent, ISceneManager* mgr, s32 id);

		virtual void OnRegisterSceneNode() IRR_OVERRIDE;

		//! renders the node.
		virtual void render() IRR_OVERRIDE;

		//! returns the axis aligned bounding box of this node
		virtual const core::aabbox3d<f32>& getBoundingBox() const IRR_OVERRIDE;

		//! returns the material based on the zero based index i. To get the amount
		//! of materials used by this scene node, use getMaterialCount().
		//! This function is needed for inserting the node into the scene hierarchy on a
		//! optimal position for minimizing renderstate changes, but can also be used
		//! to directly modify the material of a scene node.
		virtual video::SMaterial& getMaterial(u32 i) IRR_OVERRIDE;

		//! returns amount of materials used by this scene node.
		virtual u32 getMaterialCount() const IRR_OVERRIDE;

		//! Returns type of the scene node
		virtual ESCENE_NODE_TYPE getType() const IRR_OVERRIDE { return ESNT_SKY_BOX; }

		//! Creates a clone of this scene node and its children.
		virtual ISceneNode* clone(ISceneNode* newParent=0, ISceneManager* newManager=0) IRR_OVERRIDE;

	private:

		core::aabbox3d<f32> Box;
		u16 Indices[4];
		video::S3DVertex Vertices[4*6];
		video::SMaterial Material[6];
	};

} // end namespace scene
} // end namespace irr

#endif
