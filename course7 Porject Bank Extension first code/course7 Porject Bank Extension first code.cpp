
#include <iostream>
#include<string >
#include<vector>
#include<iomanip>
#include<fstream>

using namespace std;
void ShowMainMenue();
void ShowTrasactionsScreen();

const string ClientsFileName = "Clients.txt";
struct stClient {

	string AccountNumber = "";
	string PinCode = "";
	string ClientName = "";
	string Phone = "";
	double Balance = 0;
	bool MarkForDelete = false;
};

//load, save, split, converting  ,string ,files,search

vector<string> SplitString(string S1, string Delim = "#//#") {
	string Word;
	size_t Pos;
	vector<string>vDataString;
	while ((Pos = S1.find(Delim)) != string::npos) {
		Word = S1.substr(0, Pos);
		if (Word != "") {
			vDataString.push_back(Word);
		}

		S1.erase(0, Pos + Delim.length());

	}
	if (S1 != "") {
		vDataString.push_back(S1);
	}
	return vDataString;


}
stClient ConvertFromLineToRecord(const string& DataLine) {
	stClient Client;
	vector<string> DataSplited = SplitString(DataLine, "#//#");
	if (DataSplited.size() == 5) {
		Client.AccountNumber = DataSplited[0];
		Client.PinCode = DataSplited[1];
		Client.ClientName = DataSplited[2];
		Client.Phone = DataSplited[3];
		Client.Balance = stod(DataSplited[4]);

	}return Client;

}
string ConvertFromRecordToLine(const stClient& Client, string  Delim = "#//#") {
	string Line = Client.AccountNumber + Delim;
	Line += Client.PinCode + Delim;
	Line += Client.ClientName + Delim;
	Line += Client.Phone + Delim;
	Line += std::to_string(Client.Balance) + Delim;
	return Line;
}
vector <stClient> LoadClientsDataFromFile(const string& ClientsFileName) {
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	vector<stClient> vClients;
	if (MyFile.is_open()) {
		string DataLine;

		stClient Client;
		while (getline(MyFile, DataLine))
		{
			Client = ConvertFromLineToRecord(DataLine);
			if (Client.AccountNumber != "")
				vClients.push_back(Client);

		}
		MyFile.close();
	}

	return vClients;

}
void SaveClientsDataToFile(const string& ClientsFileName, const vector<stClient>& vClients) {

	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open()) {
		string DataLine;
		for (const stClient& C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertFromRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();
	}
	else {

		cout << "\aFile ( " << ClientsFileName << " ) Can Not Open !";
	}

}
bool FindClientByAccountNumber(const string& AccountNumber, const vector<stClient>& vClients, stClient& Client) {
	for (const stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool ClientExistsByAccountNumber(const string& AccountNumber, string  ClientsFileName) {
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	if (MyFile.is_open()) {
		string DataLine;

		stClient Client;
		while (getline(MyFile, DataLine))
		{
			Client = ConvertFromLineToRecord(DataLine);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();

				return true;
			}
		}
	}
	MyFile.close();

	return false;
}

//ShowClientsList

void PrintClientRecordLine(const stClient& Client) {

	cout << "|" << left << setw(12) << Client.AccountNumber;
	cout << "|" << left << setw(8) << Client.PinCode;
	cout << "|" << left << setw(40) << Client.ClientName;
	cout << "|" << left << setw(12) << Client.Phone;
	cout << "|" << left << setw(12) << Client.Balance;

}
void PrintClientCard(const stClient& Client) {

	cout << "\nThis Following is Client Info :\n";
	cout << "__________________________________________\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "PinCode : " << Client.PinCode << endl;
	cout << "Client Name : " << Client.ClientName << endl;
	cout << "Phone : " << Client.Phone << endl;
	cout << "Balance : " << Client.Balance << endl;
	cout << "__________________________________________\n";


}
void ShowAllClientsScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\n\n\t\t\tClients List (" << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________________________________________\n";
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(8) << "PinCode";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(12) << "Phone";
	cout << "|" << left << setw(12) << "Balance";
	cout << "\n________________________________________________________________________________________\n";
	if (vClients.size() != 0) {
		for (const stClient& C : vClients) {
			PrintClientRecordLine(C);
			cout << endl;
		}
	}
	else {

		cout << "\t\t\t\tNo Clients Available in system!";
	}
	cout << "\n________________________________________________________________________________________\n";


}

//Add New Client Screen

stClient ReadNewClient() {
	stClient Client;

	cout << "Enter Account Number?";
	getline(cin >> ws, Client.AccountNumber);


	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {

		cout << "\n\aClient with [" << Client.AccountNumber << "] already exists, Enter Another Account Number? \a";

		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Client Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Balance? ";
	cin >> Client.Balance;

	return Client;

}
string ReadAccountNumber(string Message = "Please Enter Account Number?") {
	string AccountNumber;

	cout << Message;
	getline(cin >> ws, AccountNumber);
	return AccountNumber;

}
void AddDataLineToFile(string ClientsFileName, string DataLine) {
	fstream MyFile(ClientsFileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << DataLine << endl;

	}
	else {
		cout << "File Can't open !";

	}

	MyFile.close();


}
void AddNewClient() {
	stClient Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertFromRecordToLine(Client));
}
void AddNewClients() {
	char AddMore = 'y';
	do {
		cout << "\n\n\nAdding New Client :\n\n";
		AddNewClient();
		cout << "Client Added successfully .\n";

		cout << "Do you want to add new client ? y/n ?";
		cin >> AddMore;

	} while (tolower(AddMore) == 'y');

}
void ShowAddNewClientsScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();


}

