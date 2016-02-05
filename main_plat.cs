using System;
using System.Text;
using System.Runtime.InteropServices;
using PlatFunctionStyle;

namespace PlatFunctionTest
{
    public class PlatTest
    {
        public static string User_data1 = "USER_DATA1";
        public static string User_data2 = "USER_DATA2";
        public static string User_data3 = "USER_DATA3";

        public static void cb1_(IntPtr handle, IntPtr user_data)
        {
            int a = 0, b_len = 0;
            StringBuilder b = new StringBuilder(100);
            Test.test_handle_get_a(handle, ref a);
            Test.test_handle_get_b(handle, b, b.Capacity, ref b_len);

            Console.WriteLine("cb -> a = {0}", a);
            Console.WriteLine("cb -> b = {0}", b.ToString());

            Test.test_handle_set_a(handle, 555);
            Test.test_handle_set_b(handle, "Changed!!!");

            Test.test_handle_get_a(handle, ref a);
            Test.test_handle_get_b(handle, b, b.Capacity, ref b_len);

            Console.WriteLine("cb set -> a = {0}", a);
            Console.WriteLine("cb set -> b = {0}", b.ToString());

            GCHandle gch = GCHandle.FromIntPtr(user_data);
            string ud_str = (string)gch.Target;
            Console.WriteLine("cb -> user_data = {0}", ud_str);
            gch.Free();
        }

        public static void cb2_(int a, int b, int c)
        {
            Console.WriteLine("cb2 -> {0}, {1}, {2}", a, b, c);
        }

        public static int cb3_1_(ref Test.test_struct2_1 handle, IntPtr user_data)
        {
            Console.WriteLine("a={0}, b={1}, c={2}", handle.a, handle.b, handle.c);

            GCHandle gch = GCHandle.FromIntPtr(user_data);
            string ud_str = (string)gch.Target;
            Console.WriteLine("cb -> user_data = {0}", ud_str);
            gch.Free();

            return 123;
        }
        public static int cb3_2_(ref Test.test_struct2_2 handle, IntPtr user_data)
        {
            Console.Write("a={0}, b={1}, d=[ ", handle.a, handle.b);
            foreach (int n in handle.d)
            {
                Console.Write("{0} ", n);
            }
            Console.WriteLine("]");

            GCHandle gch = GCHandle.FromIntPtr(user_data);
            string ud_str = (string)gch.Target;
            Console.WriteLine("cb -> user_data = {0}", ud_str);
            gch.Free();

            return 123;
        }

        public static void Main(string[] args)
        {
            Test.test_struct_simple st = new Test.test_struct_simple {
                a = 123, buf = "HelloWorld"
            };
            Test.test_pass_struct(st);

            IntPtr handle = IntPtr.Zero;
            Test.test_create_handle(ref handle);

            GCHandle gch = GCHandle.Alloc(User_data1);
            Test.test_cb1_register(handle, cb1_, GCHandle.ToIntPtr(gch));

            Test.test_cb2 cb2 = cb2_;
            Test.test_cb2_register(cb2, 123, 456, 789);
            Test.test_cb2_register(cb2, 111, 222, 333);
            Test.test_cb2_register(cb2, 444, 555, 666);

            GCHandle gch2 = GCHandle.Alloc(User_data2);
            Test.test_struct2_1 st2 = new Test.test_struct2_1 {
                a = 123,
                b = 456,
                c = 789,
            };
            Test.test_cb3_register(ref st2, cb3_1_, GCHandle.ToIntPtr(gch2));

            Test.test_struct2_2 st22 = new Test.test_struct2_2 {
                a = 123,
                b = 456,
                d = new int[] {1,2,3,4,5,6,7,8,9,10},
            };
            Test.test_cb3_register2(ref st22, cb3_2_, GCHandle.ToIntPtr(GCHandle.Alloc(User_data3)));

            Test.test_cb1_run(handle, 1234, "Ok It's regisitered string");
            Test.test_cb2_run();
            Test.test_cb3_run(ref st2);
            Test.test_cb3_run2(ref st22);

            Test.test_destroy_handle(handle);
        }
    }
}
