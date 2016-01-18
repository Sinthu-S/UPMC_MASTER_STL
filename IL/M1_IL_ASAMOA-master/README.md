  
Recap des principales commandes:

recuperer le depot pour la premiere fois (totalité du projet): 
	git clone <une adresse>

recuperer la derniere version du depot:
	git pull

ajouter un fichier (encore jamais versionné): 
	git add  <nom fichier>

mettre a jour les fichiers: 
	git commit -a -m «commentaire » 
	git push

N'oubliez pas d'update votre git pour que l'on ai votre nom ! (voir git --config)


Petites règles : 
- Toujours faire des commits en expliquant (en quelques mots ce que l’on a change)
- On ne modifie jamais du code de quelqu’un (parce qu’on voit un optimissation ou un bug… Globalement, on en parle avant !). 
- On ne push pas de mofification si les tests JUnit ne passent plus.
