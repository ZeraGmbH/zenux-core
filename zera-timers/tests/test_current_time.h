#ifndef TEST_CURRENT_TIME_H
#define TEST_CURRENT_TIME_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QTimeZone>

class test_current_time : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void disableTest();
    void enableTestNoTimeProgression();
    void enableTestTimeProgression();
    void enableTestSetTime();
    void enableTestSetTimeProgression();
    void enableTestSetTimeReset();
    void enableTestSetProgressionCompareUTC();
    void enableTestSetCompareBothSetters();
private:
    QDateTime createTestDateTime(QDate &date, QTime &time, QTimeZone &tz) const;
};

#endif // TEST_CURRENT_TIME_H
