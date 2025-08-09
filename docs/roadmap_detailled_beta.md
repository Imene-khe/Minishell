# Roadmap du projet Minishell

## Lexer

**Objectif :** Analyser la ligne de commande brute et la découper en tokens élémentaires (mots, arguments, opérateurs comme |, <, >, etc.). Chaque token est stocké dans une liste chaînée avec son type (CMD, PIPE, REDIR, ARG, …).

**Notions théoriques :** Le lexer effectue une analyse lexicale : il parcourt la chaîne caractère par caractère pour identifier les lexèmes. Il doit gérer les guillemets : tout texte entre quotes simples est pris littéralement, sans expansion (même si on voit des | ou > dedans), et entre quotes doubles on autorise l'expansion de variables ($VAR) mais pas l'interprétation des pipes ou redirections. Par exemple, echo "cat | ls" lol produit deux tokens (le deuxième contenant la chaîne entière "cat | ls"). On doit aussi reconnaître les redirections (<, >, >>, <<) et les tubes | en tokens spécifiques.

**Travail en binôme :** Commencez en pair programming pour concevoir ensemble la structure t_token (chaînage, champs) et l'algorithme de base de tokenisation. Par exemple, au début, travaillez à deux sur la boucle principale du lexer (gestion des espaces, accumulation d'un mot). Ensuite, branchez-vous deux : l'un·e peut se concentrer sur les cas particuliers (gestion fine des quotes et caractères spéciaux), l'autre sur la détection des opérateurs et la création de tokens basiques (mots et symboles). Une fois chacun son implémentation prête, exposez-vous mutuellement votre code puis fusionnez les branches.

**Étapes pratiques :**

1. Vérifier d'abord qu'il n'y a pas de quotes non fermées dans la ligne (sinon afficher une erreur).
2. Parcourir la chaîne de caractères :
   - Ignorer les espaces entre tokens.
   - Si on rencontre ' ou ", capter tous les caractères jusqu'à la quote fermante correspondante en créant un token unique (en incluant les quotes dans la chaîne du token si désiré).
   - Si on rencontre <, >, >>, << ou |, créer un token de redirection ou de pipe de type correspondant.
   - Sinon, accumuler les caractères dans un token de type mot/ARG jusqu'au prochain séparateur (espace ou opérateur).
3. Ajouter chaque token créé à la liste chaînée. À la fin, vérifier que le dernier token n'est pas un pipe (sinon erreur).
4. Retourner la liste de tokens.

**Tests / Validation :** Testez le lexer sur des lignes simples puis complexes :

- Commandes simples (ls, echo foo), commandes avec redirections (echo hi > out.txt), et pipelines sans espaces (cat|wc).
- Cas de quotes : echo "une | phrase", echo '$HOME' (les $ doivent être préservés), echo "mix''te" etc.
- Erreurs attendues : guillemets non fermées, pipe en fin de ligne. Vérifiez que chaque token a bien le type attendu (CMD, PIPE, INPUT, APPEND, ARG…).

## Parser

**Objectif :** Construire une représentation des commandes à exécuter à partir de la liste de tokens. Typiquement, on crée une liste chaînée de structures t_cmd, une par commande (séparée par des pipes). Chaque t_cmd contient les file descriptors d'entrée/sortie ainsi que le tableau d'arguments (argv) pour execve(). Les redirections sont traitées ici : si un token de redirection est trouvé, on ouvre le fichier suivant et on affecte le fd correspondant au t_cmd.

**Notions théoriques :** C'est l'étape d'analyse syntaxique (parsing). Plutôt qu'un AST complet, on utilise une structure t_cmd simplifiée. Par exemple, pour echo a | grep b > out, on aura deux t_cmd en liste : le premier aura argv ["echo","a"], le second ["grep","b"], avec le second t_cmd enregistrant outfile="out". Un pipe | indique la fin d'un t_cmd et le début du suivant.

