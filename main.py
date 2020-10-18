import ai

game_board = [[' ' for _ in range(3)] for _ in range(3)]
piece_placed = []
game_over_messages = {
    'X': 'USER WON!',
    'O': 'CPU WON!',
    'tie': 'Its TIE!'
}

def print_board(board):
    display = '\n'
    for i in range(3):
        for j in range(3):
            if j < 2:
                display += board[i][j]+'|'
            else:
                display += board[i][j]
        if i < 2:
            display += '\n-+-+-\n'
    print(display, '\n')

def check_win(board):
    is_tie = True

    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                is_tie = False
                break
    if is_tie:
        return 'tie'
    
    row1 = board[0][0] == board[0][1] == board[0][2] != ' '
    row2 = board[1][0] == board[1][1] == board[1][2] != ' '
    row3 = board[2][0] == board[2][1] == board[2][2] != ' '

    col1 = board[0][0] == board[1][0] == board[2][0] != ' '
    col2 = board[0][1] == board[1][1] == board[2][1] != ' '
    col3 = board[0][2] == board[1][2] == board[2][2] != ' '

    dia1 = board[0][0] == board[1][1] == board[2][2] != ' '
    dia2 = board[0][2] == board[1][1] == board[2][0] != ' '

    if row1:
        return board[0][0]
    if row2:
        return board[1][0]
    if row3:
        return board[2][0]

    if col1:
        return board[0][0]
    if col2:
        return board[0][1]
    if col3:
        return board[0][2]

    if dia1:
        return board[0][0]
    if dia2:
        return board[0][2]
    
    return False

def place_piece(board, pos, player):
    piece = None
    if player == 'cpu':
        piece = 'O'
    elif player == 'user':
        piece = 'X'
    else:
        piece = ' '

    if pos == 1:
        board[0][0] = piece
    elif pos == 2:
        board[0][1] = piece
    elif pos == 3:
        board[0][2] = piece
    elif pos == 4:
        board[1][0] = piece
    elif pos == 5:
        board[1][1] = piece
    elif pos == 6:
        board[1][2] = piece
    elif pos == 7:
        board[2][0] = piece
    elif pos == 8:
        board[2][1] = piece
    elif pos == 9:
        board[2][2] = piece

def eval_move(move):
    i = move[0]
    j = move[1]
    
    if i == j == 0:
        return 1
    elif i == 0 and j == 1:
        return 2
    elif i == 0 and j == 2:
        return 3
    elif i == 1 and j == 0:
        return 4
    elif i == 1 and j == 1:
        return 5
    elif i == 1 and j == 2:
        return 6
    elif i == 2 and j == 0:
        return 7
    elif i == 2 and j == 1:
        return 8
    elif i == 2 and j == 2:
        return 9

def make_move(board, pos, player, piece_placed):
    piece_placed.append(pos)
    place_piece(board, pos, player)
    print_board(board)

if __name__ == "__main__":
    print_board(game_board)
    while True:
        user_choice = None

        try:
            user_choice = int(input("Choose where to place? (1-9): "))
            if user_choice < 1 or user_choice > 9:
                raise Exception()
            elif user_choice in piece_placed:
                print("Place already taken...")
                continue
        except Exception as e:
            print("Invalid input")
            continue

        make_move(game_board, user_choice, 'user', piece_placed)
        
        result = check_win(game_board)
        if result:
            print(game_over_messages[result])
            break
        

        cpu_choice = eval_move(ai.best_move(game_board))

        make_move(game_board, cpu_choice, 'cpu', piece_placed)
        
        result = check_win(game_board)
        if result:
            print(game_over_messages[result])
            break

