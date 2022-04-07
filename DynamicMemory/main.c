#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // 동적 할당 함수들이 들어있는 헤더파일

// 동적 메모리 할당 ( 힙 영역에 메모리를 동적으로 할당 )
// 
// 동적으로 메모리를 할당해주는 함수 : 
// malloc( 할당 메모리 byte 크기 );
//
// 쓰는 이유 :
// 배열의 크기와 같은 경우 다양한 종류나 값이 할당되어야 할때
// 크기를 미리 정해줄 수 없고, 조건에 따라 맞는 크기를 확보해야하는 경우가 있기 때문
//
// 동적으로 메모리를 할당한 후에 0으로 초기화 해주는 함수 :
// calloc(할당할 메모리 단위 수, 할당할 메모리 단위 크기)
//
// 쓰는 이유 : 
// 할당한 후에 쓰레기값이 들어있으면 안되는경우
//
// 동적으로 할당된 메모리의 할당 크기를 조절해주는 함수
// realloc
//
// 쓰는이유 :
// 이미 할당했지만 할당한 공간의 크기를 변경하고 싶을때 &
// 기존 쓰던 주소를 유지하고 싶을때
// 만약 포인터가 null일 경우, malloc 과 똑같이 동작한다.

// DOS 창에서 실행파일 실행시
// C\: > 실행파일 이름
// 이라고 하면 단순 실행되지만 특별한 기능이나 옵션을 부여하고싶을때
// C\: > 실행파일이름 문자열1 문자열2 ...
// 형태로 써주면
// 모든 문자열을 동적할당한 후에 main함수 인자로 넘겨준다

int main(int argc, char **argv) {

	// argc : argument count, 문자열 갯수
	// argv : argument vector, 문자열 배열, 끝에는 null추가

	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

	while(*argv)
	{
		printf("%s\n", *argv);
		argv++;
	}


	int* p;
	p = (int*)malloc(sizeof(int));
	
	if (p == NULL) exit(1);

	printf("%d\n", *p);

	int* p2, a = 0;
	p2 = &a;
	// free
	// 인자로 넣어준 포인터의 값(주소)에 접근해서
	// 해당 포인터 주소부터 할당받은 영역을 해제함.
	//
	// 선언된 변수의 주소를 포인터에 대입해서 사용할때는
	// 포인터는 스택영역의 주소를 가리키고 있기때문에 
	// 함수 호출스택이 해제될때, 해당 변수의 주소의 메모리는 같이 해제되기때문에
	// free함수를 통해서 해당 메모리 영역을 해제해줄 필요없지만
	// 동적할당된 힙 영역의 메모리는 함수가 스택에서 해제되어도
	// 힙영역의 메모리영역이 해제되지 않기 때문에 힙영역에 할당된 메모리의 주소를
	// 참조해서 동적할당된 메모리를 해제해줘야함
	free(p);

	// calloc
	int count = 16;
	p = calloc(16, sizeof(int));
	//p = malloc(16 * sizeof(int));
	p[0] = 4;
	p[1] = 3;
	p[2] = 1;
	p[3] = 0;
	p[4] = 5;
	for (int i = 0; i < count; i++)
	{
		printf("%d\n", p[i]);
	}

	p = (int*)realloc(p, count * sizeof(int));

	free(p);

	printf("\n");

	// 입력 문자열을 저장하는 예시
	char input[100];
	count = 3;

	char** spp;

	spp = (char**)malloc(count * sizeof(char*));
	if (spp == NULL) exit(1);

	for (int i = 0; i < count; i++)
	{
		scanf("%s", input);
		spp[i] = (char*)malloc(strlen(input) + 1);
		strcpy(spp[i], input);
	}

	for (int i = 0; i < count; i++)
	{
		printf("%s (%d).", spp[i], strlen(spp[i]));
		free(spp[i]);
	}
	
	free(spp);

	return 0;
}