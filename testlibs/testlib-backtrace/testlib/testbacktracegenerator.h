#ifndef TESTBACKTRACEGENERATOR_H
#define TESTBACKTRACEGENERATOR_H

#include <QStringList>
#include <execinfo.h>

// If
// * we miss important
// * test_memallocs_atomic starts to fail
//
// increase maxStacktraceDepth but be aware it slows down
// tests significantly
static constexpr int maxStacktraceDepth = 15;

class TestBacktraceGenerator
{
public:
    struct BacktraceRaw {
        void *bufferBacktrace[maxStacktraceDepth];
        int startPos = 0;
        int afterLastPos = 0;
    };
    static void createBacktraceRaw(BacktraceRaw *btrace);
    static QStringList generateSymbols(BacktraceRaw *btrace);

private:
    static QStringList generateAllSymbols(BacktraceRaw *btrace);
    static void alignStartPosition(BacktraceRaw *btrace);
    static void cacheSpecialFunctionAddresses(BacktraceRaw *btrace);

    static QStringList removeUnwantedTopTraces(const QStringList &backtrace,
                                               const QString &removeCFunctionAndAllAbove);
    static QStringList removeFileName(const QStringList &backtrace);
};

#endif // TESTBACKTRACEGENERATOR_H
