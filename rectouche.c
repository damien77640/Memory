#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rectouche(void) {

  #define SCREEN_VISIBLE 0
  #define SCREEN_TRICHE 5
  #define SCREEN_SAVE 8

  #define SCREEN_WIDTH 1220
  #define SCREEN_HEIGHT 812

  int touche;
  int poubelle;
  if(ToucheEnAttente()){
    touche= Touche();
    if(touche==XK_t){/* si la touche t est presser save l'ecran actuel */
      CopierZone(SCREEN_VISIBLE, SCREEN_SAVE, 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 40);
      /* place les cartes face visible */
      CopierZone(SCREEN_TRICHE, SCREEN_VISIBLE, 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 40);
      ToucheEnAttente();
      touche= Touche();
      /* nettoyage du tampon du clique */
      while(SourisCliquee()){
        poubelle=_X;
        poubelle=_Y;
      }
      /* verification de la touche */
      while(touche!=XK_t){
        printf("La touche n'est pas prise en charge\n");
        ToucheEnAttente();
        touche= Touche();
      }
      /* reprise de la partie */
      CopierZone(SCREEN_SAVE, SCREEN_VISIBLE, 0, 40, 1220, 812, 0, 40);
    }
    else{/* verification de la touche */
      printf("La touche n'est pas prise en charge\n");
    }
  }
}
