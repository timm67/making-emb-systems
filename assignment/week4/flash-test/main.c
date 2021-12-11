#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <strings.h> // for bcmp

#include "spi_flash.h"

#define PAGES_IN_PART (4096)
#define PAGES_IN_SECTOR (16)
#define PAGE_SIZE (256)
#define FLASH_ID (0x00ef4014)

static uint8_t test_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, \
						   0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

#define PAGE_TO_ADDR(p) ((p)*PAGE_SIZE)

int main(int argc, char *argv[])
{
	char read_buffer[16] = {0};
	uint32_t read_id;
	int temp;

	sFLASH_Init();

	read_id = sFLASH_ReadID();

	sFLASH_EraseBulk();

	sFLASH_WritePage(test_data, PAGE_TO_ADDR(13), 16);

	sFLASH_ReadBuffer(read_buffer, PAGE_TO_ADDR(13), 16);

	temp = bcmp(test_data, read_buffer, 16);

	printf("%s: Flash id test %s\n", __FUNCTION__, (read_id == FLASH_ID) ? "passed" : "failed");

	printf("%s: write/read one page test %s\n", __FUNCTION__, (temp == 0) ? "passed" : "failed");

	sFLASH_DeInit();

	return 0;
}
