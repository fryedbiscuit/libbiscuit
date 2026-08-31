#include "inc/biscuit.h"
#include "inc/sys.h"
#include "inc/libc.h"

int main() {
	char* str = "Hello, world!\n";
	raw char rev[bc_strlen(str) + 1];
	bc_write(STDOUT, str, bc_strlen(str));
	bc_write(STDOUT, rev, bc_strlen(rev));

	return 0;
}
