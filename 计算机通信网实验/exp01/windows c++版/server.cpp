#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma comment (lib, "ws2_32.lib")  //���ؾ�̬��ws2_32.dll
/**
CRT�е�һ�麯�����ʹ�ò��������ܻ���������ڴ�й¶��������������Ƿ����ʵȰ�ȫ���⡣��Щ�����磺strcpy��strcat�ȡ�
������Щ���⣬VC2005����ʹ����Щ�����ĸ��߼��İ�ȫ�汾��������Щ�������������һ��_s�ĺ�����
��Щ��ȫ�汾����ʹ����������Ч��Ҳ����ʶ���磺strcpy_s,calloc_s�ȡ�
��Ȼ�����ִ��ʹ���ϰ汾���ǰ�ȫ�汾����,�ڳ���ͷ���, 
#pragma  warning(disable:4996)	 //ȫ���ص�     
#pragma  warning(once:4996)      //����ʾһ��
*/      
#pragma warning(disable:4996)
using namespace std;
int main()
{
    WSADATA wsaData;
	int i = 0;
	/**
	socket���Ҫ���ø���socket������������Ҫ��Ws2_32.lib��ͷ�ļ�Winsock2.h��
	�����WSAStartup����Ϊ�������ϵͳ˵��������Ҫ���ĸ����ļ����øÿ��ļ��뵱ǰ��Ӧ�ó���󶨣��Ӷ��Ϳ��Ե��øð汾��socket�ĸ��ֺ����ˡ�
	*/
	/** ͷ�ļ� header�� ��Winsock2.h
	��library��      Ws2_32.lib
	ԭ�ͣ�int   PASCAL   FAR  WSAStartup ( WORD  wVersionRequested, LPWSADATA   lpWSAData );
	������wVersionRequested��Windows Sockets API�ṩ�ĵ��÷���ʹ�õ���߰汾�š���λ�ֽ�ָ�����汾(����)�ţ���λ�ֽ�ָ�����汾�š�
    lpWSAData ��ָ��WSADATA���ݽṹ��ָ�룬��������Windows Socketsʵ�ֵ�ϸ�ڡ�
	*/
    WSAStartup(MAKEWORD(2, 2), &wsaData);
	/**
	�������ò�ͬ��Winsock�汾������MAKEWORD(2,2)���ǵ���2.2�棬MAKEWORD(1,1)���ǵ���1.1�档
	��ͬ�汾��������ģ�����1.1��ֻ֧��TCP/IPЭ�飬��2.0�����֧�ֶ�Э�顣
	2.0�������õ��������ԣ��κ�ʹ��1.1���Դ���롢�������ļ���Ӧ�ó��򶼿��Բ����޸ĵ���2.0�淶��ʹ�á�
	����winsock 2.0֧���첽 1.1��֧���첽.
	*/
    SOCKET array_servSock[10] =	{0};
    //�����׽���,���һ����������ָ��Э�顣�׽ӿ����õ�Э�顣������߲���ָ��������0
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);  
    //���׽���
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = htons(18000);  //�˿�
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //�������״̬
    listen(servSock, 20);
    //���տͻ�������
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
  
   
	char str[20] = {0};
	char *str1 = "����";
	char str2[5] = {0};
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    while (1)   // ѭ����������
    {
		for(i=1;i<101;i++)
		{
			//printf("%s1",str);
			strcpy(str,str1);
			itoa(i,str2,10);
			strcat(str,str2);
			//printf("22");
			//printf("%s2",str);
			printf("%s\n",str);
			send(clntSock, str, strlen(str) + sizeof(char), NULL);
			Sleep(100);
			memset(str, 0, strlen(str));  //���û�����
		}

    }
    closesocket(clntSock);  //�ر��׽���
    //�ر��׽���
    closesocket(servSock);
    //��ֹ DLL ��ʹ��
    WSACleanup();
    return 0;
}
