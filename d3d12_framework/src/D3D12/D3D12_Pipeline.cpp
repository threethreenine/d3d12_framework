#include <sstream>
#include "private_inc/D3D12/D3D12_Pipeline.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_Shader.h"
#include "private_inc/D3D12/D3D12_StreamOutputConfig.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

#if 0 /* old debug code, keeping around just in case it is needed again */
void dump_pso_desc(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc)
{
  std::ostringstream out;
  out << "root sig: " << desc.pRootSignature << '\n'
    << "vs:       " << desc.VS.BytecodeLength << ' ' << desc.VS.pShaderBytecode << '\n'
    << "ps:       " << desc.PS.BytecodeLength << ' ' << desc.PS.pShaderBytecode << '\n'
    << "ds:       " << desc.DS.BytecodeLength << ' ' << desc.DS.pShaderBytecode << '\n'
    << "hs:       " << desc.HS.BytecodeLength << ' ' << desc.HS.pShaderBytecode << '\n'
    << "gs:       " << desc.GS.BytecodeLength << ' ' << desc.GS.pShaderBytecode << '\n'
    << "so:       " << desc.StreamOutput.NumEntries << ' ' << desc.StreamOutput.NumStrides << ' ' << desc.StreamOutput.pBufferStrides << ' ' << desc.StreamOutput.pSODeclaration << ' '
    << desc.StreamOutput.RasterizedStream << '\n'
    << "blend:    " << desc.BlendState.AlphaToCoverageEnable << desc.BlendState.IndependentBlendEnable << '\n';
  for (int i = 0; i < 8; i++)
  {
    const D3D12_RENDER_TARGET_BLEND_DESC& blend = desc.BlendState.RenderTarget[i];
    out << "blend[" << i << "]: " << blend.BlendEnable << ' ' << blend.LogicOpEnable << ' ' << blend.SrcBlend << ' ' << blend.DestBlend << ' ' << blend.BlendOp << ' ' << blend.SrcBlendAlpha << ' '
      << blend.DestBlendAlpha << ' ' << blend.BlendOpAlpha << ' ' << blend.LogicOp << ' ' << (UINT)blend.RenderTargetWriteMask << '\n';
  }
  out << "smask:    " << desc.SampleMask << '\n'
    << "rstate:   " << desc.RasterizerState.FillMode << ' ' << desc.RasterizerState.CullMode << ' ' << desc.RasterizerState.FrontCounterClockwise << ' ' << desc.RasterizerState.DepthBias << ' '
    << desc.RasterizerState.DepthBiasClamp << ' ' << desc.RasterizerState.SlopeScaledDepthBias << ' ' << desc.RasterizerState.DepthClipEnable << ' ' << desc.RasterizerState.MultisampleEnable << ' '
    << desc.RasterizerState.AntialiasedLineEnable << ' ' << desc.RasterizerState.ForcedSampleCount << ' ' << desc.RasterizerState.ConservativeRaster << '\n'
    << "dstate:   " << desc.DepthStencilState.DepthEnable << ' ' << desc.DepthStencilState.DepthWriteMask << ' ' << desc.DepthStencilState.DepthFunc << ' ' << desc.DepthStencilState.StencilEnable
    << ' ' << (UINT)desc.DepthStencilState.StencilReadMask << ' ' << (UINT)desc.DepthStencilState.StencilWriteMask << ' ' << desc.DepthStencilState.FrontFace.StencilFailOp << ' '
    << desc.DepthStencilState.FrontFace.StencilDepthFailOp << ' ' << desc.DepthStencilState.FrontFace.StencilPassOp << ' ' << desc.DepthStencilState.FrontFace.StencilFunc << ' '
    << desc.DepthStencilState.BackFace.StencilFailOp << ' ' << desc.DepthStencilState.BackFace.StencilDepthFailOp << ' ' << desc.DepthStencilState.BackFace.StencilPassOp << ' '
    << desc.DepthStencilState.BackFace.StencilFunc << '\n'
    << "layouts:  " << desc.InputLayout.NumElements << '\n';
  for (UINT j = 0; j < desc.InputLayout.NumElements; j++)
  {
    const D3D12_INPUT_ELEMENT_DESC& layout = desc.InputLayout.pInputElementDescs[j];
    out << "layout[" << j << "] " << layout.SemanticName << ' ' << layout.SemanticIndex << ' ' << layout.Format << ' ' << layout.InputSlot << ' ' << layout.AlignedByteOffset << ' '
      << layout.InputSlotClass << ' ' << layout.InstanceDataStepRate << '\n';
  }
  out << "ib strip: " << desc.IBStripCutValue << '\n'
    << "topology: " << desc.PrimitiveTopologyType << '\n'
    << "targets:  " << desc.NumRenderTargets << '\n';
  for (int i = 0; i < 8; i++)
  {
    out << "rtv[" << i << "]:   " << desc.RTVFormats[i] << '\n';
  }
  out << "dsv:      " << desc.DSVFormat << '\n'
    << "sample:   " << desc.SampleDesc.Count << ' ' << desc.SampleDesc.Quality << '\n'
    << "node:     " << desc.NodeMask << '\n'
    << "flags:    " << desc.Flags << '\n'
    << "cache:    " << desc.CachedPSO.pCachedBlob << ' ' << desc.CachedPSO.CachedBlobSizeInBytes << '\n';

  OutputDebugStringA(out.str().c_str());
}
#endif /* 0 */

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
  const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode, UINT ms_count, UINT ms_quality,
  bool wireframe)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 ps     = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_ROOT_SIGNATURE_FLAGS stage_access = root.GetStageAccess();
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a vertex shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a pixel shader but the root signature doesn\'t allow it");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  CreateDefaultPipelineDesc(desc, layout, depth_stencil_config, rtv, root, (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology, cull_mode, ms_count, ms_quality, wireframe, stream_output);
  desc.VS = vs.GetShader();
  desc.PS = ps.GetShader();
  desc.SampleMask                       = UINT_MAX;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create pipeline state (HRESULT = " << rc << ')';
    throw FrameworkException(out.str());
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config,
  const RootSignature& root_sig, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 hs     = (const D3D12_Shader&)hull_shader;
  const D3D12_Shader&                 ds     = (const D3D12_Shader&)domain_shader;
  const D3D12_Shader&                 ps     = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_ROOT_SIGNATURE_FLAGS stage_access = root.GetStageAccess();
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a vertex shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a hull shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a domain shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a pixel shader but the root signature doesn\'t allow it");
  }

  if (topology != TOPOLOGY_PATCH)
  {
    throw FrameworkException("Hull and domain shaders being used requires the topology to be set to TOPOLOGY_PATCH");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  CreateDefaultPipelineDesc(desc, layout, depth_stencil_config, rtv, root, (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology, cull_mode, ms_count, ms_quality, wireframe, stream_output);
  desc.VS                               = vs.GetShader();
  desc.HS                               = hs.GetShader();
  desc.DS                               = ds.GetShader();
  desc.PS                               = ps.GetShader();
  desc.SampleMask                       = UINT_MAX;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create pipeline state (HRESULT = " << rc << ')';
    throw FrameworkException(out.str());
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
  const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig,
  CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 gs     = (const D3D12_Shader&)geometry_shader;
  const D3D12_Shader&                 ps     = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_ROOT_SIGNATURE_FLAGS stage_access = root.GetStageAccess();
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a vertex shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a geometry shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a pixel shader but the root signature doesn\'t allow it");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  CreateDefaultPipelineDesc(desc, layout, depth_stencil_config, rtv, root, (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology, cull_mode, ms_count, ms_quality, wireframe, stream_output);
  desc.VS                               = vs.GetShader();
  desc.GS                               = gs.GetShader();
  desc.PS                               = ps.GetShader();
  desc.SampleMask                       = UINT_MAX;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create pipeline state (HRESULT = " << rc << ')';
    throw FrameworkException(out.str());
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const Shader& geometry_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, const DepthStencilConfig* depth_stencil_config,
  const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 hs     = (const D3D12_Shader&)hull_shader;
  const D3D12_Shader&                 ds     = (const D3D12_Shader&)domain_shader;
  const D3D12_Shader&                 gs     = (const D3D12_Shader&)geometry_shader;
  const D3D12_Shader&                 ps     = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_ROOT_SIGNATURE_FLAGS stage_access = root.GetStageAccess();
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a vertex shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a hull shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a domain shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a geometry shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a pixel shader but the root signature doesn\'t allow it");
  }

  if (topology != TOPOLOGY_PATCH)
  {
    throw FrameworkException("Hull and domain shaders being used requires the topology to be set to TOPOLOGY_PATCH");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */
  
  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  CreateDefaultPipelineDesc(desc, layout, depth_stencil_config, rtv, root, (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology, cull_mode, ms_count, ms_quality, wireframe, stream_output);
  desc.VS                               = vs.GetShader();
  desc.HS                               = hs.GetShader();
  desc.DS                               = ds.GetShader();
  desc.GS                               = gs.GetShader();
  desc.PS                               = ps.GetShader();
  desc.SampleMask                       = UINT_MAX;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create pipeline state (HRESULT = " << rc << ')';
    throw FrameworkException(out.str());
  }

  return new D3D12_Pipeline(pipeline);
}

Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
  const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_ROOT_SIGNATURE_FLAGS stage_access = root.GetStageAccess();
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a vertex shader but the root signature doesn\'t allow it");
  }
  if (stage_access & D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS)
  {
    throw FrameworkException("Pipeline to be created with a pixel shader but the root signature doesn\'t allow it");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  CreateDefaultPipelineDesc(desc, layout, NULL, rtv, root, (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology, CULL_BACK, 1, 0, false, stream_output);
  desc.VS = vs.GetShader();

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create pipeline state (HRESULT = " << rc << ')';
    throw FrameworkException(out.str());
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline::D3D12_Pipeline(ID3D12PipelineState* pipeline)
:m_pipeline(pipeline)
{
}

D3D12_Pipeline::~D3D12_Pipeline()
{
  m_pipeline->Release();
}

ID3D12PipelineState* D3D12_Pipeline::GetPipeline() const
{
  return m_pipeline;
}

void D3D12_Pipeline::CreateDefaultPipelineDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, const D3D12_InputLayout& layout, const DepthStencilConfig* depth_stencil_config,
  const D3D12_RenderTargetViewConfig& rtv, const D3D12_RootSignature& root, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology, CullMode cull_mode, UINT ms_count, UINT ms_quality, bool wireframe,
  const StreamOutputConfig* stream_output)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (layout.GetNextIndex() != layout.GetNum())
  {
    throw FrameworkException("Not all input layout entries have been set");
  }
  if (ms_count < 1)
  {
    throw FrameworkException("Invalid multisample count");
  }
  else if (ms_count == 1 && ms_quality != 0)
  {
    throw FrameworkException("Multisampling quality must be 0 when multisampling is disabled");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  desc.pRootSignature                        = root.GetRootSignature();
  desc.InputLayout.pInputElementDescs        = layout.GetLayout();
  desc.InputLayout.NumElements               = layout.GetNum();
  desc.RasterizerState.FillMode              = wireframe ? D3D12_FILL_MODE_WIREFRAME : D3D12_FILL_MODE_SOLID;
  desc.RasterizerState.CullMode              = (D3D12_CULL_MODE)cull_mode;
  desc.RasterizerState.FrontCounterClockwise = false;
  desc.RasterizerState.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
  desc.RasterizerState.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
  desc.RasterizerState.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
  desc.RasterizerState.DepthClipEnable       = true;
  desc.RasterizerState.MultisampleEnable     = ms_count > 1;
  desc.RasterizerState.AntialiasedLineEnable = false;
  desc.RasterizerState.ForcedSampleCount     = 0;
  desc.RasterizerState.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
  desc.BlendState                            = rtv.GetBlendState();
  desc.DepthStencilState.DepthEnable         = depth_stencil_config && depth_stencil_config->depth_enable;
  desc.DepthStencilState.StencilEnable       = depth_stencil_config && depth_stencil_config->stencil_enable;
  desc.SampleMask                            = UINT_MAX;
  desc.PrimitiveTopologyType                 = topology;
  desc.NumRenderTargets                      = rtv.GetNumRenderTargets();
  desc.SampleDesc.Count                      = ms_count;
  desc.SampleDesc.Quality                    = ms_quality;
  memcpy(desc.RTVFormats, rtv.GetFormats(), sizeof(RenderTargetViewFormat) * desc.NumRenderTargets);
  if (depth_stencil_config)
  {
    desc.DSVFormat = (DXGI_FORMAT)depth_stencil_config->dsv_format;
    if (depth_stencil_config->depth_enable)
    {
      desc.DepthStencilState.DepthFunc      = (D3D12_COMPARISON_FUNC)depth_stencil_config->depth_comparison;
      desc.DepthStencilState.DepthWriteMask = depth_stencil_config->depth_write_enabled ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
    }
    if (depth_stencil_config->stencil_enable)
    {
      desc.DepthStencilState.StencilWriteMask = depth_stencil_config->stencil_write_mask;
      desc.DepthStencilState.StencilReadMask  = depth_stencil_config->stencil_read_mask;
      desc.DepthStencilState.FrontFace.StencilFailOp      = (D3D12_STENCIL_OP)depth_stencil_config->stencil_front_face.stencil_fail;
      desc.DepthStencilState.FrontFace.StencilDepthFailOp = (D3D12_STENCIL_OP)depth_stencil_config->stencil_front_face.depth_fail;
      desc.DepthStencilState.FrontFace.StencilPassOp      = (D3D12_STENCIL_OP)depth_stencil_config->stencil_front_face.pass;
      desc.DepthStencilState.FrontFace.StencilFunc        = (D3D12_COMPARISON_FUNC)depth_stencil_config->stencil_front_face.comparison;
      desc.DepthStencilState.BackFace.StencilFailOp       = (D3D12_STENCIL_OP)depth_stencil_config->stencil_back_face.stencil_fail;
      desc.DepthStencilState.BackFace.StencilDepthFailOp  = (D3D12_STENCIL_OP)depth_stencil_config->stencil_back_face.depth_fail;
      desc.DepthStencilState.BackFace.StencilPassOp       = (D3D12_STENCIL_OP)depth_stencil_config->stencil_back_face.pass;
      desc.DepthStencilState.BackFace.StencilFunc         = (D3D12_COMPARISON_FUNC)depth_stencil_config->stencil_back_face.comparison;
    }
  }

  if (stream_output)
  {
    desc.StreamOutput = ((D3D12_StreamOutputConfig*)stream_output)->GetDesc();
  }
}
