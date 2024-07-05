#include "headers/uefi.h"


EFI_HANDLE _ImageHandle;
EFI_SYSTEM_TABLE *_SystemTable;

EFI_EVENT refresh_cursor_event;

void refresh_cursor (EFI_EVENT event __attribute__((unused)), void *context __attribute__((unused))) {
    _SystemTable->ConOut->EnableCursor(_SystemTable->ConOut, !_SystemTable->ConOut->Mode->CursorVisible); 
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    _ImageHandle = ImageHandle;
    _SystemTable = SystemTable;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

    // Configure the event to be notified to refresh the cursor
    SystemTable->BootServices->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, 
                                         TPL_CALLBACK, 
                                         refresh_cursor, 
                                         NULL, 
                                         &refresh_cursor_event);

    // Set the timer to refresh the cursor every 500ms
    SystemTable->BootServices->SetTimer(refresh_cursor_event, TimerPeriodic, 3000000);

    EFI_INPUT_KEY key;
    while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS){

    }

    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);  

    return EFI_SUCCESS;
}