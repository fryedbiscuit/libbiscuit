#include "inc/biscuit.h"
#include "inc/libc.h"
#include "inc/sys.h"
const char charset[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char* strrev(char* str, char* dst){
	if (dst == NULL){
		size_t len = bc_strlen(str);
		size_t start = 0;
		size_t end = len - 1;
		char store;

		while (start < end){
			store = str[start];
			str[start] = str[end];
			str[end] = store;
			start++;
			end--;
		}
		return str;
	} else {
		char len = bc_strlen(str);
		dst += len - 1;
		while(*str){
			*dst = *str;
			str++;
			dst--;
		}

		return dst;
	}
}

int get_digit_count(ulong n,int base) {
    if (n == 0) return 1;

    int count = 0;
    while (n > 0) {
        count++;
        n /= base;
    }
    return count;
}

char *ultoa(ulong num, int base, char *buf, u64 szmax) {
	size_t index = 0;
	szmax--; // Reserver one character for '\0'

	while (szmax && num) {
		buf[index] = charset[num % base];
		num /= base;
		szmax--;
		index++;
	}

	buf[++index] = '\0';
	strrev(buf, NULL);

	return buf;
}

char *ltoa(long num, int base, char *buf, u64 szmax) {
	char* old_buf = buf; //Store the old buffer pointer in case it changes
	szmax--; // Reserve one character for '\0'

	if (num < 0){ // If negative set first character as '-'
		*buf = '-';
		num *= -1;
		buf++;
		szmax--;
	}

	size_t index = 0;
	while (szmax && num) {
		buf[index] = charset[num % base];
		num /= base;
		szmax--;
		index++;
	}

	buf[++index] = '\0';
        strrev(buf, NULL);

        return old_buf;
}

void hexprint(char* buf, size_t len) {
	size_t c = 0;
	char byte[3];

	while(len) {
		if ((c % 4) == 0) bc_write(STDOUT, "\n", 1);
		ultoa((ulong) *buf++, 16, byte, 3);
		bc_write(STDOUT,byte,2);
		c++;
		len--;

	}

	bc_write(STDOUT, "\n", 1);
}

//TODO remake cat so it doesnt depend on libc, while keeping it performant
// size_t cat(u32 count, ...) {
//   // prints any number of strings.
//   // last argument has to be NULL
//
//   char *str = NULL;
//   u32 cnum = 0;
//   va_list args;
//
//   va_start(args, count);
//
//   while (count) {
// 	str = va_arg(args, char *);
//     cnum += fwrite(str, sizeof(char),strlen(str), stdout);
// 	count--;
//   }
//
//   va_end(args);
//
//   fflush(stdout);
//   return cnum;
// }
