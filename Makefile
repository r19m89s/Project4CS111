protect : protectfile.c
	gcc -o protectfile protectfile.c

system : mfsdone vfsdone hgfsdone othersdone
	make includes -C /usr/src
	make -C /usr/src/servers/hgfs
	make -C /usr/src/servers/mfs
	make -C /usr/src/servers/vfs
	make hdboot -C /usr/src/tools
	rm -f mfsdone vfsdone hgfsdone othersdone


mfsdone :
	cp mfs/*.[ch] /usr/src/servers/mfs/
	cp mfs/Makefile /usr/src/servers/mfs/
	touch mfsdone

vfsdone :
	cp vfs/*.[ch] /usr/src/servers/vfs/
	touch vfsdone

hgfsdone :
	cp hgfs/*.[ch] /usr/src/servers/hgfs/
	touch hgfsdone


othersdone :
	cp callnr.h /usr/src/include/minix/
	cp skeylib.h /usr/include/
	cp vfsif.h /usr/src/include/minix/
	touch othersdone


getfiles :
	scp -r thomasmiller@192.168.0.195:~/cmps/cmps111/proj4/Project4CS111/* .