**Travail en binôme :** Commencez à deux pour définir la structure t_cmd (champs et chaîne) et le parcours logique des tokens. Puis séparez-vous : un·e peut implémenter la découpe de la liste de tokens en commandes (créer un nouveau t_cmd à chaque pipe) et construire l'array argv à partir des tokens CMD/ARG, tandis que l'autre gère l'affectation des fichiers de redirection (infile/outfile) et l'ouverture (open()) correspondante. Après codage, comparez et fusionnez.

**Étapes pratiques :**

1. Parcourir la liste de tokens. À chaque pipe ou au début, allouer un nouveau t_cmd (initialiser ses champs).
2. Pour chaque t_cmd, collecter les tokens de type CMD ou ARG jusqu'au prochain pipe. Placer leur chaîne dans un tableau argv[] (terminé par NULL).
3. Traiter les redirections : si un token est INPUT (<), OUTPUT (>), APPEND ou HEREDOC, son token suivant est un nom de fichier. Ouvrir ce fichier (open()) en mode approprié et stocker le FD dans t_cmd->infile ou outfile.
4. Lier les t_cmd entre eux (liste chaînée). Fermer les fds inutiles ou traiter les erreurs d'ouverture.
5. Vérifier qu'on n'a pas de token inattendu (pipe final, syntaxe incorrecte).

**Tests / Validation :**

- Vérifiez la liste résultante pour echo x, ls | wc, cat < in.txt | sort > out.txt : nombre de t_cmd correct, chaque argv et redirection corrects.
- Simuler des entrées aberrantes : chaîne vide, | en début/fin, >> sans nom de fichier.
- Contrôler qu'il n'y a pas de fuite mémoire (tous les tokens doivent être libérés correctement après usage).

## Expander

**Objectif :** Gérer l'expansion des variables d'environnement et des codes spéciaux après le parsing. Par exemple, remplacer $VARNAME par sa valeur dans l'environnement, et $? par le code de retour de la dernière commande. Les expansions respectent les quotes (pas d'expansion dans les simples quotes).

**Notions théoriques :** La substitution shell : tout motif commençant par $ suivi d'un nom est substitué par la valeur d'une variable d'environnement (comme $HOME, $PATH, etc.) ou par $?. Attention, dans une chaîne entre quotes simples ('…'), on ne fait aucune substitution. En revanche, entre doubles quotes, on remplace $VAR par la valeur, et "$HOME" se comporte comme $HOME, tandis que '$HOME' reste littéral.

**Travail en binôme :** Au début du bloc Expander, travaillez ensemble pour énumérer les cas (variables simples, $?, variables non définies, quotes). Ensuite séparez-vous : un·e peut implémenter la recherche et le remplacement des $VARNAME dans les tokens (avec getenv()), l'autre la gestion de $? et les cas particuliers.

**Étapes pratiques :**

