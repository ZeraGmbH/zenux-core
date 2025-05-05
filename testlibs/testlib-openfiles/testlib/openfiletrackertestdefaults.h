#ifndef TIMERTESTDEFAULTS_H
#define TIMERTESTDEFAULTS_H

#ifdef QT_NO_DEBUG
#define SKIP_TESTS_ON_RELEASE_BUILD QSKIP("These tests crash in qemu on OE builds.");
#else
#define SKIP_TESTS_ON_RELEASE_BUILD
#endif

#endif // TIMERTESTDEFAULTS_H
