#ifndef D3D12_PIPELINE_H
#define D3D12_PIPELINE_H

#include <d3d12.h>
#include "Graphics/Pipeline.h"
#include "private_inc/D3D12/D3D12_InputLayout.h"
#include "private_inc/D3D12/D3D12_RenderTargetViewConfig.h"
#include "private_inc/D3D12/D3D12_RootSignature.h"

/// <summary>
/// Collection of settings for the graphics pipeline
/// </summary>
class D3D12_Pipeline : public Pipeline
{
  public:
    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, depth stencil enabled, multisampling disabled, and only the vertex and pixel shaders active
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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
      const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode, UINT ms_count,
      UINT ms_quality, bool wireframe);

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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
      const Shader& domain_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config,
      const RootSignature& root_sig, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe);

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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
      const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig,
      CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe);

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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
      const Shader& domain_shader, const Shader& geometry_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe);

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
    static Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);
    
    ~D3D12_Pipeline();

    ID3D12PipelineState* GetPipeline() const;
    
  private:
    D3D12_Pipeline(ID3D12PipelineState* pipeline);

    // disabled
    D3D12_Pipeline();
    D3D12_Pipeline(const D3D12_Pipeline& cpy);
    D3D12_Pipeline& operator=(const D3D12_Pipeline& cpy);

    /// <summary>
    /// Helper function for filling in D3D12_GRAPHICS_PIPELINE_STATE_DESC with default values
    /// </summary>
    /// <param name="desc">
    /// descriptor to write to
    /// </param>
    /// <param name="layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="depth_stencil_config">
    /// depth stencil configuration
    /// NULL to disable depth and stencil testing
    /// </param>
    /// <param name="rtv">
    /// configuration for the render target views
    /// </param>
    /// <param name="root">
    /// root signature
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
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
    /// <param name="stream_output">
    /// pointer to the configuration to use for the stream output stage
    /// NULL if stream output should be disabled
    /// </param>
    static void CreateDefaultPipelineDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, const D3D12_InputLayout& layout, const DepthStencilConfig* depth_stencil_config,
      const D3D12_RenderTargetViewConfig& rtv, const D3D12_RootSignature& root, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe,
      const StreamOutputConfig* stream_output);

    /// <summary>
    /// pipeline state object that matches the configuration specified when the instance was created
    /// </summary>
    ID3D12PipelineState* m_pipeline;
};

#endif /* D3D12_PIPELINE_H */
