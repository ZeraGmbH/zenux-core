#include "demoeventloopfeeder.h"
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

void DemoEventLoopFeeder::feedEventLoop()
{
    while(QCoreApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents));
}
