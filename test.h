#ifndef __TEST_H__
#define __TEST_H__

struct test_struct_simple
{
  int a;
  char buf[128];
};

struct test_struct2
{
  int id;
  int a;
  int b;
  union {
    int c;
    int d[10];
  } u;
};

typedef struct test_struct* test_handle;
typedef struct test_struct1* test_struct1_h; 
typedef struct test_struct2* test_struct2_h;

typedef void (*test_cb1)(test_struct1_h test_handle, void *user_data);
typedef void (*test_cb2)(int a, int b, int c);
typedef int (*test_cb3)(test_struct2_h test_handle, void *user_data);
typedef int (*test_cb4)(const char *text);

void test_pass_struct(struct test_struct_simple *st);

void test_create_handle(test_handle *handle);
void test_cb1_register(test_handle handle, test_cb1 cb, void *user_data);
void test_cb2_register(test_cb2 cb, int a, int b, int c);
void test_cb3_register(struct test_struct2 *obj, test_cb3 cb, void *user_data);
void test_cb3_register2(test_struct2_h handle, test_cb3 cb, void *user_data);
void test_destroy_handle(test_handle handle);

void test_handle_set_a(test_struct1_h handle, int a);
void test_handle_set_b(test_struct1_h handle, const char *buf);
void test_handle_get_a(test_struct1_h handle, int *a);
void test_handle_get_b(test_struct1_h handle, char *buf, int buf_size, int *copied_size);
void test_cb1_run(test_handle handle, int a, char *str);
void test_cb2_run();
void test_cb3_run(struct test_struct2 *obj);
void test_cb3_run2(test_struct2_h handle);

int test_cb4_default(const char *txt);
int test_cb4_run(test_cb4 cb, const char *txt);

#endif 
