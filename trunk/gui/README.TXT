Ceci est un programme permettant de visualiser des arborescences crées par ARF.
Pour compiler, jdom doit se trouver dans le classpath.
Pour fonctionner, il faut avoir créé une arborescence à partir d'une table (voir dans src/table).
Le programme "arf" généré à partir de src/Makefile doit être une commande accessible par l'interface ( -> besoin d'un symlink ou d'integrer le programme au PATH).

Les fichiers générés par arf lors de la création de l'arborescence à partir de la table (arf -i ...table.xml) doivent se trouver au même endroit que le fichier arbo.xml, le plus simple etant de travailler dans le dossier courant.

Il faut ensuite lancer l'interface compilée, et ouvrir l'arborescence, soit directement par la ligne de commande (java ui arbo.xml) soit en passant par le menu ouvrir.