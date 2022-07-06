#include "game.h"
#include <cmath>
#include <chrono>
#include <thread>


#define P2P_MSG "P2P mode selected."
#define OP_ERR_MSG "Invalid opposition. Please try again: "
#define INP_ERR_MSG "Invalid square. PLease choose a free, valid square: "
#define O_CHOOSE_MSG "It's 'O's turn. Please choose square (x,y): "
#define X_CHOOSE_MSG "It's 'X's turn. Please choose square (x,y): "
#define PLAYER_CHOOSE_MSG "It's your turn. Please choose square (x,y): "
#define CPU_CHOOSE_MSG "AI chooses best possible move..."
#define REMATCH_ERR_MSG "Please enter 'y' or 'n': "
#define END_MSG "Thank you for playing TicTacToe."
#define PLY_AGN_MSG " Play Again? (y/n): "
#define CPU_MSG "CPU mode selected. Would you like to play first? (y/n): "
#define DRAW_MSG "Draw, you gotta do better."
#define CPU_WIN_MSG "Computer wins, that's embarrassing."
#define PLAYER_WIN_MSG "You win! Impressive."
#define O_WIN_MSG "'O' is the winner. Congratulations!" << endl << "'X' \
is a loser, pick up the game."
#define X_WIN_MSG "'X' is the winner. Congratulations!" << endl << "'O' \
is a loser, pick up the game."

#define MINI_VAL -10
#define MAXI_VAL 10

using std::pair;
using std::max;
using std::min;
using namespace std::chrono_literals;


void Game::run ()
{
  _turn = 'O';
  _board.reset_board();
  select_opponent();
}

void Game::select_opponent ()
{
  std::string input;
  cout << OP_MSG << endl;
  cin >> input;
  while (input != "CPU" && input != "cpu" && input != "P2P" && input != "p2p")
  {
    cout << OP_ERR_MSG << endl;
    cin >> input;
  }
  if (input == "cpu" || input == "CPU") { _game_choice = "cpu"; run_cpu_game
        (); }
  if (input == "p2p" || input == "P2P") { _game_choice = "p2p"; run_p2p_game
  (); }
}

void Game::run_p2p_game ()
{
  cout << P2P_MSG << endl << endl;
  while (is_not_over())
  {
    run_p2p_turn ();
  }
  play_again ();
}

void Game::play_again ()
{
  std::string input;
  cout << PLY_AGN_MSG << endl;
  cin >> input;
  while (input != "y" && input != "Y" && input != "n" && input != "N")
  {
    cout << REMATCH_ERR_MSG << endl;
    cin >> input;
  }
  if (input == "y" || input == "Y") { run (); }
  if (input == "n" || input == "N") { cout << END_MSG << endl; return;}
}

void Game::run_p2p_turn ()
{
  if (_turn == 'O')
  {
    cout << O_CHOOSE_MSG << endl;
    pair<int,int> selection = get_turn_selection();
    validate_and_add_input (selection, 'O');
    cout << _board << endl;
    _turn = 'X';
    return;
  }
  cout << X_CHOOSE_MSG << endl;
  pair<int,int> selection = get_turn_selection();
  validate_and_add_input (selection, 'X');
  cout << _board << endl;
  _turn = 'O';
}

void Game::run_cpu_turn ()
{
  if (_turn == _player_side)
  {
    cout << PLAYER_CHOOSE_MSG << endl;
    pair<int,int> selection = get_turn_selection();
    validate_and_add_input (selection, _player_side);
    cout << _board << endl;
    _turn = _cpu_side;
    return;
  }
  cout << CPU_CHOOSE_MSG << endl;
  std::this_thread::sleep_for(1s);
  pair<int,int> selection = find_best_move (_board);
  validate_and_add_input (selection, _cpu_side);
  cout << _board << endl;
  _turn = _player_side;
}

void Game::validate_and_add_input (pair<int, int> &selection, const char side)
{
  while (validate_input (selection.first, selection.second))
  {
    cout << INP_ERR_MSG << endl;
    selection = get_turn_selection ();
  }
  _board.set_val (selection.first, selection.second, side);
}

