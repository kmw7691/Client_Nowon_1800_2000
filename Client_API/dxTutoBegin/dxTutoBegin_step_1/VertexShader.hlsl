

struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};



//매개변수로 들어오는 것은 IA에서 전달받은 것이다
//리턴값은 PixelShader로 전달된다
//
//정점셰이더 : 정점 하나당 작동하는 프로그램
VS_OUTPUT main( float4 pos : POSITION, float4 Color : COLOR)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.Pos = pos;

	o.Color = Color;

	return o;
}