#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;
enum enChoices { Stone = 1, Peper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
    enChoices Player1Choice = enChoices::Scissor;
    enChoices ComputerChoice = enChoices::Scissor;
    enWinner Winner = enWinner::Computer;
    string WinnerName = "";
    short RoundNumber = 0;
};
struct stGameInfo
{
    short GameRounds = 0;
    short Player1WonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner Winner = enWinner::Computer;
    string WinnerName;
};
short RandomNumber(short From, short To)
{
    short randNumber = rand() % (To - From + 1) + From;
    return randNumber;
}
short ReadNumber(string Message)
{
    short Number;
    cout << Message << endl;
    cin >> Number;
    return Number;
}
short ReadNumberOfRound()
{
    short NumOfRound;
    do
    {
        NumOfRound = ReadNumber("How Many Rounds Do You Want To Play From 1 To 10 ?");

    } while (NumOfRound < 1 || NumOfRound>10);
    return NumOfRound;
}
enChoices ReadPlayer1Choice()
{
    short NumberOfChoice;
    do
    {
        NumberOfChoice = ReadNumber("Your Choice: [1]: Stone, [2]:Peper, [3]:Scissor ?");
    } while (NumberOfChoice < 1 || NumberOfChoice>3);
    return (enChoices)NumberOfChoice;
}
enChoices GetComputerChoice()
{
    return (enChoices)RandomNumber(1, 3);

}

string enWinnerToString(enWinner Winner)
{
    string arrWinner[3] = { "Player1","Computer","No Winner" };
    return arrWinner[Winner - 1];
}
enWinner WhoWonRound(stRoundInfo Info)
{
    if (Info.Player1Choice == Info.ComputerChoice)
        return enWinner::Draw;
    switch (Info.Player1Choice)
    {
    case enChoices::Stone:
        if (Info.ComputerChoice == enChoices::Peper)
            return enWinner::Computer;
        break;
    case enChoices::Peper:
        if (Info.ComputerChoice == enChoices::Scissor)
            return enWinner::Computer;
        break;
    case enChoices::Scissor:
        if (Info.ComputerChoice == enChoices::Stone)
            return enWinner::Computer;
        break;
    }
    return enWinner::Player1;
}
void ChangeScreenColor(enWinner Winner)
{

    if (Winner == enWinner::Player1)
        system("color 2F");
    else if (Winner == enWinner::Computer)
    {
        system("color 4F");
        cout << "\a";
    }
    else
        system("color 6F");
}
string ChoiceToSTring(enChoices Choice)
{
    string arrChoices[3] = { "Stone","Peper","Scissor" };
    return arrChoices[Choice - 1];
}
void RoundResult(stRoundInfo Info)
{

    cout << "_______________Round[" << Info.RoundNumber << "]_______________" << endl;
    cout << "Player1 Choice: " << ChoiceToSTring(Info.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceToSTring(Info.ComputerChoice) << endl;
    cout << "Round Winner: " << Info.WinnerName << endl;
    cout << "______________________________________" << endl;
    cout << endl;
}
enWinner WhoWonGame(short Player1WonTimes, short ComputerWonTimes)
{
    if (Player1WonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (Player1WonTimes = ComputerWonTimes)
        return enWinner::Draw;
    else
        return enWinner::Computer;
}
stGameInfo FillGameResult(short RoundNumber, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
    stGameInfo GameResult;
    GameResult.GameRounds = RoundNumber;
    GameResult.Player1WonTimes = Player1WonTimes;
    GameResult.ComputerWonTimes = ComputerWonTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.Winner = WhoWonGame(Player1WonTimes, ComputerWonTimes);
    GameResult.WinnerName = enWinnerToString(GameResult.Winner);
    return GameResult;
}
string tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1;i < NumberOfTabs;i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}
void PrintGameOver()
{
    cout << tabs(2) << "__________________________________________________________" << endl;
    cout << tabs(2) << "\t\t\t+++Game Over+++" << endl;
    cout << tabs(2) << "__________________________________________________________" << endl;
}
stGameInfo PlayGame(short NumOfRounds)
{
    stRoundInfo Info;
    stGameInfo gInfo;
    short ComputerWonTimes = 0, DrawTimes = 0, Player1WonTimes = 0;
    for (short RoundNumber = 1;RoundNumber <= NumOfRounds;RoundNumber++)
    {
        cout << "Round[" << RoundNumber << "] Begins: " << endl;
        Info.RoundNumber = RoundNumber;
        Info.Player1Choice = ReadPlayer1Choice();
        Info.ComputerChoice = GetComputerChoice();
        Info.Winner = WhoWonRound(Info);
        Info.WinnerName = enWinnerToString(Info.Winner);
        if (Info.WinnerName == "Player1")
            Player1WonTimes++;
        else if (Info.WinnerName == "Computer")
            ComputerWonTimes++;
        else
            DrawTimes++;
        ChangeScreenColor(Info.Winner);
        RoundResult(Info);
    }
    return FillGameResult(NumOfRounds, Player1WonTimes, ComputerWonTimes, DrawTimes);
}
void ShowGameResult(stGameInfo GameResult)
{
    cout << tabs(2) << "_______________________[Game Result]______________________" << endl;
    cout << tabs(2) << "Game Rounds: " << GameResult.GameRounds << endl;
    cout << tabs(2) << "Player1 Won Times: " << GameResult.Player1WonTimes << endl;
    cout << tabs(2) << "Computer Won Times: " << GameResult.ComputerWonTimes << endl;
    cout << tabs(2) << "Draw Times: " << GameResult.DrawTimes << endl;
    cout << tabs(2) << "Final Winner: " << GameResult.WinnerName << endl;
    cout << tabs(2) << "__________________________________________________________" << endl;

}
void ResetScreen()
{
    system("color 07");
    system("cls");
}
void StartGame()
{
    char Play = 'y';
    do
    {
        ResetScreen();
        stGameInfo GameResult = PlayGame(ReadNumberOfRound());
        PrintGameOver();
        ShowGameResult(GameResult);
        cout << tabs(2) << "Do You Want To Play Again? Y/N ?";
        cin >> Play;

    } while (Play == 'Y' || Play == 'y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}

