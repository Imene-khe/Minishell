# 🚀 Roadmap Minishell (42) – 3 semaines, 4h/jour (en binôme)

## 🧭 Vision globale

Un shell minimal en C, décomposé en 4 phases :

1. **Lexer** – découpage en tokens
2. **Parser** – construire AST ou structure de commande
3. **Expander** – gestion des variables (`$VAR`, `$?`), quotes
4. **Executor** – forks, execve, redirections, pipes, builtins [oai_citation:0‡reddit.com](https://www.reddit.com/r/C_Programming/comments/1fclitu/minishell42/?utm_source=chatgpt.com) [oai_citation:1‡yannick.eu](https://yannick.eu/minishell/?utm_source=chatgpt.com) [oai_citation:2‡m4nnb3ll.medium.com](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218?utm_source=chatgpt.com) [oai_citation:3‡github.com](https://github.com/mcombeau/minishell?utm_source=chatgpt.com) [oai_citation:4‡gitee.com](https://gitee.com/liu2guang/minishell?utm_source=chatgpt.com)

---

## 📅 Semaine 1 — Fondations & Architecture

### 🎯 Objectifs

- Structure du projet + Makefile conforme
- Prompt interactif avec `readline`
- Lexer basique, parsing espace-quote
- Exécution simple (`PATH`, execve)

### ✅ Étapes détaillées

- **Jour 1** : créer arborescence (`src/`, `include/`, `builtin/`, `Makefile` complet)
- **Jour 2** : intégrer `readline()`, `add_history()`, gestion `Ctrl-D`, prompt personnalisé
- **Jour 3-4** : écrire lexer → découpe ligne en tokens, prendre en compte quotes simples/doubles [oai_citation:5‡github.com](https://github.com/hu8813/minishell?utm_source=chatgpt.com)
- **Jour 5-7** : parser minimal → structure `t_cmd` par commande; implémenter `find_path()` et `execve` (chemin relatif/absolu/$PATH)

---

## 📅 Semaine 2 — Redirections, pipes, builtins

### 🎯 Objectifs

- Redirections `<`, `>`, `>>`, `<<`
- Pipes `|`
- Implémentation des built-in standards
- Expansion de variables

### ✅ Étapes détaillées

- **Jour 8** : redirections `<`/`>` via `open()`, `dup2()`, `close()`
- **Jour 9** : gestion de `>>` et `<<` (here-doc non ajouté à l’historique) [oai_citation:6‡github.com](https://github.com/ygor-sena/42cursus-minishell?utm_source=chatgpt.com) [oai_citation:7‡github.com](https://github.com/qingqingqingli/minishell?utm_source=chatgpt.com)
- **Jour 10-11** : pipes : création de pipeline, `fork()` pour chaque commande, `dup2()` pour lier stdin/stdout
- **Jour 12** : builtins dans le shell (`cd`, `export`, `unset`, `exit`) + builtins forkables (`echo`, `pwd`, `env`)
- **Jour 13** : expander d’environnement : `$VAR`, `${VAR}`, `$?`, quotes [oai_citation:8‡github.com](https://github.com/mcombeau/minishell?utm_source=chatgpt.com)

---

## 📅 Semaine 3 — Signaux, robustesse, tests

### 🎯 Objectifs

- Signaux : `Ctrl-C`, `Ctrl-\`, `Ctrl-D`
- Code de sortie `$?`, `exit`
- Gestion mémoire et fuites
- Tests exhaustifs, fiabilisation

### ✅ Étapes détaillées

- **Jour 14-15** : gérer signaux avec `sigaction()` ou `signal()`, única variable globale pour signal reçu [oai_citation:9‡github.com](https://github.com/mcombeau/minishell?utm_source=chatgpt.com) [oai_citation:10‡github.com](https://github.com/qingqingqingli/minishell?utm_source=chatgpt.com) [oai_citation:11‡harm-smits.github.io](https://harm-smits.github.io/42docs/projects/minishell?utm_source=chatgpt.com) [oai_citation:12‡gitee.com](https://gitee.com/liu2guang/minishell?utm_source=chatgpt.com)
- **Jour 16** : `$?` précis, `exit [n]`, propagation des codes via `waitpid()`
- **Jour 17-18** : audit mémoire (Valgrind), correction de fuites internes
- **Jour 19-20** : couvrir tous les edge‑cases (quotes non fermées, fichiers manquants, nom de commande invalide)
- **Jour 21** : tests finaux, mini‑tutoriels, README

---

## 💡 Suggestions & Références

- Architecture inspirée de : lexer → parser → expander → executor [oai_citation:13‡github.com](https://github.com/migmanu/minishell?utm_source=chatgpt.com) [oai_citation:14‡yannick.eu](https://yannick.eu/minishell/?utm_source=chatgpt.com)
- Explorer les solutions suivantes pour design & structure :
  - `mcombeau/minishell` (exécutif complet et stable) [oai_citation:15‡github.com](https://github.com/mcombeau/minishell?utm_source=chatgpt.com)
  - `Uatilla/42Porto_Minishell` a mis en place un AST et une Infra propre [oai_citation:16‡github.com](https://github.com/Uatilla/42Porto_Minishell?utm_source=chatgpt.com)
  - Tutoriels Medium : maniement du shell, parsing avancé [oai_citation:17‡m4nnb3ll.medium.com](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218?utm_source=chatgpt.com)

---

## 📋 Récapitulatif jour par jour

| Jour  | Focus principal                          |
| ----- | ---------------------------------------- |
| 1–2   | Setup projet, Makefile, prompt, readline |
| 3–7   | Lexer + parser + exécution simple        |
| 8–13  | Redirections, pipes, builtins, expansion |
| 14–17 | Signaux, `$?`, exit, fuites mémoire      |
| 18–21 | Robustesse, tests, mise au propre        |

---

## ✅ Suivi en Markdown (à coller dans ton repo)

```markdown
- [x] Jour 1 : structure + Makefile
- [x] Jour 2 : readline + prompt
- [ ] Jour 3 : lexer
- [ ] Jour 4 : parser minimal
      …
- [ ] Jour 21 : tests finaux & README
```
