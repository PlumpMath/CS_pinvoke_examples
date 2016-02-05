#include <stdio.h>
#include <string.h>

#include <test.h>

static char *User_data1 = "USER_DATA1";
static char *User_data2 = "USER_DATA2";

void cb1(test_struct1_h handle, void *user_data)
{
  int a, b_len;
  char b[100];

  test_handle_get_a(handle, &a);
  test_handle_get_b(handle, b, 100, &b_len);

  printf("cb -> a = %d\n", a);
  printf("cb -> b = \"%s\"\n", b);

  test_handle_set_a(handle, 555);
  test_handle_set_b(handle, "Changed!!!");

  test_handle_get_a(handle, &a);
  test_handle_get_b(handle, b, 100, &b_len);

  printf("cb set -> a = %d\n", a);
  printf("cb set -> b = \"%s\"\n", b);

  if (user_data == User_data1)
  {
    printf("cb -> user_data = %s\n", (char*)user_data);
  }
}

void cb2(int a, int b, int c)
{
  printf("cb2 %d, %d, %d\n", a, b, c);
}

int cb3(test_struct2_h handle, void *user_data)
{
  int i;
  printf("a = %d, b = %d, u.c = %d, u.d = [ ", handle->a, handle->b, handle->u.c);
  for (i=0; i<10; i++)
  {
    printf("%d ", handle->u.d[i]);
  }
  printf("]\n");

  return 123;
}

int main()
{
  struct test_struct_simple ts1;
  ts1.a = 123;
  strcpy(ts1.buf, "Hello World");
  test_pass_struct(&ts1);

  test_handle handle;

  test_create_handle(&handle);

  test_cb1_register(handle, cb1, User_data1);
  
  test_cb2_register(cb2, 123, 456, 789);
  test_cb2_register(cb2, 111, 222, 333);
  test_cb2_register(cb2, 444, 555, 666);

  struct test_struct2 st2;
  st2.a = 123;
  st2.b = 456;
  st2.u.c = 789;

  test_cb3_register(&st2, cb3, User_data2);

  struct test_struct2 st3;
  test_struct2_h handle2 = &st3;
  handle2->a = 123;
  handle2->b = 456;
  handle2->u.d[0] = 1;
  handle2->u.d[1] = 2;
  handle2->u.d[2] = 3;
  handle2->u.d[3] = 4;
  handle2->u.d[4] = 5;
  handle2->u.d[5] = 6;
  handle2->u.d[6] = 7;
  handle2->u.d[7] = 8;
  handle2->u.d[8] = 9;
  handle2->u.d[9] = 10;

  test_cb3_register2(handle2, cb3, User_data2);

  test_cb1_run(handle, 1234, "Ok It's regisitered string");
  test_cb2_run();
  test_cb3_run(&st2);
  test_cb3_run2(handle2);

  test_destroy_handle(handle);

  int x = test_cb4_run(test_cb4_default, "Apple!!");
  printf("test_cb4_run = %d\n", x);

  return 0;
}
