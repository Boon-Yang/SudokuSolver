void load_board(const char* filename, char board[9][9]); 
void display_board(const char board[9][9]);

/* declare functions for completed board check*/
bool is_complete(const char board[9][9], int start_row=0, int start_col=0);
bool is_complete_row(const char* data, int start_col);


/*declare functions for valid move check (and fill)*/
bool make_move(const char position[], const char digit, char board[9][9]);
bool is_valid_row(int row_idx, const char digit,const char board[9][9]);
bool is_valid_col(int col_idx, const char digit,const char board[9][9]);
bool is_valid_local(int row_idx, int col_idx, const char digit,const char board[9][9]);
bool is_within_bound(int row_idx, int col_idx);
  
/*declare function save_board*/
bool save_board(const char* filename, const char board[9][9]);

/*declare function solve_board*/
bool solve_board(char board[9][9], int row=0, int col=0, bool is_first_time_call=true);
	       
