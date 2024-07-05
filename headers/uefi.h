#ifndef EFI_H
#define EFI_H

#include <stdint.h>
#include <stddef.h>


#include "uefi-data-types.h"
#include "uefi-status-codes.h"
#include "uefi-system-table.h"
#include "uefi-boot-services.h"
#include "uefi-runtime-services.h"


#define TRUE    1
#define FALSE   0

/* EFI_IMAGE_ENTRY_POINT (4.1.1)
This is the main entry point for a UEFI Image. This entry point is the same 
for UEFI applications and UEFI drivers.
*/
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT) (
    IN EFI_HANDLE ImageHandle,              // The firmware allocated handle for the UEFI image.
    IN EFI_SYSTEM_TABLE *SystemTable        // A pointer to the EFI System Table.
);

#endif // EFI_H
