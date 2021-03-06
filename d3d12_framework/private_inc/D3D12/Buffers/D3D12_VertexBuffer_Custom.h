#ifndef D3D12_VERTEX_BUFFER_CUSTOM_H
#define D3D12_VERTEX_BUFFER_CUSTOM_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBuffer_Custom.h"

class D3D12_VertexBufferArray;

/// <summary>
/// Vertex buffer that applications define the data of
/// </summary>
class D3D12_VertexBuffer_Custom : public VertexBuffer_Custom
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
    /// <param name="size">
    /// number of bytes in 1 entry
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
    static D3D12_VertexBuffer_Custom* Create(GraphicsCore& graphics, UINT num, UINT size, const void* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    ~D3D12_VertexBuffer_Custom();

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified byte
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the byte in the vertex buffer to start writing data to
    /// </param>
    /// <param name="data">
    /// data to write to the vertex buffer
    /// </param>
    /// <param name="num_bytes">
    /// number of bytes to write to the vertex buffer
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Upload(UINT buffer_start_index, const void* data, UINT num_bytes);

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    UINT GetNumVertices() const;

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
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, const VertexBufferGPU_Custom& buffer);
    
  private:
    // disabled
    D3D12_VertexBuffer_Custom();
    D3D12_VertexBuffer_Custom(const D3D12_VertexBuffer_Custom& cpy);
    D3D12_VertexBuffer_Custom& operator=(const D3D12_VertexBuffer_Custom& cpy);
    
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
    D3D12_VertexBuffer_Custom(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view);

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

#endif /* D3D12_VERTEX_BUFFER_CUSTOM_H */
