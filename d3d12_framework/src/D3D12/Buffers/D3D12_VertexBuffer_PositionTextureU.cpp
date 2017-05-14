#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBuffer_PositionTextureU* D3D12_VertexBuffer_PositionTextureU::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureU* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionTextureU), num, data, buffer, view);
  return new D3D12_VertexBuffer_PositionTextureU(num, buffer, view);
}

D3D12_VertexBuffer_PositionTextureU::D3D12_VertexBuffer_PositionTextureU(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBuffer_PositionTextureU::~D3D12_VertexBuffer_PositionTextureU()
{
  m_buffer->Release();
}

UINT D3D12_VertexBuffer_PositionTextureU::GetNumVertices() const
{
  return m_num;
}

void D3D12_VertexBuffer_PositionTextureU::Upload(UINT buffer_start_index, const Vertex_PositionTextureU* data, UINT num_entries)
{
  const UINT num_bytes = num_entries * sizeof(Vertex_PositionTextureU);

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if ((buffer_start_index + num_bytes) > m_buffer->GetDesc().Width)
  {
    throw FrameworkException("Attempting to upload beyond the end of the vertex buffer");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  void* buffer_data;
  HRESULT rc = m_buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to map buffer for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(((Vertex_PositionTextureU*)buffer_data) + buffer_start_index, data, num_bytes);
  m_buffer->Unmap(0, NULL);
}

void D3D12_VertexBuffer_PositionTextureU::PrepUpload(GraphicsCore& graphics, CommandList& command_list, const VertexBufferGPU_PositionTextureU& buffer)
{
  D3D12_VertexBuffer::PrepUpload(graphics, command_list, m_buffer, ((const D3D12_VertexBufferGPU_PositionTextureU&)buffer).GetResource());
}
