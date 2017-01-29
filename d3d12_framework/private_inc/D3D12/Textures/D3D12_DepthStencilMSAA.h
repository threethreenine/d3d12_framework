#ifndef D3D12_DEPTH_STENCIL_MSAA_H
#define D3D12_DEPTH_STENCIL_MSAA_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/DepthStencilMSAA.h"
#include "private_inc/D3D12/Buffers/D3D12_DepthStencilDescHeap.h"

class D3D12_DepthStencilMSAA : public DepthStencilMSAA
{
  public:
    /// <summary>
    /// Creates a D3D12 MSAA depth stencil
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="quality">
    /// image quality level
    /// </param>
    /// <param name="default_depth_clear">
    /// default value to use for clearing the depth stencil
    /// </param>
    /// <returns>
    /// D3D12 depth stencil
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static DepthStencilMSAA* Create(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, float default_depth_clear);

    ~D3D12_DepthStencilMSAA();

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the depth stencil
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Retrieves the GPU address for the depth stencil
    /// </summary>
    /// <returns>
    /// GPU address for the depth stencil
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

    /// <summary>
    /// Retrieves the D3D12 CPU descriptor handle for the depth stencil
    /// </summary>
    /// <returns>
    /// D3D12 CPU descriptor handle
    /// </returns>
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() const;

  private:
    // disabled
    D3D12_DepthStencilMSAA();
    D3D12_DepthStencilMSAA(const D3D12_DepthStencilMSAA& cpy);
    D3D12_DepthStencilMSAA& operator=(const D3D12_DepthStencilMSAA& cpy);

    D3D12_DepthStencilMSAA(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, D3D12_CPU_DESCRIPTOR_HANDLE cpu_mem, UINT width, UINT height, UINT64 upload_size,
      D3D12_DepthStencilDescHeap* desc_heap);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="quality">
    /// image quality level
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(UINT width, UINT height, UINT sample_count, UINT quality, D3D12_RESOURCE_DESC& resource_desc);

    /// <summary>
    /// D3D12 depth stencil resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the depth stencil
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// CPU descriptor handle for depth stencil
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle;

    /// <summary>
    /// width of the depth stencil in pixels
    /// </summary>
    UINT m_width;

    /// <summary>
    /// height of the depth stencil in pixels
    /// </summary>
    UINT m_height;

    /// <summary>
    /// D3D12 descriptor heap that the depth stencil was created from
    /// </summary>
    D3D12_DepthStencilDescHeap* m_desc_heap;
};

#endif /* D3D12_DEPTH_STENCIL_MSAA_H */
