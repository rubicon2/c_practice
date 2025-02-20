// Exercise 1.24 - Write a rudimentary syntax checker for C code - unbalanced parentheses, brackets, braces.
// Don't forget about quotes, single and double, escape sequences and comments. This program is hard if you do it in full generality. 
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE  100
#define      MAX_LINES 1000
#define  MAX_LINE_SIZE  500
#define           TRUE    1
#define          FALSE    0

struct Stack {
  // Array of void pointers which can point to any data type.
  void* array[MAX_STACK_SIZE];
  // Last index keeps track of the item on top of the stack. It is incremented when something is pushed onto the stack, and decremented when popped off.
  int size;
};
struct Position { int x; int y; };

// Stack methods.
void push(struct Stack* stack, void* ptr);
void* pop(struct Stack* stack);
void free_stack_mem(struct Stack* stack);

// Other methods.
int get_input_lines(char to[MAX_LINES][MAX_LINE_SIZE]);
void print_lines(char from[MAX_LINES][MAX_LINE_SIZE]);
void copy_line(char to[], char from[]);
void add_error(char errors[MAX_LINES][MAX_LINE_SIZE], int* error_count, int line, int col, char message[]);
void add_stack_errors(char errors[MAX_LINES][MAX_LINE_SIZE], int* error_count, struct Stack stack_ptr, char message[]);
int compare_str(char a[], char b[]);

// Program arrays and stacks and whatnot.
struct Position braces_arr[MAX_STACK_SIZE];
struct Stack braces = { .array = &braces_arr, .size = 0 };

struct Position parentheses_arr[MAX_STACK_SIZE];
struct Stack parentheses = { .array = &parentheses_arr, .size = 0 };

struct Position square_brackets_arr[MAX_STACK_SIZE];
struct Stack square_brackets = { .array = &square_brackets_arr, .size = 0 };

struct Position single_quotes_arr[MAX_STACK_SIZE];
struct Stack single_quotes = { .array = &single_quotes_arr, .size = 0 };

struct Position double_quotes_arr[MAX_STACK_SIZE];
struct Stack double_quotes = { .array = &double_quotes_arr, .size = 0 };

char lines[MAX_LINES][MAX_LINE_SIZE];

char errors[MAX_LINES][MAX_LINE_SIZE];
int error_count = 0;

void push(struct Stack* stack_ptr, void* stack_item_ptr)
{
  if (stack_ptr->size >= MAX_STACK_SIZE) {
    fprintf(stderr, "Error: Max stack size exceeded!\n");
    exit(1);
  }
  // Store pointer to new item on the end of the array.
  (*stack_ptr).array[stack_ptr->size] = stack_item_ptr;
  (*stack_ptr).size += 1;
}

void* pop(struct Stack* stack_ptr)
{
  // Give null pointer if stack size is at zero.
  if (stack_ptr->size == 0) return NULL;
  // Otherwise, return the last pointer added to the stack.
  void* stack_item_ptr = (*stack_ptr).array[stack_ptr->size - 1];
  (*stack_ptr).size -= 1;
  return stack_item_ptr;
}

int get_input_lines(char to[MAX_LINES][MAX_LINE_SIZE])
{
  int c, line, col;
  line = col = 0;
  while ((c = getchar()) != EOF && line < MAX_LINES && col < MAX_LINE_SIZE) {
    to[line][col] = c;
    ++col;
    if (c == '\n') {
      to[line][col] = '\0';
      ++line;
      col = 0;
    }
  }

  // As line and col start at zero, the max value is one less than MAX_LINES/MAX_LINE_SIZE.
  if (line >= MAX_LINES - 1) {
    fprintf(stderr, "Error: max input line count exceeded! The maximum is 1000 lines. How is that not enough?\n");
    exit(1);
  }

  // The max is actually 499 - need to leave the final character for EOF.
  if (col >= MAX_LINE_SIZE - 1) {
    fprintf(stderr, "Error: max input line size exceeded! The maximum is 500 characters per line\n");
    exit(1);
  }

  to[line][col] = EOF;
  // Return line count.
  return line;
}

void print_lines(char from[MAX_LINES][MAX_LINE_SIZE])
{
  int c, line, col;
  line = col = 0;
  while ((c = from[line][col]) != EOF && line < MAX_LINES && col < MAX_LINE_SIZE) {
    printf("%c", c);
    ++col;
    if (c == '\n') {
      ++line;
      col = 0;
    }
  }
}

void copy_line(char to[], char from[])
{
  int c, i;
  i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}

void add_error(char errors[MAX_LINES][MAX_LINE_SIZE], int* error_count, int line, int col, char message[])
{
  char error[MAX_LINE_SIZE];
  sprintf(error, "Line %3d, col %3d: %s\n", line, col, message);
  copy_line(errors[*error_count], error);
  ++*error_count;
}

void add_stack_errors(char errors[MAX_LINES][MAX_LINE_SIZE], int* error_count, struct Stack stack, char message[])
{
  for (int i = 0; i < stack.size; ++i) {
    // Get pointer to position struct from array, cast from void* to Position*, then dereference.
    struct Position pos = *(struct Position*)stack.array[i];
    add_error(errors, error_count, pos.y, pos.x, message);
  }
}

