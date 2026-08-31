// My own implementation of libc functions
// This is so i don't depend on libc at all, and can use my library on a freestanding executable
#include "inc/biscuit.h"

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
