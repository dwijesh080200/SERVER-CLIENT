# SERVER-CLIENT
##Execution server-client

> ETAPES

- Cloner le projet

- Pour le serveur, diriger vous vers le dossier server
  ```
  - $cd server
  ```
- Etant dans le dossier server, sur votre terminal, faites un pwd
  ```
  - $pwd
  ```
- le path que vous avez, copier coller le dans le fichier client.c, où on a ecrit:~/SERVER-CLIENT/server
  
- Pour le client, diriger vous vers le dossier client
  ```
  - $cd client
  ```
- Pour compiler le server.c et executer
  ```
  - $gcc server.c -o server
  - $./server
  ```
- Pour compiler le client.c et executer
  ```
  - $gcc client.c -o client
  ```
> Fonctionnalités
- Pour server:
  - `send` : va demander au serveur le nom du fichier a envoyer
  - `list` : va afficher la liste des documents disponible au client
  - `del` : supprime un document du server
  
- Pour client
  - `send` : va envoyer cette commande pour dire d'envoyerun fichier
    - Pour servir de cette commande faites `send nom_du_fichier`
  - `list` : demande une liste de document disponible depuis le server
  - `del` : demande au server a supprimer un document
    - Pour servir de cette commande faites `del nom_du_fichier`
    
> NOTES
- Lancer le fichier server.c avant puis ce du client.c
