gcc -ggdb -Wall -Werror -fpic -I . -rdynamic -shared test.c -o libtest.so

gcc -I. main.c -L. -ltest

mcs /t:library test_plat.cs
#mcs /t:library test_oo.cs

mcs /reference:test_plat.dll /t:exe main_plat.cs
#mcs /reference:test_oo.dll /t:exe main_oo.cs
