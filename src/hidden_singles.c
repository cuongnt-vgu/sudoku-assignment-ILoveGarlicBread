// hidden_singles.c
#include "hidden_singles.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
// putting down obvious comments in case of brain fog
int find_hidden_singles(Cell **p_cells) {
  int counter = 0;
  for (int value = 0; value < BOARD_SIZE; value++) {
    int candidates_count = 0;
    Cell *hidden_single = NULL;
    // check value from 1 to 9 if there are a candidate
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (is_candidate(p_cells[i], value)) { // when found a candidate
        candidates_count++;
        if (p_cells[i]->num_candidates > 1) { // when candidate count>1
          if (hidden_single == NULL) {  // when no hidden_single found so far
            hidden_single = p_cells[i]; // assign current cell
          } else {                // if a potential hidden_single found earlier
            hidden_single = NULL; // reset because duplicate candidate
            break;
          }
        }
      }
    }
    if (hidden_single != NULL) { // if exist hidden single
      hidden_single->value = value;
      unset_candidate(hidden_single, value);
      counter++;
    }
  }
  return counter;
}

int hidden_singles(SudokuBoard *p_board) {
  int hidden_singles_counter = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    // check hidden single in rows
    hidden_singles_counter += find_hidden_singles(p_board->p_rows[i]);
  }
  for (int i = 0; i < BOARD_SIZE; i++) {
    // check hidden single in cols
    hidden_singles_counter += find_hidden_singles(p_board->p_cols[i]);
  }
  for (int i = 0; i < BOARD_SIZE; i++) {
    // check hidden single in boxes
    hidden_singles_counter += find_hidden_singles(p_board->p_boxes[i]);
  }
  return hidden_singles_counter;
}
// Finished, I think, maybe
void print_hidden_singles(SudokuBoard *p_board) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      Cell *current_cell = &(p_board->data[i][j]);
      if (current_cell->num_candidates == 1 && current_cell->value == 0) {
        printf("SINGLE: %c%d set to %d, unique in ", 'A' + i, j + 1,
               get_candidates(current_cell)[0]);

        // Check uniqueness in Row
        bool unique_in_row = true;
        for (int k = 0; k < BOARD_SIZE; k++) {
          if (k != j &&
              current_cell->candidates[get_candidates(current_cell)[0] - 1] ==
                  1) {
            unique_in_row = false;
            break;
          }
        }
        if (unique_in_row)
          printf("Row ");

        // Check uniqueness in Column
        bool unique_in_column = true;
        for (int k = 0; k < BOARD_SIZE; k++) {
          if (k != i &&
              p_board->data[k][j]
                      .candidates[get_candidates(current_cell)[0] - 1] == 1) {
            unique_in_column = false;
            break;
          }
        }
        if (unique_in_column)
          printf("Column ");

        // Check uniqueness in Box
        bool unique_in_box = true;
        int start_row = i - i % 3;
        int start_col = j - j % 3;
        for (int row = start_row; row < start_row + 3; row++) {
          for (int col = start_col; col < start_col + 3; col++) {
            if (row != i && col != j &&
                p_board->data[row][col]
                        .candidates[get_candidates(current_cell)[0] - 1] == 1) {
              unique_in_box = false;
              break;
            }
          }
          if (!unique_in_box)
            break;
        }
        if (unique_in_box)
          printf("Box");

        printf("\n");
      }
    }
  }
}