int compare_str(char a[], char b[])
{
  int i = 0;
  while (a[i] != '\0' || b[i] != '\0') {
    if (a[i] != b[i]) return FALSE;
    ++i;
  }
  return TRUE;
}

void free_stack_mem(struct Stack* stack_ptr)
{
  void* stack_item_ptr;
  do {
    stack_item_ptr = pop(stack_ptr);
    free(stack_item_ptr);
  } while (stack_item_ptr != NULL);
}

int main(void)
{
  get_input_lines(lines);

  // Go through input lines char by char.
  int eof_reached, in_double_quotes, in_single_quotes, in_multi_line_comment;
  eof_reached = in_double_quotes = in_single_quotes = in_multi_line_comment = FALSE;
  for (int line = 0; !eof_reached && line < MAX_LINES; ++line) {
    char last_two_chars[3] = { EOF, EOF, '\0' };
    for (int col = 0, eol_reached = FALSE; !eol_reached && col < MAX_LINE_SIZE; ++col) {
      char c = lines[line][col];

      // Check for quotes first.
      if (!in_multi_line_comment) {
        switch (c) {
          case '"': {
            if (!in_single_quotes) {
              in_double_quotes = !in_double_quotes;
            }
            continue;
          }
          
          case '\'': {
            if (!in_double_quotes) {
              in_single_quotes = !in_single_quotes;
            }
            continue;
          }
        }
      }

      // Now check if we are starting or ending a comment.
      last_two_chars[0] = last_two_chars[1];
      last_two_chars[1] = c;

      // If we have reached a single line comment, skip the rest of the line.
      if (!in_multi_line_comment && compare_str(last_two_chars, "//")) {
        eol_reached = TRUE;
        continue;
      }

      if (compare_str(last_two_chars, "/*")) {
        in_multi_line_comment = TRUE;
        continue;
      }

      if (compare_str(last_two_chars, "*/")) {
        in_multi_line_comment = FALSE;
        continue;
      }

      // If we are currently in a string or a comment, skip each iteration until we are not!
      if (in_double_quotes || in_single_quotes || in_multi_line_comment) continue;

      // If we are not in a string...
      // Add one to line and col so they start at one instead of zero.
      // This way, the error info will start with "Line 1, Col 1..." instead of "Line 0, Col 0...".
      struct Position pos = { .x = col + 1, .y = line + 1 };
      switch (c) {
        case EOF: {
          // This will satisfy the conditions to end both loops.
          eol_reached = TRUE;
          eof_reached = TRUE;
          continue;
        }

        case '\0': {
          // This will satisfy the col loop, and begin the next iteration of the line loop.
          eol_reached = TRUE;
          break;
        }

        case '\n': {
          // This will satisfy the col loop, and begin the next iteration of the line loop.
          eol_reached = TRUE;
          break;
        }

        case '{': {
          // Playing with fire here bro! Get ready for those segfaults!
          struct Position* pos_ptr = malloc(sizeof(struct Position));
          *pos_ptr = pos;
          push(&braces, pos_ptr);
          break;
        }
        
        case '}': {
          // If pop returns null pointer, there are too many closing braces - it's a syntax error.
          struct Position* closing_pos = (struct Position*)pop(&braces);
          if (closing_pos == NULL) {
            add_error(errors, &error_count, line + 1, col + 1, "unbalanced braces");
          }
          break;
        }

        case '(': {
          struct Position* pos_ptr = malloc(sizeof(struct Position));
          *pos_ptr = pos;
          push(&parentheses, pos_ptr);
          break;
        }

        case ')': {
          struct Position* closing_pos = (struct Position*)pop(&parentheses);
          if (closing_pos == NULL) {
            add_error(errors, &error_count, line + 1, col + 1, "unbalanced parentheses");
          }
          break;
        }

        case '[': {
          struct Position* pos_ptr = malloc(sizeof(struct Position));
          *pos_ptr = pos;
          push(&square_brackets, pos_ptr);
          break;
        }

        case ']': {
          struct Position* closing_pos = (struct Position*)pop(&square_brackets);
          if (closing_pos == NULL) {
            add_error(errors, &error_count, line + 1, col + 1, "unbalanced square brackets");
          }
          break;
        }
      }
    }
  }

  // When an open brace, etc. is encountered (and we're not in a comment or string), add to the braces stack.
  // When a closing brace, etc. is encountered (and we're not in a comment or string), pop from the braces stack.
  // Once all lines have been processed, check if there are any braces, etc. left on their respective stack.
  // If so, a pair of braces, etc. were not terminated. Print the error message with the position of the offending brace, etc.
  add_stack_errors(errors, &error_count, braces, "unbalanced braces");
  add_stack_errors(errors, &error_count, parentheses, "unbalanced parentheses");
  add_stack_errors(errors, &error_count, square_brackets, "unbalanced square brackets");

  if (error_count > 0) {
    printf("%d errors found:\n", error_count);
    print_lines(errors);
  } else {
    printf("No errors found\n");
  }

  // Free memory!
  free_stack_mem(&braces);
  free_stack_mem(&parentheses);
  free_stack_mem(&square_brackets);
}
