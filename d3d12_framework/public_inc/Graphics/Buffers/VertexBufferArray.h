#ifndef VERTEX_BUFFER_ARRAY_H
#define VERTEX_BUFFER_ARRAY_H

class VertexBuffer_Custom;
class VertexBuffer_PositionTexture;
class VertexBuffer_PositionColor;

#include <windows.h>
#include "Graphics/Buffers/VertexBuffer_Custom.h"
#include "Graphics/Buffers/VertexBuffer_PositionTexture.h"
#include "Graphics/Buffers/VertexBuffer_PositionColor.h"

/// <summary>
/// Container of multiple vertex buffers and allows for quickly sending multiple vertex buffers to the input assembler stage
/// </summary>
class VertexBufferArray
{
  public:
    /// <summary>
    /// Creates a vertex buffer array with the specified number of elements. The array is initialized to all elements clear of a vertex buffer.
    /// </summary>
    /// <param name="num_buffers">
    /// number of buffers that will be in the array
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer array instance on success
    /// NULL on error
    /// </returns>
    static VertexBufferArray* CreateD3D12(UINT num_buffers);
    
    virtual ~VertexBufferArray();
    
    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// <remarks>
    /// This does not perform bounds checking
    /// </remarks>
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    virtual void Set(UINT index, const VertexBuffer_Custom& buffer) = 0;

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// <remarks>
    /// This does not perform bounds checking
    /// </remarks>
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    virtual void Set(UINT index, const VertexBuffer_PositionTexture& buffer) = 0;

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// <remarks>
    /// This does not perform bounds checking
    /// </remarks>
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    virtual void Set(UINT index, const VertexBuffer_PositionColor& buffer) = 0;
    
    /// <summary>
    /// Removes any vertex buffer from the specified index
    /// </summary>
    /// <param name="index">
    /// which index to clear
    /// <remarks>
    /// This does not perform bounds checking
    /// </remarks>
    /// </param>
    virtual void Clear(UINT index) = 0;

    /// <summary>
    /// Retrieves the number of buffers the array was created to hold
    /// </summary>
    /// <returns>
    /// number of entries in the array
    /// </returns>
    virtual UINT GetNumBuffers() const = 0;

  protected:
    VertexBufferArray();
    
  private:
    // disabled
    VertexBufferArray(const VertexBufferArray& cpy);
    VertexBufferArray& operator=(const VertexBufferArray& cpy);
};

#endif /* VERTEX_BUFFER_ARRAY_H */
