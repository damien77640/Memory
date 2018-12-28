/* Programme créé par Félix Legrelle */
/* - */
#include "jeu.h"
#include <graph.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  #define SCREEN_WIDTH 1220
  #define SCREEN_HEIGHT 812

  int x, y; /*recupère les coordonnees de la souris */
  int curseur;

  InitialiserGraphique();
  /*initialisation de la fenetre*/
  CreerFenetre(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  ChoisirTitreFenetre("Memory - Menu"); /* change le nom de la fenetre */
  ChoisirEcran(2);                      /* se place sur l'écran virtuel 2 */
  ChargerImageFond("images/Menu.png"); /* place les images sur l'écran actuel*/
  CopierZone(2, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0,0); /* copie de l'écran 2 vers le 0 le met en haut gauche avec un décalage vers le haut*/

  /* creation du Menu */
  curseur = ChargerSprite("images/Curseur.png"); /* préparation du curseur */

  ChoisirEcran(0);
  while (True) {

    /* initialisation de la souris */
    SourisPosition();
    x = _X;
    y = _Y;

    /* Check des survols de la souris*/
    /*facile*/
    if ((x > 350) && (x < 460) && (y > 290) && (y < 345)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 270, 300);
    }

    /*moyen*/
    else if ((x > 335) && (x < 475) && (y > 390) && (y < 455)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 270, 405);
    }

    /*difficile*/
    else if ((x > 335) && (x < 470) && (y > 495) && (y < 555)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 270, 500);
    }

    /*exit*/
    else if ((x > 255) && (x < 335) && (y > 625) && (y < 670)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 180, 630);
    } else {
      CopierZone(2, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
      ChoisirCurseur(2);
    };

    /*clique souris*/
    if (SourisCliquee()) {
      x = _X;
      y = _Y;

      /*facile*/
      if ((x > 350) && (x < 460) && (y > 290) && (y < 345)) {
        FermerGraphique();
        jeu(1,4,4);
      };

      /*moyen*/
      if ((x > 335) && (x < 475) && (y > 390) && (y < 455)) {
        FermerGraphique();
        jeu(2,6,6);
      };

      /*difficile*/
      if ((x > 335) && (x < 470) && (y > 495) && (y < 555)) {
        FermerGraphique();
        jeu(3,5,10);
      };

      /*exit*/
      if ((x > 255) && (x < 335) && (y > 625) && (y < 670)) {
        FermerGraphique();
        return EXIT_SUCCESS;
      };
    };
  };
}
