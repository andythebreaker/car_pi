/*
 * testSocketClient.c
 *
 *  Created on: 2012-8-16
 *      Author: 皓月繁星
 */
#include <WINSOCK.H> 
#include <stdio.h>   
#include <iostream>

 //定義程式中使用的常量    
#define SERVER_ADDRESS "140.116.177.150" //伺服器端IP地址    
#define PORT           10087         //伺服器的埠號    
#define MSGSIZE        1024         //收發緩衝區的大小    
#pragma comment(lib, "ws2_32.lib")    

using namespace std;
int main()
{
	WSADATA wsaData;
	//連線所用套節字    
	SOCKET sClient;
	//儲存遠端伺服器的地址資訊    
	SOCKADDR_IN server;
	//收發緩衝區    
	char szMessage[MSGSIZE];
	//成功接收位元組的個數    
	int ret;
	// Initialize Windows socket library    
	WSAStartup(0x0202, &wsaData);
	// 建立客戶端套節字    
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP協議族；    
														 //SOCK_STREAM, IPPROTO_TCP具體指明使用TCP協議    
	// 指明遠端伺服器的地址資訊(埠號、IP地址等)    
	memset(&server, 0, sizeof(SOCKADDR_IN)); //先將儲存地址的server置為全0    
	server.sin_family = PF_INET; //宣告地址格式是TCP/IP地址格式    
	server.sin_port = htons(PORT); //指明連線伺服器的埠號，htons()用於 converts values between the host and network byte order    
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //指明連線伺服器的IP地址    
														//結構SOCKADDR_IN的sin_addr欄位用於儲存IP地址，sin_addr欄位也是一個結構體，sin_addr.s_addr用於最終儲存IP地址    
														//inet_addr()用於將 形如的"127.0.0.1"字串轉換為IP地址格式    
	//連到剛才指明的伺服器上    
	connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN)); //連線後可以用sClient來使用這個連線    
																		//server儲存了遠端伺服器的地址資訊    
	while (TRUE) {
		printf("Send:");
		//從鍵盤輸入    
		//gets(szMessage); //The gets() functionreads characters from stdin and loads them into szMessage  
		cin >> szMessage;
		// 傳送資料    
		send(sClient, szMessage, strlen(szMessage), 0); //sClient指明用哪個連線傳送； szMessage指明待發送資料的儲存地址 ；strlen(szMessage)指明資料長度    
	}
	// 釋放連線和進行結束工作    
	closesocket(sClient);
	WSACleanup();
	return 0;
}