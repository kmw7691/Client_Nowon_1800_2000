


//cbuffer 상수버퍼 만들기 예약어
//
//16byte단위로 정렬 해야 안전
cbuffer CBTransform
{
	matrix World;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix View;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix Projection;			//전역변수: 이 파일 전체에서 유효한 변수

	float4 LightDir;
	float4 LightColor;
};

struct VS_INPUT
{
	float4 Pos:POSITION; //<--주의 : 여기는4로, 3이면 작동안함
	float2 Tex:TEXCOORD;
						 //float3 Norm:NORMAL;	//법선데이터
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float2 Tex:TEXCOORD;
	//float3 Norm:NORMAL;//법선데이터
	//float4 Color:COLOR0;
};

PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;

	//o.Pos = pos;

	//IA에서 넘겨받은 정점 위치데이터에 
	//월드, 뷰, 투영 변환을 적용한다.
	o.Pos = mul(i.Pos, World);		//mul 셰이더함수, 벡터와 행렬의 곱셈
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);




	//일단은 그냥 넘기는 것으로 테스트
	//o.Norm = i.Norm;


	//월드변환을 적용하여 월드좌표계의 법선데이터로 인지

	//위치로 인지하고있다(x,y,z,1)
	o.Norm = mul(float4(i.Norm, 1), World).xyz;

	//벡터로 인지하고있다(x,y,z,0)
	o.Norm = mul(float4(i.Norm, 0), World).xyz;

	//색상 정보는 그대로 다음 단계로 넘긴다
	//o.Color = i.Color;

	return o;
}



