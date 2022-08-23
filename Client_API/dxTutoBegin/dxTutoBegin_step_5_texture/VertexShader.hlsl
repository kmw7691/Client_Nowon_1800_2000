


//cbuffer ������� ����� �����
//
//16byte������ ���� �ؾ� ����
cbuffer CBTransform
{
	matrix World;				//��������: �� ���� ��ü���� ��ȿ�� ����
	matrix View;				//��������: �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;			//��������: �� ���� ��ü���� ��ȿ�� ����

	float4 LightDir;
	float4 LightColor;
};

struct VS_INPUT
{
	float4 Pos:POSITION; //<--���� : �����4��, 3�̸� �۵�����
	float2 Tex:TEXCOORD;
						 //float3 Norm:NORMAL;	//����������
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float2 Tex:TEXCOORD;
	//float3 Norm:NORMAL;//����������
	//float4 Color:COLOR0;
};

PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;

	//o.Pos = pos;

	//IA���� �Ѱܹ��� ���� ��ġ�����Ϳ� 
	//����, ��, ���� ��ȯ�� �����Ѵ�.
	o.Pos = mul(i.Pos, World);		//mul ���̴��Լ�, ���Ϳ� ����� ����
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);




	//�ϴ��� �׳� �ѱ�� ������ �׽�Ʈ
	//o.Norm = i.Norm;


	//���庯ȯ�� �����Ͽ� ������ǥ���� ���������ͷ� ����

	//��ġ�� �����ϰ��ִ�(x,y,z,1)
	o.Norm = mul(float4(i.Norm, 1), World).xyz;

	//���ͷ� �����ϰ��ִ�(x,y,z,0)
	o.Norm = mul(float4(i.Norm, 0), World).xyz;

	//���� ������ �״�� ���� �ܰ�� �ѱ��
	//o.Color = i.Color;

	return o;
}



