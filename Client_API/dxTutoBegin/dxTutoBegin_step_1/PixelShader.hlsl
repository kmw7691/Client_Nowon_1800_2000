



//vertex shader 로부터 데이터를 전달받는다
//최종적으로는 최종픽셀색상값을 만들어낸다

float4 main() : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}