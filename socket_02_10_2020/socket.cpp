#include <iostream>
// biblioteki pozwalaj¹ce na przep³yw informacji
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")
// Komentarz #pragma wskazuje konsolidatorowi, ¿e potrzebny jest plik Ws2_32.lib


//#include <string>

using namespace std;

void main()
{

	// inicjowanie winsock
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);
	/*
		Parametr MAKEWORD (2,2) WSAStartup
		wysy³a ¿¹danie wersji 2.2 Winsock
		w systemie i ustawia przekazan¹ wersjê
		jako najwy¿sz¹ wersjê obs³ugi gniazd
		Windows, z której mo¿e korzystaæ
		wywo³uj¹cy.
	*/
	int wsOK = WSAStartup(ver, &wsaData);
	/*
		Funkcja WSAStartup jest wywo³ywana
		w celu zainicjowania u¿ycia WS2_32.dll
	*/
	if (wsOK != 0) {
		cout << "Nie moge zainicjowac winsock! Koniec\n";
		return; // koniec programu
	}

	// utworzenie socketu (gniazda)
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	// sprawdzenie gniazda czy jest prawid³owe
	if (listenSocket == INVALID_SOCKET) {
		cout << "Bload gniazda (socket)\n";
		return;
	}
	// powi¹zanie (bind) gniazda z adresem IP i portem
	sockaddr_in gHadd;
	gHadd.sin_family = AF_INET;
	gHadd.sin_port = htons(54000); // Funkcja htons konwertuje u_short z hosta na kolejnoœæ bajtów sieci TCP / IP (czyli big-endian)
	gHadd.sin_addr.S_un.S_addr = INADDR_ANY; // mozliwe jest przez uzycie inet_pton

	bind(listenSocket, (sockaddr*)&gHadd, sizeof(gHadd));

	// nas³uchiwaæ na tym adresie IP i porcie pod k¹tem przychodz¹cych ¿¹dañ po³¹czenia
	listen(listenSocket, SOMAXCONN); // Funkcja nas³uchiwania umieszcza gniazdo w stanie, w którym nas³uchuje po³¹czenia przychodz¹cego.

	// czekanie na po³¹czenie (akceptacja po³¹czenie w gnieŸdzie)
	sockaddr_in client;	// Struktura SOCKADDR_IN okreœla adres transportowy i port dla rodziny adresów AF_INET .
	int  clientSize = sizeof(client);
	SOCKET clientSocket = accept(listenSocket, (sockaddr*)&client, &clientSize);

	int res;
	const char wiadomosc[] = "Succesfull sending";
	//string wiadomosc = "Udane przeslanie";
	res = send(clientSocket, wiadomosc, sizeof(wiadomosc), NULL);
	if (res == SOCKET_ERROR) {
		wprintf(L"send failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return;
	}
	else
	{
		printf(wiadomosc);
	}

	//int iSendResult = send(clientSocket, recvbuf, iResult, 0);

	/*if (clientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return;
	}*/

	


		// odbiernie i wysylanie danych na serwer
		// funkcje recv i send u¿ywane przez serwer

		// Gdy serwer zakoñczy odbieranie danych od klienta i wysy³anie danych z powrotem do klienta, od³¹cza siê od klienta i zamyka gniazdo.

		// zamkniêcie socketu (gniazda)

		// zamkniêcie winsock



}