1. Pour chaque token de type ARG (ou CMD s'il contient $), parcourir sa chaîne à la recherche de $.
2. Si $? est trouvé, remplacer par la valeur string du code de retour (int) de la dernière commande.
3. Sinon extraire le nom de variable (lettres, chiffres, underscore) après $, récupérer sa valeur depuis l'environnement (getenv()) et remplacer $NOM par cette valeur (ou chaîne vide si indéfini).
4. Gérer correctement les quotes : ne pas toucher aux $ situés dans des segments en quotes simples.
5. Mettre à jour le token avec la nouvelle chaîne.

**Tests / Validation :**

- Définissez des variables d'environnement (avec export) et testez echo $HOME, echo "$HOME", echo '$HOME'. Les résultats doivent correspondre aux règles ci-dessus.
- Exécutez une commande qui définit un code de sortie (par ex. false) puis echo $? pour vérifier la substitution.
- Vérifiez que les variables non définies disparaissent (echo $UNDEF donne rien).

## Executor

**Objectif :** Exécuter les commandes issues du parsing : créer les processus, câbler les pipes et redirections, et lancer les exécutables ou builtins. Pour chaque t_cmd de la liste, on devra faire un fork() ; dans l'enfant, on prépare les dup2() pour les entrées/sorties, puis on appelle execve() pour les commandes externes. Les commandes internes (builtins) sont exécutées dans le shell.

**Notions théoriques :** Les concepts clés sont le fork, la gestion des descripteurs et l'appel execve(). Chaque commande externe est exécutée via execve(path, argv, envp), où path est le chemin du binaire (à chercher dans PATH), argv est le tableau d'arguments (argv[0] est le nom de la commande), et envp le tableau des variables d'environnement. Si on a modifié l'environnement (export/unset), il faut passer un envp correspondant (recréé à partir de la liste actuelle). Les tubes (pipe()) et dup2() relient la sortie d'un processus à l'entrée du suivant selon les t_cmd.

**Travail en binôme :** Commencez ensemble : discutez de l'algorithme de création de fork et de pipes. Ensuite, un·e développe la boucle de création de processus (gestion de fork(), pipe() et dup2() pour les entrées/sorties) pendant que l'autre implémente l'appel à execve() et la gestion des builtins dans les enfants ou dans le parent. Reprenez le schéma proposé par Hqndler : chaque commande prend ses paramètres et l'environnement.

**Étapes pratiques :**

1. Créer les pipes nécessaires (si plusieurs t_cmd) avant les fork().
2. Pour chaque t_cmd : fork() un nouveau processus. Dans l'enfant :
   - Si ce n'est pas la première commande, dup2(pipe_in, STDIN_FILENO). Si ce n'est pas la dernière, dup2(pipe_out, STDOUT_FILENO).
   - Pour chaque redirection de t_cmd, ouvrir le fichier (open()) et dup2() pour STDIN ou STDOUT. Fermer les fds inutiles.
   - Si la commande est un builtin (cd, echo, etc.), l'exécuter directement (sans execve). Sinon, appeler execve() avec les paramètres (PATH, args, env).
3. Dans le parent : fermer les bouts de pipes non utilisés et attendre (wait()) les enfants. Propager le code de retour du dernier processus.
4. Gérer les codes de sortie : par convention SIGINT (ctrl+C) donne 130, SIGQUIT 131.

**Tests / Validation :**

- Testez des commandes simples (/bin/ls, echo foo) et pipelines (ls | wc). Assurez-vous que la sortie est correcte et que les processus enfants se terminent.
- Vérifiez les redirections : echo hi > out && cat out, cat < fichier.
- Assurez-vous que les builtins fonctionnent dans la séquence (par ex. echo hi | cd /tmp doit changer de répertoire dans le shell principal pour être visible après).
- Validez les codes de retour (echo $?). Utilisez bash --posix pour comparer les comportements.

## Builtins

**Objectif :** Réaliser les commandes internes du shell (sans appel à execve) : echo, cd, pwd, export, unset, env, exit (et éventuellement unset, exit). Ces commandes modifient le shell lui-même (dossier courant ou environnement) et doivent renvoyer le bon code de sortie.

**Notions théoriques :** Chaque builtin a des règles spécifiques :

- echo affiche ses arguments, interprète l'option -n (pas de saut de ligne).
- cd change de dossier (chdir) et met à jour les variables PWD et OLDPWD.
- pwd affiche le répertoire courant (sans arguments).
- env affiche la liste des variables d'environnement avec une valeur.
- export sans argument affiche l'env (trié lexicographiquement) ; avec NAME=VAL il ajoute/mets à jour la variable.
- unset supprime des variables d'environnement.
- exit termine le shell avec un code (par défaut 0 ou celui fourni). Les codes de retour (via $?) sont importants.

Ces comportements doivent correspondre à Bash (voir manuel POSIX).

**Travail en binôme :** Répartissez-vous les builtins. Par exemple, une personne implémente echo, exit et pwd, l'autre fait cd, env, export et unset. Collaborez particulièrement sur export/unset car ils touchent à la même structure d'environnement. Avant de coder, testez ensemble chaque builtin dans Bash pour bien comprendre les subtilités (options -n, comportements de export avec/puis sans argument, etc.).

**Étapes pratiques :**

1. Dans le code principal, détecter si la commande est un builtin. Si oui, appeler la fonction correspondante sans forker (sauf exit qui quitte le shell).
2. Implémenter chaque builtin :
   - echo : parcourir argv[], ignorer -n et afficher les args séparés par des espaces, terminer par ou sans \n selon -n.
   - cd : utiliser chdir(path). Mettre à jour OLDPWD=PWD puis PWD=getcwd() ou utiliser getcwd. Gérer cd - (revenir en OLDPWD).
   - pwd : printf("%s\n", getcwd(NULL,0)).
   - export : si aucun arg, lister les variables (ft_sort, puis print declare -x VAR="VAL"). Sinon pour chaque KEY=VAL, ajouter/modifier la table d'environnement. Interdire les noms invalides.
   - unset : pour chaque nom, supprimer de la table d'environnement.
   - env : lister toutes les variables key=val.
   - exit : convertir l'argument en int et exit(code).
3. Mettre à jour le code de retour du shell (g_last_status = ...).

**Tests / Validation :**

- Vérifiez le comportement exact de chaque builtin (par ex. echo -n a -n affiche quoi, export sans args trie les variables, cd ~, cd -, codes d'erreur pour les mauvais paramètres).
- Après chaque builtin, vérifiez $? : exit 5 doit renvoyer 5, false -> 1, etc.
- Testez des cas limites : unset d'une variable inexistante (pas d'erreur), export=non (commande inconnue), etc.
- Assurez-vous que l'env interne du shell est bien mise à jour (et utilisée lors des execve suivants).

## Signaux

**Objectif :** Gérer proprement les signaux utilisateur pour que le shell réagisse comme Bash. Au minimum, capturer SIGINT (Ctrl-C), SIGQUIT (Ctrl-\) et l'EOF (Ctrl-D). Par exemple, Ctrl-C doit interrompre la commande en cours (ou effacer la ligne) et afficher un nouveau prompt. Ctrl-\ envoie SIGQUIT (core dump dans un programme bloqué, sinon rien au prompt). Ctrl-D sur une ligne vide doit sortir du shell.

**Notions théoriques :** Utiliser signal() ou sigaction() pour redéfinir le comportement par défaut. En mode prompt, un SIGINT doit afficher simplement un nouveau prompt (et code 130). En mode exécution d'une commande (dans l'enfant), laisser la commande réagir au signal (par exemple, quitter avec code 130). Ctrl-\ affiche généralement "Quit" et code 131 dans un processus bloqué (par ex. sleep). Ctrl-D (EOF) en lecture doit détecter readline renvoyant NULL et quitter le shell.

