#include "headers/uefi.h"

EFI_HANDLE _ImageHandle;
EFI_SYSTEM_TABLE *_SystemTable;

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    _ImageHandle = ImageHandle;
    _SystemTable = SystemTable;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

    UINTN columns = 0;
    UINTN rows = 0;
    
    UINTN mode = (UINTN) _SystemTable->ConOut->Mode->Mode;

    EFI_STATUS status = _SystemTable->ConOut->QueryMode(_SystemTable->ConOut, mode, &columns, &rows);
    if (status != EFI_SUCCESS) {

            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"QueryMode failed\r\n");
    }
    
    EFI_INPUT_KEY key;
    while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS)
    {
    }

    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);

    return EFI_SUCCESS;
}