pair<int,int> Game::get_turn_selection () const
{
  int x, y;
  char tmp;
  cin >> x >> tmp >> y;
  return {x,y};
}

void Game::run_cpu_game ()
{
  std::string input;
  cout << CPU_MSG << endl;
  cin >> input;
  while (input != "y" && input != "Y" && input != "n" && input != "N")
  {
    cout << REMATCH_ERR_MSG << endl;
    cin >> input;
  }
  if (input == "y" || input == "Y")
  {
    _player_side = 'O';
    _cpu_side = 'X';
  }
  if (input == "n" || input == "N")
  {
    _player_side = 'X';
    _cpu_side = 'O';
  }
  while (is_not_over())
  {
    run_cpu_turn ();
  }
  play_again();
}

bool Game::is_not_over ()
{
  if (_board.board_is_full())
  {
    _winner = 'd';
    print_end_game_msg ();
    return false;
  }
  if (win (_board))
  {
    print_end_game_msg ();
    return false;
  }
  return true;
}

void Game::print_end_game_msg ()
{
  if (_game_choice == "cpu")
  {
    if (_winner == _player_side) {cout << PLAYER_WIN_MSG; return;}
    if (_winner == _cpu_side) {cout << CPU_WIN_MSG; return;}
  }
  if (_game_choice == "p2p")
  {
    if (_winner == 'O') {cout << O_WIN_MSG; return;}
    if (_winner == 'X') {cout << X_WIN_MSG; return;}
  }
  if (_winner == 'd') {cout << DRAW_MSG; return;}
}

bool Game::win (const Board& board) // works for all size
// boards
{
  for (int i = 0; i < board.get_dim(); ++i)
  {
    for (int j = 0; j < board.get_dim(); ++j)
    {
      if (board.n_in_a_row (i, j, u)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, d)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, l)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, r)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, ur)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, ul)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, dr)) {_winner = board.get_val (i,j);
        return true;}
      if (board.n_in_a_row (i, j, dl)) {_winner = board.get_val (i,j);
        return true;}
    }
  }
  return false;
}

int Game::evaluate_board (Board& board)
{
  if (board.board_is_full()) {return 0;}
  if (win(board))
  {
    if (_winner == _player_side) {return MINI_VAL;}
    if (_winner == _cpu_side) {return MAXI_VAL;}
  }
  return 0;
}

int Game::minimax (Board& board, int depth, bool is_maxi)
{
  Board tmp_board (_dim);
  tmp_board.get_board() = board.get_board();
  if (tmp_board.board_is_full() || win (board)) { return evaluate_board
  (board); }

  if (is_maxi)
  {
    int best_val = INT16_MIN;
    for (int i = 0; i < _dim; i++)
    {
      for (int j = 0; j < _dim; ++j)
      {
        if (tmp_board.get_val (i, j) == ' ')
        {
          tmp_board.set_val (i, j, _cpu_side);
          int value = minimax (tmp_board, depth + 1, false);
          best_val = max (best_val, value);
          tmp_board.set_val (i, j, ' ');
        }
      }
    }
    return best_val;
  }
  else
  {
    int best_val = INT16_MAX;
    for (int i = 0; i < _dim; i++)
    {
      for (int j = 0; j < _dim; ++j)
      {
        if (tmp_board.get_val (i,j) == ' ')
        {
          tmp_board.set_val (i,j,_player_side);
          int value = minimax (tmp_board, depth + 1, true);
          best_val = min (best_val, value);
          tmp_board.set_val (i, j, ' ');
        }
      }
    }
    return best_val;
  }
}

pair<int,int> Game::find_best_move (Board& board)
{
  int best_val = INT16_MIN;
  pair<int,int> best_move = {-1,-1}, cur_move;
  for (int i = 0; i < _dim; i++)
  {
    for (int j = 0; j < _dim; ++j)
    {
      if (_board.get_val (i, j) == ' ')
      {
        cur_move = {i,j};
        board.set_val (i,j,_cpu_side);
        int move_val = minimax (board,0,false);
        board.set_val (i,j,' ');
        if (move_val > best_val)
        {
          best_move = {i,j};
          best_val = move_val;
        }
      }
    }
  }
  return best_move;
}