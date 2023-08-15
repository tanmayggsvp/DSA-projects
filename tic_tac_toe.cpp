#include<bits/stdc++.h>
using namespace std;

// function to represent tic tac board
void show_board(vector<vector<char>>&board)
{
    cout<<endl<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<"    "<<board[0][0]<<"   |   "<<board[0][1]<<"   |   "<<board[0][2]<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<"    "<<board[1][0]<<"   |   "<<board[1][1]<<"   |   "<<board[1][2]<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<"    "<<board[2][0]<<"   |   "<<board[2][1]<<"   |   "<<board[2][2]<<endl;
    cout<<"     "<<"   |   "<<"    |   "<<endl;
    cout<<endl<<endl;

}

// function to get player choice.
void get_player_choice(vector<vector<char>>&board)
{
    while(true)
    {
        int row_number;
        int column_number;
        cout<<"Enter row: ";
        cin>>row_number;
        cout<<endl;
        cout<<"Enter column: ";
        cin>>column_number;
        cout<<endl;
        if(row_number<0 or row_number>2 or column_number<0 or column_number>2)
        {
            cout<<"please select valid choice"<<endl;
        }
        else if(board[row_number][column_number]!=' ')
        {
            cout<<"please select empty cell"<<endl;
        }
        else
        {
            board[row_number][column_number] = 'X';
            break;
        }


    }
}

// function which will return status of the board
string result(vector<vector<char>>&board)
{
    for(int i = 0;i<3;i++)
    {
        if(board[i][0]!=' ' and board[i][0]==board[i][1] and board[i][1]==board[i][2]) // checking rows
        {
            return "win";
        }
        if(board[0][i]!=' ' and board[0][i] == board[1][i] and board[1][i]==board[2][i])  //checking columns
        {
            return "win";
        }
    }
    if(board[0][0]!=' ' and board[0][0] == board[1][1] and board[1][1] == board[2][2])  //checking diagnol
    {
        return "win";
    }
    if(board[0][2]!=' ' and board[0][2] == board[1][1] and board[1][1] == board[2][0])   // checking diagnol
    {
        return "win";
    }

    for(int i = 0;i<3;i++)     // checkinh whether there are empty spaces
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                return "incomplete";
            }
        }
    }
    return "tie";  
}

// function which retur
int Min_max_score(vector<vector<char>>board,bool is_maximizing)
{
    string a = result(board);
    if(is_maximizing and a=="win")
    {
        return -1;
    }
    if(!is_maximizing and a=="win")
    {
        return +1;
    }
    if(a=="tie")
    {
        return 0;
    }
    if(is_maximizing)
    {
        int score = -1e9;
        for(int i = 0;i<3;i++)
        {
            for(int j = 0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j] = 'O';
                    score = max(score,Min_max_score(board,false));
                    board[i][j] = ' ';
                }
            }
        }
        return score;
    }
    else
    {
        int score = +1e9;
        for(int i = 0;i<3;i++)
        {
            for(int j = 0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j] = 'X';
                    score = min(score,Min_max_score(board,true));
                    board[i][j] = ' ';
                }
            }
        }
        return score;
    }

}
pair<int,int> next_best_move(vector<vector<char>>board)
{
    int best_score = -1e9;
    pair<int,int>best_move;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j] = 'O';
                int score = Min_max_score(board,false);
                if(best_score<score)
                {
                    best_score = score;
                    best_move = {i,j};
                }
                board[i][j] = ' ';
            }
        }
    }
    return best_move;
}


// function which fills with the computers best choice.
void get_computer_choice(vector<vector<char>>&board)
{
    pair<int,int>best_move = next_best_move(board);
    int row = best_move.first;
    int column = best_move.second;
    board[row][column] = 'O';
}

int main()
{
    vector<vector<char>>board(3,vector<char>(3,' '));

    // infinite loop till the game ends;
    while(true)
    {
        show_board(board);                 //show_board

        get_player_choice(board);  //getting player choice

        //checking whether the game is ended
        string a = result(board);  
        if(a=="win")
        {
            show_board(board); 
            cout<<"Congratulations! you have beaten the unbeatable"<<endl;
            break;
        }
        else if(a=="tie")
        {
            show_board(board); 
            cout<<"The game is Tie!"<<endl;
            break;
        }

        get_computer_choice(board);   //getting computer choice

        // checking whether the game is ended or not
        string b = result(board);
        if(b=="win")
        {
            cout<<"The computer had won!"<<endl;
            break;
        }
        else if(b=="tie")
        {
            cout<<"The game is Tie!"<<endl;
            break;
        }        

    }

    return 0;
}