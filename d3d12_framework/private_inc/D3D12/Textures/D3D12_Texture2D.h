#ifndef D3D12_TEXTURE_2D_H
#define D3D12_TEXTURE_2D_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture2D.h"

class D3D12_Texture2D : public Texture2D
{
  public:
    /// <summary>
    /// Creates a D3D12 texture
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
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture 2D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture2D* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format, UINT16 mip_levels);

    ~D3D12_Texture2D();

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Retrieves the GPU address for the texture
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

    /// <summary>
    /// Retrieves the number of mipmap levels the resource was created with
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    UINT16 GetNumMipmapLevels() const;

  private:
    // disabled
    D3D12_Texture2D();
    D3D12_Texture2D(const D3D12_Texture2D& cpy);
    D3D12_Texture2D& operator=(const D3D12_Texture2D& cpy);

    D3D12_Texture2D(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, GraphicsDataFormat format, UINT16 num_mip_levels);

    /// <summary>
    /// D3D12 texture resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the texture
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// width of the texture in pixels
    /// <summary>
    UINT m_width;

    /// <summary>
    /// height of the texture in pixels
    /// <summary>
    UINT m_height;

    /// <summary>
    /// texture format
    /// <summary>
    GraphicsDataFormat m_format;

    /// <summary>
    /// number of mipmap levels in the resource
    /// </summary>
    UINT16 m_num_mipmap_levels;
};

#endif /* D3D12_TEXTURE_2D_H */
