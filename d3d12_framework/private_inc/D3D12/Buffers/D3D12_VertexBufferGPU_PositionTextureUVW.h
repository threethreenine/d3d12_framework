#ifndef D3D12_VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H
#define D3D12_VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUVW.h"

class D3D12_VertexBufferArray;

/// <summary>
/// Vertex buffer whose elements are position and texture values
/// </summary>
class D3D12_VertexBufferGPU_PositionTextureUVW : public VertexBufferGPU_PositionTextureUVW
{
  public:
    /// <summary>
    /// Creates a vertex buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_VertexBufferGPU_PositionTextureUVW* Create(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    ~D3D12_VertexBufferGPU_PositionTextureUVW();

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    UINT GetNumVertices() const;

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the vertex buffer
    /// </returns>
    ID3D12Resource* GetResource() const;
    
  private:
    // disabled
    D3D12_VertexBufferGPU_PositionTextureUVW();
    D3D12_VertexBufferGPU_PositionTextureUVW(const D3D12_VertexBufferGPU_PositionTextureUVW& cpy);
    D3D12_VertexBufferGPU_PositionTextureUVW& operator=(const D3D12_VertexBufferGPU_PositionTextureUVW& cpy);
    
    /// <summary>
    /// Creates a vertex buffer
    /// </summary>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="buffer">
    /// vertex buffer
    /// </param>
    /// <param name="view">
    /// vertex buffer view
    /// </param>
    /// <param name="type">
    /// which type of texture coordinates are stored in this vertex buffer
    /// </param>
    D3D12_VertexBufferGPU_PositionTextureUVW(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view);

    /// <summary>
    /// number of entries in the buffer
    /// </summary>
    UINT m_num;

    /// <summary>
    /// vertex buffer
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// vertex buffer view, used to provide data to the command list for rendering
    /// </summary>
    D3D12_VERTEX_BUFFER_VIEW m_view;

    // allow D3D12_VertexBufferArray full access to the members since it is an optimization for multiple vertex buffers
    friend D3D12_VertexBufferArray;
};

#endif /* D3D12_VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H */
