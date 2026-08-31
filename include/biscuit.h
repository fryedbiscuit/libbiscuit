// This is the API of my library
#ifndef BISCUIT_H
#define BISCUIT_H

// ---------------- ARENA ------------------ //
#define FNV_OFFSET_32 0x811c9dc5
#define FNV_PRIME_32 0x01000193
#define FNV_OFFSET_64 14695981039346656037ULL
#define FNV_PRIME_64 ((1ULL << 40) + (1ULL << 8) + 0xb3)

// Sized integers
typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long i64;
typedef unsigned long u64;

typedef u64 size_t;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef int _bool;
#define bool _bool
#define true 1
#define false 0

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#ifndef NULL
#define NULL 0
#endif

#define ALIGN_16(size) (((size) + 15) & ~15)

typedef struct Arena {
	u8* buffer;
	u64 size;
	u64 offset;
	bool expandable;
	struct Arena* next;
	void* (*allocator)(u64 size);
	void (*free)(void* buffer);
} Arena;

void arena_init(Arena* arena, u64 size, bool expandable);
void* arena_alloc(Arena* arena, u64 size);
void* arena_calloc(Arena* arena, u64 size);
void arena_clear(Arena*);
void arena_free(Arena* arena);

u64 fnv1a64(const void* data, u64 len);
u32 fnv1a32(const void* data, u64 len);
u32 djb2(const void* data, u64 size);

void* alloc(u64 size);
void alloc_free(void* addr);

char* strrev(char* str, char* dst);
int get_digit_count(unsigned long n,int base);
char* ultoa(ulong num, int base, char* buf, u64 szmax);
char* ltoa(long num, int base, char* buf, u64 szmax);
void hexprint(char* buf, size_t len);
size_t cat(u32 count, ...);

#endif
