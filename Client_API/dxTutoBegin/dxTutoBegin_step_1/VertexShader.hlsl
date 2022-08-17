





//매개변수로 들어오는 것은 IA에서 전달받은 것이다
//리턴값은 PixelShader로 전달된다
//
//정점셰이더 : 정점 하나당 작동하는 프로그램
float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}