#include "../include/uefi.h"

#define CHARACTER_WIDTH 1
#define FRAME_LEFT_PADDING 1
#define FRAME_RIGHT_PADDING 1
#define FRAME_LEFT_RIGHT_WIDTH 2
#define FRAME_TOP_BOTTOM_WIDTH 1

EFI_HANDLE _ImageHandle;
EFI_SYSTEM_TABLE *_SystemTable;

UINTN console_columns;
UINTN console_rows;

UINTN cursor_column;
UINTN cursor_row;

CHAR16 cursor[2] = {0x2588, 0x0000};
CHAR16 single_frame[2] = {0x2588, 0x0000};
CHAR16 double_frame[3] = {0x2588, 0x2588, 0x0000};

// Function prototypes
void draw_cursor();
void render_background();
void process_key_stroke(EFI_INPUT_KEY key);

/**
 * @file uefi-tele-sketch.c
 * @brief UEFI main function for the tele-sketch example
 *
 * This file contains the UEFI main function for the tele-sketch example.
 *
 * @param ImageHandle The handle to the loaded image
 * @param SystemTable A pointer to the EFI_SYSTEM_TABLE structure
 *
 * @return EFI_STATUS The status of the UEFI main function
 */
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    _ImageHandle = ImageHandle;
    _SystemTable = SystemTable;

    render_background();

    // Define the initial position of the cursor in the middle of the console
    cursor_column = console_columns / 2;
    cursor_row = console_rows / 2;

    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, cursor_column, cursor_row);
    _SystemTable->ConOut->OutputString(_SystemTable->ConOut, cursor);

    EFI_INPUT_KEY key;
    while (TRUE)
    {
        // If there is an error reading the key, continue the loop
        if (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS)
        {
            continue;
        }
        
        process_key_stroke(key);
        draw_cursor();
    }

    return EFI_SUCCESS;
}


/**
 * Renders the background for the tele-sketch application.
 *
 * Selects the colors and provides the drawing frame for the game.
 */
void render_background()
{
    // Configures background and foreground colors
    _SystemTable->ConOut->SetAttribute(_SystemTable->ConOut, EFI_WHITE | EFI_BACKGROUND_RED);
    _SystemTable->ConOut->ClearScreen(_SystemTable->ConOut);

    // Checks the current mode of the console to get the number of columns and rows
    UINTN mode = _SystemTable->ConOut->Mode->Mode;

    EFI_STATUS status = _SystemTable->ConOut->QueryMode(_SystemTable->ConOut, mode, &console_columns, &console_rows);
    if (status != EFI_SUCCESS)
    {
        _SystemTable->ConOut->OutputString(_SystemTable->ConOut, L"QueryMode failed\r\n");
    }

    // Renders the drawing frame
    for (UINTN i = 0; i < console_rows; i++)
    {
        // Left-side drawing frame
        _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, FRAME_LEFT_PADDING, i); // First column is empy
        _SystemTable->ConOut->OutputString(_SystemTable->ConOut, double_frame);

        // Top and bottom drawing frame
        if (i == 0 || i == console_rows - 1)
        {
            for (UINTN j = (FRAME_RIGHT_PADDING + FRAME_LEFT_RIGHT_WIDTH); j < (console_columns - FRAME_LEFT_PADDING); j++)
            {
                _SystemTable->ConOut->OutputString(_SystemTable->ConOut, single_frame);
            }
        }
        else
        {
            // Right-side drawing frame
            _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, console_columns - FRAME_LEFT_PADDING - FRAME_LEFT_RIGHT_WIDTH, i); // Last column is empty
            _SystemTable->ConOut->OutputString(_SystemTable->ConOut, double_frame);
        }
    }
}

/**
 * Process a key stroke and update the cursor position accordingly.
 *
 * @param key The EFI_INPUT_KEY structure representing the key stroke.
 */
void process_key_stroke(EFI_INPUT_KEY key)
{
    switch (key.ScanCode)
    {
    case SCAN_UP:
        if (!(cursor_row == FRAME_TOP_BOTTOM_WIDTH))
        {
            cursor_row--;
        }
        break;
    case SCAN_DOWN:
        if (!(cursor_row == console_rows - FRAME_TOP_BOTTOM_WIDTH - CHARACTER_WIDTH))
        {
            cursor_row++;
        }
        break;
    case SCAN_RIGHT:
        if (!(cursor_column == console_columns - FRAME_LEFT_RIGHT_WIDTH - FRAME_LEFT_PADDING - CHARACTER_WIDTH))
        {
            cursor_column++;
        }
        break;
    case SCAN_LEFT:
        if (!(cursor_column == FRAME_LEFT_RIGHT_WIDTH + CHARACTER_WIDTH))
        {
            cursor_column--;
        }
        break;
    case SCAN_ESCAPE:
        _SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
        return;
    default:
        break;
    }
}

/**
 * Draws the cursor on the screen.
 */
void draw_cursor()
{
    _SystemTable->ConOut->SetAttribute(_SystemTable->ConOut, EFI_WHITE | EFI_BACKGROUND_RED);
    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, cursor_column, cursor_row);
    _SystemTable->ConOut->OutputString(_SystemTable->ConOut, cursor);
}