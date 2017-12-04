#pragma once

/// <summary>
/// 
/// </summary>
class IRenderable
{
	friend class RenderSystem;

protected:	
	/// <summary>
	/// Renders this instance.
	/// </summary>
	virtual void render() = 0;
};
