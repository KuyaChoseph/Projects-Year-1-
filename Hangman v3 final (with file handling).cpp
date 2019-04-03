#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include <fstream>

using namespace std;

void game (string word, string hint, char *diffp, int *scorep);
//function for the algorithm of the game
void hangman (int wrong, string word);
//function for printing the hangman every wrong guess
void blankfunc (string word, char *blankp);
//function for printing the blanks with the length of the word
void bubblesort (struct scores *player);
//function for sorting the score from highest to lowest
int checkwin (char *blnkp, char *wordcp, string word);
//function for throwing the word size if blank == word
void highscorefile (struct scores *player, int plyrctr);
//function for saving the scores to a text file and printing it
void wordsdatabase (int wordsize, class wordclass *easy, class wordclass *med, class wordclass *hard);
//function for getting the words from a text file to the classes created in the main program
void printhangman (void);
void printcongrats(void);
void printgameover(void);

class wordclass
{
    public:
    string word[10];
    string hint[10];
};

struct scores
{
    string name[10];
    int score[10];
};

int main()
{
    string word, hint, name;
    char diff, restart, *diffp;
    int wordsize = 10, random, plyrctr = 0, score[3], *scorep;
    scorep = score;
    diffp = &diff;

    wordclass easy, med, hard;
    struct scores player;

    for (int i = 0; i < 10; i++)
    player.score[i] = 0;

    wordsdatabase(wordsize, &easy, &med, &hard);

    do
    {
    diff = 'E';
    switch (diff)
    {
    case 'E':
    srand(time(NULL));
    random = rand() % 10;

    word = easy.word[random];
    hint = easy.hint[random];

    system("CLS");
    system("COLOR B");
    printhangman();
    cout << "\nBefore we proceed, please type your name (DO NOT USE SPACE): ";
    cin >> player.name[plyrctr];
    cout << "\nHi, Mr./Ms. " << player.name[plyrctr] << "!" << endl;
    cout << "The difficulty for this round is EASY." << endl;
    cout << "The alloted points for this round is 100." << endl;
    cout << "Ten points will be deducted for every wrong character you guess." << endl;
    cout << "\nLet's start the game! Press enter to start!";
    getch();

    system("CLS");
    game (word, hint, diffp, scorep);

    player.score[plyrctr] = score[0];
    if (diff == 'E')
    {
        plyrctr++;
        break;
    }

    case 'M':
    srand(time(NULL));
    random = rand() % 10;

    word = med.word[random];
    hint = med.hint[random];

    system("CLS");
    system("COLOR B");
    printhangman();
    cout << "\nHi, Mr./Ms. " << player.name[plyrctr] << "!" << endl;
    cout << "The difficulty for this round is MEDIUM." << endl;
    cout << "The alloted points for this round is 200." << endl;
    cout << "Twenty points will be deducted for every wrong character you guess." << endl;
    cout << "\nLet's start the game! Press enter to start!";
    getch();

    system("CLS");
    game (word, hint, diffp, scorep);
    player.score[plyrctr] = score[1];
    if (diff == 'M')
    {
        plyrctr++;
        break;
    }

    case 'H':
    srand(time(NULL));
    random = rand() % 10;

    word = hard.word[random];
    hint = hard.hint[random];

    system("CLS");
    system("COLOR B");
    printhangman();
    cout << "\nHi, Mr./Ms. " << player.name[plyrctr] << "!" << endl;
    cout << "The difficulty for this round is HARD." << endl;
    cout << "The alloted points for this round is 300." << endl;
    cout << "Thirty points will be deducted for every wrong character you guess." << endl;
    cout << "\nLet's start the game! Press enter to start!";
    getch();

    system("CLS");
    game (word, hint, diffp, scorep);
    player.score[plyrctr] = score[2];
    plyrctr++;
    }
    cout << "\nType 'r' to play again. (WILL END IF THERE ARE ALREADY 10 PLAYERS)" << endl;
    }
    while ( (getch() == 'r' || getch() == 'R') && plyrctr != 10);

    cout << "\n\nHighscores: " << endl << endl;
    bubblesort (&player);
    highscorefile (&player, plyrctr);

return 0;
}

