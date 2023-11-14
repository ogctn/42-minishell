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

Düzenlenecek:
	Parse:
		Whitespace alıyor. Command+Space basınca whitespace atar. Readline ile komut
		alırken arrayin indexlerini gezsin "printf("%d\n", readline.input);" böyle
		baktığında -96 veya -100 gibi değerler görürsün bu whitespace. Parse kısmında
		boşluklarla yaptığın işlemi libft ft_isprint fonksiyonunda eklemen gerek.


redir_out(&data); sadece 0 return ediyor?
builtin çıktılarını aldım execve fonksiyonunu değiştirdim