**Travail en binôme :** Ensemble, implémentez les handlers : par exemple, un pointeur de signal pour SIGINT qui écrit ^C et remet un prompt, et un autre pour SIGQUIT. Puis, confiez à chacun un cas de test : pendant qu'un·e fait intervenir le handler dans l'invite, l'autre teste les interruptions dans des commandes bloquantes (cat, sleep).

**Étapes pratiques :**

1. Dans le main, avant la boucle, rediriger SIGINT vers un handler qui affiche un prompt vide (\nminishell> ) et remet le statut à 1. Rediriger SIGQUIT vers un handler qui ignore ou affiche un message minime.
2. Dans les processus enfants, rétablir le comportement par défaut (ou gérer différemment). Par exemple, pour les heredocs, on peut gérer Ctrl-C pour interrompre la saisie (asynchrone).
3. Gérer Ctrl-D : si readline() renvoie NULL, quitter proprement (exit(g_last_status)).
4. Toujours réafficher un prompt après gestion de signal dans le shell.

**Tests / Validation :**

- À l'invite vide, tapez Ctrl-C : un prompt doit réapparaître (aucun caractère restant). Vérifiez que le code de retour global est 130.
- Lancez sleep 5 et pressez Ctrl-C : sleep devrait s'interrompre et le shell reprendre.
- Lancez sleep 5 et pressez Ctrl-\ : sleep doit s'arrêter (core dump) et le shell reprendre avec code 131.
- Testez Ctrl-D sur une invite vide : le shell doit se terminer (comme exit). Sur une entrée dans cat par exemple, Ctrl-D envoie EOF à cat.

