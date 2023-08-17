#include "bootparam.h" 
#define NULL 0 

int init_boot_param(struct boot_params *bp)
{
	char sign_bp[8] = {'B', 'P', 'I', '0', '1', '0', '0', '0'};
	memcpy(bp, sign_bp, 8);
	bp->efitab = &systab;
	bp->elh = NULL;

	return bp;
}
