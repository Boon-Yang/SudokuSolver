#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
// ==================Q1==================

/* helper function for is_complete.
   is_complete_row checks if subsequent boxes from 
   start_col have been filled with proper digits(1-9).*/

bool is_complete_row(const char* data, int start_col){

  // initialise the bounds
  int low_bound = '1';
  int up_bound = '9';
  int col = start_col;
  
  // loop thru by col and check if the contents inside the boxes are between 1-9
  while (col<=8){
    if (data[col]<low_bound || data[col]>up_bound)
      return false;
    col++;
  }
  // return true if all the boxes are filled with proper digits
  return true;
}

/* is_complete checks if a given board state
   is complete. Has the option to start looping
   from any box at (start_row, start_col).

   Note: The starting indices, start_row and start_col are 0 by default. 
   Calling is_complete without passing in starting indices will inspect the
   full board state

   With the option to inspect from any box, redundant inspections can be avoided
   in solve_board*/

bool is_complete(const char board[9][9], int start_row, int start_col) {

  int row = start_row;

  // check the fillings in each row  
  while (row<=8) {
    if (!is_complete_row(board[row], start_col))
      return false;
    row++;
    // for subsequent rows, start from 0th col
    start_col = 0;
  }
  return true;
}

// ====================Q2===================

/*helper function for make_move. is_valid_row checks if
  a given digit satisfies the row constraint*/

bool is_valid_row(int row,
		  const char digit,
		  const char board[9][9]) {
  // returs false if the digit has appeared before in the same row
  for (int i=0; i<9; i++)   {
    if (board[row][i] == digit)
	return false;
    }
  return true;
}

/*helper function for make_move. is_valid_col checks if
  the digit satisfies the column constraint*/

bool is_valid_col(int col,
		  const char digit,
		  const char board[9][9]) {
  //  returns false if the digit has appeared in the same col
  for (int r=0; r<9; r++) {
    if (board[r][col] == digit)
      return false;
  }
  return true;
}

/*helper function for make_move. is_valid_local checks if
  the digit satisfies the local constraint*/

bool is_valid_local(int row_idx, int col_idx,
		    const char digit,
		    const char board[9][9]) {

  // calculate row and col start indices
  row_idx -= (row_idx % 3);
  col_idx -= (col_idx % 3);
  
  // returns false if the digit has appeared locally
  for (int row=row_idx; row<=row_idx+2; row++) {
    for (int col=col_idx; col<=col_idx+2; col++) {
      if (board[row][col] == digit)
	return false;
    }
  }
  return true;
}

/*helper function for make_move. is_within_bound checks if the 
  row and column indices are within bound*/

bool is_within_bound(int row, int col) {
  // returns false if either the row or col is out of bound
  return ((row>=0 && row<9)&&(col>=0 && col<9));
}


/* make_move places a digit onto board at a given position, 
   if the digit is valid and returns true, otherwise returns 
   false

Note: in additional to the constraints, make_move will also skip through any
non-empty box.
*/

bool make_move(const char position[], const char digit,
	       char board[9][9]) {

  // convert the row and col indices before passing into the helper functions
  int row = position[0] - 'A';
  int col = position[1] - '1';

  // if guard: check for the length of position string (to
  // avoid positions like A10 being interpreted as A1)
  if ((strlen(position)!=2)||(board[row][col]!='.'))
    return false;

  // only fill in the box with digit if the row, col, bound and local
  // constraints are satisfied
  if (is_valid_row(row, digit, board)&&
      is_valid_col(col, digit, board)&&
      is_valid_local(row, col, digit, board) &&
      is_within_bound(row, col)) {
    board[row][col]=digit;
    return true;
    }
  return false;
}

//=======================Q3==============================
// save_board saves a given board as a file with file name, filename

bool save_board(const char* filename, const char board[9][9]) {

  ofstream out;
  out.open(filename);
  if (!out) 
    return false;
  for (int row=0; row<9; row++){
    for (int col=0; col<9; col++) {
      out.put(board[row][col]);
      if (!((col+1)%9))
	out.put('\n');
    }
  }
  out.close();
  return true;
}

//====================Q4&Q5====================

/* solve_board attempts to solve the sudoku with recursive backtracking.
It fills in the board with the solution, returns true and prints out the 
number of recursive calls if the sudoku puzzle is solvable. Otherwise, it 
returns flase when the puzzle has no solution.

For clarity, these are the important steps invloved:

Step 0: Check if the board needs to be solved
Step 1: Get an empty box
Step 2: Attempt to fill in the empty box with a valid trial digit
Step 3: If successful attempt: Recursively solve for the next empty box
Step 4: If unsuccessful: Backtrack ie increment the trial digit by one */

bool solve_board(char board[9][9], int row, int col, bool is_first_time_call) {

  // the specific format for board indices
  char position[2];

  // count the recursive calls
  static int count=0;
  if (is_first_time_call) {
    count = 0;
    is_first_time_call = false;
  }
  count++;
  
  // if guard: move to the first element of the next row if col exceeds bound
  if (col > 8 && row < 8) {
      col = 0;
      row++;
    }
  // ----------------- Step 0: Check if the board state is complete -----------------
  // Perform checks with a loop starting from current box (row, col)
  // to avoid redundant checks. Returns true if the board state is complete.
  if (is_complete(board, row, col)){
    cout<<"The number of recursive calls: "<< count<< endl;
    count = 0; // reset count to 0 to avoid carry forward
    return true;
  }
  
  // else if the board state is incomplete the board needs to be solved
  // ----------------- Step 1: Get the empty box-----------------
  // get the row and col indices for the next empty box (row, col)
  while ((board[row][col]!='.')&&(row<=8)){
    col++;
    if (col > 8) {
      col = 0;
      row++;
    } 
  }
  // convert the indices of the empty box to appropriate form
  position[0] = 'A' + row;
  position[1] = '1' + col;

  // ----------------- Step 2: Attempt to fill in the box with a valid digit -----------------
  for (char digit='1'; digit<='9'; digit++) {
    if (make_move(position, digit, board)) {

      // -----------------  Step 3: Recursion -----------------
      // Note: if guard at the beginning  prevents going beyond the column bound
      if (solve_board(board, row, ++col, is_first_time_call)) 	
    	return true;
      else {
	// ----------------- Step 4: Backtrack if necessary -----------------
	// decrement col index and revert back
	board[row][--col]='.';
      }
    }
  }
  // Exhausted all 9 digits, failed attempt (return false)
  return false;
}




  
