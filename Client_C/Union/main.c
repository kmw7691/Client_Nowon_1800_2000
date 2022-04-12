#include <stdio.h>


// ����ü union
// union ���� ���� ����� ū ����� ������ ũ�⸸ŭ ���� �Ҵ�
// ������ ������� �ش� ������ ������
typedef union _Jobinfo {
	char schoolName[20];
	char companyName[20];
}Jobinfo;

typedef struct Person {
	char name[20];
	Jobinfo jobinfo;
}Person;

int main() {
	
	Person a, b;

	strcpy(a.name, "Luke");
	strcpy(a.jobinfo.schoolName, "KoreaSchool");

	strcpy(b.name, "Dina");
	strcpy(b.jobinfo.companyName, "StrongCompany");

	printf("Luke's schoolName : %s\n", a.jobinfo.schoolName);
	printf("Luke's CompanyName : %s\n", a.jobinfo.companyName);
	printf("Dina's CompanyName : %s\n", b.jobinfo.companyName);
	printf("Dina's SchoolName : %s\n", b.jobinfo.schoolName);
}