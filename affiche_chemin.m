function [] = affiche_chemin(chemin, carte, x, y, nbr_villes)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% SYNOPSIS [] = affiche_chemin (chemin, carte ,x, y)
%          
% INPUT * chemin : vecteur contenant les villes à visiter dans l'ordre
%         carte : carte à afficher 
%         x,y : coordonnées des villes
%         
% OUTPUT Affichage du chemin sur la carte
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Affichage Carte
image(carte) ;
x_new = [];
y_new = [] ;

%Crée la liste des coordonnées dans l'ordre du chemin
 
for k=1:nbr_villes 
    ville = chemin(k) ;
    x_new(k) = x(ville) ;
    y_new(k) = y(ville) ;
end 

hold on ;
plot(x_new,y_new) ;
end 