#pragma warning (disable : 4996)
#include <stdio.h>

int main() {
	// 표준입출력함수
	// printf. scanf, putc, getc, puts, gets
	//                (char)       


	// fopen()
	// 기본적으로 현재 프로그램 파일이 있는 폴더에서 파일을 검색한다.
	// 하드디스크로부터 파일을 읽어들여서 FILE Stream의 버퍼에 등록하는 함수
	//
	//  파일 개방모드
	// r : 읽기 전용 (read mode) : 파일이 없으면 에러
	// w : 쓰기 전용 (write mode) : 파일이 없으면 생성
	// a : 덧붙여쓰기 전용 (append mode) : 파일이 없으면 생성
	// r+ : 읽기 쓰기 다가능 : 파일이없으면 에러
	// w+ : 읽기 쓰기 다가능 : 파일이 없으면 생성
	// a+ : 읽기 덧붙여쓰기 다가능 : 파일이 없으면 에러
	// rb : 바이너리 파일 읽기 전용 : 파일이 없으면 에러
	// wb : 바이너리 파일 쓰기 전용 : 파일이 없으면 생성
	// ab : 바이너리파일 덧붙여쓰기 전용 : 파일이 없으면 생성
	
	FILE* fp1 = fopen("a.txt", "r");

	// read mode에서 FILE* 가 NULL 이면
	// 파일을 못찾았다는 의미
	if (fp1 == NULL) {
		printf("failed to open a.txt\n");
		exit(1);
	}

	printf("%c\n", fgetc(fp1));
	printf("%c\n", fgetc(fp1));
	
	// FILE Stream의 버퍼에 등록되어있는 해당 파일을 등록 해제시키는 함수
	fclose(fp1);


	FILE* fp2 = fopen("b.txt", "r");
	if (fp2 == NULL) {
		printf("failed to create b.txt\n");
		exit(1);
	}
	char doOverwrite = 'N';
	printf("b,txt 를 덮어 쓰시겠습니까? 기존내용은 모두 삭제됩니다 (Y / N)");
	scanf("%c", &doOverwrite);
	if (doOverwrite != 'Y') {
		printf("b,txt에 파일 덮어쓰기를 취소하였습니다. 프로그램을 종료합니다.\n");
		fclose(fp2);
		exit(0);
	}

	// write mode로 파일을 열면 원래 내용이 모두 삭제됨
	// write mode로 파일을 여는데 실패하면 해당 파일을 생성함
	fp2 = fopen("b.txt", "w");
	

	// write mode에서 FILE* 가 NULL이면 
	// 파일을 생성하지 못했다는 의미
	if (fp2 == NULL) {
		printf("failed to create b.txt");
	}

	fputc('c', fp2);
	fclose(fp2);
	
	// 쓰기모드에서 버퍼에 들어있는 파일의 내용 수정이 끝나자마자 fclose를 호출해주는것이 안전.
	// 버퍼에서 해제되기 전까지는 하드디스크에 수정한 내용이 반영안되기 때문

	// append mode
	// 파일이 없으면 생성함
	FILE* fp3 = fopen("c.txt", "a");
	if (fp3 == NULL) {
		printf("failed to create c.txt\n");
		exit(1);
	}

	fputc('s', fp3);
	fclose(fp3);

	// 다양한 형태의 입출력
	FILE* fp4;
	FILE* fp5;

	char name[20] = "chulsu";
	int korean = 10, english = 20, math = 20;
	double average;

	fp4 = fopen("chulsu.txt", "r");
	if (fp4 == NULL) {
		printf("failed to open chulsu.txt. exit program");
		exit(0);
	}

	fp5 = fopen("youngheui.txt", "w");
	if (fp5 == NULL) {
		printf("failed to open chulsu.txt. exit program");
		exit(0);
	}
	// chulsu.txt.파일 내용으로 변수값수정
	fscanf(fp4, "%s %d %d %d", name, &korean, &english, &math);
	printf("%s %d %d %d\n", name, korean, english, math);
	fclose(fp4);

	fprintf(fp5, "%s %d %d %d\n", name, korean, english, math);
	printf("%s %d %d %d\n", name, korean, english, math);
	fclose(fp5);


	// 대용량 데이터의 입출력을 빠르게 해야한다면
	// fscanf 나 fprint 처럼 서식에 맞게 입출력하는 함수 말고
	// 바이너리 파일 그대로 입출력하는 fread 나 fwrite함수를 사용한다.
	FILE* fp6;
	fp6 = fopen("binary.txt", "wb");
	char a[] = ("qrfdasdkgabshd\n");
	fwrite(a, sizeof(a), 1, fp6);
	fclose(fp6);

	return 0;
}