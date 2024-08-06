#ifndef UEFI_PROTOCOLS_IMAGE_LOADER_H
#define UEFI_PROTOCOLS_IMAGE_LOADER_H

#include "uefi-data-types.h"
#include "uefi-system-table.h"

/* EFI Loaded Image Protocol (9.1)
 https://uefi.org/specs/UEFI/2.10/09_Protocols_EFI_Loaded_Image.html#efi-loaded-image-protocol

 This protocol describe an Image that has been loaded into memory and specifies 
 the device path used when a PE/COFF image was loaded through the EFI Boot Service LoadImage(). 
 These descriptions include the source from which the image was loaded, the current location 
 of the image in memory, the type of memory allocated for the image, and the parameters passed 
 to the image when it was invoked.
*/

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
  {0x5B1B31A1,0x9562,0x11d2,\
    {0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}}

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
   {0xbc62157e,0x3e33,0x4fec,\
  {0x99,0x20,0x2d,0x3b,0x36,0xd7,0x50,0xdf}}

// Unloads an image from memory.
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE               ImageHandle         // The image handle of the image to unload.
);

typedef struct {
   UINT32                        Revision;          // Defines the revision of the EFI_LOADED_IMAGE_PROTOCOL structure. All future revisions will be backward compatible to the current revision.
   EFI_HANDLE                    ParentHandle;      // Parent image’s image handle. NULL if the image is loaded directly from the firmware’s boot manager. 
   EFI_SYSTEM_TABLE              *SystemTable;      // The image’s EFI system table pointer. 

   // Source location of the image
   EFI_HANDLE                    DeviceHandle;      // The device handle that the image was loaded from.
   EFI_DEVICE_PATH_PROTOCOL      *FilePath;         // A pointer to the file path portion of DeviceHandle that the image was loaded from.
   VOID                          *Reserved;         // Reserved. Do not use.

   // Image’s load options
   UINT32                        LoadOptionsSize;   // The size in bytes of LoadOptions.
   VOID                          *LoadOptions;      // A pointer to the image’s binary load options.

   // Location where image was loaded
   VOID                          *ImageBase;        // The base address at which the image was loaded.
   UINT64                        ImageSize;         // The size in bytes of the loaded image.
   EFI_MEMORY_TYPE               ImageCodeType;     // The memory type that the code sections were loaded as.
   EFI_MEMORY_TYPE               ImageDataType;     // The memory type that the data sections were loaded as.
   EFI_IMAGE_UNLOAD              Unload;            // Unload() is a pointer to the image’s unload function.
} EFI_LOADED_IMAGE_PROTOCOL;

#endif // UEFI_PROTOCOLS_IMAGE_LOADER_H