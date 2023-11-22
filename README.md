### TO DO

* Expand $? (dans le sujet : "Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.")
* regler les signaux dans les enfants
* gerer les exit status de maniere generale
* echo Hello >> test.txt | wc -l : redirs + pipes ne marchent pas ensembles
* norme (leila)
* et apres ca on est pretes a demander a ce que quelqu'un vienne nous casser notre code

### C'est fait
* Heredocs : C'EST BON ! ON A !
------
Start_exec : tte les fonctions en dessous ft_isbltn sont juste en commentaire pour tester les builtin,
c'est temporaire, tu peux retirer le comm pour reprendre tkt.

Le main : pareil, mais sans commentaire. tu peux retirer tout ce quil y a ds le if (ft_parse()) ss pb.

ft_manage_fds() : a la fin de ft_parse dans parser.c, le parser appelle ft_manage_fd, pour le moment
elle ne fait que tt mettre à 0 et 1 pour le bon fonctionnement des builtins mais je te laisse gérer
tt ce que tu a à gérer, si les builtin on été bien codées (lol), elles fonctionneront avec n'importe quel fd valide.

(../)../include/minishell.h : ds tt les fichiers que j'utilise pr la compile manuel j'ai modifié le path,
parce que le make ignore les dossiers ds sources mais pas le cc manuel en ligne de commande, du
coup faudra remodifier ça aussi, sorry :s

-> questions diverses:
-c'est quoi l'extend vscode pr mettre les headers ? celle pr le nbr de lignes ds une fonction ?
-à l'école on a bien valgrind 2017-2022 ?
-mon bash posix ne met pas à jour PWD si je fais "unset PWD", "cd ..", il est censé ?
