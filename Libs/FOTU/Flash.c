/*
 * Flash.c
 *
 *  Created on: Nov 1, 2021
 *      Author: janoko
 */

#include "Flash_conf.h"
#include "Flash.h"


static uint32_t getSector(uint32_t);
const uint32_t listOfAddrSector[FLASH_NUM_OF_SECTORS] = {
    FLASH_START_ADDR_SECTOR_0,
    FLASH_START_ADDR_SECTOR_1,
    FLASH_START_ADDR_SECTOR_2,
    FLASH_START_ADDR_SECTOR_3,
    FLASH_START_ADDR_SECTOR_4,
    FLASH_START_ADDR_SECTOR_5,
    FLASH_START_ADDR_SECTOR_6,
    FLASH_START_ADDR_SECTOR_7
};


uint32_t Flash_Write(uint32_t address, uint32_t *data, uint16_t numberOfWords)
{
  int sofar = 0;

  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR |
                         FLASH_FLAG_PGSERR);

  while (sofar < numberOfWords)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data[sofar]) == HAL_OK)
    {
      address += 4;  // use StartPageAddress += 2 for half word and 8 for double word
      sofar++;
    }
    else
    {
      /* Error occurred while writing data in Flash memory*/
      return HAL_FLASH_GetError ();
    }
  }

  HAL_FLASH_Lock();
  return 0;
}

uint32_t Flash_Erase(uint32_t startSectorAddress, uint16_t numberOfWords)
{
  static FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t SECTORError;

  HAL_FLASH_Unlock();
  /* Erase the user Flash area */

  /* Get the number of sector to erase from 1st sector */
  uint32_t StartSector = getSector(startSectorAddress);
  uint32_t EndSectorAddress = startSectorAddress + ((uint32_t)numberOfWords)*4;
  uint32_t EndSector = getSector(EndSectorAddress);

  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector        = StartSector;
  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
  {
    return HAL_FLASH_GetError ();
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();
  return 0;
}

static uint32_t getSector(uint32_t address)
{

  uint32_t sector = FLASH_SECTOR_0;

  for(uint8_t i = 1; i < FLASH_NUM_OF_SECTORS; i++){
    if(address < listOfAddrSector[i]){
      break;
    }
    sector = (uint32_t) i;
  }

  return (sector);
}
