/* hacked-together header ... APE does not provide struct statfs */
/* I am trying to redirect approximate definitions to APE functions */
/* Need to do some more reading... */

#include <stdio.h>
#include <sys/stat.h>

/* Only the parts expected to be included in struct statfs (pointed to from statvfs.c) are 
* included in the struct below. Types are the same as in corresponding statvfs elements.
*/

typedef struct statfs {
	unsigned long f_bsize;
	uint64_t f_blocks;
	uint64_t f_bfree;
	uint64_t f_bavail;
	uint64_t f_files;
	uint64_t f_ffree;
	fsid_t f_fsid;
};

/* short description of the variables:
* f_bsize : optimal transfer block size
* f_blocks : total data blocks in file
* f_bfree : free blocks in fs
* f_bavail : free blocks available to unpriviliged user
* f_files : total file nodes in file
* f_ffree : free file nodes in fs
* f_fsid : file system id
*/



