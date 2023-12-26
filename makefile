default:
	gcc -Wall -Wextra main.c input.c stringutils.c cache.c date.c -o prog.exe

debug:
	gcc -Wall -Wextra -g main.c input.c stringutils.c cache.c date.c -o prog.exe

clean:
	del prog.exe