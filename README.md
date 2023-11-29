![Alfred](https://github.com/leitn/MiniAlfred_shared/assets/104629160/337ddfbe-ab55-425b-bc64-a138bc66ea9d)


### TO DO
* passer toute la correction blanche avec valgrind et le flag track-fds=yes
* gerer toutes les return values des process pour les expandre avec $?
* Verifier les messages d'erreur d'un maximum de cas d'erreurs

### TO FIX
* VALGRIND : unset PATH, puis export PATH=/bin : ls -> invalid read dans init_path (parse_utils4.c ligne 94) + ft_calloc issue in init_utils2.c ligne 66 + conditional jump dans free_utils ligne 72
* exit + pipe : ne doit pas ecrire exit.


### TO BETTER
* NORME : ft_end_size et Ft_print dans echo ont cinq arguments, quatre est le maximum autorise.
* NORME : quelques fonctions depassent les 25 lignes
* PROPRETE 1 : on a des fonctions doublons. Ft_is_eof peut etre remplace par strcmp. Ft_is_builtn et Ft_check_builtn sont doublons.
* PROPRETE 2 : On a des fichierss d'utils presque vides. env.c est-il utile ? ft_error a-t-il besoin d'un fichier juste pour lui ? title_utils peuvent-ils etre vires au vu des undefined behaviors causes par toilet ? On peut faire un prompt en moins de fichiers je pense. ft_write_lst_redir in parse_utils5 peut etre deplacee ?
* PROPRETE 3 : Mettre toutes les fonctions dans le .h, meme quand c'est inutile, pour avoir in inventaire clair
* PROPRETE 4 : commenter toutes les fonctions brievement.

### FIXED

* il se passe quoi si on s'amuse a TOUT unset ? Comme des gros sagouins ? (OK : meme comportement que POSIX)
* le cas de env -i ./minishell : SEGGAULT :'( (FIXED)
* echo || cat : ouch, SEGFAULT (FIXED Helia)
* VALGRIND : ctrl D Heredoc : unadressable bytes in execve in start_exec.c(ligne 108) + invalid read of size 8 in execve (ligne 110) (UPDATE : FIXED Helia)
* > bonjour : SEGFAULT
* > bonjour | cat : execute comme bash --posix
* export + pipe et cd + pipe : added if pid == 0 exit(0);
* ctrl + C dans un prompt vide renvoie un double prompt, dont un en rouge // UPDATE : FIXED (minishell Helia)
* Expand issue on $PATH dans unset (UPDATE : FIXED (Helia))
* unset USER, puis export USER, puis env : core dumped aussi // UPDATE : FIXED (Helia)
* verifier une derniere fois que l'historique ne detruit pas le prompt // UPDATE : FIXED (Helia)
* export BLABLA=pouet, (entree), env : on a un IOT instruction (core dumped) // UPDATE : FIXED (Helia)
* unset PATH puis blabla ou ls : idem, unadressable bytes in execve in start_exec.c (ligne 108) // FIXED (Leila)

### flags valgrind
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp --track-fds=yes -q ./minishell
