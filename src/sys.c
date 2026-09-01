// My own implementations of syscalls and libc functions, so i don't need libc
#include "inc/biscuit.h"
#include "inc/syscall.h"
#include "inc/syscall_defs.h"

//--------------=== SYSCALL ===--------------//
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

//--------------=== LIBC ===--------------//
void* bc_memset(void* addr, i32 byte, size_t lenght) {
	char* caddr = addr;
	while(lenght) {
		*caddr = (char)byte;
		caddr++;
		lenght--;
	}
	return addr;
}

void* bc_memcpy(void* dst, const void* src, size_t size) {
	char* cdst = dst;
	const char* csrc = src;
	while(size){
		*cdst++ = *csrc++;
		size--;
	}
	return dst;
}

char* bc_strncpy(char* dst, const char* src, size_t dsize) {
	char* old_dst = dst;
	while(dsize) {
		if(*src == '\0') break;
		*dst++ = *src++;
		dsize--;
	}
	return old_dst;
}
size_t bc_strlen(const char* str) {
	size_t len = 0;
	
	while(*str != '\0') {
		str++;
		len++;
	}

	return len;
}
