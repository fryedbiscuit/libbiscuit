#include "biscuit.h"

// OPEN FLAGS
#ifndef O_RDONLY
#define O_RDONLY	0x00000
#define O_WRONLY	0x00001
#define O_RDWR  	0x00002

#define O_CREAT 	0x00040
#define O_EXCL  	0x00080
#define O_NOCTTY	0x00100
#define O_TRUNC 	0x00200
#define O_APPEND	0x00400
#define O_NONBLOCK 	0x00800 
#define O_DSYNC 	0x01000
#define O_DIRECT 	0x04000
#define O_DIRECTORY 0x10000
#define O_NOFOLLOW 	0x20000
#define O_CLOEXEC 	0x80000
#endif

// MMAP FLAGS
#ifndef  PROT_READ
#define PROT_NONE 0x0
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4

#define MAP_SHARED 0x1
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS
#endif

int bc_open(const char* file, int flags, u16 mode);
int bc_close(int fd);
long bc_write(long fd, char* buffer, long count);
long bc_read(long fd, char* buffer, long count);
void* bc_mmap(void* addr, size_t length, int prot, int flags,int fd, size_t offset) ;
int bc_munmap(void* addr, size_t len);
