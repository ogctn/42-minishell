# 42-minishell
sevgi: .h dosyasını temizle

type numaraları
0->string
1->pipe
2-> <
3-> <<
4-> >
5-> >>
6-> ||


add history kontrol et

NOTE(1)
bash-3.2$ lksdf
bash: lksdf: command not found
bash-3.2$ echo $?
127
bash-3.2$ lksdf | ls
bash: lksdf: command not found
Makefile        README.md       inc             leaks.sh        lib             minishell       src
