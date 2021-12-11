#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>

#include "spi_flash.h"

#define TRUE (1)
#define FALSE (0)
#define NULL (0)

#define PAGES_IN_PART (4096)
#define PAGES_IN_SECTOR (16)
#define PAGE_SIZE (256)

// 1MByte device 
// 4K pages in part, 256 bytes each, 16 pages per sector
// 256 erasable sectors in part, 16 erasable blocks
// could malloc data as well to conserve heap

typedef struct _page_t
{
	int page_erased = FALSE;
	uint8_t data[PAGE_SIZE];
} page_t;

page_t *page_list = NULL;

#define GET_PAGE(num, offset) (page_list[(num)+(offset)])

static int init_done = FALSE;
static int write_enable = FALSE;

void sFLASH_DeInit(void)
{
	init_done = FALSE;

	free(page_list);
}

void sFLASH_Init(void)
{
	init_done = TRUE;

	page_list = malloc(sizeof(page_t) * PAGES_IN_PART)
}

void sFLASH_EraseSector(uint32_t SectorAddr)
{
	int i;
	uint32_t page_num;
	page_t *ppage;

	if (init_done == FALSE)
		return; // TODO: assert an error

	// ensure sector addr is 16 page aligned
	if (SectorAddr % (PAGE_SIZE*PAGES_IN_SECTOR))
		printf("__FUNCTION__: SectorAddr not aligned: %08x\n", SectorAddr);
		// TODO: assert address error
		return;

	// for pages within the sector, mark them as erased
	page_num = SectorAddr / (PAGE_SIZE*PAGES_IN_SECTOR);
	printf("__FUNCTION__: page number to start: %08x\n", page_num);
	for(i=0; i<PAGES_IN_SECTOR; i++)
	{
		ppage = GET_PAGE(page_num, i);
		ppage->page_erased = TRUE;
	}

	return;
}

void sFLASH_EraseBulk(void)
{
	int i;
	if (init_done == FALSE)
		return; // TODO: assert an error

	printf("__FUNCTION__: entry\n");

	// mark all pages in list as erased; if not in list, assume it is erased
	for(i=0; i<PAGES_IN_PART; i++)
	{
		ppage = GET_PAGE(0, i);
		ppage->page_erased = TRUE;
	}
}

void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	page_t *ppage;
	int page_num;
	int offset_in_page;


	if ((init_done == FALSE) || (NumByteToWrite > 256) || (pBuffer == NULL))
	{
		printf("__FUNCTION__: page number to start: %08x\n", page_num);
		return; // TODO: assert an error
	}

	// see if page is already written
	page_num = WriteAddr / PAGES_IN_PART;
	offset_in_page = WriteAddr % 256;

	printf("__FUNCTION__: page_num[%08x] offset_in_page[%08x]\n", page_num, offset_in_page);
	return; // TODO: assert an error

	ppage = GET_PAGE(page_num, 0);

	// can't write an unerased page
	if (ppage->page_erased == FALSE)
		return;

	// if not written, assume it is erased, add data
	ppage->page_erased = FALSE;

	bcopy(pBuffer, (char *)(ppage->data + offset_in_page), NumByteToWrite);
}

void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	if (init_done == FALSE)
		return; // TODO: assert an error
	
}

void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	if (init_done == FALSE)
		return; // TODO: assert an error
	
}

uint32_t sFLASH_ReadID(void)
{
	return 0x00ef4014;
}

void sFLASH_StartReadSequence(uint32_t ReadAddr)
{
	if (init_done == FALSE)
		return; // TODO: assert an error
	
}

/* low level methods */

// use fifo to simulate command fifo in flash chiop
// ensure that b
uint8_t sFLASH_ReadByte(void)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	// read a byte from fifo
}

uint8_t sFLASH_SendByte(uint8_t byte)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	// write a byte to fifo
}

uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	// write 2 bytes to fifo
}

void sFLASH_WriteEnable(void)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	write_enable = TRUE;
}

void sFLASH_WaitForWriteEnd(void)
{
	return;
}