//Delete Client 

void MarkClientForDelete(string AccountNumber, vector<stClient>& vClients) {
	for (stClient& C : vClients)
		if (C.AccountNumber == AccountNumber)
			C.MarkForDelete = true;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
	char Answer = 'y';
	stClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "Are you sure you want to delete this client ? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkClientForDelete(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Succssfully:-)\n";
			return true;
		}
	}
	else {
		cout << "\aClient with [" << AccountNumber << "]  not found \n";
		return false;
	}

}
void ShowDeleteClientScreen() {
	cout << "\n=========================================\n";
	cout << "\tDelete Client Screen";
	cout << "\n=========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}


//update client 

stClient ChangeClientRecord(string AccountNumber) {
	stClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Client Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Balance? ";
	cin >> Client.Balance;

	return Client;



}
bool  UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
	char Answer = 'y';
	stClient Client;



	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "Are you sure you want update this client ? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			for (stClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient updated Succssfully:-)\n";
			return true;
		}
	}
	else {
		cout << "\aClient with [" << AccountNumber << "]  not found \n\a";
		return false;
	}
}
void ShowUpdateScreen() {
	cout << "\n=========================================\n";
	cout << "\tUpdate Client Screen";
	cout << "\n=========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}


//find Client Screen
void ShowFindScreen() {
	cout << "\n=========================================\n";
	cout << "\tFind Client Screen";
	cout << "\n=========================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	Client.AccountNumber = ReadAccountNumber();;
	if (FindClientByAccountNumber(Client.AccountNumber, vClients, Client)) {


		PrintClientCard(Client);

	}
	else {
		cout << "Client with [" << Client.AccountNumber << "]  not found \n";
	}




}

//end Screen
void ShowEndScreen() {
	cout << "\n==================================\n";
	cout << "\n         Program Ends .\n";
	cout << "\n==================================\n";
	system("pause>0");
}

//options 
enum enMainMenuOption
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5,eTarnsactionsList=6, eExit = 7
};
enum enTransactions {
	eDeposit=1,eWithdraw=2,
	eTotalBalance=3 , eMainMenue=4
};
 

void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionsMenu() {
	
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTrasactionsScreen();
}


//deposit:
bool DepositBalanceToClientByAccountNumber(const string &AccountNumber, double Amount, vector<stClient> &vClients) {
	char Answer = 'n';
	cout << "Are you sure you want perform this transaction? y/n? ";
	cin >> Answer;
	if (tolower(Answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {

				C.Balance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\nDone Successfully. New Balance is: " << C.Balance << endl;
				return true;
				
			}
		}
	}
	return false;

}
void ShowDepositScreen() {
	cout << "\n==================================\n";
	cout << "\n         Deposit Screen.\n";
	cout << "\n==================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with[" << AccountNumber << "]does not exist.\n";
		cout << "Enter Another AccountNumber :\n";
		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	double DepositAmount = 0;
	cout << "Please enter Deposit Amount?";
	cin >> DepositAmount;

	DepositBalanceToClientByAccountNumber(AccountNumber, DepositAmount, vClients);

}

