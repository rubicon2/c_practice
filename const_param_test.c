// This program confirms that the const keyword that can be used in function parameters
// does not have to be passed declared const in the calling function. 
// It just means that the copy local to that function is const.
#include <stdio.h>

int len(const char s[]);
void change_str(char s[]);

int len(const char s[])
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

void change_str(char s[])
{
  int i = 0;
  while (s[i] != 's') {
    s[i] = 'p';
    ++i;
  }
  s[i] = '\0';
}

int main(void)
{
  char s[20] = "My first string";
  int s_len = len(s);
  printf("Original string (%3d):\t%s\n", s_len, s);

  change_str(s);
  s_len = len(s);
  printf("Modified string (%3d):\t%s\n", s_len, s);
}
