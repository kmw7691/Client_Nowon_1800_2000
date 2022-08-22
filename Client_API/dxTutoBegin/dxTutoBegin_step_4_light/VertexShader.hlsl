


//cbuffer 상수버퍼 만들기 예약어
//
//16byte단위로 정렬 해야 안전
cbuffer CBTransform
{
	matrix World;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix View;				//전역변수: 이 파일 전체에서 유효한 변수
	matrix Projection;			//전역변수: 이 파일 전체에서 유효한 변수
};


struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};

//매개변수로 들어오는 것은 IA 에서 전달받은 것이다.
//리턴값은 PixelShader로 전달된다
//
//정점셰이더: 정점 하나당 작동하는 프로그램
//float4 main( float4 pos : POSITION, float4 Color:COLOR ) : SV_POSITION	//SystemValue 시맨틱
VS_OUTPUT main(float4 pos : POSITION, float4 Color : COLOR) 
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	//o.Pos = pos;

	//IA에서 넘겨받은 정점 위치데이터에 
	//월드, 뷰, 투영 변환을 적용한다.
	o.Pos = mul(pos, World);		//mul 셰이더함수, 벡터와 행렬의 곱셈
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);

	//색상 정보는 그대로 다음 단계로 넘긴다
	o.Color = Color;

	return o;
}