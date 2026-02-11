#ifndef TIMERTESTDEFAULTS_H
#define TIMERTESTDEFAULTS_H

// These should remain fixed (huge) because
// * here we are testing delays and timers span widely in oe-ctest
// * when using TimerForTestTemplate there are no delays
static constexpr int DEFAULT_EXPIRE = 50;
static constexpr int DEFAULT_EXPIRE_WAIT = DEFAULT_EXPIRE * 2;
static constexpr int DEFAULT_PERIODIC_EXTRA_WAIT = DEFAULT_EXPIRE * 0.8;
static constexpr int EXPIRE_INFINITE = 1000000;

#ifdef QT_NO_DEBUG
#define SKIP_TEST_ON_RELEASE_BUILD QSKIP("This is flaky test relying on timers.");
#else
#define SKIP_TEST_ON_RELEASE_BUILD
#endif

#endif // TIMERTESTDEFAULTS_H
