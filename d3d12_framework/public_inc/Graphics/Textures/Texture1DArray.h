#ifndef TEXTURE1D_ARRAY_H
#define TEXTURE1D_ARRAY_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class Texture1DArray
{
  public:
    /// <summary>
    /// Creates a D3D12 1D texture array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture 1D array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture1DArray* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT16 length, GraphicsDataFormat format, UINT16 mip_levels = 1);

    virtual ~Texture1DArray();
    
  protected:
    Texture1DArray();

  private:
    // disabled
    Texture1DArray(const Texture1DArray& cpy);
    Texture1DArray& operator=(const Texture1DArray& cpy);
};

#endif /* TEXTURE1D_ARRAY_H */
