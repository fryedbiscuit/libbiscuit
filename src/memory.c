#include "inc/biscuit.h"
#include "inc/sys.h"

void* alloc(size_t size) {
	char* mem = bc_mmap(NULL,sizeof(long) + size,PROT_READ | PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
	*(u64*)mem = size;

	return (void*)(mem + sizeof(long));
}
void alloc_free(void* addr) {
	bc_munmap(addr, *(u64*)((char*)addr - sizeof(long)));	
}
