#include <lib.h>
#include <unistd.h>
#define setkey _setkey
PUBLIC int setkey (unsigned int k0, unsigned int k1){
	message m;
	m.m1_i1 = k0;
	m.m1_i2 = k1;
	char* name = "/usr";
	_loadname(name, &m);
	return (_syscall(VFS_PROC_NR, SETKEY, &m));
}
