// hidden_singles.h
#pragma once

#include "utils.h"

typedef struct HiddenSingle_impl {
  Cell *p_cell;
  int value;
} HiddenSingle;

int find_hidden_singles(Cell **p_cells);
int hidden_singles(SudokuBoard *p_board);
void print_hidden_singles(SudokuBoard *p_board);
