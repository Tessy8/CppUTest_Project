#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/time.h>

extern char _end;  // Defined by the linker script
static char *heap_end;

int _write(int file, char *ptr, int len) {
    return len;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _close(int file) {
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

void _exit(int status) {
    while (1) {}
}

int _kill(int pid, int sig) {
    return -1;
}

int _getpid(void) {
    return 1;
}

void *_sbrk(ptrdiff_t increment) {
    if (heap_end == 0) {
        heap_end = &_end;
    }
    char *prev_heap_end = heap_end;
    heap_end += increment;
    return (void *)prev_heap_end;
}

int _open(const char *name, int flags, int mode) {
    return -1;  // Not implemented
}

int _gettimeofday(struct timeval *tv, struct timezone *tz) {
    if (tv) {
        tv->tv_sec = 0;
        tv->tv_usec = 0;
    }
    return 0;  // Return 0 to indicate success
}
