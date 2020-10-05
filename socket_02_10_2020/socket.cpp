#include <iostream>
// biblioteki pozwalaj�ce na przep�yw informacji
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")
// Komentarz #pragma wskazuje konsolidatorowi, �e potrzebny jest plik Ws2_32.lib


//#include <string>

using namespace std;

void main()
{

	// inicjowanie winsock
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);
	/*
		Parametr MAKEWORD (2,2) WSAStartup
		wysy�a ��danie wersji 2.2 Winsock
		w systemie i ustawia przekazan� wersj�
		jako najwy�sz� wersj� obs�ugi gniazd
		Windows, z kt�rej mo�e korzysta�
		wywo�uj�cy.
	*/
	int wsOK = WSAStartup(ver, &wsaData);
	/*
		Funkcja WSAStartup jest wywo�ywana
		w celu zainicjowania u�ycia WS2_32.dll
	*/
	if (wsOK != 0) {
		cout << "Nie moge zainicjowac winsock! Koniec\n";
		return; // koniec programu
	}

	// utworzenie socketu (gniazda)
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	// sprawdzenie gniazda czy jest prawid�owe
	if (listenSocket == INVALID_SOCKET) {
		cout << "Bload gniazda (socket)\n";
		return;
	}
	// powi�zanie (bind) gniazda z adresem IP i portem
	sockaddr_in gHadd;
	gHadd.sin_family = AF_INET;
	gHadd.sin_port = htons(54000); // Funkcja htons konwertuje u_short z hosta na kolejno�� bajt�w sieci TCP / IP (czyli big-endian)
	gHadd.sin_addr.S_un.S_addr = INADDR_ANY; // mozliwe jest przez uzycie inet_pton

	bind(listenSocket, (sockaddr*)&gHadd, sizeof(gHadd));

	// nas�uchiwa� na tym adresie IP i porcie pod k�tem przychodz�cych ��da� po��czenia
	listen(listenSocket, SOMAXCONN); // Funkcja nas�uchiwania umieszcza gniazdo w stanie, w kt�rym nas�uchuje po��czenia przychodz�cego.

	// czekanie na po��czenie (akceptacja po��czenie w gnie�dzie)
	sockaddr_in client;	// Struktura SOCKADDR_IN okre�la adres transportowy i port dla rodziny adres�w AF_INET .
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
		// funkcje recv i send u�ywane przez serwer

		// Gdy serwer zako�czy odbieranie danych od klienta i wysy�anie danych z powrotem do klienta, od��cza si� od klienta i zamyka gniazdo.

		// zamkni�cie socketu (gniazda)

		// zamkni�cie winsock



}