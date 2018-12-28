/* Programme créé par Félix Legrelle */
/* - */

#include "main.h"
#include <graph.h>
#include <stdio.h>
#include <stdlib.h>

int fin(void) {
  int x, y; /*recupère les coordonnees de la souris */
  int curseur;
  InitialiserGraphique();

  /*initialisation de la fenetre*/
  CreerFenetre(0, 0, 1220, 812);
  ChoisirTitreFenetre("Memory - Fin"); /* change le nom de la fenetre */
  ChoisirEcran(2);                      /* se place sur l'écran virtuel 2 */
  ChargerImageFond("images/Fin.png"); /* place les images sur l'écran actuel*/
  CopierZone(2, 0, 0, 0, 1220, 812, 0,
             0); /* copie de l'écran 2 vers le 0 le met en haut gauche avec un
                    décalage vers le haut*/

  /* creation du Menu */
  ChoisirEcran(0); /* se place sur l'écran 0 */

  curseur = ChargerSprite("images/Curseur.png"); /* préparation du curseur */

  while (True) {
    /* initialisation de la souris */
    SourisPosition();
    x = _X;
    y = _Y;

    /* Check des survols de la souris*/
    /*Menu*/
    if ((x > 375) && (x < 500) && (y > 310) && (y < 370)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 300, 315);
    }

    /*Exit*/
    else if ((x > 380) && (x < 480) && (y > 470) && (y < 530)) {
      ChoisirCurseur(1);
      AfficherSprite(curseur, 300, 480);
    }
    else {
      CopierZone(2, 0, 0, 0, 1220, 812, 0, 0);
      ChoisirCurseur(2);
    };

    /*clique souris*/
    if (SourisCliquee()) {
      x = _X;
      y = _Y;

      /*Menu*/
      if ((x > 375) && (x < 500) && (y > 310) && (y < 370)) {
        FermerGraphique();
        main();
      };

      /*Exit*/
      if ((x > 380) && (x < 480) && (y > 470) && (y < 530)) {
        FermerGraphique();
        exit(0);
      };
    };
  };
}
