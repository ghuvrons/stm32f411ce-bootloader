/*
 * debug_by_usb_otg.c
 *
 *  Created on: Oct 29, 2021
 *      Author: janoko
 */

#include <stdio.h>
#include "usbd_cdc_if.h"

void _write(int fd, char* ptr, int len)
{
    if(len) CDC_Transmit_FS((uint8_t *) ptr, len);
}
