#include "GraphicsTimer.h"

GraphicsTimer::GraphicsTimer(long int msec, void (*notify_function) (union sigval), void *ptr)
{
    struct sigevent sev;

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_value.sival_ptr = ptr;
    sev.sigev_notify_function = notify_function;
    sev.sigev_notify_attributes = NULL;

    if (timer_create(CLOCK_REALTIME, &sev, &m_id) == -1) {
        printf("%s: %s (%i): ERROR - timer_create() \n", __FILE__, __FUNCTION__, __LINE__);
        return;
    }

    setTimeInterval(msec);
}

GraphicsTimer::~GraphicsTimer()
{
    if (m_id)
        timer_delete(m_id);
}

bool GraphicsTimer::setTimeInterval(long int msec)
{
    struct itimerspec ts;

    long int sec = msec / 1000;
    long int nsec = (msec % 1000) * 1e06;

    ts.it_value.tv_sec = sec;
    ts.it_value.tv_nsec = nsec;
    ts.it_interval.tv_sec = sec;
    ts.it_interval.tv_nsec = nsec;

    if (timer_settime(m_id, 0, &ts, NULL) == -1) {
        printf("%s: %s (%i): ERROR - timer_settime()\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}
