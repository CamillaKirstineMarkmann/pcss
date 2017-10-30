//TCP SERVER source file
#include "SERVER.h"
using namespace std;

//Variables declared at the top in catagories:

//NETWORKING VARIABLES:
long SUCCESSFUL;
WSAData WinSockData;
WORD DLLVERSION; //Word are objects of a data size that our processor naturally handles (16 or 32-bit)
string CONVERTER;
char MESSAGE[200];

//Strings for Assigning tasks using String Comparison:


std::string createGame("Server Create me a Game");
std::string joinGame("Server join a game");
std::string rockChosen("You chose rock");
std::string paperChosen("You chose paper");
std::string scissorChosen("You chose scissor");
std::string assignTask;

//Variables for evaluating game creation




//STRUCT for holding game information

struct games_01and02 {
	string title;

	int score_Player01;
	int score_Player02;

	int weapon_Player01;
	int weapon_Player02;

	bool game_01_created = false;
} Game01, Game02;


//Functions declared here before main


void createGameonServer() {

	
	Game01.title = "Game 01";
	Game01.score_Player01 = 0;
	Game01.score_Player02 = 0;
	
	Game01.weapon_Player01 = 1;

}

void printGameData() {

cout << Game01.title << endl;
cout << Game01.score_Player01 << endl;
cout << Game01.score_Player02 << endl;
}

void CompareWeapons() {
	if (Game01.weapon_Player01 == Game01.weapon_Player02) {
		cout << "It's a draw" << endl;
	}
	else if (Game01.weapon_Player01 == 1 && Game01.weapon_Player02 == 2) {
		cout << "Player 1 wins" << endl;
		Game01.score_Player01++;
	}
	else if (Game01.weapon_Player01 == 1 && Game01.weapon_Player02 == 3) {
		cout << "Player 2 wins" << endl;
		Game01.score_Player02++;
	}

}


void JoinSpecificGame() {




}



void main()
{
	

	DLLVERSION = MAKEWORD(2, 1); //macro to create WORD value by concatenating(Means link serveral object together) its arguments //Start Winsock DLL
	SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData); //WSAStartup starts the winsock application interface


	//Create Socket Structure
	SOCKADDR_IN ADDRESS; //Instantiate a SOCKADDR_IN object and name ADRESS
	int AddressSize = sizeof(ADDRESS); //Store Adress size in an int 

	//Create Sockets
	SOCKET sock_LISTEN; //Listen for incomming connection
	SOCKET sock_CONNECTION;//activate if connection found


	sock_CONNECTION = socket(AF_INET, SOCK_STREAM, NULL); //socket Arguments: AF_INET = internet domain (not Unix doman), //SOCK_STREAM = connection oriented TCP (not SOCK_DGRAM(UDP))
	ADDRESS.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY, means use the IP of the machine you are on, you can also specify it to Local //inet_addr("127.0.0.1"); //Set IP, this number must be converted
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(444); //port, htons method to convert the type to a network type

	sock_LISTEN = socket(AF_INET, SOCK_STREAM, NULL); //The server needs a socket to listen in on for incomming connections. 
	bind(sock_LISTEN, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS)); //Bind command bind a socket to an adress, we bind the sock_LISTEN to our IP Adress
	listen(sock_LISTEN, SOMAXCONN); //LISTEN without limits. First argument is the socket we set to listen and SOMAXCONN is the maximum number of connections a system will allow. The maximum lenght of the queue of pending connections. f set to SOMAXCONN, the underlying service provider responsible for socket s will set the backlog to a maximum reasonable value. There is no standard provision to obtain the actual backlog value.

	//If connection found:

	cout << "\n\tSERVER: Waiting for incoming connection...";

	if (sock_CONNECTION = accept(sock_LISTEN, (SOCKADDR*)&ADDRESS, &AddressSize))
	{
		cout << "\n\tA connection was found!" << endl;

		SUCCESSFUL = send(sock_CONNECTION, "Welcome! You have connected to the Server!", 46, NULL);
	

		for (;;) //Infinite foor loop will loop forever...
		{
			/*cout << "\n\tSERVER: Waiting for incoming connection...";

			if (sock_CONNECTION = accept(sock_LISTEN, (SOCKADDR*)&ADDRESS, &AddressSize))
			{
				cout << "\n\tA connection was found!" << endl;

				SUCCESSFUL = send(sock_CONNECTION, "Welcome! You have connected to the Server!", 46, NULL);*/


			SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, 46, NULL); //Create Game Request!

			assignTask = MESSAGE;

			cout << assignTask << endl;

			if (assignTask.compare(createGame) == 0) {
				createGameonServer();
				cout << "Correct input for CreateGame" << endl;
				std::string assignTask = "";
			}
			else if (assignTask.compare(joinGame) == 0) {
				cout << "Correct input for Joingame" << endl;
				std::string assignTask = "";
			}
			else if (assignTask.compare(rockChosen) == 0) {
				cout << "Correct input for rock chosen" << endl;
				Game01.weapon_Player02 = 1;
				CompareWeapons();
				SUCCESSFUL = send(sock_CONNECTION, "It's a draw!", 46, NULL);
				printGameData();
				std::string assignTask = "";
			}
			else if (assignTask.compare(paperChosen) == 0) {
				cout << "Correct input for paper chosen" << endl;
				Game01.weapon_Player02 = 2;
				CompareWeapons();
				SUCCESSFUL = send(sock_CONNECTION, "Player 1 wins!", 46, NULL);
				printGameData();
				std::string assignTask = "";
			}
			else if (assignTask.compare(scissorChosen) == 0) {
				cout << "Correct input for scissor chosen" << endl;
				Game01.weapon_Player02 = 3;
				CompareWeapons();
				SUCCESSFUL = send(sock_CONNECTION, "Player 2 wins!", 46, NULL);
				printGameData();
				std::string assignTask = "";
			}


			//cout << CONVERTER;


		}
		//}
	}
}