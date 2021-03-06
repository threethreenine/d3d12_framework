#include "private_inc/D3D12/Textures/D3D12_Texture2DRenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_Texture.h"

Texture2DRenderTarget* D3D12_Texture2DRenderTarget::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format)
{
  D3D12_Texture::CreatedTexture tex = D3D12_Texture::Create(graphics, shader_buffer_heap, width, height, 1, format, D3D12_SRV_DIMENSION_TEXTURE2D, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, 1);
  return new D3D12_Texture2DRenderTarget(tex.buffer, tex.gpu_handle, width, height, format);
}

D3D12_Texture2DRenderTarget::D3D12_Texture2DRenderTarget(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, GraphicsDataFormat format)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_width(width),
 m_height(height),
 m_format(format)
{
}

D3D12_Texture2DRenderTarget::~D3D12_Texture2DRenderTarget()
{
  m_buffer->Release();
}

ID3D12Resource* D3D12_Texture2DRenderTarget::GetResource() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_Texture2DRenderTarget::GetGPUAddr() const
{
  return m_gpu_mem;
}
