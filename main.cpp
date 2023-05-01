#include<stdio.h>
void printBoard(char board[26][26], int n);
bool checkLegalInDirection(char board[][26], int n, int row, int col,char colour, int deltaRow, int deltaCol);
int makeMove(char arr[26][26], int n, char turn,int *row, int *col);
int score_for_position_advantage(char board[][26],int n,char colour);
int number_of_moves_available(char board[26][26],int n,char colour);
int Bhai_char_ka_int_bnade(char c){
    char alpha[27] = "abcdefghijklmnopqrstuvwxyz";
    int s = 0;
    for (int i = 0; i <= 25; ++i) {
        if (alpha[i] == c){
            return s;
        }
        s++;
    }
}
bool is_board_filled(char arr[26][26],int n){
    bool tu = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j]=='U'){
                tu = false;
            }
        }
    }
    return tu;
}
void flipTiles(char board[][26], int n, int row, int col, char colour);
int count_specefic_color(char board[26][26],int n, char color){
    int uy = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(board[i][j] == color){
                uy++;
            }
        }
    }
    return uy;
}
void printBoard(char board[26][26], int n){
    char ch = 'a';
    printf("  ");
    for (int i = 0; i < n; ++i) {
        printf("%c",ch+i);
    }
    ch = 'a';
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%c ",ch+i);
        for (int j = 0; j < n; ++j) {
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
}
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int i = row + deltaRow;
    int j = col + deltaCol;
    char opponent_colour = (colour == 'W') ? 'B' : 'W'; // determine opponent's colour
    bool found_opponent = false;
    while (i >= 0 && i < n && j >= 0 && j < n) {
        if (board[i][j] == opponent_colour) {
            found_opponent = true;
        } else if (board[i][j] == colour && found_opponent) {
            return true; // legal move found
        } else {
            return false; // empty square or same colour
        }
        i += deltaRow;
        j += deltaCol;
    }
    return false; // out of bounds
}
void flipTiles(char board[][26], int n, int row, int col, char colour) {
    // Check all directions from the current position
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            // Skip the current position and directions with no movement
            if (deltaRow == 0 && deltaCol == 0) {
                continue;
            }
            // Check if the current direction is legal
            if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
                int r = row + deltaRow;
                int c = col + deltaCol;
                // Move along the direction and flip tiles until the end tile is reached
                while (board[r][c] != colour && board[r][c] != 'U') {
                    board[r][c] = colour;
                    r += deltaRow;
                    c += deltaCol;
                }
            }
        }
    }
}
int makeMove(char arr[26][26], int n, char turn,int* row,int* col) {
    char chabl[30][3];
    char Antiturn;
    if(turn=='B'){
        Antiturn='W';
    } else if(turn=='W'){
        Antiturn='B';
    }
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 3; ++j) {
            chabl[i][j] = 'z';
        }
    }
    int iu = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool che1 = checkLegalInDirection(arr,n,i,j,turn,1,1) || checkLegalInDirection(arr,n,i,j,turn,-1,-1) || checkLegalInDirection(arr,n,i,j,turn,1,-1) || checkLegalInDirection(arr,n,i,j,turn,-1,1) || checkLegalInDirection(arr,n,i,j,turn,1,0) || checkLegalInDirection(arr,n,i,j,turn,0,1) || checkLegalInDirection(arr,n,i,j,turn,-1,0) || checkLegalInDirection(arr,n,i,j,turn,0,-1) ;
            if (che1 && arr[i][j]=='U'){
                char t1 = i + 97; ;
                char t2 = j + 97;
                chabl[iu][0] = turn;
                chabl[iu][1] = t1;
                chabl[iu][2] = t2;
                iu++;
            }
        }
    }
    int in_while = 0;
    int best_move_at = 0;
    int best_move_score = 0;
    while (1){
        if ((chabl[in_while][0] != turn)){
            break;
        }
        char nakli_board[26][26];
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < 25; ++j) {
                nakli_board[i][j] = arr[i][j];
            }
        }
        char op1_row = chabl[in_while][1];
        char op2_col = chabl[in_while][2];
        int real_row = Bhai_char_ka_int_bnade(op1_row);
        int real_col = Bhai_char_ka_int_bnade(op2_col);
        nakli_board[real_row][real_col] = turn;
        flipTiles(nakli_board, n, real_row, real_col, turn);
        int uypo = count_specefic_color(nakli_board,n,turn);
        char chabl_inside[30][3];
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 3; ++j) {
                chabl_inside[i][j] = 'z';
            }
        }
        int inside_iu=0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool che2 = checkLegalInDirection(nakli_board,n,i,j,turn,1,1) || checkLegalInDirection(nakli_board,n,i,j,turn,-1,-1) || checkLegalInDirection(nakli_board,n,i,j,turn,1,-1) || checkLegalInDirection(nakli_board,n,i,j,turn,-1,1) || checkLegalInDirection(nakli_board,n,i,j,turn,1,0) || checkLegalInDirection(nakli_board,n,i,j,turn,0,1) || checkLegalInDirection(nakli_board,n,i,j,turn,-1,0) || checkLegalInDirection(nakli_board,n,i,j,turn,0,-1) ;
                if (che2 && arr[i][j]=='U'){
                    char t1 = i + 97; ;
                    char t2 = j + 97;
                    chabl_inside[inside_iu][0] = Antiturn;
                    chabl_inside[inside_iu][1] = t1;
                    chabl_inside[inside_iu][2] = t2;
                    inside_iu++;
                }
            }
        }
        int inside_in_while = 0;
        int to_cal_uypo_inside[50];
        int best_move_score_inside = 0;
        while(1){
            if(chabl_inside[inside_in_while][0]=='z'){
                break;
            }
            char nakli_ka_bhi_nakli_board[26][26];
            for (int i = 0; i < 25; ++i) {
                for (int j = 0; j < 25; ++j) {
                    nakli_ka_bhi_nakli_board[i][j] = nakli_board[i][j];
                }
            }
            char op1_row_inside = chabl_inside[inside_in_while][1];
            char op2_col_inside = chabl_inside[inside_in_while][2];
            int real_row_inside = Bhai_char_ka_int_bnade(op1_row_inside);
            int real_col_inside = Bhai_char_ka_int_bnade(op2_col_inside);
            nakli_ka_bhi_nakli_board[real_row_inside][real_col_inside] = Antiturn;
            flipTiles(nakli_ka_bhi_nakli_board, n, real_row_inside, real_col_inside, Antiturn);
            double uypo_inside = 5*count_specefic_color(nakli_ka_bhi_nakli_board,n,Antiturn) + 2*score_for_position_advantage(nakli_ka_bhi_nakli_board,n,Antiturn) + number_of_moves_available(nakli_ka_bhi_nakli_board,n,Antiturn);
            to_cal_uypo_inside[inside_in_while] = uypo_inside;
            inside_in_while++;
        }
        int avg_of_uypo_inside;
        int yoro;
        for (int i = 0; i < 50; ++i) {
            if(to_cal_uypo_inside[i]==0){
                break;
            }
            avg_of_uypo_inside+=to_cal_uypo_inside[i];
            yoro++;
        }
        avg_of_uypo_inside = avg_of_uypo_inside/yoro;
        int total_score= uypo - (0.75*avg_of_uypo_inside);
        if (total_score>best_move_score_inside){
            best_move_score_inside = total_score;
            best_move_at = in_while;
        }
        in_while++;
    }
    //
    char salman = chabl[best_move_at][1];
    char jack = chabl[best_move_at][2];
    *row = Bhai_char_ka_int_bnade(salman);
    *col = Bhai_char_ka_int_bnade(jack);
}
int score_for_position_advantage(char board[26][26],int n,char colour){
    int score =0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == colour){
                if((i==0 && j==0)||(i==(n-1)&&j==(n-1))||(i==0&&j==(n-1))||(i==(n-1)&&j==0)){
                    score+= 100;
                }
                else if(i==0 || j==0 || j==(n-1) || i==(n-1)){
                    score+=10;
                }
                else if((((i==(n-1)/2))&&(j==((n-1)/2)))||((i==((n-1)/2)+1)&&(j==((n-1)/2)+1))) {
                    score+=30;
                }
                else if ((i==(n/2)-1 && j==(n/2)) || (i==(n/2)) && (j==(n/2)-1)) {
                    score+=30;
                }else{
                    score+= 2;
                }
            }
        }
    }
    return score;
}
int number_of_moves_available(char board[26][26],int n,char colour) {
    int moves=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (checkLegalInDirection(board, n, i, j, colour, 1, 1)) {
                moves++;
            }
            if (checkLegalInDirection(board, n, i, j, colour, -1, -1)){
                moves++;
            }
            if (checkLegalInDirection(board, n, i, j, colour, 1, -1)){
                moves++;
            }
            if (checkLegalInDirection(board, n, i, j, colour, -1, 1)){
                moves++;
            }
            if(checkLegalInDirection(board, n, i, j, colour, 1, 0)){
                moves;
            }
            if(checkLegalInDirection(board, n, i, j, colour, 0, 1)){
                moves++;
            }
            if(checkLegalInDirection(board, n, i, j, colour, -1, 0)){
                moves++;
            }
            if(checkLegalInDirection(board, n, i, j, colour, 0, -1)){
                moves++;
            }
        }
    }
    return moves;
}
int main(void) {
    int n;
    char colour;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    printf("Computer plays (B/W): ");
    scanf(" %c", &colour);
    char arr[26][26];
    char Anticolour;
    if (colour == 'B') {
        Anticolour = 'W';
    } else {
        Anticolour = 'B';
    }
    for (int i = 0; i < n; ++i) {  // initializing the board
        for (int j = 0; j < n; ++j) {
            if ((((i == (n - 1) / 2)) && (j == ((n - 1) / 2))) ||
                ((i == ((n - 1) / 2) + 1) && (j == ((n - 1) / 2) + 1))) {
                arr[i][j] = 'W';
            } else if ((i == (n / 2) - 1 && j == (n / 2)) || (i == (n / 2)) && (j == (n / 2) - 1)) {
                arr[i][j] = 'B';
            } else {
                arr[i][j] = 'U';
            }
        }
    }
    printBoard(arr, n);
    bool game_over = false;
    int t = 0;
    while (!game_over) {
        int row, col;
        // Loop until the user enters a valid position
        while (1) {
            if (t == 0 && colour == 'B') {
                t++;
                break;
            }
            printf("Enter move for colour %c (RowCol): ", Anticolour);
            char row_letter;
            char col_letter;
            scanf(" %c%c", &row_letter, &col_letter);
            row = Bhai_char_ka_int_bnade(row_letter);
            col = Bhai_char_ka_int_bnade(col_letter);
            bool che1 = checkLegalInDirection(arr, n, row, col, Anticolour, 1, 1) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, -1, -1) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, 1, -1) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, -1, 1) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, 1, 0) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, 0, 1) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, -1, 0) ||
                        checkLegalInDirection(arr, n, row, col, Anticolour, 0, -1);
            if (che1) {
                arr[row][col] = Anticolour;
                flipTiles(arr, n, row, col, Anticolour);
                printBoard(arr, n);
                break;
            } else {
                printf("Invalid move.\n");
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        arr[i][j] = colour;
                    }
                }
                break;
            }
        }
        if (count_specefic_color(arr, n, colour) > count_specefic_color(arr, n, Anticolour) &&
            is_board_filled(arr, n)) {
            printf("%c player wins.", colour);
            game_over = true;
            break;
        } else if (count_specefic_color(arr, n, colour) < count_specefic_color(arr, n, Anticolour) &&
                   is_board_filled(arr, n)) {
            printf("%c player wins.", Anticolour);
            game_over = true;
            break;
        } else if (count_specefic_color(arr, n, colour) == count_specefic_color(arr, n, Anticolour) &&
                   is_board_filled(arr, n)) {
            printf("Draw!");
            game_over = true;
            break;
        }
        int move_result;
        int row_computer;
        int column_computer;
        move_result = makeMove(arr, n, colour, &row_computer, &column_computer);
        if (row_computer >= n || row_computer < 0 || column_computer >= n || column_computer < 0) {
            printf("%c player has no valid move.\n", colour);
            continue;
        }
        printf("Computer places %c at %c%c.\n", colour, row_computer + 97, column_computer + 97);
        arr[row_computer][column_computer] = colour;
        flipTiles(arr, n, row_computer, column_computer, colour);
        printBoard(arr, n);
    }
}