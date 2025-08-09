🎯 **Avantages de cette Architecture**

1. **Séparation des Responsabilités**

   - Chaque module a un rôle précis et bien défini
   - Facilite le debug et la maintenance
   - Permet le travail en binôme efficace

2. **Respect des Contraintes**  
   ✅ Une seule variable globale pour les signaux  
   ✅ Pas de structure "norm" globale  
   ✅ Pipeline logique suivant le fonctionnement d'un shell

3. **Modularité**

   - Chaque phase peut être testée indépendamment
   - Facilite l'implémentation progressive
   - Code réutilisable et extensible

4. **Gestion d'Erreurs Centralisée**
   - Chaque module retourne des codes d'erreur clairs
   - Nettoyage de mémoire structuré
   - Propagation d'erreurs cohérente

---

🚀 **Ordre d'Implémentation Recommandé**

- Infrastructure de base (structures, utils)
- Lexer (tokenisation simple puis gestion des quotes)
- Parser (commandes simples puis pipes/redirections)
- Builtins (commandes intégrées)
- Executor (exécution simple puis pipes)
- Expander (variables d'environnement)
- Signaux (gestion des interruptions)
- Tests et robustesse
