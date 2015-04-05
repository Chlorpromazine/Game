#ifndef _CANIMATION_H_
    #define _CANIMATION_H_
 
#include <SDL.h>
#include <iostream>
class CAnimation {
    private:
        int    CurrentFrame;
 
        int     FrameInc;
 
    private:
        unsigned int FrameRate; //Milliseconds
 
        unsigned long OldTime;
 
    public:
        int    MaxFrames;
 
        bool    Oscillate;
 
    public:
        CAnimation();
 
        void OnAnimate();
 
    public:
        void SetFrameRate(int Rate);
 
        void SetCurrentFrame(int Frame);
 
        int GetCurrentFrame();

		void setMaxFrames(int max);
};
 
#endif