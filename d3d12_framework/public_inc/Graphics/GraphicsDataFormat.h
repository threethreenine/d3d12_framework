#ifndef GRAPHICS_DATA_FORMAT_H
#define GRAPHICS_DATA_FORMAT_H

/// <summary>
/// Enum of the various graphics data formats
/// </summary>
/// <remarks>
/// Values must match up to the values used by DXGI_FORMAT
/// </remarks>
enum GraphicsDataFormat
{
  R32G32B32A32_FLOAT = 2,
  R32G32B32_FLOAT    = 6,
  R32G32_FLOAT       = 16,
  D32_FLOAT_S8_UINT  = 20,
  R8B8G8A8_UNORM     = 28,
  D32_FLOAT          = 40,
  R32_FLOAT          = 41,
  R32_UINT           = 42,
  // todo: fill in the rest
};

#endif /* GRAPHICS_DATA_FORMAT_H */
