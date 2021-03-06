#ifndef COMMANDLIST_H
#define COMMANDLIST_H

class GraphicsCore;
class RootSignature;
class Pipeline;
class VertexBufferArray;
class HeapArray;
class ConstantBuffer;
class StreamOutputBufferArray;
class Texture1D;
class Texture2D;
class Texture2DRenderTarget;
class Texture3D;
class Texture1DArray;
class Texture2DArray;
class TextureCube;
class TextureCubeArray;
class DepthStencil;
class RenderTargetMSAA;
class DepthStencilMSAA;

#include <vector>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Pipeline.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Viewports.h"
#include "Graphics/Textures/RenderTarget.h"
#include "Graphics/HeapArray.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/Topology.h"
#include "Graphics/Buffers/VertexBufferArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/StreamOutputBufferArray.h"
#include "Graphics/Textures/Texture1D.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/Texture2DRenderTarget.h"
#include "Graphics/Textures/Texture3D.h"
#include "Graphics/Textures/Texture1DArray.h"
#include "Graphics/Textures/Texture2DArray.h"
#include "Graphics/Textures/TextureCube.h"
#include "Graphics/Textures/TextureCubeArray.h"
#include "Graphics/Textures/DepthStencil.h"
#include "Graphics/Textures/RenderTargetMSAA.h"
#include "Graphics/Textures/DepthStencilMSAA.h"

/// <summary>
/// Interface for list of commands for the rendering process
/// </summary>
class CommandList
{
  public:
    /// <summary>
    /// Creates a D3D12 direct command list
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="pipeline">
    /// Optional pipleline state to use initally for the command list.  This should be NULL if no inital pipeline is to be specified for the command list.
    /// </param>
    /// <returns>
    /// pointer to the command list
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static CommandList* CreateD3D12Direct(const GraphicsCore& graphics, Pipeline* pipeline);

    virtual ~CommandList();

    /// <summary>
    /// Resets the command list back to its initial state
    /// </summary>
    /// <param name="pipeline">
    /// Optional pipleline state to use initally for the command list.  This should be NULL if no inital pipeline is to be specified for the command list.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void Reset(Pipeline* pipeline) = 0;

    /// <summary>
    /// Informs the command list that recording of commands is complete
    /// </summary>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void Close() = 0;

    /// <summary>
    /// Sets the pipeline that is applicable to the subsequent member function calls
    /// </summary>
    /// <param name="pipeline">
    /// Pipeline to use
    /// </param>
    virtual void SetPipeline(const Pipeline& pipeline) = 0;

    /// <summary>
    /// Sets the root signature that is applicable to the subsequent member function calls
    /// </summary>
    /// <param name="sig">
    /// Root signature to use
    /// </param>
    virtual void SetRootSignature(const RootSignature& sig) = 0;

    /// <summary>
    /// Sets descriptor heaps
    /// </summary>
    /// <param name="heap_array">
    /// heap array to use
    /// </param>
    virtual void SetHeapArray(const HeapArray& heap_array) = 0;

