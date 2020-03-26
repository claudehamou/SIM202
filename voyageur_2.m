% Lire un fichier pour le chemin optimal
% Format du fichier un espace entre chaque ville
f_chemin = fopen('Chemin.txt','r') ;
chemin = fscanf(f_chemin,'%d',nbr_villes*2) ;
chemin = chemin' ;
   
affiche_chemin(chemin,Image,x,y,nbr_villes) ;