#pragma once
//I also combine this with slow aim since I feel they belong together
class trigger {
public:
    trigger(); //We might not need this later on
    //Trigger stuff
private:
    bool inCross; //GetDef Type
    bool trigStyle;//0 = Unity style, 1 = logical way a triggerbot should work
    int delay; //Time to wait before shooting upon seeing
    int maxBullets; //Max bullets to shoot until stopping
    int postBurst; //Shots to fire after a burst?
    bool slow; //What's slow trigger? Maybe meant for slow aim?
    //Slow aim stuff
private:
    float factor; //How much to slow down aiming by
    int timeout; //How long to slow down aim for in ms
};
