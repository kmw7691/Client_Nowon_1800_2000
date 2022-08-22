

//struct VS_OUTPUT
//{
//	float4 Pos:SV_POSITION;
//	float4 Color:COLOR0;
//};

cbuffer CBTransform
{
	matrix World;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix View;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix Projection;			//전역변수: 이 파일 전체에서 유효한 변수

	float4 LightDir;
	float4 LightColor;
};


struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL;//법선데이터
	//float4 Color:COLOR0;
};


//Vertex Shader로부터 데이터를 전달받는다.
//최종적으로는 최종픽셀색상값을 만들어낸다.

//float4 main() : SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	//이제 vertex shading단계에서 전달받은 정점의 색상으로 픽셀을 칠한다
	//return i.Color;

	float4 color = 0;


	//빛벡터와 법선벡터를 이용하여 음영을 만들자
	saturate(dot((float3)LightDir, i, Norm)* LightColor);

	color.a = 1;



	return color;
}