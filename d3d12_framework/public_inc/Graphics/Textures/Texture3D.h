#ifndef TEXTURE3D_H
#define TEXTURE3D_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class Texture3D
{
  public:
    /// <summary>
    /// Creates a D3D12 3D texture
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
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="depth">
    /// depth of the texture in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture 3D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture3D* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, UINT16 mip_levels = 1);

    virtual ~Texture3D();
    
  protected:
    Texture3D();

  private:
    // disabled
    Texture3D(const Texture3D& cpy);
    Texture3D& operator=(const Texture3D& cpy);
};

#endif /* TEXTURE3D_H */
