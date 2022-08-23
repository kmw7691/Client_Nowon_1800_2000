

//struct VS_OUTPUT
//{
//	float4 Pos:SV_POSITION;
//	float4 Color:COLOR0;
//};

cbuffer CBTransform
{
	matrix World;				//��������: �� ���� ��ü���� ��ȿ�� ����
	matrix View;				//��������: �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;			//��������: �� ���� ��ü���� ��ȿ�� ����

	float4 LightDir;
	float4 LightColor;
};


struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL;//����������
	//float4 Color:COLOR0;
};


//Vertex Shader�κ��� �����͸� ���޹޴´�.
//���������δ� �����ȼ������� ������.

//float4 main() : SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	//���� vertex shading�ܰ迡�� ���޹��� ������ �������� �ȼ��� ĥ�Ѵ�
	//return i.Color;

	float4 color = 0;



	//�����Ϳ� �������͸� �̿��Ͽ� ������ ������
	//���� = ������ dot ��������<----[-1,1]
	//��������(����) <---[0,12\]
	color = saturate(dot((float3)LightDir, i.Norm) * LightColor);

	color.a = 1;



	return color;
}