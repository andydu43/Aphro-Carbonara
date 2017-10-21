#include <stdio.h>

#define HAUTEUR_FENETRE 600
#define LARGEUR_FENETRE 950

#define TAILLE_BLOC 50

#include "evenement.h"
#include "display.h"
#include "charac.h"
#include "map.h"

int main()
{
  int time = 0;
  int timeMax = 0;
  data_touche touche;

  charac_t player;
  SDL_Renderer * renderer;

  map_t map;
  int x_init_player;
  int y_init_player;

  /* variable d'initialisation de SDL_image */
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  /* variable liee a la fenetre */
  SDL_Window * window;
  /* variables liees a la capture d'evenement */
  SDL_Event event;
  int run = 1;

  /* initialisation de la SDL2 */
  if(SDL_Init(SDL_INIT_VIDEO) == 1){
      fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  /* initialisation de SDL_ttf */
  if (TTF_Init() != 0){
    fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  /* initialisation de SDL_image */
  if((IMG_Init(flags)&flags) != flags){
      printf("IMG_Init: Failed to init required jpg and png support!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
      TTF_Quit();
      SDL_Quit();
      return EXIT_FAILURE;
  }

  /* ouverture de la fenetre */
  window = SDL_CreateWindow("Carbonara",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            LARGEUR_FENETRE,HAUTEUR_FENETRE,
                            0);

  if(!window){
    fprintf(stderr,"Erreur de creation de la fenetre : %s\n", SDL_GetError());
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  /* initialisation du renderer */
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  if(!renderer){
    fprintf(stderr,"Erreur de creation du renderer\n");
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  /*intialisation de la map*/
  x_init_player = 0;
  y_init_player = 0;
  /*TO DO: définir la variable "map"*/
  initMapTexture(renderer, &map);
  initEnnemis(renderer, &map);

  /*initialisation des différentes variables*/
  player = new_charac(x_init_player*TAILLE_BLOC, y_init_player*TAILLE_BLOC+50, DIR_STOP);
  initPlayerTexture(renderer, &player);

  /*initialisation des evenements clavier*/
  touche = init_touche();

  /* boucle d'evenement */
  while(run){
    time += 1;
    evenement(&run, &event, &touche);
    evenementPlay(&map, &touche, &player);

    /*displayAll(renderer, )*/
    /*TO DO*/
    SDL_Delay(32);
  }

  closeTexture(&map, &player);

  /* on libere le renderer */
  if(renderer)
    SDL_DestroyRenderer(renderer);

  /* on libere la fenetre */
  SDL_DestroyWindow(window);
  /* fermeture de SDL_image, SDL_ttf et SDL2 */
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
