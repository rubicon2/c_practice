#include <stdio.h>
#include <stdlib.h>

#define            TRUE    1
#define           FALSE    0
#define       MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

int get_input_lines(char to[MAX_LINES][MAX_LINE_LENGTH], int max_lines, int max_line_length);
void print_lines(char lines[MAX_LINES][MAX_LINE_LENGTH], int print_line_numbers);
int do_str_match(char a[], char b[]);
void copy_line(char to[], char from[]);
void remove_comments(char to[MAX_LINES][MAX_LINE_LENGTH], char from[MAX_LINES][MAX_LINE_LENGTH]);
void remove_blank_lines(char to[MAX_LINES][MAX_LINE_LENGTH], char from[MAX_LINES][MAX_LINE_LENGTH]);

char input_lines[MAX_LINES][MAX_LINE_LENGTH];
char lines_no_comments[MAX_LINES][MAX_LINE_LENGTH];
char lines_no_comments_or_blanks[MAX_LINES][MAX_LINE_LENGTH];

int get_input_lines(char to[MAX_LINES][MAX_LINE_LENGTH], int max_lines, int max_line_length)
{
    int c, col_i, line_i;
    col_i = line_i = 0;
    while ((c = getchar()) != EOF) {
        if (line_i > max_lines) {
            fprintf(stderr, "Error: Too many lines in input. Maximum is 1000 lines.\n");
            exit(1);
        }
        if (col_i > max_line_length) {
            fprintf(stderr, "Error: Too many characters on input line %d. Maximum is 1000 characters per line\n", line_i + 1);
            exit(1);
        }
        to[line_i][col_i] = c;
        ++col_i;
        if (c == '\n') {
            ++line_i;
            col_i = 0;
        }
    }
    // Add EOF to the end of the last line.
    to[line_i][col_i] = EOF;
    // Return the number of lines.
    return line_i;
}

void print_lines(char lines[MAX_LINES][MAX_LINE_LENGTH], int print_line_numbers)
{
    int eof_reached = FALSE;
    for (int row = 0; !eof_reached && row < MAX_LINES; ++row) {
        for (int col = 0; !eof_reached && col < MAX_LINE_LENGTH; ++col) {
            char c = lines[row][col];
            if (c == EOF) {
                eof_reached = TRUE;
            } else {
                // The natural place to put this is in the row loop, but we only want it to
                // print if we actually have at least one non-EOF character on this line.
                if (col == 0 && print_line_numbers == TRUE) printf("%3d: ", row + 1);
                printf("%c", c);
                // If newline reached, break out of inner loop back into row loop.
                if (c == '\n') break;
            }
        }
    }
}

int do_str_match(char a[], char b[])
{
    int c, i;
    i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return FALSE;
        ++i;
    }
    // Make sure the strings end at the same point.
    // The \0 on both strings won't be checked by the loop as that condition is used to exit the loop.
    // if (a[i] != b[i]) return FALSE;
    return TRUE;
}

void remove_comments(char to[MAX_LINES][MAX_LINE_LENGTH], char from[MAX_LINES][MAX_LINE_LENGTH])
{
    int eof_reached = FALSE;
    int in_single_quotes = FALSE;
    int in_double_quotes = FALSE;
    int in_multi_line_comment = FALSE;
    char last_two[2] = { EOF, EOF };

    for (int line = 0; !eof_reached && line < MAX_LINES; ++line) {
        for (int col = 0, to_col = 0, eol_reached = FALSE; !eof_reached && !eol_reached && col < MAX_LINE_LENGTH; ++col) {
            char c = from[line][col];
            last_two[0] = last_two[1];
            last_two[1] = c;
            // Check whether we are in in a string or not - if so, we will treat // and /* */ as a string, not as a comment.
            switch (c) {
                case '"': {
                    if (in_single_quotes == FALSE) {
                        in_double_quotes = !in_double_quotes;
                    } 
                    break;
                }
                case '\'': {
                    if (in_double_quotes == FALSE) {
                        in_single_quotes = !in_single_quotes;
                    } 
                    break;
                }
                case '\n': {
                    if (in_double_quotes == FALSE && in_single_quotes == FALSE) {
                        eol_reached = TRUE;
                        to[line][to_col] = '\n';
                        // Skip the rest of this col loop iteration, and leave the col loop since eol_reached now is TRUE.
                        // Onto the next row!
                        continue;
                    }
                }
                case EOF: {
                    eof_reached = TRUE;
                    // Always add onto the end, regardless of whether we are in a comment or string or whatever.
                    to[line][to_col] = EOF;
                    // Skip the rest of this loop iteration, and leave both the col and row loops since eof_reached now is TRUE.
                    continue;
                }
            }

            // If we are not in a string, check if we have started a comment.
            if (in_double_quotes == FALSE && in_single_quotes == FALSE) {
                if (do_str_match(last_two, "//")) {
                    eol_reached = TRUE;
                    // Overwrite last / written to col and replace with '\n' since the line will end there.
                    to[line][to_col - 1] = '\n';
                    // Skip rest of the col loops and move onto the next line.
                    // As in_single_line_comment is true, it will skip the rest of the col loops for this line and move onto the next row.
                    continue;
                }
                
                if (!in_multi_line_comment && do_str_match(last_two, "/*")) {
                    in_multi_line_comment = TRUE;
                    --to_col;
                }
                
                if (in_multi_line_comment && do_str_match(last_two, "*/")) {
                    in_multi_line_comment = FALSE;
                    // Skip the rest of this col loop so we don't put the / on the line.
                    continue;
                }
            }

            if (in_multi_line_comment == FALSE) {
                to[line][to_col] = c;
                ++to_col;
            }
        }
    }

    // If we are still in a multi line comment after loop is done, the comment was not terminated! Give an error.
    if (in_double_quotes || in_single_quotes) {
        fprintf(stderr, "Error: String not terminated\n");
        exit(1);
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

void remove_blank_lines(char to[MAX_LINES][MAX_LINE_LENGTH], char from[MAX_LINES][MAX_LINE_LENGTH])
{
    for (int line = 0, to_line = 0; line < MAX_LINES; ++line) {
        for (int col = 0; col < MAX_LINE_LENGTH; ++col) {
            char c = from[line][col];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\0') {
                // Copy over and then move onto the next line in from.
                copy_line(to[to_line], from[line]);
                ++to_line;
                break;
            } else if (c == '\n' || c == '\0') {
                break;
            }
        }
    }
}

// Exercise 1.13 - remove all comments from a C program.
int main()
{
    get_input_lines(input_lines, MAX_LINES, MAX_LINE_LENGTH);
    remove_comments(lines_no_comments, input_lines);
    remove_blank_lines(lines_no_comments_or_blanks, lines_no_comments);
    print_lines(lines_no_comments_or_blanks, TRUE);
}