//withdraw:
void ShowWithDrawScreen() {
	cout << "\n==================================\n";
	cout << "\n         WithDraw Screen.\n";
	cout << "\n==================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with[" << AccountNumber << "] does not exist.\n";
		cout << "Enter Another AccountNumber :\n";
		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "Please enter withdraw Amount?";
	cin >> Amount;
	while (Amount > Client.Balance) {

		cout << "\nAmount Exceeds the balance, you can withdraw up to : ";
		cout << Client.Balance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;

	}
	DepositBalanceToClientByAccountNumber(AccountNumber,Amount*-1, vClients);


}

//total balances screen ,printing:
void PrintClientBalanceLine(stClient Client) {
	cout << "|" << left << setw(14) << Client.AccountNumber;
	cout << "|" << left << setw(40) << Client.ClientName;
	cout << "|" << left << setw(12) << Client.Balance;

}
void ShowTotalBalances() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\n\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
	cout << "\n________________________________________________________________________________________\n";
	cout << "|" << left << setw(12) << "Account Number";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(12) << "Balance";
	cout << "\n________________________________________________________________________________________\n";
	double TotalBalances = 0;
	if (vClients.size() != 0) {
		for (const stClient& C : vClients) {
			PrintClientBalanceLine(C);
			cout << endl;
			TotalBalances += C.Balance;
		}
	}
	else {

		cout << "\t\t\t\tNo Clients Available in system!";
	}
	cout << "\n________________________________________________________________________________________\n";
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}
void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}

//transactions menue functions:
void PerformTranactionsMenuOption(enTransactions TransactionsMenueOption) {
	switch (TransactionsMenueOption) {
	case enTransactions::eDeposit:

		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactions::eWithdraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenu();


		break;
	case enTransactions::eTotalBalance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenu();

		break;
	case enTransactions::eMainMenue:
		system("cls");

		
		ShowMainMenue();


		break;
	}
}
short ReadTranactionsMenuOption() {
	short Choice = 0;
	while (Choice <= 0 || Choice > 4) {
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choice;
	}
	return Choice;

}
void ShowTrasactionsScreen() {
	system("cls");
	cout << "\n==================================\n";
	cout << "\n         Trasaction Screen .\n";
	cout << "\n==================================\n";
	cout << "\n      [1] Deposit.\n";
	cout << "\n      [2] Withdraw.\n";
	cout << "\n      [3] Total Balance.\n";
	cout << "\n      [4] Main Menue.\n";
	cout << "\n==================================\n";

	PerformTranactionsMenuOption(enTransactions(ReadTranactionsMenuOption()));
}

//Main menue functions:
void PerformMainMenuOption(enMainMenuOption MainMenuOption) {
	switch (MainMenuOption) {
	case enMainMenuOption::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();

		break;
	case enMainMenuOption::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eUpdateClient:
		system("cls");

		ShowUpdateScreen();
		GoBackToMainMenu();

		break;
	case enMainMenuOption::eFindClient:
		system("cls");

		ShowFindScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eTarnsactionsList:
		system("cls");
		ShowTrasactionsScreen();
		GoBackToTransactionsMenu();
		break;

	
	case enMainMenuOption::eExit:
		system("cls");
		ShowEndScreen();
		break;

	}

}
short ReadMainMenueOption() {
	short Choice = 0;
	while (Choice <= 0 || Choice >= 7) {
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Choice;
	}
	return Choice;

}
void ShowMainMenue() {
	system("cls");
	cout << "\n==================================\n";
	cout << "\n      Main Menue Screen.\n";
	cout << "\n==================================\n";
	cout << "\n      [1] Show Clients List.\n";
	cout << "\n      [2] Add New Client.\n";
	cout << "\n      [3] Delete Client.\n";
	cout << "\n      [4] update Client.\n";
	cout << "\n      [5] Find Client.\n";
	cout << "\n      [6] Tarnsactions.\n";
	cout << "\n      [7] Exit.\n";
	cout << "\n================================\n";
	PerformMainMenuOption(enMainMenuOption(ReadMainMenueOption()));


}


int main() {

	ShowMainMenue();
	system("pause>0");
	return 0;

}