void blankfunc (string word, char *blankp)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] != ' ')
            *(blankp + i) = '-';
        else
            *(blankp + i) = ' ';
    }
}

void game (string word, string hint, char *diffp, int *scorep)
{
    int wrong = 0;
    char Guess, guess, GUESS, blank[50], wordc[50];
    char *blankp, *wordcp;
    blankp = blank;
    wordcp = wordc;

    blankfunc(word, blankp);

    for (int i = 0; i < word.size(); i++)
    wordc[i] = word[i];

    while (wrong < 11)
    {
        if (*diffp == 'E')
            *(scorep) = 100 - wrong * 10;

        else if (*diffp == 'M')
            *(scorep+1) = *(scorep) + 200 - wrong * 20;

        else
            *(scorep+2) = *(scorep+1) + 300 - wrong * 30;
        //nested if statements for the scoring system

        if (wrong == 10)
        break;

        //if statement for checking if the player guessed the word on difficulty EASY
        if (checkwin(blankp, wordcp, word) == word.size() && *diffp == 'E')
        {
            system("CLS");
            system("COLOR A");
            *diffp = 'M';
            printcongrats();
            cout << "The word is " << word << "!" << endl;
            cout << "\nPress enter to proceed to difficulty MEDIUM!";
            getch();
            break;
        }
        //if statement for checking if the player guessed the word on difficulty MEDIUM
        if (checkwin(blankp, wordcp, word) == word.size() && *diffp == 'M')
        {
            system("CLS");
            system("COLOR A");
            *diffp = 'H';
            printcongrats();
            cout << "The word is " << word << "!" << endl;
            cout << "\nPress enter to proceed to difficulty HARD!";
            getch();
            break;
        }
        //if statement for checking if the player guessed the word on difficulty HARD
        if (checkwin(blankp, wordcp, word) == word.size() && *diffp == 'H')
        {
            system("CLS");
            system("COLOR A");
            printcongrats();
            cout << "The word is " << word << "!" << endl;
            break;
        }

        cout << "\nThe hint is: " << hint << endl << endl;
        for (int i = 0; i < word.size(); i++)
        cout << blank[i];

        cout << "\n\nEnter a letter/letters (A SINGLE LETTER IS BETTER FOR INPUT): ";
        cin >> Guess;
        GUESS = toupper(Guess);
        guess = tolower(Guess);
        //we have noe 2 variables from guess, a uppercased and a lowercased

        if (word.find (guess) != string::npos || word.find(GUESS) != string::npos)
        {
            system("CLS");
            hangman (wrong, word);
            for (int i = 0; i < word.size(); i++)
            {
                if (word[i] == guess || word[i] == GUESS)
                blank[i] = word[i];
            }
        }

        else
        {
            system("CLS");
            wrong++;
            hangman (wrong, word);
        }
    }
}

int checkwin (char *blnkp, char *wordcp, string word)
{
    int check = 0;

    for (int i = 0; i < word.size(); i++)
        if (*(blnkp + i) == *(wordcp + i))
            check++;

    return check;
}

void hangman (int wrong, string word)
{

    if (wrong == 1)
    {
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 2)
    {
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 3)
    {
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }


    if (wrong == 4)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }


    if (wrong == 5)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 6)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||   U" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 7)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||  !U" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 8)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||  !U!" << endl;
        cout << "\t\t\t||" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 9)
    {
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||  !U!" << endl;
        cout << "\t\t\t||  1" << endl;
        cout << "\t\t\t||" << endl;
    }

    if (wrong == 10)
    {
        system("COLOR C");
        cout << "\t\t\t||=====" << endl;
        cout << "\t\t\t||   O" << endl;
        cout << "\t\t\t||  !U!" << endl;
        cout << "\t\t\t||  1 1 " << endl;
        cout << "\t\t\t||YOU DIED!" << endl;
        cout << "\nThe word is " << word << "." << endl;
        printgameover();
    }
}