    /// <summary>
    /// Sets the root signature slot to the specified constant buffer
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the constant buffer to
    /// </param>
    /// <param name="constant_buffer">
    /// constant buffer to use
    /// </param>
    virtual void SetConstantBuffer(UINT slot, const ConstantBuffer& constant_buffer) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1D& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2D& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DRenderTarget& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture3D& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1DArray& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DArray& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCube& texture) = 0;

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCubeArray& texture) = 0;

    // todo: overloads for clearing just the stencil, and both depth and stencil

    /*
     * Input assembler functions
     */

      /// <summary>
      /// Sets the topology to use for vertex data passed to the input assembler stage
      /// </summary>
      /// <param name="topology">
      /// topology for vertex data passed to the input assembler stage
      /// </param>
      virtual void IASetTopology(IATopology topology) = 0;

      /// <summary>
      /// Sets the vertex buffers to pass to the input assembler stage
      /// </summary>
      /// <param name="buffers">
      /// vertex buffers to pass to the input assembler stage
      /// </param>
      virtual void IASetVertexBuffers(const VertexBufferArray& buffers) = 0;
      // todo: override to allow for a subset of the buffers to be used

      /// <summary>
      /// Sets the index buffer to pass to the input assembler stage
      /// </summary>
      /// <param name="buffer">
      /// index buffer to pass to the input assembler stage
      /// </param>
      virtual void IASetIndexBuffer(const IndexBuffer& buffer) = 0;

    /*
     * Stream output functions
     */

      /// <summary>
      /// Sets the buffers to use for the stream outputstage
      /// </summary>
      /// <param name="buffers">
      /// buffers to use for stream output
      /// </param>
      virtual void SOSetBuffers(const StreamOutputBufferArray& buffers) = 0;

      /// <summary>
      /// Makes a steam output buffer ready to use as a vertex buffer
      /// </summary>
      /// <param name="buffer">
      /// stream output buffer
      /// </param>
      virtual void SOBufferToVertexBuffer(const StreamOutputBuffer& buffer) = 0;

      /// <summary>
      /// Makes a steam output buffer that previously had SOBufferToVertexBuffer called on it ready to use as a stream output buffer again
      /// </summary>
      /// <param name="buffer">
      /// stream output buffer
      /// </param>
      virtual void SOVertexBufferToStreamOutputBuffer(const StreamOutputBuffer& buffer) = 0;

    /*
     * Rasterizer functions
     */

      /// <summary>
      /// Sets the viewport to use for the rasterizer stage
      /// </summary>
      /// <param name="viewport">
      /// The viewports to make active
      /// </param>
      virtual void RSSetViewport(const Viewport& viewport) = 0;

      /// <summary>
      /// Sets the viewports to use for the rasterizer stage
      /// </summary>
      /// <param name="viewports">
      /// All the viewports to make active
      /// </param>
      virtual void RSSetViewports(const Viewports& viewports) = 0;

      /// <summary>
      /// Sets the viewports to use for the rasterizer stage
      /// </summary>
      /// <param name="viewports">
      /// All the viewports to make active
      /// </param>
      /// <param name="start">
      /// index of the first viewport to apply to the rendering pipeline
      /// </param>
      /// <param name="num">
      /// number of viewports to apply
      /// </param>
      virtual void RSSetViewports(const Viewports& viewports, UINT start, UINT num) = 0;

      /// <summary>
      /// Sets the scissor rect to use for the rasterizer stage
      /// </summary>
      /// <param name="rect">
      /// the scissor rect to make active
      /// </param>
      virtual void RSSetScissorRect(const RECT& rect) = 0;

      /// <summary>
      /// Sets the scissor rects to use for the rasterizer stage
      /// </summary>
      /// <param name="rects">
      /// array of the scissor rects to make active
      /// </param>
      virtual void RSSetScissorRects(const std::vector<RECT>& rects) = 0;

      /// <summary>
      /// Sets the scissor rects to use for the rasterizer stage
      /// </summary>
      /// <param name="rects">
      /// array of the scissor rects to make active
      /// </param>
      /// <param name="start">
      /// index of the first scissor rect to apply to the rendering pipeline
      /// </param>
      /// <param name="num">
      /// number of scissor to apply
      /// </param>
      virtual void RSSetScissorRects(const std::vector<RECT>& rects, UINT start, UINT num) = 0;

    /*
     * Output merger functions
     */

      /// <summary>
      /// Preps a render target of a back buffer for use as a render target
      /// </summary>
      /// <param name="target">
      /// Render target to prepare for being drawn to
      /// </param>
      virtual void PrepRenderTarget(const RenderTarget& target) = 0;

      /// <summary>
      /// Preps a MSAA render target of a back buffer for use as a render target
      /// </summary>
      /// <param name="target">
      /// MSAA render target to prepare for being drawn to
      /// </param>
      virtual void PrepRenderTarget(const RenderTargetMSAA& target) = 0;

      /// <summary>
      /// Preps a render target of a back buffer for being presented to the screen
      /// </summary>
      /// <param name="target">
      /// Render target to prepare for being presented
      /// </param>
      virtual void RenderTargetToPresent(const RenderTarget& target) = 0;

      /// <summary>
      /// Preps a render target of a back buffer that was used to resolve a MSAA render target for being presented to the screen
      /// </summary>
      /// <param name="target">
      /// Render target to prepare for being presented
      /// </param>
      virtual void RenderTargetResolvedToPresent(const RenderTarget& target) = 0;

      /// <summary>
      /// Resolves a MSAA render target into a presentable render target
      /// </summary>
      /// <param name="src">
      /// MSAA render target to be resolved
      /// </param>
      /// <param name="dst">
      /// Render target to resolve to
      /// </param>
      virtual void RenderTargetToResolved(const RenderTargetMSAA& src, const RenderTarget& dst) = 0;

      /// <summary>
      /// Prepares a texture to be used as a render target by the corresponding RenderTarget instance
      /// </summary>
      /// <param name="texture">
      /// texture to be used as a render target
      /// </param>
      virtual void TextureToRenderTarget(const Texture2DRenderTarget& texture) = 0;

      /// <summary>
      /// Allows the render target to be used as a texture by the corresponding Texture2D instance
      /// </summary>
      /// <param name="target">
      /// Render target to allow to be used as a texture
      /// </param>
      virtual void RenderTargetToTexture(const RenderTarget& target) = 0;

      /// <summary>
      /// Clears a render target with the specified color
      /// </summary>
      /// <param name="target">
      /// Render target to clear
      /// </param>
      /// <param name="clear_color">
      /// array of a RGBA color with each component in the [0,1] range to use as the clear color for the render target
      /// </param>
      virtual void ClearRenderTarget(const RenderTarget& target, const float clear_color[4]) = 0;

      /// <summary>
      /// Clears a MSAA render target with the specified color
      /// </summary>
      /// <param name="target">
      /// MSAA render target to clear
      /// </param>
      /// <param name="clear_color">
      /// array of a RGBA color with each component in the [0,1] range to use as the clear color for the render target
      /// </param>
      virtual void ClearRenderTarget(const RenderTargetMSAA& target, const float clear_color[4]) = 0;

      /// <summary>
      /// Clears the depth portion of a depth stencil
      /// </summary>
      /// <param name="depth_stencil">
      /// depth stencil to clear
      /// </param>
      /// <param name="depth_clear_value">
      /// value to use for clearing the depth stencil
      /// </param>
      virtual void ClearDepthStencil(const DepthStencil& depth_stencil, float depth_clear_value) = 0;

      /// <summary>
      /// Clears the depth portion of a depth stencil
      /// </summary>
      /// <param name="depth_stencil">
      /// MSAA depth stencil to clear
      /// </param>
      /// <param name="depth_clear_value">
      /// value to use for clearing the depth stencil
      /// </param>
      virtual void ClearDepthStencil(const DepthStencilMSAA& depth_stencil, float depth_clear_value) = 0;

      /// <summary>
      /// Sets the render target to use for the output merger stage
      /// </summary>
      /// <param name="target">
      /// render target to use
      /// </param>
      virtual void OMSetRenderTarget(const RenderTarget& target) = 0;

      /// <summary>
      /// Sets the render target to use for the output merger stage
      /// </summary>
      /// <param name="target">
      /// render target to use
      /// </param>
      /// <param name="depth_stencil">
      /// depth stencil to use
      /// </param>
      virtual void OMSetRenderTarget(const RenderTarget& target, const DepthStencil& depth_stencil) = 0;

      /// <summary>
      /// Sets the render target to use for the output merger stage
      /// </summary>
      /// <param name="target">
      /// MSAA render target to use
      /// </param>
      /// <param name="depth_stencil">
      /// MSAA depth stencil to use
      /// </param>
      virtual void OMSetRenderTarget(const RenderTargetMSAA& target, const DepthStencilMSAA& depth_stencil) = 0;

      // todo: create OMSetRenderTargets to set multiple render targets at once

    /*
     * Drawing functions
     */

      /// <summary>
      /// Draws instances of indexed primitives
      /// </summary>
      /// <param name="indices_per_instance">
      /// number of indices for each instance
      /// </param>
      /// <param name="instance_cnt">
      /// number of instances
      /// </param>
      /// <param name="instance_start_index">
      /// index in the instance buffer to start at
      /// </param>
      virtual void DrawIndexedInstanced(UINT indices_per_instance, UINT instance_cnt, UINT instance_start_index) = 0;

      /// <summary>
      /// Draws instances of indexed primitives
      /// </summary>
      /// <param name="indices_per_instance">
      /// number of indices for each instance
      /// </param>
      /// <param name="index_start_index">
      /// index in the index buffer to start at
      /// </param>
      /// <param name="instance_cnt">
      /// number of instances
      /// </param>
      /// <param name="instance_start_index">
      /// index in the instance buffer to start at
      /// </param>
      virtual void DrawIndexedInstanced(UINT indices_per_instance, UINT index_start_index, UINT instance_cnt, UINT instance_start_index) = 0;

      /// <summary>
      /// Draws instances of primitives
      /// </summary>
      /// <param name="vertices_per_instance">
      /// number of vertices for each instance
      /// </param>
      /// <param name="instance_cnt">
      /// number of instances
      /// </param>
      /// <param name="instance_start_index">
      /// index in the instance buffer to start at
      /// </param>
      virtual void DrawInstanced(UINT vertices_per_instance, UINT instance_cnt, UINT instance_start_index) = 0;

      /// <summary>
      /// Draws instances of primitives
      /// </summary>
      /// <param name="vertices_per_instance">
      /// number of vertices for each instance
      /// </param>
      /// <param name="vertex_start_index">
      /// index in the vertex buffer to start at
      /// </param>
      /// <param name="instance_cnt">
      /// number of instances
      /// </param>
      /// <param name="instance_start_index">
      /// index in the instance buffer to start at
      /// </param>
      virtual void DrawInstanced(UINT vertices_per_instance, UINT vertex_start_index, UINT instance_cnt, UINT instance_start_index) = 0;

  protected:
    CommandList();
    
  private:
    // disabled
    CommandList(const CommandList& cpy);
    CommandList& operator=(const CommandList& cpy);
};

#endif /* COMMANDLIST_H */
