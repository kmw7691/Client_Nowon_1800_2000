

struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};



//vertex shader �κ��� �����͸� ���޹޴´�
//���������δ� �����ȼ������� ������

float4 main(VS_OUTPUT i) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	//���� vertex shading �ܰ迡�� ���޹��� ������ �������� �ȼ��� ĥ�Ѵ�
	return i.Color;
}