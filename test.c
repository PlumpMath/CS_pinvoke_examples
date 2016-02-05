#include <stdio.h>
#include <string.h>

#include <test.h>

struct test_struct
{
  int index;
  int cb_cnt;
  test_cb1 cb[100];
  void *user_data;
};

static struct test_struct handles[100];
static int handle_cnt = 0;

struct test_struct1
{
  int a;
  char str[100];
};

struct test_cb2_struct
{
  test_cb2 cb;
  int a, b, c;
};

static struct test_cb2_struct global_cbs[100];
static int cb2_cnt = 0;

struct test_struct2_container
{
  struct test_struct2 st;
  test_cb3 cb;
  void *user_data;
};

static struct test_struct2_container global_structs2[200];
static int st2_cnt = 0;

void test_pass_struct(struct test_struct_simple *st)
{
  if (st == NULL)
  {
    printf("test_pass_struct : NULL\n");
  }
  else
  {
    printf("test_pass_struct : a = %d, buf = %s\n", st->a, st->buf);
  }
}

void test_create_handle(test_handle *handle)
{
  handles[handle_cnt].index = handle_cnt+1;
  handles[handle_cnt].cb_cnt = 0;
  handles[handle_cnt].user_data = NULL;
  *handle = &handles[handle_cnt++];
}
void test_cb1_register(test_handle handle, test_cb1 cb, void *user_data)
{
  handle->cb[handle->cb_cnt++] = cb;
  handle->user_data = user_data;
}
void test_cb2_register(test_cb2 cb, int a, int b, int c)
{
  global_cbs[cb2_cnt].cb = cb;
  global_cbs[cb2_cnt].a = a;
  global_cbs[cb2_cnt].b = b;
  global_cbs[cb2_cnt].c = c;
  cb2_cnt++;
}
void test_cb3_register(struct test_struct2* obj, test_cb3 cb, void *user_data)
{
  printf("cb3 address : %p\n", obj);
  obj->id = st2_cnt;
  memcpy(&global_structs2[st2_cnt].st, obj, sizeof (struct test_struct2));
  global_structs2[st2_cnt].cb = cb;
  global_structs2[st2_cnt].user_data = user_data;
  st2_cnt++;
}
void test_cb3_register2(test_struct2_h handle, test_cb3 cb, void *user_data)
{
  test_cb3_register(handle, cb, user_data);
}
void test_destroy_handle(test_handle handle)
{
  int index = handle->index-1;
  handles[index].cb_cnt = 0;
  handles[index].user_data = NULL;
}

void test_handle_set_a(test_struct1_h handle, int a)
{
  handle->a = a;
}

void test_handle_set_b(test_struct1_h handle, const char *buf)
{
  int slen = strlen(buf)+1;
  int size = slen > 100 ? 100 : slen;
  strncpy(handle->str, buf, size);
}

void test_handle_get_a(test_struct1_h handle, int* a)
{
  *a = handle->a;
}
void test_handle_get_b(test_struct1_h handle, char *buf, int buf_size, int *copied_size)
{
  int size = buf_size > 100 ? 100 : buf_size;
  strncpy(buf, handle->str, size);
  *copied_size = size;
}
void test_cb1_run(test_handle handle, int a, char *str)
{
  struct test_struct1 tmp;
  int i;
  for (i=0; i<handle->cb_cnt; i++)
  {
    tmp.a = i;
    strcpy(tmp.str, str);
    handle->cb[i](&tmp, handle->user_data);
  }
}
void test_cb2_run()
{
  int i, a, b, c;
  for (i=0; i<cb2_cnt; i++)
  {
    a = global_cbs[i].a;
    b = global_cbs[i].b;
    c = global_cbs[i].c;
    global_cbs[i].cb(a, b, c);
  }
}
void test_cb3_run(struct test_struct2* obj)
{
  int i;
  printf("run cb3 address : %p\n", obj);
  for (i=0; i<200; i++)
  {
    if (global_structs2[i].st.id == obj->id)
    {
      global_structs2[i].cb(&global_structs2[i].st, global_structs2[i].user_data);
      break;
    }
  }
}
void test_cb3_run2(test_struct2_h handle)
{
  test_cb3_run(handle);
}

int test_cb4_default(const char *txt)
{
  printf("test_cb4_default is called with %s\n", txt);
  return txt[0] == 'a' || txt[0] == 'A';
}

int test_cb4_run(test_cb4 cb, const char *txt)
{
  return cb(txt);
}
