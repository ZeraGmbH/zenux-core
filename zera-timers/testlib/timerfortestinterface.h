#ifndef TIMERFORTESTINTERFACE_H
#define TIMERFORTESTINTERFACE_H

class TimerForTestInterface
{
public:
    TimerForTestInterface(int expireMs, bool singleShot) :
        m_expireMs(expireMs == 0 ? 1 : expireMs),
        m_singleShot(singleShot) {}
    virtual ~TimerForTestInterface() = default;
    virtual void fireExpired() = 0;

    const int m_expireMs;
    const bool m_singleShot;
};

#endif // TIMERFORTESTINTERFACE_H
