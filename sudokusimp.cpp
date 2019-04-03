#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

void printcongrats(void);
int checkwin (int board[][9]);

int main ()
{
int board[9][9], boardadj[9][9], row, column, ahe = 0;

ifstream fin;

fin.open("board.txt");

for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
        fin >> board[i][j];

fin.close();

for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
        boardadj[i][j] = board[i][j];

while (checkwin(boardadj) != 27)
{
    system("CLS");

        cout << "\n\n\t=============================" << endl;
    for (int i = 0; i < 3; i++)
        cout << "\t|| " << boardadj[i][0] << " " << boardadj[i][1] << " " << boardadj[i][2] << " || " << boardadj[i][3] << " " << boardadj[i][4] << " " << boardadj[i][5] << " || " << boardadj[i][6] << " " << boardadj[i][7] << " " << boardadj[i][8] << " ||" << endl;
        cout << "\t=============================" << endl;

    for (int i = 3; i < 6; i++)
        cout << "\t|| " << boardadj[i][0] << " " << boardadj[i][1] << " " << boardadj[i][2] << " || " << boardadj[i][3] << " " << boardadj[i][4] << " " << boardadj[i][5] << " || " << boardadj[i][6] << " " << boardadj[i][7] << " " << boardadj[i][8] << " ||" << endl;
        cout << "\t=============================" << endl;

    for (int i = 6; i < 9; i++)
        cout << "\t|| " << boardadj[i][0] << " " << boardadj[i][1] << " " << boardadj[i][2] << " || " << boardadj[i][3] << " " << boardadj[i][4] << " " << boardadj[i][5] << " || " << boardadj[i][6] << " " << boardadj[i][7] << " " << boardadj[i][8] << " ||" << endl;
        cout << "\t=============================" << endl << endl;

    cout << "\nRow and column of the block you want to manipulate: ";
    cin >> row >> column;

    if (board[row - 1][column - 1] == 0)
    {
        cout << "Number (1-9): ";
        cin >> boardadj[row - 1][column - 1];
    }

    else
        cout << "The block is a constant block.";
}

printcongrats();

return 0;
}

int checkwin (int board[][9])
{
    int sum1[9], sum2[9], sumspec[9], check = 0;

    for (int i = 0; i < 9; i++)
    {
        sum1[i] = 0;
        sum2[i] = 0;
        sumspec[i] = 0;
    }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sum1[i] += board[i][j];

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sum2[i] += board[j][i];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            sumspec[0] += board[i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 3; j < 6; j++)
            sumspec[1] += board[i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 6; j < 9; j++)
            sumspec[2] += board[i][j];

    for (int i = 3; i < 6; i++)
        for (int j = 0; j < 3; j++)
            sumspec[3] += board[i][j];

    for (int i = 3; i < 6; i++)
        for (int j = 3; j < 6; j++)
            sumspec[4] += board[i][j];

    for (int i = 3; i < 6; i++)
        for (int j = 6; j < 9; j++)
            sumspec[5] += board[i][j];

    for (int i = 6; i < 9; i++)
        for (int j = 0; j < 3; j++)
            sumspec[6] += board[i][j];

    for (int i = 6; i < 9; i++)
        for (int j = 3; j < 6; j++)
            sumspec[7] += board[i][j];

    for (int i = 6; i < 9; i++)
        for (int j = 6; j < 9; j++)
            sumspec[8] += board[i][j];

    for (int i = 0; i < 9; i++)
        if (sum1[i] == 45)
            check++;

    for (int i = 0; i < 9; i++)
        if (sum2[i] == 45)
            check++;

    for (int i = 0; i < 9; i++)
        if (sumspec[i] == 45)
            check++;

    return check;
}

void printcongrats(void)
{
    cout << "\n" << endl;
    cout << " ,adPPYba,                                                             ,d                 88" << endl;
    cout << "a8'     aa                                                             88                 88" << endl;
    cout << "8b          ,adPPYba,  8b,dPPYba,   ,adPPYb,d8 8b,dPPYba, ,adPPYYba, MM88MMM ,  adPPYba,  88" << endl;
    cout << "8b         a8'     '8a 88P'   `'8a a8'    `Y88 88P'   'Y8 ''     `Y8   88      I8[    ''  88" << endl;
    cout << "8b         8b       d8 88       88 8b       88 88         ,adPPPPP88   88       `'Y8ba,   88" << endl;
    cout << "'8a,   ,aa '8a,   ,a8' 88       88 '8a,   ,d88 88         88,    ,88   88,     aa    ]8I    " << endl;
    cout << " `'Ybbd8''  `'YbbdP''  88       88  `'YbbdP'Y8 88         `'8bbdP'Y8   'Y888   `'YbbdP''  88" << endl;
    cout << "                                    aa,    ,88                                              " << endl;
    cout << "                                     'Y8bbdP'                                               " << endl;
}
