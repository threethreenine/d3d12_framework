#include "private_inc/D3D12/Textures/D3D12_TextureUploadBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_BufferResourceHeap.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture3D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2DArray.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::Create(const GraphicsCore& graphics, const Texture1D& texture, BufferResourceHeap& resource_heap)
{
  return CreateInternal(graphics, texture.GetUploadBufferSize(), 1, resource_heap);
}

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::Create(const GraphicsCore& graphics, const Texture2D& texture, BufferResourceHeap& resource_heap)
{
  return CreateInternal(graphics, texture.GetUploadBufferSize(), 1, resource_heap);
}

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::Create(const GraphicsCore& graphics, const Texture3D& texture, BufferResourceHeap& resource_heap)
{
  return CreateInternal(graphics, texture.GetUploadBufferSize(), 1, resource_heap);
}

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::Create(const GraphicsCore& graphics, const Texture1DArray& texture, BufferResourceHeap& resource_heap)
{
  const D3D12_Texture1DArray& tex_array = (const D3D12_Texture1DArray&)texture;
  return CreateInternal(graphics, texture.GetUploadBufferSize(), tex_array.GetLength(), resource_heap);
}

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::Create(const GraphicsCore& graphics, const Texture2DArray& texture, BufferResourceHeap& resource_heap)
{
  const D3D12_Texture2DArray& tex_array = (const D3D12_Texture2DArray&)texture;
  return CreateInternal(graphics, texture.GetUploadBufferSize(), tex_array.GetLength(), resource_heap);
}

D3D12_TextureUploadBuffer* D3D12_TextureUploadBuffer::CreateInternal(const GraphicsCore& graphics, UINT64 upload_buffer_size, UINT16 length, BufferResourceHeap& resource_heap)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_BufferResourceHeap& buffer_heap = (D3D12_BufferResourceHeap&)resource_heap;

  D3D12_RESOURCE_DESC resource_desc;
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = upload_buffer_size;
  resource_desc.Height             = 1;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = DXGI_FORMAT_UNKNOWN;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

  ID3D12Resource* buffer = buffer_heap.CreateResource(graphics, resource_desc);
  if (buffer == NULL)
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  return new D3D12_TextureUploadBuffer(buffer);
}

D3D12_TextureUploadBuffer::D3D12_TextureUploadBuffer(ID3D12Resource* buffer)
:m_buffer(buffer)
{
}

D3D12_TextureUploadBuffer::~D3D12_TextureUploadBuffer()
{
  m_buffer->Release();
}

void D3D12_TextureUploadBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1D& texture, const vector<UINT8>& data)
{
  ID3D12Resource* dst_texture = ((D3D12_Texture1D&)texture).GetBuffer();
  PrepUploadInternal(graphics, command_list, dst_texture, 0, data);
}

void D3D12_TextureUploadBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture, const vector<UINT8>& data)
{
  ID3D12Resource* dst_texture = ((D3D12_Texture2D&)texture).GetBuffer();
  PrepUploadInternal(graphics, command_list, dst_texture, 0, data);
}

void D3D12_TextureUploadBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture3D& texture, const vector<UINT8>& data)
{
  ID3D12Resource* dst_texture = ((D3D12_Texture3D&)texture).GetBuffer();
  PrepUploadInternal(graphics, command_list, dst_texture, 0, data);
}

void D3D12_TextureUploadBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1DArray& texture, UINT16 index, const vector<UINT8>& data)
{
  ID3D12Resource* dst_texture = ((D3D12_Texture1DArray&)texture).GetBuffer();
  PrepUploadInternal(graphics, command_list, dst_texture, index, data);
}

void D3D12_TextureUploadBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2DArray& texture, UINT16 index, const vector<UINT8>& data)
{
  ID3D12Resource* dst_texture = ((D3D12_Texture2DArray&)texture).GetBuffer();
  PrepUploadInternal(graphics, command_list, dst_texture, index, data);
}

void D3D12_TextureUploadBuffer::PrepUploadInternal(GraphicsCore& graphics, CommandList& command_list, ID3D12Resource* texture, UINT16 index, const vector<UINT8>& data)
{
  ID3D12Device*       device      = ((D3D12_Core&)graphics).GetDevice();
  D3D12_RESOURCE_DESC dst_desc    = texture->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT dst_layout;
  UINT   dst_num_rows;
  UINT64 dst_row_size_in_bytes;
  UINT64 dst_total_bytes;
  device->GetCopyableFootprints(&dst_desc, index, 1, 0, &dst_layout, &dst_num_rows, &dst_row_size_in_bytes, &dst_total_bytes);

  SIZE_T memcpy_size = (SIZE_T)dst_row_size_in_bytes;

  D3D12_RESOURCE_DESC src_desc = m_buffer->GetDesc();
  if (src_desc.Width < (dst_total_bytes + dst_layout.Offset))
  {
    throw FrameworkException("Upload texture buffer too small for target texture");
  }
  else if (dst_row_size_in_bytes != memcpy_size)
  {
    throw FrameworkException("Target texture row size too large for upload texture buffer");
  }
  else if (data.size() < (memcpy_size * dst_num_rows * dst_layout.Footprint.Depth))
  {
    throw FrameworkException("Insufficient number of bytes for upload texture buffer");
  }

  UINT8* cpu_mem_start;
  HRESULT rc = m_buffer->Map(0, NULL, (void**)&cpu_mem_start);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to map texture upload buffer memory");
  }
  cpu_mem_start += dst_layout.Offset;
  const UINT8* src_mem_start = &(data[0]);
  for (UINT z = 0; z < dst_layout.Footprint.Depth; z++)
  {
    for (UINT row = 0; row < dst_num_rows; row++)
    {
      memcpy(cpu_mem_start, src_mem_start, memcpy_size);
      cpu_mem_start += dst_layout.Footprint.RowPitch;
      src_mem_start += memcpy_size;
    }
  }
  m_buffer->Unmap(0, NULL);

  D3D12_TEXTURE_COPY_LOCATION src;
  src.pResource        = m_buffer;
  src.Type             = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
  src.PlacedFootprint  = dst_layout;

  D3D12_TEXTURE_COPY_LOCATION dst;
  dst.pResource        = texture;
  dst.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
  dst.SubresourceIndex = index;

  ID3D12GraphicsCommandList* cmd_list = ((D3D12_CommandList&)command_list).GetCommandList();
  D3D12_RESOURCE_BARRIER prep_copy;
  prep_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  prep_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  prep_copy.Transition.pResource   = texture;
  prep_copy.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  prep_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
  prep_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
  cmd_list->ResourceBarrier(1, &prep_copy);

  cmd_list->CopyTextureRegion(&dst, 0, 0, 0, &src, NULL);

  D3D12_RESOURCE_BARRIER done_copy;
  done_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  done_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  done_copy.Transition.pResource   = texture;
  done_copy.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  done_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  done_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
  cmd_list->ResourceBarrier(1, &done_copy);
}
