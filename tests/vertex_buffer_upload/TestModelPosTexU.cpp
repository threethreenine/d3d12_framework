#include <sstream>
#include <directxmath.h>
#include "TestModelPosTexU.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestModelPosTexU::TestModelPosTexU(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList& command_list)
{
  command_list.Reset(NULL);

  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  m_vert_data[0] = { XMFLOAT3(-4.0f,-3.0f, 1.0f), 0 };
  m_vert_data[1] = { XMFLOAT3(-3.0f,-3.0f, 1.0f), 1 };
  m_vert_data[2] = { XMFLOAT3(-3.0f,-2.0f, 1.0f), 1 };
  m_vert_data[3] = { XMFLOAT3(-4.0f,-2.0f, 1.0f), 0 };
  try
  {
    m_verts = VertexBuffer_PositionTextureU::CreateD3D12(graphics, ARRAYSIZE(m_vert_data), m_vert_data);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the gpu vertex buffer
  try
  {
    m_gpu_verts = VertexBufferGPU_PositionTextureU::CreateD3D12(graphics, m_verts->GetNumVertices());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload to the GPU vertex buffer
  try
  {
    m_verts->PrepUpload(graphics, command_list, *m_gpu_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    2, 1, 0,
    3, 2, 0
  };
  try
  {
    m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the gpu index buffer
  try
  {
    m_gpu_indices = IndexBufferGPU16::CreateD3D12(graphics, m_indices->GetNumIndices());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create GPU index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload to the GPU index buffer
  try
  {
    m_indices->PrepUpload(graphics, command_list, *m_gpu_indices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to GPU index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the texture image
  UINT width;
  GraphicsDataFormat format;
  vector<UINT8> tex_bytes;
  CreateTexture(width, format, tex_bytes);

  // create the texture
  try
  {
    m_texture = Texture1D::CreateD3D12(graphics, *shader_buffer_heap, width, format);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  TextureUploadBuffer* upload_texture;
  try
  {
    upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // start uploading the texture
  try
  {
    upload_texture->PrepUpload(graphics, command_list, *m_texture, tex_bytes);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // finish uploading the textures
  try
  {
    command_list.Close();
    graphics.ExecuteCommandList(command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to finish uploading textures:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  delete upload_texture;
}

TestModelPosTexU::~TestModelPosTexU()
{
  delete m_texture;
  delete m_indices;
  delete m_verts;
  delete m_gpu_verts;
  delete m_gpu_indices;
}

void TestModelPosTexU::UpdateVertexBuffer(GraphicsCore& graphics, bool initial, CommandList& command_list)
{
  if (initial)
  {
    m_vert_data[0] = { XMFLOAT3(-4.0f,-3.0f, 1.0f), 0 };
    m_vert_data[1] = { XMFLOAT3(-3.0f,-3.0f, 1.0f), 1 };
    m_vert_data[2] = { XMFLOAT3(-3.0f,-2.0f, 1.0f), 1 };
    m_vert_data[3] = { XMFLOAT3(-4.0f,-2.0f, 1.0f), 0 };
  }
  else
  {
    m_vert_data[0] = { XMFLOAT3(-4.0f,-3.0f, 1.0f), 1 };
    m_vert_data[1] = { XMFLOAT3(-3.0f,-3.0f, 1.0f), 0 };
    m_vert_data[2] = { XMFLOAT3(-3.0f,-2.0f, 1.0f), 0 };
    m_vert_data[3] = { XMFLOAT3(-4.0f,-2.0f, 1.0f), 1 };
  }
  try
  {
    m_verts->Upload(0, m_vert_data, ARRAYSIZE(m_vert_data));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload to the GPU vertex buffer
  try
  {
    m_verts->PrepUpload(graphics, command_list, *m_gpu_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

const VertexBufferGPU_PositionTextureU* TestModelPosTexU::GetVertexBuffer() const
{
  return m_gpu_verts;
}

const IndexBufferGPU16* TestModelPosTexU::GetIndexBuffer() const
{
  return m_gpu_indices;
}

const Texture1D* TestModelPosTexU::GetTexture() const
{
  return m_texture;
}

void TestModelPosTexU::CreateTexture(UINT& width, GraphicsDataFormat& format, std::vector<UINT8>& bytes)
{
  width  = 64;
  format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent = x / (float)width;
    bytes[byte_index] = (UINT8)(255 * (1 - percent));
    bytes[byte_index + 1] = 0;
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}
