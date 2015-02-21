#ifndef CAT_H
#define CAT_H
#include <SDL2/SDL.h>

#include <Const.h>

class Cat
{
    public:
    Cat();
    void updateAnim();
    int getStatus(){return this->status;};
    int getOffset(){return this->offset;};
    int getFrame(){return this->frame;};
    int getVelocity(){return this->velocity;};
    void updateVelocity(int val){velocity = val;};
    void updateFrame();

    private:
    int offset;
    int velocity;
    int frame;
    int status;
};


#endif
