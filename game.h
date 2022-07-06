#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include <iostream>

#define WELCOME_MSG "Welcome to TicTacToe"
#define OP_MSG "Please select opponent (CPU,P2P): "
#define DIM_MSG "Please select board size: "

using std::cout;
using std::endl;
using std::cin;
using std::pair;

class Game
{
  Board _board;
  int _dim = DEF_DIM;
  char _turn;
  char _player_side;
  char _cpu_side;
  std::string _game_choice;
  char _winner = 'd';

 public:
  Game ()
  {
    cout << WELCOME_MSG << endl << endl;
//    cout << DIM_MSG << endl;
//    cin >> _dim;
    Board board(_dim);
    _board = board;
  }

  void run ();
  void select_opponent ();
  void run_cpu_game ();
  void run_p2p_game ();
  void run_p2p_turn ();
  pair<int,int> get_turn_selection () const;
  bool win (const Board& board);

  bool validate_input (const int x, const int y) const
  {
    return _board.square_is_not_empty (x,y) || x < 0 || x > _dim - 1 || y <
    0 || y > _dim - 1;
  }

  void validate_and_add_input (pair<int, int> &selection, const char side);

  int minimax (Board& board, int depth, bool is_maxi);
  int evaluate_board (Board &board);
  pair<int, int> find_best_move (Board &board);
  void run_cpu_turn ();
  void print_end_game_msg ();
  bool is_not_over ();
  void play_again ();
};

#endif //_GAME_H_
