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
% Mettre dans un fichier la matrice des distances ? 
% Lire un fichier pour le chemin optimal
% Retourne le chemin optimal
chemin = [2 5 1 3 4] ;
affiche_chemin(chemin,Image,x,y,nbr_villes) ;


