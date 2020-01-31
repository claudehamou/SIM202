%-----------------------------------------
%-----------------------------------------
%       SCRIPT VOYAGEUR DU COMMERCE
%-----------------------------------------
%-----------------------------------------

%--------- Sélection des villes ----------
Image = imread('Carte_France.jpg') ;
image(Image) ;

% Récupère les coordonnées des villes
[x y] = ginput ;
close() ;

% Nombre de villes sélectionnées
nbr_villes = length(x) ;
villes = [1:nbr_villes] ;

% Matrice des distances
distance = zeros(nbr_villes,nbr_villes) ;

% Calcul des distances
for ville_1=1:nbr_villes
    
    for ville_2=ville_1:nbr_villes
        
        % Ville retourne sur elle-même
        if ville_1 == ville_2
            distance(ville_1,ville_2) = -1 ;
        else 
            distance(ville_1,ville_2) = sqrt((x(ville_1)-x(ville_2))^2+(y(ville_1)-y(ville_2))^2) ;
            distance(ville_2,ville_1) = distance(ville_1,ville_2) ; 
        end         
    end
end 

% Mettre dans un fichier la matrice des distances
fid = fopen('Matrice_distance.txt','w') ;
% On ajoute le nombre de villes sélectionnées
fprintf(fid, '%d', nbr_villes) ;
fprintf(fid, '\n') ;

% Ecriture du fichier avec le graphe sous forme vecteur colonne
for k=1:nbr_villes
    for i=1:nbr_villes
        fprintf(fid,'%4.3d  ',distance(k,i)) ;
        fprintf(fid,'\n') ;
    end     
end 
fclose(fid) ;

% Lire un fichier pour le chemin optimal
% Format du fichier un espace entre chaque ville
f_chemin = fopen('Chemin.txt','r') ;
chemin = fscanf(f_chemin,'%d',nbr_villes*2) ;
chemin = chemin' ;
  
affiche_chemin(chemin,Image,x,y,nbr_villes) ;
