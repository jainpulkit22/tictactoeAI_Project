/*
    We have designed the tictactoe game using minimax algorithm with alpha beta pruning, and it always follow the winning strategy for the first player,
    i.e. Computer in our case. So, irrespective of what move the user(second player) takes our first player(computer) always
    follows a winning strategy (i.e the result of this game is either in the favour of computer(first player) or the match
    is tied, but the second player(user) will not be the winner in any case).

    Time Complexity: O(b^(d/2)), where b denotes the branching factor and d denotes the depth of the solution(/recursion) tree.

    Team Memebers:
    _______________________________

    |Pulkit Jain      |  18UCS163 |
    |Ayush Rathi      |  18UCS227 |
    |Lakshya Akar     |  18UCC020 |
    |Jayant Khandelwal|  18UCC034 |
    _______________________________
*/
#include<bits/stdc++.h>
using namespace std;
char gameboard[3][3];//char array to store the gameboard
char computer = 'x', opponent = 'o'; //character x is the character played by customer and character 'o' is the character played by opponent(User)
int score;
//evaluating if anybody has won the match
bool evaluate()
{
    //checking if any of the row has all the columns with same value and not equal to initial
    for (int i = 0; i < 3; i++)
    {
        if (gameboard[i][0] == gameboard[i][1] &&
                gameboard[i][1] == gameboard[i][2])
        {
            if (gameboard[i][0] == computer) {
                score = 10;
                return true;
            }
            else if (gameboard[i][0] == opponent) {
                score = -10;
                return true;
            }
        }
    }
    //checking if any column has all the rows with same value and not equal to initial
    for (int j = 0; j < 3; j++)
    {
        if (gameboard[0][j] == gameboard[1][j] &&
                gameboard[1][j] == gameboard[2][j])
        {
            if (gameboard[0][j] == computer) {
                score = 10;
                return true;
            }

            else if (gameboard[0][j] == opponent) {
                score = -10;
                return true;
            }
        }
    }
    //checking if all the values of the left diagonal are same and not equal to initial
    if (gameboard[0][0] == gameboard[1][1] && gameboard[1][1] == gameboard[2][2])
    {
        if (gameboard[0][0] == computer) {
            score = 10;
            return true;
        }
        else if (gameboard[0][0] == opponent) {
            score = -10;
            return true;
        }
    }
    //checking if all the values of the right diagonal are same and not equal to initial
    if (gameboard[0][2] == gameboard[1][1] && gameboard[1][1] == gameboard[2][0])
    {
        if (gameboard[0][2] == computer) {
            score = 10;
            return true;
        }
        else if (gameboard[0][2] == opponent) {
            score = -10;
            return true;
        }
    }
    score = 0;
    return false;
}
//checking if the game is over or not
bool gameover()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameboard[i][j] == '_')
                return false;
        }
    }
    return true;
}
//function to display the game board
void displaygameboard()
{
    cout << " -------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " | " << gameboard[i][0] << " | " << gameboard[i][1] << " | " << gameboard[i][2] << " | " << endl;
    }
    cout << " -------------" << endl;
}
void resetgameboard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            gameboard[i][j] = '_';
    }
}
//minimax algorithm with alpha beta pruning to find best move
pair<int, pair<int, int> > minimax(char playChar, int Solutiondepth, int alpha, int beta)
{
    // Initializing Best Move
    pair<int, int> bestMove = { -1, -1};
    pair<int, int> curMove;
    int moveVal;
    // Initializing the Best Move with an initial value
    int bestMoveVal;
    if(playChar == computer)
        bestMoveVal = -10;
    else
        bestMoveVal = 10;
    // Returning if the game is over or there is a tie 
    if (evaluate())
    {
        return {score, bestMove};
    }
    if (gameover())
    {
        return {0, bestMove};
    }
    // Evaluating all the value of all the possible moves with alpha beta pruning to find the best move
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameboard[i][j] != '_')
            {
                continue;
            }
            curMove = {i, j};
            gameboard[i][j] = playChar;
            if (playChar == computer)
            {
                moveVal = minimax(opponent, Solutiondepth + 1, alpha, beta).first;
                if (bestMoveVal < moveVal)
                {
                    bestMoveVal = moveVal - Solutiondepth * 1;
                    bestMove = curMove;
                    alpha = max(alpha, bestMoveVal);
                    gameboard[i][j] = '_';
                    // Pruning the Nodes if the condition is satisfied
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
            else
            {
                moveVal = minimax(computer, Solutiondepth + 1, alpha, beta).first;
                if (bestMoveVal > moveVal)
                {
                    bestMoveVal = moveVal + Solutiondepth * 1;
                    bestMove = curMove;
                    alpha = min(beta, bestMoveVal);
                    gameboard[i][j] = '_';
                    // Pruning the nodes if the condition is satisfied
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
            gameboard[i][j] = '_';
        }
    }
    // Returning the best possible move along with a score assigned to it
    return {bestMoveVal, bestMove};
}
void playgame()
{
    int x, y;
    pair<int, pair<int, int> >move; //pair (x,y) to stoe the best move calculated
    cout << "Board at the start of the game" << endl;
    //displaying the initial state of the board at the start of the game
    displaygameboard();
    while (true) {
        //First turn is of computer so we are calculating the best move using the minimax algorithm
        move = minimax(computer, 0, -10, 10);
        gameboard[move.second.first][move.second.second] = computer;
        cout << "Modified Board after computer's turn" << endl;
        displaygameboard();
        //checking whether the computer has won the game after playing this move or is the match tied.
        //If both the cases are false then the game continues.
        if (evaluate())
        {
            cout << "Computer won the game" << endl;
            return;
        }
        if (gameover())
        {
            cout << "Match Tied!" << endl;
            return;
        }
        //Users turn to make a move
        cout << "Its your turn to make a move" << endl;
        invalid:
            cout << "Enter x-coordinate(0-2): ";
            cin >> x;
            cout << endl;
            cout << "Enter y-coordinate(0-2): ";
            cin >> y;
            cout << endl;
        //checking if the user's move is invalid or not
        if (x > 2 || y > 2 || x < 0 || y < 0 || gameboard[x][y] != '_') {
            cout << "Invalid move!" << endl;
            cout << "Please move again!" << endl;
            goto invalid;
        }
        gameboard[x][y] = opponent;
        cout << "Modified board after your turn" << endl;
        displaygameboard();
        //checking whether the user has won the game after playing this move or is the match tied.
        //If both the cases are false then the game continues.
        if (evaluate())
        {
            cout << "You won the game" << endl;
            return;
        }
        if (gameover())
        {
            cout << "Match Tied!" << endl;
            return;
        }
    }
}
int main()
{
    cout << "Instructions: " << endl;
    cout << "1) All the indexes are 0-based i.e. the top left square of the board is represented by (0,0) and bottom right by (2,2)" << endl;
    cout << "2) You will be playing with computer" << endl;
    cout << "3) After every chance the current situation of the gameboard will be displayed to you to make your next move" << endl;
    cout << "Let's Start the game!!" << endl;
    //reset the game board toits initial start before starting the game
    resetgameboard();
    playgame();
    return 0;
}