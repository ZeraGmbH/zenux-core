#ifndef TEST_OPENFILETRACKER_H
#define TEST_OPENFILETRACKER_H

#include <QObject>

class test_openfiletracker : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void cleanup();

    void openFileOnce();
    void openFileTwice();
    void openTwoFilesOnce();
    void openTwoFilesOnceClear();
    void openTwoFilesTwice();
};

#endif // TEST_OPENFILETRACKER_H
