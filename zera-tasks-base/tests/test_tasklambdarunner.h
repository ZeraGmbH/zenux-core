#ifndef TEST_TASKLAMBDARUNNER_H
#define TEST_TASKLAMBDARUNNER_H

#include <QObject>

class test_tasklambdarunner : public QObject
{
    Q_OBJECT
private slots:
    void startPass();
    void startFail();
};

#endif // TEST_TASKLAMBDARUNNER_H
