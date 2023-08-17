#include <sys/linux/types.h>  
#include <efi_api.h>

struct ext_list_hdr {
  u64  sign;
  u32  len;
  u8   rev;
  u8   checksum;
  struct  ext_list_hdr *next;
} __attribute__((__packed__)); 

struct boot_params{
	u64 sign;	//{'B', 'P', 'I', '0', '1', '0', '0', '0'}
	void *efitab;
	struct ext_list_hdr *elh;
} __attribute__((__packed__));
