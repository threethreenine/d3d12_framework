#include <sstream>
#include <directxmath.h>
#include "TestGraphicsPipelinePosTexU.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestGraphicsPipelinePosTexU::TestGraphicsPipelinePosTexU(GraphicsCore& graphics)
:m_model(NULL),
 m_camera(NULL)
{
  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(2, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, 0, 1, COMPARISON_FUNC_NEVER, BORDER_COLOR_TRANSPARENT_BLACK,
      0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
    m_root_sig = RootSignature::CreateD3D12(graphics, *config);
    delete config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create root signature:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  Shader* vertex_shader;
  Shader* pixel_shader;
  InputLayout* input_layout;
  try
  {
    vertex_shader = Shader::LoadD3D12("vertex_buffer_upload_postexu_vs.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load vertex shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    pixel_shader = Shader::LoadD3D12("vertex_buffer_upload_postexu_ps.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load pixel shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    input_layout = InputLayout::CreateD3D12(2);
    input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
    input_layout->SetNextElement(SEM_TEXCOORD, 0, R32_FLOAT,       0, false);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create input layout:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    DepthStencilConfig ds_config;
    ds_config.depth_enable        = true;
    ds_config.stencil_enable      = false;
    ds_config.dsv_format          = D32_FLOAT;
    ds_config.depth_write_enabled = true;
    ds_config.depth_comparison    = COMPARISON_FUNC_LESS_EQUAL;
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_pipeline = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader, &ds_config, *rtv_config, *m_root_sig);
    delete rtv_config;
    delete input_layout;
    delete pixel_shader;
    delete vertex_shader;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create pipeline:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create vertex buffer array
  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the descriptor heap
  try
  {
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 2);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create resource descriptor heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the constant buffer
  try
  {
    m_constant_buffer = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMMATRIX));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the heap array
  try
  {
    m_heap_array = HeapArray::CreateD3D12(1);
    m_heap_array->SetHeap(0, *m_shader_buffer_heap);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create heap array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

TestGraphicsPipelinePosTexU::~TestGraphicsPipelinePosTexU()
{
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer;
  delete m_vert_array;
  delete m_pipeline;
  delete m_root_sig;
}

ShaderResourceDescHeap* TestGraphicsPipelinePosTexU::GetShaderResourceDescHeap() const
{
  return m_shader_buffer_heap;
}

void TestGraphicsPipelinePosTexU::SetModel(const TestModelPosTexU* model)
{
  m_model = model;

  // add the vertex buffer to the vertex buffer array
  try
  {
    m_vert_array->Set(0, *m_model->GetVertexBuffer());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to set model vertex buffer into the vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void TestGraphicsPipelinePosTexU::SetCamera(const Camera* cam)
{
  m_camera = cam;
}

void TestGraphicsPipelinePosTexU::Draw(GraphicsCore& graphics, CommandList& command_list)
{
  try
  {
    const IndexBuffer* index_buffer = m_model->GetIndexBuffer();

    command_list.SetPipeline(*m_pipeline);
    command_list.SetRootSignature(*m_root_sig);

    // upload the wvp matrix for the camera to the constant buffer
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    m_camera->GetView(tmp);
    wvp *= tmp;
    m_camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    command_list.SetHeapArray(*m_heap_array);
    command_list.SetTextureAsStartOfDescriptorTable(0, *m_model->GetTexture());
    command_list.SetConstantBuffer(1, *m_constant_buffer);

    command_list.IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    command_list.IASetVertexBuffers(*m_vert_array);
    command_list.IASetIndexBuffer(*index_buffer);

    command_list.DrawIndexedInstanced(index_buffer->GetNumIndices(), 2, 0);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw frame:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}
