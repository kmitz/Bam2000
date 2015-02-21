#include "Cat.h"

using namespace std;

Cat::Cat()
{
    offset = 0;
    velocity = 0;
    frame = 0;
    status = CAT_RIGHT;
}


void Cat::updateAnim()
{
    offset += velocity;
    if( ( CONST_POSX_INI + offset - CAT_WIDTH < 0 ) || ( CONST_POSX_INI + offset - CAT_WIDTH > SCREEN_WIDTH ) )
    {
        offset -= velocity;
    }
    if( velocity < 0 ){
        status = CAT_LEFT;
    }
    else if( velocity > 0 ){
        status = CAT_RIGHT;
    }
}

void Cat::updateFrame()
{
    if( velocity == 0 ){
        frame = 1;
    }
    else{
        frame++;
        if (frame >= 3){
            frame = 0;
        }
    }
}

