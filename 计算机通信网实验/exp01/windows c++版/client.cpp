#include <stdlib.h>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll
#pragma warning(disable:4996)
int main()
{
    //��ʼ��DLL
    WSADATA wsaData;
	int re = 0;
    WSAStartup(MAKEWORD(2, 2), &wsaData);//���õ������µ�2.2�汾   MAKEWORD�������Զ԰汾�Ž����л�����һ���꺯��

    //�����׽���
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //���������������
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(18000);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //���շ��������ص�����
    char szBuffer[MAXBYTE] = { 0 };
	while(1){
		    re = recv(sock, szBuffer, MAXBYTE, NULL);
			if(re<0 || re==0)
				break;
			//������յ�������
			printf("Message form server: %s\n", szBuffer);
			memset(szBuffer,0,MAXBYTE);
	}

    system("pause");
    //�ر��׽���
    closesocket(sock);
    //��ֹʹ�� DLL
    WSACleanup();   
    return 0;
}
