#include "board.h"

ostream& operator << (ostream& os, const Board& board)
{
  for (int i = 0; i < board._dim; ++i)
  {
    for (int j = 0; j < board._dim; ++j)
    {
        (j == 0) ? os << board.get_val (i,j) : os << " | " <<
        board.get_val (i,j);
    }
    os << std::endl;
  }
  return os;
}

bool Board::n_in_a_row (const int x, const int y, direction dir) const
{
  if (get_val (x,y) == ' ') { return false;}
  bool res = true, tmp_res;
  int tmp_x = x, tmp_y = y;
  for (int i = 0; i < DEF_WIN - 1; ++i)
    {
      if (!res) {return res;}
      switch (dir)
      {
        case ul:
          tmp_res = is_equal (tmp_x, tmp_y, ul);
          res = tmp_res && res; tmp_x--; tmp_y--; break;
        case ur:
          tmp_res = is_equal(tmp_x, tmp_y, ur);
          res = tmp_res && res; tmp_x--; tmp_y++; break;
        case dl:
          tmp_res = is_equal(tmp_x, tmp_y, dl);
          res = tmp_res && res; tmp_x++; tmp_y--; break;
        case dr:
          tmp_res = is_equal(tmp_x, tmp_y, dr);
          res = tmp_res && res; tmp_x++; tmp_y++; break;
        case u:
          tmp_res = is_equal(tmp_x, tmp_y, u);
          res = tmp_res && res; tmp_x--; break;
        case d:
          tmp_res = is_equal(tmp_x, tmp_y, d);
          res = tmp_res && res; tmp_x++; break;
        case l:
          tmp_res = is_equal(tmp_x, tmp_y, l);
          res = tmp_res && res; tmp_y--; break;
        case r:
          tmp_res = is_equal(tmp_x, tmp_y, r);
          res = tmp_res && res; tmp_y++; break;
      }
    }
  return res;
}

bool Board::is_adjacent (const int x, const int y, direction dir) const
{
  switch (dir)
  {
    case ul:
      return (x - 1 >= 0 &&  y - 1 >= 0);
    case ur:
      return (x - 1 >= 0 &&  y + 1 < _dim);
    case dl:
      return (x + 1 < _dim && y - 1 >= 0);
    case dr:
      return (x + 1 < _dim &&  y + 1 < _dim);
    case u:
      return (x - 1 >= 0);
    case d:
      return (x + 1 < _dim);
    case l:
      return (y - 1 >= 0);
    case r:
      return (y + 1 < _dim);
  }
  return true;
}

bool Board::is_equal (const int x, const int y, direction dir) const
{
  switch (dir)
  {
    case ul:
      if (is_adjacent (x,y,ul)) {return get_val (x - 1, y - 1) == get_val (x, y);}
      return false;
    case ur:
      if (is_adjacent (x,y,ur)) {return get_val (x - 1, y + 1) == get_val (x, y);}
      return false;
    case dl:
      if (is_adjacent (x,y,dl)) {return get_val (x + 1, y - 1) == get_val (x, y);}
      return false;
    case dr:
      if (is_adjacent (x,y,dr)) {return get_val (x + 1, y + 1) == get_val (x, y);}
      return false;
    case u:
      if (is_adjacent (x,y,u)) {return get_val (x - 1, y) == get_val (x, y);}
      return false;
    case d:
      if (is_adjacent (x,y,d)) {return get_val (x + 1, y) == get_val (x, y);}
      return false;
    case l:
      if (is_adjacent (x,y,l)) {return get_val (x, y - 1) == get_val (x, y);}
      return false;
    case r:
      if (is_adjacent (x,y,r)) {return get_val (x, y + 1) == get_val (x, y);}
      return false;
  }
  return false;
}