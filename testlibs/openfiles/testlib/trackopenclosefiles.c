#define _GNU_SOURCE // otherwise RTLD_NEXT is not found
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>

void handleOpenFile(const char *path, int fd);
void handleFOpenFile(const char *path, FILE *stream);
void handleCloseFile(int ret, int fd);

// Note on 64-variants / O_LARGEFILE: We can not test which function was
// called e.g open or open64. We could read /proc/<pid>/fdinfo/<fd> but on
// 64bit systems O_LARGEFILE is used by default. So we have to do careful
// optical inspection in here...

int open(const char *path, int flags, ...) {
    static int (*real_func)(const char *path, int flags, ...) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "open");

    mode_t mode = 0;
    if (flags & O_CREAT || flags & O_TMPFILE) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int fd = real_func(path, flags, mode);
    handleOpenFile(path, fd);
    return fd;
}

int creat(const char *path, mode_t mode) {
    static int (*real_func)(const char *path, mode_t mode) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "creat");

    int fd = real_func(path, mode);
    handleOpenFile(path, fd);
    return fd;
}

int openat(int dirfd, const char *path, int flags, ...) {
    static int (*real_func)(int dirfd, const char *path, int flags, ...) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "openat");

    mode_t mode = 0;
    if (flags & O_CREAT || flags & O_TMPFILE) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int fd = real_func(dirfd, path, flags, mode);
    handleOpenFile(path, fd);
    return fd;
}

int open64(const char *path, int flags, ...) {
    static int (*real_func)(const char *path, int flags, ...) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "open64");

    mode_t mode = 0;
    if (flags & O_CREAT || flags & O_TMPFILE) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }
    int fd = real_func(path, flags, mode);
    handleOpenFile(path, fd);
    return fd;
}

FILE *fopen(const char *restrict path, const char *restrict mode) {
    static FILE* (*real_func)(const char *restrict path, const char *restrict mode) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "fopen");

    FILE *stream = real_func(path, mode);
    handleFOpenFile(path, stream);
    return stream;
}

FILE *fopen64(const char *restrict path, const char *restrict mode) {
    static FILE* (*real_func)(const char *restrict path, const char *restrict mode) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "fopen64");

    FILE *stream = real_func(path, mode);
    handleFOpenFile(path, stream);
    return stream;
}

int close(int fd) {
    static int (*real_func)(int fd) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "close");
    int ret = real_func(fd);
    handleCloseFile(ret, fd);
    return ret;
}

int fclose(FILE *stream) {
    static int (*real_func)(FILE *stream) = NULL;
    if (!real_func)
        real_func = dlsym(RTLD_NEXT, "fclose");
    int fd = fileno(stream);
    int ret = real_func(stream);
    handleCloseFile(ret, fd);
    return ret;
}
