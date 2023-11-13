# 42-minishell
sevgi: .h dosyasını temizle

type numaraları
0->string
1->pipe
2-> <
3-> <<
4-> >
5-> >>


Düzenlenecek:
	Parse: 
			❍Girdi boyunca quote içinde olmayan boşluklar görmezden gelinir.
			eğer line'ın sonuna ulaşılırsa token ayrılmaz
			örnek;____________________________________  -> ayırma işlemi yapma
	Parse:
		Whitespace alıyor. Command+Space basınca whitespace atar. Readline ile komut
		alırken arrayin indexlerini gezsin "printf("%d\n", readline.input);" böyle
		baktığında -96 veya -100 gibi değerler görürsün bu whitespace. Parse kısmında
		boşluklarla yaptığın işlemi libft ft_isprint fonksiyonunda eklemen gerek.
	
	Parse:
		Tırnak içinde gelen Pipeların typelarını kontrol etmen gerek. Stringmi yoksa pipe
		mı diye.
	Parse:
		"cat ><" : hata vermeli
	Parse:
		sadece "<", ">" : hata vermeli, Redirection veya pipe sonrası dolu olmalı
