#ifndef UEFI_SYSTEM_TABLE_H
#define UEFI_SYSTEM_TABLE_H

#include "uefi-simple-text-protocol.h"
#include "uefi-boot-services.h"
#include "uefi-runtime-services.h"


/* EFI_SYSTEM_TABLE (4.3.1)
UEFI uses the EFI System Table, which contains pointers to the 
runtime and boot services tables.  Except for the table header, 
all elements in the service tables are pointers to functions as 
defined in Services — Boot Services and Services — Runtime Services . 

Prior to a call to EFI_BOOT_SERVICES.ExitBootServices() , all of 
the fields of the EFI System Table are valid. After an operating 
system has taken control of the platform with a call to ExitBootServices() ,
only the Hdr , FirmwareVendor , FirmwareRevision , RuntimeServices , 
NumberOfTableEntries , and ConfigurationTable fields are valid.

https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html#id6
*/

#define EFI_SYSTEM_TABLE_SIGNATURE          0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION     ((2<<16) | (100))
#define EFI_SYSTEM_TABLE_REVISION           EFI_2_100_SYSTEM_TABLE_REVISION
#define EFI_SPECIFICATION_VERSION           EFI_SYSTEM_TABLE_REVISION


/* The EFI Configuration Table is the ConfigurationTable field in the EFI System Table. 
This table contains a set of GUID/pointer pairs. Each element of this table is described 
by the EFI_CONFIGURATION_TABLE structure below. The number of types of configuration tables 
is expected to grow over time. This is why a GUID is used to identify the configuration table type. 
The EFI Configuration Table may contain at most once instance of each table type.
*/
typedef struct{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;


typedef struct {
    /* The table header for the EFI System Table. This header contains the 
    EFI_SYSTEM_TABLE_SIGNATURE and EFI_SYSTEM_TABLE_REVISION values along 
    with the size of the EFI_SYSTEM_TABLE structure and a 32-bit CRC to 
    verify that the contents of the EFI System Table are valid. */
    EFI_TABLE_HEADER Hdr;
    /* A pointer to a null-terminated string that identifies the vendor that
    produces the system firmware for the platform. */
    CHAR16 *FirmwareVendor;
    /* A firmware vendor specific value that identifies the revision of the
    system firmware for the platform.*/
    UINT32 FirmwareRevision;
    /* The handle for the active console input device. This handle must support
    the EFI_SIMPLE_TEXT_INPUT_PROTOCOL and EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
    If there is no active console, these protocols must still be present. */
    EFI_HANDLE ConsoleInHandle;
    /* A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL interface that is 
    associated with ConsoleInHandle.*/
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    /* The handle for the active console output device. This handle must support 
    the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL. If there is no active console, this protocol
    must still be present. */
    EFI_HANDLE ConsoleOutHandle;
    /* A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface that is associated
    with ConsoleOutHandle. */
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    /* The handle for the active standard error console device. This handle must support 
    the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL. If there is no active console, this protocol
    must still be present.*/
    EFI_HANDLE StandardErrorHandle;
    /* A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface that is associated
    with StandardErrorHandle. */
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    /* A pointer to the EFI Runtime Services Table. */
    EFI_RUNTIME_SERVICES *RuntimeServices;
    /* A pointer to the EFI Boot Services Table */
    EFI_BOOT_SERVICES *BootServices;
    /* The number of system configuration tables in the buffer ConfigurationTable.*/
    UINTN NumberOfTableEntries;
    /* A pointer to the system configuration tables. The number of entries in the table 
    is NumberOfTableEntries. */
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;


#endif // UEFI_SYSTEM_TABLE_H