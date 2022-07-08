#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
char my_ai, your_i;
char BOARD[3][3];
bool v = 0;
void print()
{
    system("CLS");
    for (int i = 0; i < 3; i++, cout << endl)
    {
        for (int j = 0; j < 3; j++)
            cout << BOARD[i][j] << ' ';
    }
}
bool notDone()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (BOARD[i][j] == '-')
                return 1;
    return 0;
}
int winLose()
{
    for (int r = 0; r < 3; r++)
    {
        if (BOARD[r][0] == BOARD[r][1] && BOARD[r][1] == BOARD[r][2])
        {
            if (BOARD[r][0] == my_ai)
                return 1;
            else if (BOARD[r][0] == your_i)
                return -1;
        }
    }
    for (int c = 0; c < 3; c++)
    {
        if (BOARD[0][c] == BOARD[1][c] && BOARD[1][c] == BOARD[2][c])
        {
            if (BOARD[0][c] == my_ai)
                return 1;

            else if (BOARD[0][c] == your_i)
                return -1;
        }
    }
    if (BOARD[0][0] == BOARD[1][1] && BOARD[1][1] == BOARD[2][2])
    {
        if (BOARD[0][0] == my_ai)
            return 1;
        else if (BOARD[0][0] == your_i)
            return -1;
    }
    if (BOARD[0][2] == BOARD[1][1] && BOARD[1][1] == BOARD[2][0])
    {
        if (BOARD[0][2] == my_ai)
            return 1;
        else if (BOARD[0][2] == your_i)
            return -1;
    }
    return 0;
}
vector<int> PruinMinMax(bool isMaximizing, int alpha = -1000, int beta = 1000)
{
    int winlose = winLose();
    if (winlose != 0)
        return vector<int>({ winlose, 0, 0 });
    if (notDone() == 0)
        return vector<int>({ 0, 0, 0 });
    if (isMaximizing)
    {

        int maxEva = -5, eva, l = 0, r = 0;
        bool f = 0;
        for (int i = 0; i < 3; i++)
        {
            if (f)
                break;
            for (int j = 0; j < 3; j++)
                if (BOARD[i][j] == '-')
                {
                    BOARD[i][j] = my_ai;
                    eva = PruinMinMax(0, alpha, beta)[0];
                    BOARD[i][j] = '-';
                    if (eva > maxEva)
                        maxEva = eva, l = i, r = j;
                    alpha = max(alpha, eva);
                    if (beta <= alpha)
                    {
                        // cout << "pruined\n";
                        f = 1;
                        break;
                    }
                }
        }
        return vector<int>({ maxEva, l, r });
    }
    else
    {
        int minEva = 5, eva = 0, l = 0, r = 0;
        bool f = 0;
        for (int i = 0; i < 3; i++)
        {
            if (f)
                break;
            for (int j = 0; j < 3; j++)
                if (BOARD[i][j] == '-')
                {
                    BOARD[i][j] = your_i;
                    eva = PruinMinMax(1, alpha, beta)[0];
                    BOARD[i][j] = '-';
                    if (eva < minEva)
                        minEva = eva, l = i, r = j;
                    beta = min(beta, eva);
                    if (beta <= alpha)
                    {
                        // cout << "pruined\n";
                        f = 1;
                        break;
                    }
                }
        }
        return vector<int>({ minEva, l, r });
    }
}
// no pruining
vector<int> noPruinMinMax(bool isMaximizing)
{
    int winlose = winLose();
    if (winlose != 0)
        return vector<int>({ winlose, 0, 0 });
    if (notDone() == 0)
        return vector<int>({ 0, 0, 0 });
    if (isMaximizing)
    {
        int maxEva = -5, eva, l = 0, r = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                if (BOARD[i][j] == '-')
                {
                    BOARD[i][j] = my_ai;
                    eva = noPruinMinMax(0)[0];
                    BOARD[i][j] = '-';
                    if (eva > maxEva)
                        maxEva = eva, l = i, r = j;
                }
        }
        return vector<int>({ maxEva, l, r });
    }
    else
    {
        int minEva = 5, eva = 0, l = 0, r = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                if (BOARD[i][j] == '-')
                {
                    BOARD[i][j] = your_i;
                    eva = noPruinMinMax(1)[0];
                    BOARD[i][j] = '-';
                    if (eva < minEva)
                        minEva = eva, l = i, r = j;
                }
        }
        return vector<int>({ minEva, l, r });
    }
}
vector<int> minMax(bool pruin)
{
    if (v)
        return PruinMinMax(1);
    return noPruinMinMax(1);
}
int main()
{
    string s;
    cout << "if you want pruining type yes if not type no\n";
    cin >> s;
    if (s == "yes")
    {
        v = 1;
    }
    int move;
    cout << "type x to play \"x\" or o to play \"o\"\n";
    cin >> your_i;
    my_ai = 'x';
    if (your_i == 'x')
        my_ai = 'o';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            BOARD[i][j] = '-';
    if (my_ai == 'x')
    {
        vector<int> kk;
        while (notDone() && !(winLose()))
        {
            kk = minMax(1);
            BOARD[kk[1]][kk[2]] = 'x';
            print();
            if (!(notDone() && !(winLose())))
                break;
            cout << "enter where to play\n";
            cin >> move;
            while (BOARD[int(ceil(move / 3.0)) - 1][((move % 3) ? (move % 3 - 1) : 2)] != '-')
            {
                cout << move << " is alredy taken please enter another number:\n";
                cin >> move;
            }
            BOARD[int(ceil(move / 3.0)) - 1][((move % 3) ? (move % 3 - 1) : 2)] = 'o';
        }
    }
    else
    {
        vector<int> kk;
        while (notDone() && !(winLose()))
        {
            cout << "enter where to play\n";
            cin >> move;
            while (BOARD[int(ceil(move / 3.0)) - 1][((move % 3) ? (move % 3 - 1) : 2)] != '-')
            {
                cout << move << " is alredy taken please enter another number:\n";
                cin >> move;
            }

            BOARD[int(ceil(move / 3.0)) - 1][((move % 3) ? (move % 3 - 1) : 2)] = your_i;
            // print();
            if (!(notDone() && !(winLose())))
                break;
            kk = minMax(1);
            BOARD[kk[1]][kk[2]] = my_ai;
            print();
        }
    }
    if (!notDone())
        cout << "It's a tie :), try again!";
    if (winLose() == 1)
        cout << "I WON I AM SMARTER THAN YOU!!";
    // you can't win you can dream of that ;)
    return 0;
}