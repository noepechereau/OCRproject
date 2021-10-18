#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>


int quit (SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *image, int statut)
{
   //Quitter la SDL proprement
  if (NULL != image)
    SDL_DestroyTexture(image);
  if (NULL != renderer)
    SDL_DestroyRenderer(renderer);
  if (NULL != window)
    SDL_DestroyWindow(window);
  SDL_Quit();
  return statut;
}


// changer le fond de couleur

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
  if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
    return -1;
  if(SDL_RenderClear(renderer) < 0)
    return -1;
  return 0;  
}




// ============================================================
// notre MAIN
// ============================================================

int main()
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *tmp = NULL; 
  SDL_Texture *texture = NULL;
    
  int statut = EXIT_FAILURE;
  SDL_Color blanc = {255, 255, 255, 255};


  //Initialisation Window et Renderer
  if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
      return quit(window, renderer, texture, statut);
    }
  if(0 != SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &window, &renderer))
    {
      fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
      return quit(window, renderer, texture, statut);
    }
 

  //Image, Surface et Texture
  tmp = IMG_Load("image/image_02.jpeg");
  if(NULL == tmp)
    {
      fprintf(stderr, "Erreur IMG_Load : %s", SDL_GetError());
      return quit(window, renderer, texture, statut);
    }
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);
  if(NULL == texture)
    {
      fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
      return quit(window, renderer, texture, statut);
    }

  
  // Début de notre programme !

  statut = EXIT_SUCCESS;
  
  setWindowColor(renderer, blanc);
  SDL_Delay(3000);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);

  return quit(window, renderer, texture, statut);
}

