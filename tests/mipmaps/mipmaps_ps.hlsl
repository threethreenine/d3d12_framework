Texture1D        tex1 : register(t0);
Texture2D        tex2 : register(t1);
Texture3D        tex3 : register(t2);
Texture1DArray   tex4 : register(t3);
Texture2DArray   tex5 : register(t4);
TextureCube      tex6 : register(t5);
TextureCubeArray tex7 : register(t6);
SamplerState     tex_sampler1 : register(s0);
SamplerState     tex_sampler2 : register(s1);

cbuffer TexturingMode : register(b1)
{
  uint mode;
  uint mipmap;
}

struct VertexShaderOutput
{
  float4 pos      : SV_POSITION;
  float3 uvw      : TEXCOORD0;
  float3 cube_uvw : TEXCOORD1;
  uint   index    : TEXCOORD2;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  if (mode == 0)
  {
    if (mipmap == 0)
    {
      return tex1.Sample(tex_sampler1, input.uvw.x);
    }
    else
    {
      return tex1.Sample(tex_sampler2, input.uvw.x);
    }
  }
  else if (mode == 1)
  {
    if (mipmap == 0)
    {
      return tex2.Sample(tex_sampler1, input.uvw.xy);
    }
    else
    {
      return tex2.Sample(tex_sampler2, input.uvw.xy);
    }
  }
  else if (mode == 2)
  {
    if (mipmap == 0)
    {
      return tex3.Sample(tex_sampler1, input.uvw);
    }
    else
    {
      return tex3.Sample(tex_sampler2, input.uvw);
    }
  }
  else if (mode == 3)
  {
    if (mipmap == 0)
    {
      return tex4.Sample(tex_sampler1, float2(input.uvw.x, input.index));
    }
    else
    {
      return tex4.Sample(tex_sampler2, float2(input.uvw.x, input.index));
    }
  }
  else if (mode == 4)
  {
    if (mipmap == 0)
    {
      return tex5.Sample(tex_sampler1, float3(input.uvw.xy, input.index));
    }
    else
    {
      return tex5.Sample(tex_sampler2, float3(input.uvw.xy, input.index));
    }
  }
  else if (mode == 5)
  {
    if (mipmap == 0)
    {
      return tex6.Sample(tex_sampler1, input.cube_uvw);
    }
    else
    {
      return tex6.Sample(tex_sampler2, input.cube_uvw);
    }
  }
  else if (mode == 6)
  {
    if (mipmap == 0)
    {
      return tex7.Sample(tex_sampler1, float4(input.cube_uvw, input.index));
    }
    else
    {
      return tex7.Sample(tex_sampler2, float4(input.cube_uvw, input.index));
    }
  }
  else
  {
    return float4(1, 0, 0, 1);
  }
}
