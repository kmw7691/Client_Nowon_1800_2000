

struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};



//�Ű������� ������ ���� IA���� ���޹��� ���̴�
//���ϰ��� PixelShader�� ���޵ȴ�
//
//�������̴� : ���� �ϳ��� �۵��ϴ� ���α׷�
VS_OUTPUT main( float4 pos : POSITION, float4 Color : COLOR)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.Pos = pos;

	o.Color = Color;

	return o;
}