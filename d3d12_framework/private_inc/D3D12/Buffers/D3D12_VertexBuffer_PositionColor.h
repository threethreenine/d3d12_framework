#ifndef D3D12_VERTEXBUFFER_POSITION_COLOR_H
#define D3D12_VERTEXBUFFER_POSITION_COLOR_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBuffer_PositionColor.h"

class D3D12_VertexBufferArray;

/// <summary>
/// Vertex buffer whose elements are position and rgba color values
/// </summary>
class D3D12_VertexBuffer_PositionColor : public VertexBuffer_PositionColor
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
    /// <param name="data">
    /// initial data for the vertex buffer
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_VertexBuffer_PositionColor* Create(GraphicsCore& graphics, UINT num, const Vertex_PositionColor* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    ~D3D12_VertexBuffer_PositionColor();

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    UINT GetNumVertices() const;

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified index
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the Vertex_PositionColor in the vertex buffer to start writing data to
    /// </param>
    /// <param name="data">
    /// data to write to the vertex buffer
    /// </param>
    /// <param name="num_entries">
    /// number of entries to write to the vertex buffer
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Upload(UINT buffer_start_index, const Vertex_PositionColor* data, UINT num_entries);

    /// <summary>
    /// Preps the command list for uploading the contents of the vertex buffer to the specified GPU-only accessible vertex buffer.  The command list must execute followed by a fence for the transfer to be
    /// completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use for uploading
    /// </param>
    /// <param name="buffer">
    /// GPU-only vertex buffer to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, const VertexBufferGPU_PositionColor& buffer);
    
  private:
    // disabled
    D3D12_VertexBuffer_PositionColor();
    D3D12_VertexBuffer_PositionColor(const D3D12_VertexBuffer_PositionColor& cpy);
    D3D12_VertexBuffer_PositionColor& operator=(const D3D12_VertexBuffer_PositionColor& cpy);
    
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
    D3D12_VertexBuffer_PositionColor(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view);

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

#endif /* D3D12_VERTEXBUFFER_POSITION_COLOR_H */
