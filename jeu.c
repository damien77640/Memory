#include "rectouche.h"
#include "fin.h"
#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


/*____________________________Initialisation_fonction________________________*/

int jeu(int difficulte,int nb_ligne,int nb_colonne) {
  InitialiserGraphique();

  #define NB_CARTE_TOTAL nb_ligne*nb_colonne
  #define NB_PAIR NB_CARTE_TOTAL/2
  #define SCREEN_WIDTH 1220
  #define SCREEN_HEIGHT 812
  #define SCREEN_VISIBLE 0
  #define SCREEN_FOND 2
  #define SCREEN_TRICHE 5
  #define SCREEN_SAVE 8
  #define CURS_SOURIS 2
  #define TAILLE_IMG 43

  int posx_carte_une;
  int posy_carte_une;
  int espace_carte_x;
  int espace_carte_y;
  int x_haut_exit;
  int y_haut_exit;
  int x_bas_exit;
  int y_bas_exit;


  if (difficulte==1){
    posx_carte_une=480;
    posy_carte_une=240;
    espace_carte_x=55;
    espace_carte_y=60;
    x_haut_exit=565;
    y_haut_exit=557;
    x_bas_exit=600;
    y_bas_exit=590;
  }
  else if (difficulte==2){
    posx_carte_une=430;
    posy_carte_une=140;
    espace_carte_x=63;
    espace_carte_y=63;
    x_haut_exit=595;
    y_haut_exit=680;
    x_bas_exit=630;
    y_bas_exit=712;
  }
  else if (difficulte==3){
    posx_carte_une=345;
    posy_carte_une=220;
    espace_carte_x=54;
    espace_carte_y=55;
    x_haut_exit=600;
    y_haut_exit=505;
    x_bas_exit=625;
    y_bas_exit=530;
  }
  else{
    printf("difficulte : %d n'existe pas merci de bien remplir la fonction jeu\n",difficulte);
    return EXIT_FAILURE;
  }
  int ligne_actu=0,colonne_actu=0;
  int n_carte=0,n_ligne=0;
  int ligne_img=0,colonne_img=0;
  int nb_paire_trouve=0;
  char image[NB_PAIR];

/*1________________________initialisation_du_tableau_________________________*/
  srand(time(NULL));
  int valeur = 0, random_ligne, random_colonne, temp1, temp2;
  int tab[nb_ligne][nb_colonne];
  /* Parcour le tableau */
  for (ligne_img = 0; ligne_img < nb_ligne; ligne_img += 1) {
    for (colonne_img = 0; colonne_img < nb_colonne; colonne_img += 1) {
      /* met dans 2 cases a la suite la meme valeur  */
      tab[ligne_img][colonne_img] = valeur;
      valeur += 1;
      if (valeur > ((nb_ligne * nb_colonne) / 2) - 1) {
        valeur = 0;
      }
    }
  }

/*2__________________________repartition_aleatoire___________________________*/

  for (ligne_img = 0; ligne_img < nb_ligne; ligne_img += 1) {
    for (colonne_img = 0; colonne_img < nb_colonne; colonne_img += 1) {
      /* echange la valeur de 2 cases aleatoire de facon aleatoire */
      random_ligne = ligne_img + rand() % (nb_ligne - ligne_img);
      temp1 = tab[ligne_img][colonne_img];
      tab[ligne_img][colonne_img] = tab[random_ligne][colonne_img];
      tab[random_ligne][colonne_img] = temp1;

      random_colonne = colonne_img + rand() % (nb_colonne - colonne_img);
      temp2 = tab[ligne_img][colonne_img];
      tab[ligne_img][colonne_img] = tab[ligne_img][random_colonne];
      tab[ligne_img][random_colonne] = temp2;
    }
  }


/*3____________________________creation_fenetre______________________________*/

  CreerFenetre(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (difficulte==1){
    ChoisirTitreFenetre("Memory - Facile");
    ChoisirEcran(SCREEN_FOND);
    ChargerImageFond("images/Facile.png");
  }
  else if (difficulte==2){
    ChoisirTitreFenetre("Memory - Moyen");
    ChoisirEcran(SCREEN_FOND);
    ChargerImageFond("images/Moyen.png");
  }
  else if (difficulte==3){
    ChoisirTitreFenetre("Memory - Difficile");
    ChoisirEcran(SCREEN_FOND);
    ChargerImageFond("images/Difficile.png");
  }
  CopierZone(SCREEN_FOND, SCREEN_VISIBLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  ChoisirEcran(SCREEN_VISIBLE);
  ChoisirCurseur(CURS_SOURIS);


/*4__________________________placement_dos_carte_____________________________*/

  for (n_carte = 0; n_carte < NB_CARTE_TOTAL; n_carte += 1) { /* fait une boucle en fonction du nombre de carte total */
    /* affiche les dos de cartes une par une tout en la décalant */
    ChargerImage("images/Logos/dos_carte.png", posx_carte_une + (colonne_actu * espace_carte_x),posy_carte_une + (espace_carte_y * n_ligne), 0, 0, TAILLE_IMG, TAILLE_IMG);
    usleep(30000);
    ligne_actu += 1, colonne_actu += 1;
    /* quand c'est arriver a la fin de colonne se remet au debut de la prochaine ligne */
    if ((ligne_actu >= nb_ligne) && (colonne_actu >= nb_colonne)) {
      ligne_actu = 0, colonne_actu = 0;
      n_ligne += 1;
    }
  }


/*5_____________________initialisation_tableau_triche________________________*/

  ChoisirEcran(SCREEN_TRICHE);
  if (difficulte==1){
    ChargerImageFond("images/Facile.png");
  }
  else if (difficulte==2){
    ChargerImageFond("images/Moyen.png");
  }
  else if (difficulte==3){
    ChargerImageFond("images/Difficile.png");
  }
  ligne_actu = 0;
  n_ligne=0;
  colonne_actu = 0;
  /* reviens au début du tableau et le re parcours */
  for (ligne_img = 0; ligne_img < nb_ligne; ligne_img+= 1) {
    for (colonne_img = 0; colonne_img < nb_colonne; colonne_img += 1) {
      /* quand c'est arriver a la fin de colonne se remet au debut de la prochaine ligne */
      if ((ligne_actu >= nb_ligne) && (colonne_actu >= nb_colonne)) {
        ligne_actu = 0, colonne_actu = 0;
        n_ligne += 1;
      }
      colonne_actu += 1;
      ligne_actu += 1;
      /* remplit un tableau de charactere avec l'image qui correspont a la valeur du tableau */
      sprintf(image,"images/Logos/img-%d.png",tab[ligne_img][colonne_img]);
      /*affiche les images sur un autre ecran */
      ChargerImage(image,(posx_carte_une-espace_carte_x) + (colonne_actu * espace_carte_x), posy_carte_une + (espace_carte_y * n_ligne),0,0,TAILLE_IMG,TAILLE_IMG);
    }
  }
  CopierZone(SCREEN_VISIBLE, SCREEN_SAVE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0,0);
  ChoisirEcran(SCREEN_VISIBLE);


/*6___________________________reception_du_clique____________________________*/
#define CYCLE 1000000L
int seconde=0;
unsigned long suivant=0;
char timer[100];
  while(True){
    int x, y;
    int coup = 0;
    int premier_clic_img = -10,deuxieme_clic_img = -10;
    int premier_clic_imgx = -1, premier_clic_imgy = -1, deuxieme_clic_imgx = 0, deuxieme_clic_imgy = 0;

    while(coup != 2){   /* Tant que coup n'est pas egale à 1 le joueur choisit une carte */
      rectouche(); /*fonction de la triche */
/*7___________________________Initialisation_du_temps________________________*/
      if ( Microsecondes() > suivant){ /* permet de ne pas avoir trop de rafréchissement */
        suivant = Microsecondes() + CYCLE;
        seconde +=1;
        sprintf(timer,"Time : %6d s",seconde);
        CopierZone(8, 0, 1000, 15, 140, 25, 1000, 15);
        /* écrit le temps en bleu */
        ChoisirCouleurDessin(CouleurParComposante(17, 180, 185));
        EcrireTexte(1015,30,timer,1);
      }
      if(SourisCliquee()){ /* si il y'a un clique */
        SourisPosition(); /* stock les positions de la souris */
        x =_X;
        y =_Y;
        /* création de la head box du bouton quitter */
        if ((x > x_haut_exit) && (x < x_bas_exit) && (y > y_haut_exit) && (y < y_bas_exit)) {
          FermerGraphique();
          exit(0);
        };
        /* création de la headbox des cartes */
        for(ligne_img=0;ligne_img < nb_ligne;ligne_img++){
          for (colonne_img=0; colonne_img < nb_colonne; colonne_img++){
            /* permet le décallage de chaque headbox */
            if((x >= posx_carte_une+(colonne_img*espace_carte_x))&&(x <= (posx_carte_une+TAILLE_IMG)+(colonne_img*espace_carte_x))) {
              if((y >= posy_carte_une+(ligne_img*espace_carte_y))&&(y <= (posy_carte_une+TAILLE_IMG)+(ligne_img*espace_carte_y))) {
                if(tab[ligne_img][colonne_img] != -1 && ((colonne_img != premier_clic_imgx)||(ligne_img != premier_clic_imgy))) {
                  char revel[10];
                  /* remplit un tableau de charactere avec l'image qui correspont a la valeur du tableau */
                  sprintf(revel,"images/Logos/img-%d.png",tab[ligne_img][colonne_img]);
                  /* affiche l'image la où on a cliquer */
                  ChargerImage(revel,posx_carte_une+(colonne_img*espace_carte_x),posy_carte_une+(ligne_img*espace_carte_y),0,0,TAILLE_IMG,TAILLE_IMG);
                  /* passage au deuxième coup */
  				        coup++;
                  if(coup==1){/* stock les valeur du premier coup */
  	                premier_clic_img = tab[ligne_img][colonne_img];
  	                premier_clic_imgx = colonne_img;                  /* Stock les coordonnees de la carte dans x et y */
  	                premier_clic_imgy = ligne_img;
                	}
                  else{/* stock les valeur du deuxième coup */
                    deuxieme_clic_img = tab[ligne_img][colonne_img];     /* Stock la valeur du tableau correspondant au choix */
                    deuxieme_clic_imgx = colonne_img;            /* Stock les coordonnees de la carte dans x et y */
                    deuxieme_clic_imgy = ligne_img;
                	}
                }
              }
            }
          }
        }
      }
    }
    /* comparaison des valeur des cartes */
    if(premier_clic_img == deuxieme_clic_img) {
      char revel[10];
      sprintf(revel,"images/Logos/img-%d.png",tab[premier_clic_imgy][premier_clic_imgx]);
      ChargerImage(revel,posx_carte_une+(premier_clic_imgx*espace_carte_x),posy_carte_une+(premier_clic_imgy*espace_carte_y),0,0,TAILLE_IMG,TAILLE_IMG);
      sprintf(revel,"images/Logos/img-%d.png",tab[premier_clic_imgy][premier_clic_imgx]);
      ChargerImage(revel,posx_carte_une+(deuxieme_clic_imgx*espace_carte_x),posy_carte_une+(deuxieme_clic_imgy*espace_carte_y),0,0,TAILLE_IMG,TAILLE_IMG);
      /* remplace les valeurs trouver dans le tableau par -1 */
      tab[premier_clic_imgy][premier_clic_imgx] = -1;
      tab[deuxieme_clic_imgy][deuxieme_clic_imgx] = -1;
      /* augmente le nombe de paire trouver */
      nb_paire_trouve++;
    }else
    {
      int drapeau=0;
      int t_sleep=Microsecondes();
      int tmp_sleep;
      while (drapeau==0) {/* fait une pause de 1s sans changer le temps de jeu */
        tmp_sleep=Microsecondes();
        if ( Microsecondes() > suivant){
          suivant = Microsecondes() + CYCLE;
          seconde +=1;
          sprintf(timer,"Time : %6d s",seconde);
          CopierZone(8, 0, 1000, 15, 140, 25, 1000, 15);
          EcrireTexte(1015,30,timer,1);
        }
        if(tmp_sleep-t_sleep>1000000){
          drapeau=1;
        }
      }
      ChargerImage("images/Logos/dos_carte.png",posx_carte_une+(premier_clic_imgx*espace_carte_x),posy_carte_une+(premier_clic_imgy*espace_carte_y),0,0,TAILLE_IMG,TAILLE_IMG);
      ChargerImage("images/Logos/dos_carte.png",posx_carte_une+(deuxieme_clic_imgx*espace_carte_x),posy_carte_une+(deuxieme_clic_imgy*espace_carte_y),0,0,TAILLE_IMG,TAILLE_IMG);
    }
    if (nb_paire_trouve>=NB_PAIR){
      usleep(1000000);
      FermerGraphique();
      fin();
    }
  }



  FermerGraphique();
  return EXIT_SUCCESS;
}
