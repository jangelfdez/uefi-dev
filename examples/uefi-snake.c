#include "../include/uefi.h"
#include <stdlib.h>

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

EFI_EVENT refresh_screen_event;

/**
 *  Implementation of the snake as a double linked list
 */

// Snake direction
typedef struct _snake_direction
{
    INTN x;
    INTN y;
} _snake_direction;

// Define the snake node structure
typedef struct _snake_node
{
    UINTN x;
    UINTN y;
    struct _snake_node *next;
    struct _snake_node *prev;
} _snake_node;

// Define the snake structure
typedef struct _snake
{
    _snake_node *head;
    _snake_node *tail;
    UINTN length;
} _snake;

_snake snake;
_snake_direction direction = {1, 0};

// Function prototypes
void render_background();
void refresh_screen();
void add_snake_node(_snake *snake, UINTN x, UINTN y);
void process_key_stroke(EFI_INPUT_KEY key);
void game_over();

/**
 * @file uefi-snake.c
 * @brief UEFI Snake Example
 *
 * This file contains the entry point function `efi_main` for the UEFI Snake Example.
 * It is called by the UEFI firmware when the application is loaded.
 *
 * @param ImageHandle The handle to the loaded image.
 * @param SystemTable A pointer to the EFI_SYSTEM_TABLE structure.
 * @return EFI_STATUS The status code returned by the entry point function.
 */
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    _ImageHandle = ImageHandle;
    _SystemTable = SystemTable;

    render_background();

    snake.head = NULL;
    snake.tail = NULL;
    snake.length = 0;

    // Define the initial position of the snake in the middle of the console
    add_snake_node(&snake, console_columns / 2, console_rows / 2);

    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, console_columns / 2 + 1, console_rows / 2);

    // Configure the event to be notified to refresh the game screen
    SystemTable->BootServices->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                                           TPL_CALLBACK,
                                           refresh_screen,
                                           NULL,
                                           &refresh_screen_event);

    // Set the timer to refresh the cursor every 500ms
    SystemTable->BootServices->SetTimer(refresh_screen_event, TimerPeriodic, 900000);

    EFI_INPUT_KEY key;
    while (TRUE)
    {
        // If there is an error reading the key, continue the loop
        if (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS)
        {
            continue;
        }

        process_key_stroke(key);
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
            direction.x = 0;
            direction.y = -1;
        }
        break;
    case SCAN_DOWN:
        if (!(cursor_row == console_rows - FRAME_TOP_BOTTOM_WIDTH - CHARACTER_WIDTH))
        {
            direction.x = 0;
            direction.y = 1;
        }
        break;
    case SCAN_RIGHT:
        if (!(cursor_column == console_columns - FRAME_LEFT_RIGHT_WIDTH - FRAME_LEFT_PADDING - CHARACTER_WIDTH))
        {
            direction.x = 1;
            direction.y = 0;
        }
        break;
    case SCAN_LEFT:
        if (!(cursor_column == FRAME_LEFT_RIGHT_WIDTH + CHARACTER_WIDTH))
        {
            direction.x = -1;
            direction.y = 0;
        }
        break;
    case SCAN_ESCAPE:
        _SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
        return;
    case SCAN_F1:
        game_over();
        break;
    default:
        break;
    }
}

// Add a new node to the snake
void add_snake_node(_snake *snake, UINTN x, UINTN y)
{
    _snake_node *new_node = NULL;

    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (snake->head == NULL)
    {
        snake->head = new_node;
        snake->tail = new_node;
    }
    else
    {
        snake->tail->next = new_node;
        new_node->prev = snake->tail;
        snake->tail = new_node;
    }

    snake->length++;
}

void refresh_screen(EFI_EVENT event __attribute__((unused)), void *context __attribute__((unused)))
{

    // Clean the snake tail position
    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, snake.tail->x, snake.tail->y);
    _SystemTable->ConOut->OutputString(_SystemTable->ConOut, u" ");

    // Move the snake into the direction selected by the user
    snake.head->x += direction.x;
    snake.head->y += direction.y;

    if (snake.head->y == FRAME_TOP_BOTTOM_WIDTH || 
        snake.head->y == console_rows - FRAME_TOP_BOTTOM_WIDTH - CHARACTER_WIDTH || 
        snake.head->x == FRAME_LEFT_RIGHT_WIDTH + CHARACTER_WIDTH ||
        snake.head->x == console_columns - FRAME_LEFT_RIGHT_WIDTH - FRAME_LEFT_PADDING - CHARACTER_WIDTH)
    {
        game_over();
    }

    // Render the snake head position
    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, snake.head->x, snake.head->y);
    _SystemTable->ConOut->OutputString(_SystemTable->ConOut, cursor);
}

void game_over()
{
    // Disable the timer to stop rendering the snake
    _SystemTable->BootServices->SetTimer(refresh_screen_event, TimerCancel, 0);
    
    // Show the Game Over message
    _SystemTable->ConOut->SetAttribute(_SystemTable->ConOut, EFI_WHITE | EFI_BACKGROUND_BLACK);
    _SystemTable->ConOut->ClearScreen(_SystemTable->ConOut);

    _SystemTable->ConOut->SetCursorPosition(_SystemTable->ConOut, console_columns / 2, console_rows / 2);
    _SystemTable->ConOut->OutputString(_SystemTable->ConOut, u"Game Over!");
}