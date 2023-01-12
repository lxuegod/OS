/*
�ṩ��ʾ��������Ϊ�˲���һ��������߽���һ�����ԣ�����������
�ȫ�ı���ʵ������˲�Ӧ��Ӧ�ó������վ��ʹ�ø�ʾ�����롣��
�ڳ�����ʾ�������Ԥ����;�����ʹ������ɵ�żȻ��̷�����ʧ��
����Ӣ��ʱ���Ƽ����޹�˾���е��κ����Ρ�
*/

#include "EOSApp.h"

//	bool����ͷ�ļ�
#include <stdbool.h>

//	�궨��10������
#define Num 10


//
// main �������������壺
// argc - argv ����ĳ��ȣ���С����Ϊ 1��argc - 1 Ϊ�����в�����������
// argv - �ַ���ָ�����飬���鳤��Ϊ�����в������� + 1������ argv[0] �̶�ָ��ǰ
//        ������ִ�еĿ�ִ���ļ���·���ַ�����argv[1] ��������ָ��ָ�����������
//        ������
//        ����ͨ������������ "a:\hello.exe -a -b" �������̺�hello.exe �� main ��
//        ���Ĳ��� argc ��ֵΪ 3��argv[0] ָ���ַ��� "a:\hello.exe"��argv[1] ָ��
//        �����ַ��� "-a"��argv[2] ָ������ַ��� "-b"��
//




int main(int argc, char* argv[])
{
	//
	// �������� EOS Ӧ�ó���ǰҪ�ر�ע����������⣺
	//
	// 1�����Ҫ�ڵ���Ӧ�ó���ʱ�ܹ����Խ����ں˲���ʾ��Ӧ��Դ�룬
	//    ����ʹ�� EOS ������Ŀ����������ȫ�汾�� SDK �ļ��У�Ȼ
	//    ��ʹ�ô��ļ��и���Ӧ�ó�����Ŀ�е� SDK �ļ��У����� EOS
	//    ������Ŀ�ڴ����ϵ�λ�ò��ܸı䡣
	//
	
	STARTUPINFO StartupInfo;
	//PROCESS_INFORMATION ProcInfoOne, ProcInfoTwo;
	
	//	�����������
	PROCESS_INFORMATION ProcInfo[Num];
	
	ULONG ulExitCode;	// �ӽ����˳���
	INT nResult = 0;	// main ��������ֵ��0 ��ʾ�ɹ����� 0 ��ʾʧ�ܡ�

	//printf("Create two processes and wait for the processes exit...\n\n");
	printf("Create ten processes and wait for the processes exit...\n\n");

	//
	// ʹ�ӽ��̺͸�����ʹ����ͬ�ı�׼�����
	//
	StartupInfo.StdInput = GetStdHandle(STD_INPUT_HANDLE);
	StartupInfo.StdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	StartupInfo.StdError = GetStdHandle(STD_ERROR_HANDLE);

	//
	// Ϊһ��Ӧ�ó���ͬʱ����ʮ���ӽ��̡�
	//
	int j;
	
	bool flag = true;
	for (j = 0; j < Num; j++) {
		flag = flag && CreateProcess("A:\\Hello.exe", NULL, 0, &StartupInfo, &ProcInfo[j]);
	}
		
	if(flag) {
		
		for (j = 0; j < Num; j++) {
			//
			// �����ӽ��̳ɹ����ȴ��ӽ������н�����
			//
			WaitForSingleObject(ProcInfo[j].ProcessHandle, INFINITE);
		}
		for (j = 0; j < Num; j++) {
			//
			// �õ�������ӽ��̵��˳��롣
			//
			GetExitCodeProcess(ProcInfo[j].ProcessHandle, &ulExitCode);
			printf("\nThe process %d exit with %d.\n", j+1, ulExitCode);
		}
		for (j = 0; j < Num; j++) {
			
			//
			// �رղ���ʹ�õľ����
			//
			CloseHandle(ProcInfo[j].ProcessHandle);
			CloseHandle(ProcInfo[j].ThreadHandle);
		}
			
	}else {

		printf("CreateProcess Failed, Error code: 0x%X.\n", GetLastError());
		nResult = 1;
	}
	


	return nResult;
}


