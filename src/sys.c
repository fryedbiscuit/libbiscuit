// My own implementations of syscalls, so i don't need libc
#include "inc/biscuit.h"
#include "inc/syscall.h"
#include "inc/syscall_defs.h"

void* bc_mmap(void* addr, size_t length, int prot, int flags,int fd, size_t offset) {
	return (void*) syscall(SYS_mmap,(u64)addr,length,prot,flags,fd,offset);
}
int bc_munmap(void* addr, size_t len) {
	return syscall(SYS_munmap,(u64)addr,len);
}

#if defined(__x86_64__) || defined(_M_X64)
int bc_open(const char* file, int flags, u16 mode){
	return syscall(SYS_open, (size_t)file, flags, mode ) };
#elif defined(__aarch64__) || defined(_M_ARM64)
int bc_open(const char* file, int flags, u16 mode){
	return syscall(SYS_openat, -100, (size_t)file, flags, mode);
}
#endif

int bc_close(int fd) {
	return syscall(SYS_close, fd);
}

long bc_write(long fd, char* buffer, long count){
	return syscall(SYS_write,fd, (u64)buffer,count);
}
long bc_read(long fd, char* buffer, long count){
	return syscall(SYS_read,fd, (u64)buffer,count);
}
