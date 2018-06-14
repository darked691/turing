I - Compilation
Ouvrir une fenêtre de commande et se placer dans le dossier projet_simulation_turing
Lancer le makefile avec la commande "make all"
Lancer le programme avec la commande ./simulateur_exe
La commande "clean" permet de nettoyer le dossier des fichiers .o inutiles
La commence "mrproper" nettoie complètement le dossier.

II - Sorties
Une fois le programme fermé, les logs de toutes les exécutions seront placés dans les fichiers log.fig, log.ps et log.tex.

III - Tests
Les fichiers test1.mdt, test2.mdt, test3.mdt peuvent être chargés via l'interface utilisateur afin de tester le programme.
test1.mdt : Remplace le premier 0 rencontré par 1, le mot n'est jamais refusé
(Test permettant de vérifier très simplement le programme)

test2.mdt : Remplace le dernier caractère par 1. Si il n'y'a pas de caractère à remplacer, le mot est refusé. Si le contenu des rubans diffère, le mot est refusé
(Test permettant de vérifier que la machine avec plusieurs rubans fonctionne, et de vérifier que les mots sont bien refusés)

test3.mdt : Écrit "1" sur le second ruban pour chaque "1" du premier ruban. Le mot est refusé si le ruban 2 manque de place.
(Test soulevant l'un des bugs restant : ici, un "1" est ajouté au début de chaque ruban et nous n'avons pas réussi à corriger cela. )

IV - Affichage des sorties
pdflatex et xfig doivent être installés pour lire les sorties machines
Les commandes pour afficher les sorties sont :
-xfig log.fig
-evince log.ps
-pdflatex log.tex : génère un pdf qui peut être ouvert ensuite

V - Utilisation du programme

Pour plus d'informations sur l'utilisation de l'interface, un manuel d'utilisation est mis à votre disposition.
