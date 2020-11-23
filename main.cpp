#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  // Test for empty space: Not completed
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  // Test for proper digit: Completed
  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  // Test for improper filling: Not Completed
  cout << "Test for improper digit"<< "\n";
  load_board("easy.dat", board);
  cout << "Board is ";
  board[3][5] = '*';
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  //  Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // write more tests
  load_board("easy.dat", board);

  // Test for local constraint: Should be NOT OK
  cout<<"Test for local constraint. \n";
  cout << "Putting '9' into I8 is ";
  if (!make_move("I8", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Test for row constraint: Should be NOT OK
   cout<<"Test for row constraint. \n";
  cout << "Putting '7' into I8 is ";
  if (!make_move("I8", '7', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Test for col constraint: Should be NOT OK
   cout<<"Test for column constraint. \n";
  cout << "Putting '6' into I8 is ";
  if (!make_move("I8", '6', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Test for bound constraint for row_idx: Should be NOT ok
  cout<<"Test for row idx bound constraint. \n";
  cout << "Putting '1' into J8 is ";
  if (!make_move("J8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);  

  // Test for bound constraint for col_idx: Should be NOT ok
  cout<<"Test for column idx bound constraint. \n";
  cout << "Putting '1' into H10 is ";
  if (!make_move("H10", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);  

  // Test for filling in a non empty box: Should be NOT ok
  cout<<"Test for filling in a non-empty box. \n";
  cout << "Putting '1' into E2 is ";
  if (!make_move("E2", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);  

  cout << "=================== Question 3 ===================" << "\n\n";

  // should be successful
  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";

  // solution exists
  load_board("easy.dat", board);

  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // solution exists
  load_board("medium.dat", board);
 
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  //  write more tests
  load_board("test01.dat", board);
 
  if (solve_board(board)) {
    cout << "The 'test01' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // last row empty test
  load_board("test02_last_row_empty.dat", board);
  if (solve_board(board)) {
    cout << "The 'test02_last_row_empty' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  
  cout << "=================== Question 5 ===================" << "\n\n";
  
  // write more tests
  // Solve for:
  // easy board
  load_board("easy.dat", board);
  
  if (solve_board(board)) {
    cout<<"easy.dat has a solution:" << '\n';
    display_board(board);
  }  else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // medium board
  load_board("medium.dat", board);
  
  if (solve_board(board)) {
    cout<<"medium.dat has a solution:" << '\n';
    display_board(board);
  }  else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // mystery board 1
  load_board("mystery1.dat", board);
  
  if (solve_board(board)) {
    cout<<"mystery1.dat has a solution:" << '\n';

    display_board(board);
  }  else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // mystery board 2
  load_board("mystery2.dat", board);
  
  if (solve_board(board)) {
    cout<<"mystery2.dat has a solution:" << '\n';
    display_board(board);
  }  else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // mystery board 3
  load_board("mystery3.dat", board);
 
  if (solve_board(board)) {
    cout<<"mystery3.dat has a solution:" << '\n';
    display_board(board);
  }  else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  return 0;
}
