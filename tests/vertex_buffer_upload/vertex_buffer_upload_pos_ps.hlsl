struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  return float4(1, 0, 0, 1);
}