void bubblesort (struct scores *player)
{
    int tempscore, n = 10;
    string tempname;
    for (int i = 0; i < (n - 1); i++)
    {
        for (int j = 0; j < (n - i - 1); j++)
        {
            if (player->score[j+1] > player->score[j])
            {
                tempscore = player->score[j+1];
                player->score[j+1] = player->score[j];
                player->score[j] = tempscore;
                tempname = player->name[j+1];
                player->name[j+1] = player->name[j];
                player->name[j] = tempname;
            }
        }
    }
}

void highscorefile (struct scores *player, int plyrctr)
{
    ofstream fout;

    fout.open ("highscores.text");

    for (int i = 0; i < plyrctr; i++)
    {
    fout << "#" << i + 1 << ": " << player->name[i] << endl;
    fout << "Score: " << player->score[i] << endl;
    }

    fout.close();

    ifstream fin;
    string word, score;

    fin.open("highscores.text");

    for (int i = 0; i < plyrctr; i++)
    {
    getline (fin, word);
    cout << word << endl;
    getline (fin, score);
    cout << score << endl << endl;
    }
    fin.close();
}

void wordsdatabase (int wordsize, class wordclass *easy, class wordclass*med, class wordclass *hard)
{
    ifstream fin("words.text");
    string trash;

    if (fin.is_open())
    {
        for (int i = 0; i < wordsize; i++)
        {
            getline (fin, easy->word[i]);
            getline (fin, easy->hint[i]);
        }

        getline (fin, trash);

        for (int i = 0; i < wordsize; i++)
        {
            getline (fin, med->word[i]);
            getline (fin, med->hint[i]);
        }

        getline (fin, trash);

        for (int i = 0; i < wordsize; i++)
        {
            getline (fin, hard->word[i]);
            getline (fin, hard->hint[i]);
        }

        fin.close();
    }
}

void printhangman(void)
{
    cout << "\n" << endl;
    cout << "88       88                                                                               88" << endl;
    cout << "88       88                                                                               88" << endl;
    cout << "88       88                                                                               88" << endl;
    cout << "88,dPPYba88  ,adPPYYba, 8b,dPPYba,   ,adPPYb,d8 88,dPYba,,adPYba,  ,adPPYYba, 8b,dPPYba,  88" << endl;
    cout << "88       8a ''     `Y8 88P'   `'8a a8'    `Y88 88P'   '88'    '8a ''     `Y8 88P'   `'8a  88" << endl;
    cout << "88       88 ,adPPPPP88 88       88 8b       88 88      88      88 ,adPPPPP88 88       88  88" << endl;
    cout << "88       88 88,    ,88 88       88 '8a,   ,d88 88      88      88 88,    ,88 88       88    " << endl;
    cout << "88       88 `'8bbdP'Y8 88       88  `'YbbdP'Y8 88      88      88 `'8bbdP'Y8 88       88  88" << endl;
    cout << "                                    aa,    ,88                                              " << endl;
    cout << "                                     'Y8bbdP'                                               " << endl;
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

void printgameover(void)
{
    cout << "\n" << endl;
    cout << " ,adPPYba,                                                                                           88" << endl;
    cout << "a8'    `Y88                                                                                          88" << endl;
    cout << "8b       88                                                                                          88" << endl;
    cout << "8b           ,adPPYYba, 88,dPYba,,adPYba,   ,adPPYba,  ,adPPYba,  8b       d8  ,adPPYba, 8b,dPPYba,  88" << endl;
    cout << "8b   yddd88  ''     `Y8 88P'   '88'    '8a a8P_____88 a8'     '8a `8b     d8' a8P_____88 88P'   'Y8  88" << endl;
    cout << "8a,     d88  ,adPPPPP88 88      88      88 8PP''''''' 8b       d8  `8b   d8'  8PP''''''' 88          88" << endl;
    cout << "'8a,   ,d8'  88,    ,88 88      88      88 '8b,   ,aa '8a,   ,a8'   `8b,d8'   '8b,   ,aa 88'           " << endl;
    cout << "  'YbbPY'    `'8bbdP'Y8 88      88      88  `'Ybbd8''  `'YbbdP''      '8'      `'Ybbd8'' 88          88" << endl;
}

