from math import inf as infinity
from main import check_win
from sys import setrecursionlimit
setrecursionlimit(10**8)

scores = {
'O': 1,
'tie': 0,
'X': -1
}

def best_move(board):
    best_score = -infinity
    move = None
    for i, j in ((i, j) for i in range(3) for j in range(3)):
        if board[i][j] == ' ':
            board[i][j] = 'O'
            score = minmax(board, 0, False, -infinity, infinity)
            board[i][j] = ' '
            if score > best_score:
                best_score = score
                move = (i, j)
    return move


def minmax(board, depth, maximizing, alpha, beta):
    result = check_win(board)
    if result:
        return scores[result]
    
    if maximizing:
        best_score = -infinity
        for i, j in ((i, j) for i in range(3) for j in range(3)):
            if board[i][j] == ' ':
                board[i][j] = 'O'
                score = minmax(board, depth + 1, False, alpha, beta)
                board[i][j] = ' '
                best_score = max(score, best_score)
                alpha = max(best_score, alpha)
                if beta <= alpha:
                    break
        return best_score
    else:
        best_score = infinity
        for i, j in ((i, j) for i in range(3) for j in range(3)):
            if board[i][j] == ' ':
                board[i][j] = 'X'
                score = minmax(board, depth + 1, True, alpha, beta)
                board[i][j] = ' '
                best_score = min(score, best_score)
                beta = min(best_score, beta)
                if beta <= alpha:
                    break
        return best_score