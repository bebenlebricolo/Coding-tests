#include <stdio.h>
#include <assert.h>

typedef struct
{
  int a;
  char b;
} test_struct_t;

void static_break(test_struct_t * const ptr)
{
  static_assert(ptr != NULL, L"ptr parameter cannot be NULL!");
  ptr->a = 26;
  ptr->b = 34;
}

int main(void)
{
  test_struct_t t = {.a = 12, .b = 13};
  static_break(&t);
  test_struct_t * const tbis = NULL;
  static_break(tbis);
  return 0;
}
