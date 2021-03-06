#ifndef PIPELINE_H
#define PIPELINE_H

class GraphicsCore;

#include "Graphics/GraphicsCore.h"
#include "Graphics/CullMode.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Topology.h"
#include "Graphics/Shader.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RootSignature.h"
#include "Graphics/DepthStencilConfig.h"
#include "Graphics/StreamOutputConfig.h"

/// <summary>
/// Collection of settings for the graphics pipeline
/// </summary>
class Pipeline
{
  public:
    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex and pixel shaders active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_stencil_config">
    /// depth stencil configuration
    /// NULL to disable depth and stencil testing
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <param name="cull_mode">
    /// which type of triangles should be culled
    /// </param>
    /// <param name="ms_count">
    /// number of multisamples per pixel.  1 means no multisampling
    /// </param>
    /// <param name="ms_quality">
    /// multisampling quality
    /// </param>
    /// <param name="wireframe">
    /// true if the fill mode should be wireframe
    /// false for solid fill mode
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
      const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode = CULL_BACK, UINT ms_count = 1,
      UINT ms_quality = 0, bool wireframe = false);

    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex, hull, domain, and pixel shaders active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="hull_shader">
    /// shader to use in the hull shader stage
    /// </param>
    /// <param name="domain_shader">
    /// shader to use in the domain shader stage
    /// </param>
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_stencil_config">
    /// depth stencil configuration
    /// NULL to disable depth and stencil testing
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <param name="ms_count">
    /// number of multisamples per pixel.  1 means no multisampling
    /// </param>
    /// <param name="cull_mode">
    /// which type of triangles should be culled
    /// </param>
    /// <param name="ms_quality">
    /// multisampling quality
    /// </param>
    /// <param name="wireframe">
    /// true if the fill mode should be wireframe
    /// false for solid fill mode
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
      const Shader& domain_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config,
      const RootSignature& root_sig, CullMode cull_mode = CULL_BACK, UINT ms_count = 1, UINT ms_quality = 0, bool wireframe = false);

    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex, geometry, and pixel shaders active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="geometry_shader">
    /// shader to use in the geometry shader stage
    /// </param>
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_stencil_config">
    /// depth stencil configuration
    /// NULL to disable depth and stencil testing
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <param name="cull_mode">
    /// which type of triangles should be culled
    /// </param>
    /// <param name="ms_count">
    /// number of multisamples per pixel.  1 means no multisampling
    /// </param>
    /// <param name="ms_quality">
    /// multisampling quality
    /// </param>
    /// <param name="wireframe">
    /// true if the fill mode should be wireframe
    /// false for solid fill mode
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
      const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig,
      CullMode cull_mode = CULL_BACK, UINT ms_count = 1, UINT ms_quality = 0, bool wireframe = false);

    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex, hull, domain, geometry, and pixel shaders
    /// active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="hull_shader">
    /// shader to use in the hull shader stage
    /// </param>
    /// <param name="domain_shader">
    /// shader to use in the domain shader stage
    /// </param>
    /// <param name="geometry_shader">
    /// shader to use in the geometry shader stage
    /// </param>
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_stencil_config">
    /// depth stencil configuration
    /// NULL to disable depth and stencil testing
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <param name="cull_mode">
    /// which type of triangles should be culled
    /// </param>
    /// <param name="ms_count">
    /// number of multisamples per pixel.  1 means no multisampling
    /// </param>
    /// <param name="ms_quality">
    /// multisampling quality
    /// </param>
    /// <param name="wireframe">
    /// true if the fill mode should be wireframe
    /// false for solid fill mode
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
      const Shader& domain_shader, const Shader& geometry_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode = CULL_BACK, UINT ms_count = 1, UINT ms_quality = 0, bool wireframe = false);

    /// <summary>
    /// Creates a graphics pipeline without rasterization
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);

    virtual ~Pipeline();

  protected:
    Pipeline();
    
  private:
    // disabled
    Pipeline(const Pipeline& cpy);
    Pipeline& operator=(const Pipeline& cpy);
};

#endif /* PIPELINE_H */
