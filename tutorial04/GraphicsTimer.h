#ifndef GraphicsTimer_h
#define GraphicsTimer_h

#include <time.h>
#include <signal.h>
#include <sys/time.h>

#include <stdio.h>

class GraphicsTimer
{
public:
    GraphicsTimer(long int, void (*) (union sigval), void*);
    ~GraphicsTimer();

    bool setTimeInterval(long int);

private:
    timer_t m_id;
};

#endif /* GraphicsTimer_h */
