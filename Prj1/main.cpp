#include "gark.h"
#include "player.h"
#include "history.h"
#include "mesa.h"
#include "game.h"
#include "globals.h"

/////////////////////////////////////////////////////////////////////////
//  main()
/////////////////////////////////////////////////////////////////////////

int main()
{
      // create a game
      // use this instead to create a mini-game:   game g(3, 4, 2);
    Game g(7, 8, 25);

      // play the game
    g.play();
}
