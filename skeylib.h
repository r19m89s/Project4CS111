#include <lib.h>
#include <unistd.h>
#define setkey _setkey
PUBLIC int setkey (unsigned int k0, unsigned int k1) {
	message m;
	char* name = "/usr";
	_loadname(name, &m);
   m.m1_i2 = k0;
	m.m1_i3 = k1;
   //printf("3skeylib k0 = %d\n", m.m1_i2);
   //printf("3skeylib k1 = %d\n", m.m1_i3);
	return (_syscall(VFS_PROC_NR, SETKEY, &m));
}
