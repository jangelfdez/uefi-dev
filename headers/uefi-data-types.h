#ifndef UEFI_DATA_TYPES_H
#define UEFI_DATA_TYPES_H

#include <stdint.h>

// UEFI Data Types (2.3.1)
// https://uefi.org/specs/UEFI/2.10/02_Overview.html#data-types

// Logical Boolean. 1-byte value containing a 0 for FALSE or a 1 for TRUE.
// Other values are undefined.
typedef uint8_t         BOOLEAN;

// Signed value of native width. 
// (4 bytes on supported 32-bit processor instructions, 
// 8 bytes on supported 64-bit processor instructions, 
// 16 bytes on supported 128-bit processor instructions)
typedef int             INTN;
// Unsigned value of native width.
typedef unsigned int    UINTN;

typedef int8_t          INT8;
typedef int16_t         INT16;
typedef int32_t         INT32;
typedef int64_t         INT64;
//typedef int128_t      INT128;

typedef uint8_t         UINT8;
typedef uint16_t        UINT16; 
typedef uint32_t        UINT32;
typedef uint64_t        UINT64;
//typedef uint128_t     UINT128;

// 1-byte character. Unless otherwise specified, all 1-byte or ASCII characters 
// and strings are stored in 8-bit ASCII encoding format, 
// using the ISO-Latin-1 character set.
typedef char            CHAR8;
// 2-byte Character. Unless otherwise specified all characters and strings 
// are stored in the UCS-2 encoding format as defined by Unicode 2.1 and 
// ISO/IEC 10646 standards.
typedef uint16_t        CHAR16;

// Undeclared type
typedef void            VOID;

// 128-bit buffer containing a unique identifier value. 
// Unless otherwise specified, aligned on a 64-bit boundary.
typedef struct {
  UINT32 Data1;
  UINT16 Data2;
  UINT16 Data3;
  UINT8 Data4[8];
} EFI_GUID;

typedef UINTN           EFI_STATUS;
typedef VOID*           EFI_HANDLE;
typedef VOID*           EFI_EVENT;
typedef UINT64          EFI_LBA;
typedef UINTN           EFI_TL;

// 32-byte buffer containing a network Media Access Control address.
typedef struct {
  INT8 Addr[32];
} EFI_MAC_ADDRESS;
// 4-byte buffer. An IPv4 internet protocol address.
typedef struct {
  INT8 Addr[4];
} EFI_IPV4_ADDRESS;
// 16-byte buffer. An IPv6 internet protocol address.
typedef struct 
{
  INT8 Addr[16];
} EFI_IPV6_ADDRESS;
// 16-byte buffer aligned on a 4-byte boundary. An IPv4 or IPv6 internet protocol address.
typedef struct {
  INT8 Addr[16];
} __attribute__((aligned(4)))  EFI_IP_ADDRESS;


#define IN          // Datum is passed to the function.
#define OUT         // Datum is returned from the function.
#define OPTIONAL    // Passing the datum to the function is optional, and a NULL may be passed if the value is not supplied.
#define CONST const // Datum is read-only.
#define EFIAPI //__attribute__((ms_abi))  // Defines the calling convention for UEFI interfaces.

#endif // UEFI_DATA_TYPES_H