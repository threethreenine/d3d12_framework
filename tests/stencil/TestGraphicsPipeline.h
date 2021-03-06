#ifndef TEST_GRAPHICS_PIPELINE_H
#define TEST_GRAPHICS_PIPELINE_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"
#include "Occluder.h"
#include "TestModel.h"
#include "Camera.h"

class TestGraphicsPipeline
{
  public:
    TestGraphicsPipeline(GraphicsCore& graphics);
    ~TestGraphicsPipeline();

    /// <summary>
    /// Retrieves the shader resource descriptor heap for the pipeline
    /// </summary>
    /// <returns>
    /// shader resource descriptor heap
    /// </returns>
    ShaderResourceDescHeap* GetShaderResourceDescHeap() const;

    /// <summary>
    /// Retrieves the command list for the pipeline
    /// </summary>
    /// <returns>
    /// the pipeline's command list
    /// </returns>
    CommandList* GetCommandList() const;

    /// <summary>
    /// Sets the position of the light source.  Since this test program only uses 1 light source, this is a set function instead of adding to a collection.
    /// </summary>
    /// <param name="light_pos">
    /// position of the light source
    /// </param>
    void SetLightPos(const DirectX::XMFLOAT3& light_pos);

    /// <summary>
    /// Sets the model for the occluder.  Since this test program only uses 1 occluder, this is a set function instead of adding to a collection.
    /// </summary>
    /// <param name="model">
    /// model to render
    /// </param>
    void SetOccluder(const Occluder* model);

    /// <summary>
    /// Sets the model to render.  Since this test program only uses 1 model, this is a set function instead of adding to a collection.
    /// </summary>
    /// <param name="model">
    /// model to render
    /// </param>
    void SetModel(const TestModel* model);

    /// <summary>
    /// Sets a camera for the viewport
    /// </summary>
    /// <param name="cam">
    /// camera to use for the viewport
    /// </param>
    void SetCamera(const Camera* cam);

    /// <summary>
    /// Draws the current frame
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void Draw(GraphicsCore& graphics);

    /// <summary>
    /// Informs the pipeline the core graphics interface has processed a resize event
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void Resize(GraphicsCore& graphics);

  private:
    // disabled
    TestGraphicsPipeline();
    TestGraphicsPipeline(const TestGraphicsPipeline& cpy);
    TestGraphicsPipeline& operator=(const TestGraphicsPipeline& cpy);

    /// <summary>
    /// Helper function for creating the depth stencil on load and on resize
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void CreateDepthStencil(GraphicsCore& graphics);

    /// <summary>
    /// Draws the shadow pass for the current frame
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void DrawShadowPass(GraphicsCore& graphics, const RenderTarget& render_target);

    /// <summary>
    /// Draws the depth fail pass for the current frame
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void DrawDepthFailPass(GraphicsCore& graphics, const RenderTarget& render_target);

    /// <summary>
    /// Draws the shadow pass for the current frame
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void DrawLitPass(GraphicsCore& graphics, const RenderTarget& render_target);

    /// <summary>
    /// light source position
    /// </summary>
    DirectX::XMFLOAT3 m_light_pos;

    /// <summary>
    /// model to block some of the light from the light source
    /// </summary>
    const Occluder* m_occluder;

    /// <summary>
    /// test model
    /// </summary>
    const TestModel* m_model;

    /// <summary>
    /// cameras for the test viewport
    /// </summary>
    const Camera* m_camera;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// graphics pipeline for the shadow pass
    /// </summary>
    Pipeline* m_pipeline_shadow;

    /// <summary>
    /// graphics pipeline for the depth fail pass
    /// </summary>
    Pipeline* m_pipeline_depth_fail;

    /// <summary>
    /// graphics pipeline for the lit pass
    /// </summary>
    Pipeline* m_pipeline_lit;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// Constant buffer for the occluder
    /// </summary>
    ConstantBuffer* m_constant_buffer_occluder;

    /// <summary>
    /// Constant buffer for the model
    /// </summary>
    ConstantBuffer* m_constant_buffer_model;

    /// <summary>
    /// Constant buffer for the light source position
    /// </summary>
    ConstantBuffer* m_constant_buffer_lighting;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;
};

#endif /* TEST_GRAPHICS_PIPELINE_H */
