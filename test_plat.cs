using System;
using System.Text;
using System.Runtime.InteropServices;

namespace PlatFunctionStyle
{
    public class Test
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void test_cb1(IntPtr handle, IntPtr user_data);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void test_cb2(int a, int b, int c);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int test_cb3_1(ref test_struct2_1 handle, IntPtr user_data);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int test_cb3_2(ref test_struct2_2 handle, IntPtr user_data);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int test_cb4([In, MarshalAs(UnmanagedType.LPStr)]string txt);

        [StructLayout(LayoutKind.Sequential)]
        public struct test_struct_simple
        {
            public int a;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst=128)]
            public string buf;
        }

        [StructLayout(LayoutKind.Sequential, Size=52)]
        public struct test_struct2_1
        {
            public int id;
            public int a;
            public int b;
            public int c;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct test_struct2_2
        {
            public int id;
            public int a;
            public int b;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst=10)]
            public int[] d;
        }

        [DllImport("libtest.so")]
        public extern static void test_pass_struct(test_struct_simple st);

        [DllImport("libtest.so")]
        public extern static void test_create_handle(ref IntPtr handle);

        [DllImport("libtest.so")]
        public extern static void test_cb1_register(IntPtr handle, test_cb1 cb, IntPtr user_data); 

        [DllImport("libtest.so")]
        public extern static void test_cb2_register(test_cb2 cb, int a, int b, int c);

        [DllImport("libtest.so")]
        public extern static void test_cb3_register(ref test_struct2_1 obj, test_cb3_1 cb, IntPtr user_data);
        [DllImport("libtest.so")]
        public extern static void test_cb3_register(ref test_struct2_2 obj, test_cb3_2 cb, IntPtr user_data);

        [DllImport("libtest.so")]
        public extern static void test_cb3_register2(ref test_struct2_1 obj, test_cb3_2 cb, IntPtr user_data);
        [DllImport("libtest.so")]
        public extern static void test_cb3_register2(ref test_struct2_2 obj, test_cb3_2 cb, IntPtr user_data);

        [DllImport("libtest.so")]
        public extern static void test_destroy_handle(IntPtr handle);

        [DllImport("libtest.so")]
        public extern static void test_handle_set_a(IntPtr handle, int a);

        [DllImport("libtest.so")]
        public extern static void test_handle_set_b(IntPtr handle, [MarshalAs(UnmanagedType.LPStr)]string buf);

        [DllImport("libtest.so")]
        public extern static void test_handle_get_a(IntPtr handle, ref int a);

        [DllImport("libtest.so")]
        public extern static void test_handle_get_b(IntPtr handle, StringBuilder b, int buf_size, ref int copied_size);

        [DllImport("libtest.so")]
        public extern static void test_cb1_run(IntPtr handle, int a,
                [MarshalAs(UnmanagedType.LPStr)]string str);

        [DllImport("libtest.so")]
        public extern static void test_cb2_run();

        [DllImport("libtest.so")]
        public extern static void test_cb3_run(ref test_struct2_1 obj);
        [DllImport("libtest.so")]
        public extern static void test_cb3_run(ref test_struct2_2 obj);

        [DllImport("libtest.so")]
        public extern static void test_cb3_run2(ref test_struct2_1 obj);
        [DllImport("libtest.so")]
        public extern static void test_cb3_run2(ref test_struct2_2 obj);

        [DllImport("libtest.so")]
        public extern static int test_cb4_default([In, MarshalAs(UnmanagedType.LPStr)]string txt);

        [DllImport("libtest.so")]
        public extern static int test_cb4_run(test_cb4 cb, [In, MarshalAs(UnmanagedType.LPStr)]string txt);
    } 
}
