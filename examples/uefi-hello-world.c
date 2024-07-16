#include "../include/uefi.h"

/**
 * Entry point for the UEFI application.
 * 
 * This function serves as the entry point for the UEFI application. It clears the screen,
 * waits for a key stroke, and then shuts down the system.
 * 
 * @param ImageHandle Handle to the loaded image.
 * @param SystemTable Pointer to the EFI System Table.
 * 
 * @return EFI_STATUS Returns EFI_SUCCESS upon successful completion.
 */
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    // Avoids warning: unused parameter ‘ImageHandle’ [-Werror=unused-parameter]
    (void) ImageHandle;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\r\n");

    EFI_INPUT_KEY key;
    while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS){

    }

    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);  

    return EFI_SUCCESS;
}