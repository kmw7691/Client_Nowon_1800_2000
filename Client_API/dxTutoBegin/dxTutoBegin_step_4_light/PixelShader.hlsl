

struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};



//Vertex Shader로부터 데이터를 전달받는다.
//최종적으로는 최종픽셀색상값을 만들어낸다.

//float4 main() : SV_TARGET
float4 main(VS_OUTPUT i) :SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	//이제 vertex shading단계에서 전달받은 정점의 색상으로 픽셀을 칠한다
	return i.Color;
}