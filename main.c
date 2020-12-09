#include<stdio.h>
#include<conio.h>
#include<math.h>

enum Players {
    CPU = 'O',
    USER = 'X'
};

char gameBoard[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

void printBoard(char board[3][3]);
void placePiece(char piece, int position);
int checkEqual(char x, char y, char z);
char checkWin(char board[3][3]);
int isExists(int* array, int value);
int minmax(char board[3][3], int depth, int maximizing, int alpha, int beta);
int bestMove(char board[3][3]);

int main(){
    int userInput;
    int placedPositions[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int currentMove = 0;
    char condition = ' ';

    printBoard(gameBoard);
    while(1){
        printf("Choose where to place? (1-9): ");
        scanf("%d", &userInput);

        while (isExists(placedPositions, userInput) || userInput < 1 || userInput > 9){
            printf("Invaild Input Try again\n");
            printf("Choose where to place? (1-9): ");
            scanf("%d", &userInput);
        }

        placePiece(USER, userInput);
        placedPositions[currentMove++] = userInput;
        condition = checkWin(gameBoard);
        if(condition != ' ') break;

        int cpuMove = bestMove(gameBoard);
        placePiece(CPU, cpuMove);
        placedPositions[currentMove++] = cpuMove;
        printBoard(gameBoard);

        condition = checkWin(gameBoard);
        if(condition != ' ') break;

    }
    printBoard(gameBoard);

    if(condition == 'T') printf("Its TIE!");
    else if(condition == CPU) printf("CPU WON!");
    else printf("YOU WON!");

    printf("\n\n");
    printf("Press any button to exit.");
    getch();
    
    return 0;
}

int isExists(int* array, int value){
    for (int i = 0; i < 9; i++)
    {   
        if(array[i] == value) return 1;
    }
    return 0;   
}

void printBoard(char board[3][3]){
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j < 2) printf("%c|", board[i][j]);
            else printf("%c", board[i][j]);
        }
        if(i < 2) printf("\n-+-+-\n");
    }
    printf("\n\n");
}

void placePiece(char piece, int position){
    switch (position)
    {
    case 1:
        gameBoard[0][0] = piece;
        break;
    case 2:
        gameBoard[0][1] = piece;
        break;
    case 3:
        gameBoard[0][2] = piece;
        break;
    case 4:
        gameBoard[1][0] = piece;
        break;
    case 5:
        gameBoard[1][1] = piece;
        break;
    case 6:
        gameBoard[1][2] = piece;
        break;
    case 7:
        gameBoard[2][0] = piece;
        break;
    case 8:
        gameBoard[2][1] = piece;
        break;
    case 9:
        gameBoard[2][2] = piece;
        break;
    }
}

int checkEqual(char x, char y, char z){
    if(x == y && y == z && x != ' ') return 1;
    else return 0;
}

char checkWin(char board[3][3]){
    //rows
    if(checkEqual(board[0][0], board[0][1], board[0][2])) return board[0][0];
    if(checkEqual(board[1][0], board[1][1], board[1][2])) return board[1][0];
    if(checkEqual(board[2][0], board[2][1], board[2][2])) return board[2][0];

    //columns
    if(checkEqual(board[0][0], board[1][0], board[2][0])) return board[0][0];
    if(checkEqual(board[0][1], board[1][1], board[2][1])) return board[0][1];
    if(checkEqual(board[0][2], board[1][2], board[2][2])) return board[0][2];

    //diagonals
    if(checkEqual(board[0][0], board[1][1], board[2][2])) return board[0][0];
    if(checkEqual(board[0][2], board[1][1], board[2][0])) return board[0][2];


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if(board[i][j] == ' ') return ' ';
        }
    }

    return 'T';
}

int minmax(char board[3][3], int depth, int maximizing, int alpha, int beta){
    if(checkWin(board) != ' ') {
        if(checkWin(board) == CPU) return 1;
        else if(checkWin(board) == USER) return -1;
        else return 0;        
    }

    if(maximizing){
        int bestScore = (int) -INFINITY;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' '){
                    board[i][j] = CPU;
                    int score = minmax(board, depth+1, 0, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = fmax(score, bestScore);
                    alpha = fmax(alpha, bestScore);
                    if(beta <= alpha) break;
                }
                
            }
            if(beta <= alpha) break;
        }
        return bestScore;
    }

    else {
        int bestScore = (int) INFINITY;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' '){
                    board[i][j] = USER;
                    int score = minmax(board, depth+1, 1, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = fmin(score, bestScore);
                    beta = fmin(beta, bestScore);
                    if(beta <= alpha) break;
                }
            }
            if(beta <= alpha) break;
        }
        return bestScore;
    }

}

int bestMove(char board[3][3]){
    int bestScore = (int) -INFINITY;
    int move[2] = {0, 0};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' '){
                board[i][j] = CPU;
                int score = minmax(board, 0, 0, (int) -INFINITY, (int) INFINITY);
                board[i][j] = ' ';
                if(score > bestScore){
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }

    if(move[0] == 0 && move[1] == 0) return 1;
    if(move[0] == 0 && move[1] == 1) return 2;
    if(move[0] == 0 && move[1] == 2) return 3;
    if(move[0] == 1 && move[1] == 0) return 4;
    if(move[0] == 1 && move[1] == 1) return 5;
    if(move[0] == 1 && move[1] == 2) return 6;
    if(move[0] == 2 && move[1] == 0) return 7;
    if(move[0] == 2 && move[1] == 1) return 8;
    if(move[0] == 2 && move[1] == 2) return 9;
}
