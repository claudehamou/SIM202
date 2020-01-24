function [] = affiche_chemin(chemin, carte, x, y, nbr_villes)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% SYNOPSIS [] = affiche_chemin (chemin, carte ,x, y)
%          
% INPUT * chemin : vecteur contenant les villes � visiter dans l'ordre
%         carte : carte � afficher 
%         x,y : coordonn�es des villes
%         
% OUTPUT Affichage du chemin sur la carte
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Affichage Carte
image(carte) ;
x_new = [];
y_new = [] ;

%Cr�e la liste des coordonn�es dans l'ordre du chemin
 
for k=1:nbr_villes 
    ville = chemin(k) ;
    x_new(k) = x(ville) ;
    y_new(k) = y(ville) ;
end 

hold on ;
plot(x_new,y_new) ;
end 