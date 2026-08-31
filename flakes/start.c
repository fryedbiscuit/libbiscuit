// A basic start for programs in a freestanding environment
// Only whats necessary to run a c program without libc

#define _GNU_SOURCE

extern int main(int argc, char **argv, char **envp);

void __attribute__((noreturn)) __start_c(long *sp) {
    int argc = (int)(*sp);
    char **argv = (char **)(sp + 1);
    
    char **envp = argv;
    while (*envp) {
        envp++;
    }
    envp++; // Skip the NULL pointer separating argv and envp

    int ret = main(argc, argv, envp);

#if defined(__x86_64__)
    __asm__ volatile (
        "movq $231, %%rax\n\t"  // __NR_exit_group
        "movq %0, %%rdi\n\t"    // Exit status from main
        "syscall\n\t"
        :
        : "r"((long)ret)
        : "rax", "rdi", "memory"
    );
#elif defined(__aarch64__)
    __asm__ volatile (
        "mov x8, #93\n\t"       // __NR_exit_group
        "mov x0, %0\n\t"        // Exit status from main
        "svc #0\n\t"
        :
        : "r"((long)ret)
        : "x8", "x0", "memory"
    );
#endif

    while (1);
}

#if defined(__x86_64__)

__attribute__((naked)) void _start(void) {
    __asm__ volatile (
        "xor %%rbp, %%rbp\n\t"   // Clear frame pointer for stack unwinding
        "mov %%rsp, %%rdi\n\t"   // Pass raw stack pointer as first argument (rdi)
        "andq $-16, %%rsp\n\t"   // Align stack pointer to 16-byte boundary
        "call __start_c\n\t"     // Transfer control to C initialization function
        :
        :
        : "memory"
    );
}

#elif defined(__aarch64__)

__attribute__((naked)) void _start(void) {
    __asm__ volatile (
        "mov x29, #0\n\t"        // Clear frame pointer
        "mov x30, #0\n\t"        // Clear link register
        "mov x0, sp\n\t"         // Pass raw stack pointer as first argument (x0)
        "mov x9, sp\n\t"         // Copy sp to scratch register x9
        "bic x9, x9, #15\n\t"    // Clear lower 4 bits for 16-byte alignment
        "mov sp, x9\n\t"         // Update stack pointer
        "bl __start_c\n\t"       // Transfer control to C initialization function
        :
        :
        : "x9", "memory"
    );
}

#else
#error "Unsupported architecture for custom _start implementation."
#endif

void* memset(void* addr, int byte, unsigned long lenght) {
	char* caddr = addr;
	while(lenght) {
		*caddr = (char)byte;
		caddr++;
		lenght--;
	}
	return addr;
}

void* memcpy(void* dst, const void* src, unsigned long size) {
	char* cdst = dst;
	const char* csrc = src;
	while(size){
		*cdst++ = *csrc++;
		size--;
	}
	return dst;
}
