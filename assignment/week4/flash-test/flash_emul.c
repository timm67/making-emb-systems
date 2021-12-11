#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <strings.h> // for bcopy

#include "spi_flash.h"

#define TRUE (1)
#define FALSE (0)

#define PAGES_IN_PART (4096)
#define PAGES_IN_SECTOR (16)
#define PAGE_SIZE (256)

// 1MByte device 
// 4K pages in part, 256 bytes each, 16 pages per sector
// 256 erasable sectors in part, 16 erasable blocks
// could malloc data as well to conserve heap

typedef struct _page_t
{
	int page_erased;
	uint8_t data[PAGE_SIZE];
} page_t;

static page_t page_list[PAGES_IN_PART] = {0};

#define GET_PAGE(num, offset) (&(page_list[((num)+(offset))]))

static int init_done = FALSE;
static int write_enable = FALSE;

void sFLASH_DeInit(void)
{
	init_done = FALSE;
	//free(page_list);
}

void sFLASH_Init(void)
{
	//page_list = (page_t *)malloc(sizeof(page_t) * PAGES_IN_PART);
	init_done = TRUE;
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
	{
		printf("%s: SectorAddr not aligned: %08x\n", __FUNCTION__, SectorAddr);
		// TODO: assert address error
		return;
	}

	// for pages within the sector, mark them as erased
	page_num = SectorAddr / (PAGE_SIZE*PAGES_IN_SECTOR);
	for(i=0; i<PAGES_IN_SECTOR; i++)
	{
		ppage = GET_PAGE(page_num, i);
		printf("%s: ppage: %08x\n", __FUNCTION__, (uint32_t)ppage);
		ppage->page_erased = TRUE;
	}

	return;
}

void sFLASH_EraseBulk(void)
{
	int i;
	page_t *ppage;

	if (init_done == FALSE)
		return; // TODO: assert an error

	printf("%s: entry\n", __FUNCTION__);

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
		return; // TODO: assert an error
	}

	// see if page is already written
	page_num = WriteAddr / PAGE_SIZE;
	offset_in_page = WriteAddr % PAGE_SIZE;

	printf("%s: page_num[%08x] offset_in_page[%08x]\n", __FUNCTION__, page_num, offset_in_page);

	ppage = GET_PAGE(page_num, 0);
	printf("%s: ppage: %08x\n", __FUNCTION__, (uint32_t)ppage);

	// can't write an unerased page
	if (ppage->page_erased == FALSE)
	{
		printf("%s: page not erased, bailing\n", __FUNCTION__);		
		return;
	}

	// if not written, assume it is erased, add data
	ppage->page_erased = FALSE;

	bcopy(pBuffer, (char *)(ppage->data + offset_in_page), NumByteToWrite);
}

void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
}

void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{

	page_t *ppage;
	int page_num;
	int offset_in_page;


	if ((init_done == FALSE) || (NumByteToRead > 256) || (pBuffer == NULL))
	{
		return; // TODO: assert an error
	}

	// see if page is already written
	page_num = ReadAddr / PAGE_SIZE;
	offset_in_page = ReadAddr % PAGE_SIZE;

	printf("%s: page_num[%08x] offset_in_page[%08x]\n", __FUNCTION__, page_num, offset_in_page);

	ppage = GET_PAGE(page_num, 0);
	printf("%s: ppage: %08x\n", __FUNCTION__, (uint32_t)ppage);

	// don't bother reading an erased page
	if (ppage->page_erased == TRUE)
	{
		printf("%s: page not written, bailing\n", __FUNCTION__);	
		return;
	}

	bcopy((char *)(ppage->data + offset_in_page), pBuffer, NumByteToRead);
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

