### Flash emulation for unit test

For this assignment we were given an API (spi_flash.h) and told to emulate a Winbond QSPI flash device. The device "geometry" given in the pound-define statements below were obtained from the data sheet. The emualtion code uses these along with some flags (page erased) to simulate flash. The implementation here is pretty simple, it does not initialize the flash to 0xff as the physical part would be initially and after an erase operation, although this could certainly be added. More test cases could also be added, but this was enough to verify that the mock works at a basic level. 

### Build/run steps

```
➜  flash-test git:(main) ✗ make clean
rm -f main main.o flash_emul.o
➜  flash-test git:(main) ✗ make
gcc -c main.c
gcc -c flash_emul.c
(warnings about printing pointers)
gcc -o main main.o flash_emul.o
➜  flash-test git:(main) ✗ ./main 
sFLASH_EraseBulk: entry
sFLASH_WritePage: page_num[0000000d] offset_in_page[00000000]
sFLASH_WritePage: ppage: a9de5d74
sFLASH_ReadBuffer: page_num[0000000d] offset_in_page[00000000]
sFLASH_ReadBuffer: ppage: a9de5d74

main: write/read one page test passed

```

### Test Code

```
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <strings.h> // for bcmp

#include "spi_flash.h"

#define PAGES_IN_PART (4096)
#define PAGES_IN_SECTOR (16)
#define PAGE_SIZE (256)

static uint8_t test_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, \
						   0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

#define PAGE_TO_ADDR(p) ((p)*PAGE_SIZE)

int main(int argc, char *argv[])
{
	char read_buffer[16] = {0};
	int temp;

	sFLASH_Init();

	sFLASH_EraseBulk();

	sFLASH_WritePage(test_data, PAGE_TO_ADDR(13), 16);

	sFLASH_ReadBuffer(read_buffer, PAGE_TO_ADDR(13), 16);

	temp = bcmp(test_data, read_buffer, 16);

	printf("%s: write/read one page test %s\n", __FUNCTION__, (temp == 0) ? "passed" : "failed");

	sFLASH_DeInit();

	return 0;
}
```
