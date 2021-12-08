#include "spi_flash.h"

#define TRUE (1)
#define FALSE (0)

typedef struct _page_t
{
	uint32_t page_addr;
	int page_erased = FALSE;
	uint8_t * data;
} page_t;

static int init_done = FALSE;
static int write_enable = FALSE;

void sFLASH_DeInit(void)
{
	init_done = FALSE;
}

void sFLASH_Init(void)
{
	init_done = TRUE;
}

// How many sectors in a page

void sFLASH_EraseSector(uint32_t SectorAddr)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	// if a page is contained in a sector, mark it as erased, free the data
}

void sFLASH_EraseBulk(void)
{
	if (init_done == FALSE)
		return; // TODO: assert an error

	// mark all pages in list as erased; if not in list, assume it is erased
}

void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	if (init_done == FALSE)
		return; // TODO: assert an error
	
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
	if (init_done == FALSE)
		return; // TODO: assert an error

	// TODO: put in real ID
	return 0xdeadbeef;
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