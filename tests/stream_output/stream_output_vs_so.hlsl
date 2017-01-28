cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos : POSITION;
};

struct VertexShaderOutput
{
  float4 raw_pos : POSITION;
  float4 pos     : SV_POSITION;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.raw_pos = input.pos;
  output.pos     = mul(input.pos, wvp);

  return output;
}
