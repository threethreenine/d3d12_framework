#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer16.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBufferGPU16.h"

D3D12_IndexBuffer16* D3D12_IndexBuffer16::Create(GraphicsCore& graphics, UINT num, const WORD* data)
{
  ID3D12Resource* buffer;
  D3D12_INDEX_BUFFER_VIEW view;
  D3D12_IndexBuffer::CreateBuffer(graphics, sizeof(WORD), DXGI_FORMAT_R16_UINT, num, data, buffer, view);
  return new D3D12_IndexBuffer16(num, buffer, view);
}

D3D12_IndexBuffer16::D3D12_IndexBuffer16(UINT num, ID3D12Resource* buffer, D3D12_INDEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_IndexBuffer16::~D3D12_IndexBuffer16()
{
  m_buffer->Release();
}

UINT D3D12_IndexBuffer16::GetNumIndices() const
{
  return m_num;
}

void D3D12_IndexBuffer16::PrepUpload(GraphicsCore& graphics, CommandList& command_list, const IndexBufferGPU16& buffer)
{
  D3D12_IndexBuffer::PrepUpload(graphics, command_list, m_buffer, ((const D3D12_IndexBufferGPU16&)buffer).GetResource());
}

const D3D12_INDEX_BUFFER_VIEW& D3D12_IndexBuffer16::GetBuffer() const
{
  return m_view;
}