## Tests / Robustesse

**Objectif :** Vérifier l'exactitude et la stabilité du programme après chaque étape. Tester à la fois les cas normaux et limites (segfault, fuites mémoire, mauvaises entrées). Utiliser systématiquement bash --posix pour comparer le comportement (le standard POSIX définit le comportement attendu).

**Notions théoriques :** Un code robuste ne doit pas planter (segfault) et doit gérer toutes les entrées légales (et renvoyer une erreur propre pour les entrées illégales). Il faut également que toutes les fuites mémoire soient identifiées (valgrind).

**Travail en binôme :** Chacun écrit et exécute des tests pour ses parties respectives, puis échange les tests. Par exemple, quand l'un·e termine le lexer, l'autre valide indépendamment plusieurs entrées pour trouver les bugs. Utilisez un dépôt de tests partagé : importer des cas de test existants (par ex. la liste de 800 cas librement diffusée) et ajoutez-les à votre suite.

**Étapes pratiques :**

- Créez un script global (run_tests.sh) qui exécute automatiquement des cas : pour chaque commande test, comparez la sortie de votre shell et celle de bash --posix.
- Intégrez des tests unitaires si possible : par exemple, dans votre code C, isolez des fonctions (lexer, parser) et écrivez de petits programmes de test qui valident leur comportement avec différents inputs.
- Surveillez les ressources : lancez régulièrement valgrind --leak-check=full sur votre binaire pour éliminer toutes les fuites.
- Revérifiez les cas limites : entrées vides, très longues, usage intense de quotes ou de redirections successives.

**Conseils :** Profitez des batteries de tests publiques (doc mentionnée ou dépôts GitHub) pour compléter les vôtres. Toujours tester en mode --posix pour éviter les divergences dues à des particularités de configuration. En cas d'échec lors d'une correction, corrigez tout avant de réessayer (les correcteurs appliquent souvent de nombreux tests aléatoires).

## 🔬 Infrastructure de test

Pour automatiser la vérification, mettez en place votre propre framework minimal :

- **Scripts de test Bash :** Écrivez un script (test.sh, run_tests.sh, etc.) qui exécute votre minishell avec différentes entrées (via printf "cmd\n" | ./minishell ou des heredoc). Comparez la sortie standard et le code retour avec ceux de bash sur les mêmes commandes. Regroupez ces commandes dans des fichiers ou tableaux.
- **Fichiers de test :** Organisez vos cas de test dans des fichiers texte (un test par ligne, ou groupe tests simples et tests d'erreur). Vous pouvez utiliser des outils comme diff ou cmp pour valider automatiquement les résultats.
- **Tests unitaires C :** Si autorisé, créez de petites fonctions main() de test pour vos composants (lexer, parser, expansion) : par exemple, appeler la fonction de tokenisation sur une entrée connue et vérifier que la liste de tokens a la bonne forme (en imprimant un bilan PASS/FAIL). Des frameworks comme Criterion/Unity peuvent aider si 42 les autorise.
- **Intégration continue locale :** Ajoutez des targets Makefile, par ex. make test, qui compile et lance tous vos scripts de test à chaque modification. Intégrez aussi des vérifications avec valgrind pour chaque exécution.
- **Ressources externes :** Utilisez les suites publiques (ex. dépôt de tests 42) comme base, mais complétez avec vos propres cas. N'hésitez pas à étendre les tests après chaque nouvelle fonctionnalité pour éviter la régression.
