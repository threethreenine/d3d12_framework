#ifndef VERTEX_BUFFER_CUSTOM_H
#define VERTEX_BUFFER_CUSTOM_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer that applications define the data of
/// </summary>
class VertexBuffer_Custom : public VertexBuffer
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
    static VertexBuffer_Custom* CreateD3D12(GraphicsCore& graphics, UINT num, UINT size, const void* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_Custom();

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
    virtual void Upload(UINT buffer_start_index, const void* data, UINT num_bytes) = 0;

  protected:
    VertexBuffer_Custom();
    
  private:
    // disabled
    VertexBuffer_Custom(const VertexBuffer_Custom& cpy);
    VertexBuffer_Custom& operator=( const VertexBuffer_Custom& cpy);
};

#endif /* VERTEX_BUFFER_CUSTOM_H */
