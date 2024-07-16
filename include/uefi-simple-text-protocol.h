#ifndef _UEFI_SIMPLE_TEXT_PROTOCOL_H_
#define _UEFI_SIMPLE_TEXT_PROTOCOL_H_

#include "uefi-data-types.h"

/* EFI_SIMPLE_TEXT_INPUT_PROTOCOL (12.3.1)
 https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-input-protocol

The Simple Text Input protocol defines the minimum input required to 
support the ConsoleIn device.

This protocol is used to obtain input from the ConsoleIn device. The EFI specification 
requires that the EFI_SIMPLE_TEXT_INPUT_PROTOCOL supports the same languages as the 
corresponding EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
*/

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID {0x387477c1,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct {
 UINT16                             ScanCode;
 CHAR16                             UnicodeChar;
} EFI_INPUT_KEY;

// Resets the input device hardware. 
typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET) (  
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL     *This,                    // A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL instance
    IN BOOLEAN                            ExtendedVerification      // Indicates that the driver may perform a more exhaustive verification operation of the device during reset.
);

// Reads the next keystroke from the input device.
typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY) (
 IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL       *This,            // A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL instance
 OUT EFI_INPUT_KEY                        *Key              // A pointer to a buffer that is filled in with the keystroke state data for the key that was pressed.
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET                       Reset;            // Reset the ConsoleIn device, EFI_SIMPLE_TEXT_INPUT_PROTOCOL.Reset() .
    EFI_INPUT_READ_KEY                    ReadKeyStroke;    // Returns the next input character, EFI_SIMPLE_TEXT_INPUT_PROTOCOL.ReadKeyStroke() .
    EFI_EVENT                             WaitForKey;       // Event to use with EFI_BOOT_SERVICES.WaitForEvent() to wait for a key to be available.
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


/* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL (12.4.1)
https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol

This protocol is used to control text-based output devices.

The Simple Text Output protocol defines the minimum requirements for a text-based ConsoleOut device. 
The EFI specification requires that the EFI_SIMPLE_TEXT_INPUT_PROTOCOL support the same languages as the 
corresponding EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
*/

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID {0x387477c2,0x69c7,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// Resets the text output device hardware.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL           *This,                 // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN BOOLEAN                                   ExtendedVerification   // Indicates that the driver may perform a more exhaustive verification operation of the device during reset.
);

// Writes a string to the output device.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING) (  
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN CHAR16                                   *String                 // The NULL-terminated string to be displayed on the output device(s).
);

// Verifies that all characters in a string can be output to the target device.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN CHAR16                                   *String                 // The NULL-terminated string to be examined for the output device(s).
);

// Returns information for an available text mode that the output device(s) supports.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN UINTN                                    ModeNumber,             // The mode number to return information on.
    OUT UINTN                                   *Columns,               // Returns information for an available text mode that the output device(s) supports.
    OUT UINTN                                   *Rows
);

// Sets the output device(s) to a specified mode.
typedef EFI_STATUS  (EFIAPI *EFI_TEXT_SET_MODE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN UINTN                                    ModeNumber              // The mode number to set.
);

// Sets the background and foreground colors for the OutputString()
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN UINTN                                    Attribute               // The attribute to set. Bits 0-3 are the foreground color, and bits 4-6 are the background color. All other bits are reserved.
);

// Clears the output device(s) display to the currently selected background color.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL           *This                  // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
);

// Sets the current coordinates of the cursor position.
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL           *This,                 // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance.
    IN UINTN                                     Column,                // The position to set the cursor to. Must greater than or equal to zero and less than                                                                        
    IN UINTN                                     Row                    // the number of columns and rows returned by EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode() .
 );

typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL           *This,
    IN BOOLEAN                                   Visible                // Makes the cursor visible or invisible.
);

/* The following data values in the SIMPLE_TEXT_OUTPUT_MODE interface are read-only 
and are changed by using the appropriate interface functions
*/
typedef struct {
    INT32                              MaxMode;                     // The maximum mode number supported by QueryMode() and SetMode().
    INT32                              Mode;                        // The text mode of the output device(s).
    INT32                              Attribute;                   // The current character output attribute.
    INT32                              CursorColumn;                // The cursor's column position.
    INT32                              CursorRow;                   // The cursor's row position.
    BOOLEAN                            CursorVisible;               // TRUE if the cursor is visible, FALSE otherwise.
} SIMPLE_TEXT_OUTPUT_MODE;


typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                           Reset;                // Reset the ConsoleOut device. EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Reset() .
    EFI_TEXT_STRING                          OutputString;          // Displays a string on the ConsoleOut device, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString() .
    EFI_TEXT_TEST_STRING                     TestString;            // Tests to see if the ConsoleOut device supports this string. See TestString() EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.TestString() .
    EFI_TEXT_QUERY_MODE                      QueryMode;             // Queries information concerning the output devices's supported text mode(s), EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode() .
    EFI_TEXT_SET_MODE                        SetMode;               // Sets the current mode of the output device. EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode() .
    EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;          // Sets the foreground and background color of the text that is output. EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute() .
    EFI_TEXT_CLEAR_SCREEN                    ClearScreen;           // Clears the screen with the currently set background color. See ClearScreen() EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.ClearScreen().
    EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;     // Sets the current cursor position. See SetCursorPosition() EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition() .
    EFI_TEXT_ENABLE_CURSOR                   EnableCursor;          // Turns the visibility of the cursor on/off. See EnableCursor() EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor() .
    SIMPLE_TEXT_OUTPUT_MODE                  *Mode;                 // Pointer to SIMPLE_TEXT_OUTPUT_MODE data. Type SIMPLE_TEXT_OUTPUT_MODE is defined in “Related Definitions” below.
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

//******************************************************
// EFI SCAN CODES for EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//******************************************************
#define SCAN_NULL                         0x00
#define SCAN_UP                           0x01
#define SCAN_DOWN                         0x02
#define SCAN_RIGHT                        0x03
#define SCAN_LEFT                         0x04
#define SCAN_HOME                         0x05
#define SCAN_END                          0x06
#define SCAN_INSERT                       0x07
#define SCAN_DELETE                       0x08
#define SCAN_PAGE_UP                      0x09
#define SCAN_PAGE_DOWN                    0x0A
#define SCAN_F1                           0x0B
#define SCAN_F2                           0x0C
#define SCAN_F3                           0x0D
#define SCAN_F4                           0x0E
#define SCAN_F5                           0x0F
#define SCAN_F6                           0x10
#define SCAN_F7                           0x11
#define SCAN_F8                           0x12
#define SCAN_F9                           0x13
#define SCAN_F10                          0x14
#define SCAN_ESCAPE                       0x17

//******************************************************
// EFI SCAN CODES for EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
//******************************************************
#define SCAN_F11                          0x15
#define SCAN_F12                          0x16
#define SCAN_PAUSE                        0x48
#define SCAN_F13                          0x68
#define SCAN_F14                          0x69
#define SCAN_F15                          0x6A
#define SCAN_F16                          0x6B
#define SCAN_F17                          0x6C
#define SCAN_F18                          0x6D
#define SCAN_F19                          0x6E
#define SCAN_F20                          0x6F
#define SCAN_F21                          0x70
#define SCAN_F22                          0x71
#define SCAN_F23                          0x72
#define SCAN_F24                          0x73
#define SCAN_MUTED                        0x7F
#define SCAN_VOLUME_UP                    0x80
#define SCAN_VOLUME_DOWN                  0x81
#define SCAN_BRIGHTNESS_UP                0x100
#define SCAN_BRIGHTNESS_DOWN              0x101
#define SCAN_SUSPEND                      0x102
#define SCAN_HIBERNATE                    0x103
#define SCAN_TOGGLE_DISPLAY               0x104
#define SCAN_RECOVERY                     0x105
#define SCAN_EJECT                        0x106

//******************************************************
// UNICODE DRAWING CHARACTERS
//******************************************************
#define BOXDRAW_HORIZONTAL                 0x2500
#define BOXDRAW_VERTICAL                   0x2502
#define BOXDRAW_DOWN_RIGHT                 0x250c
#define BOXDRAW_DOWN_LEFT                  0x2510
#define BOXDRAW_UP_RIGHT                   0x2514
#define BOXDRAW_UP_LEFT                    0x2518
#define BOXDRAW_VERTICAL_RIGHT             0x251c
#define BOXDRAW_VERTICAL_LEFT              0x2524
#define BOXDRAW_DOWN_HORIZONTAL            0x252c
#define BOXDRAW_UP_HORIZONTAL              0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL        0x253c
    
#define BOXDRAW_DOUBLE_HORIZONTAL          0x2550
#define BOXDRAW_DOUBLE_VERTICAL            0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE          0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT          0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT          0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE           0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT           0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT           0x2557
    
#define BOXDRAW_UP_RIGHT_DOUBLE            0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT            0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT            0x255a
#define BOXDRAW_UP_LEFT_DOUBLE             0x255b
#define BOXDRAW_UP_DOUBLE_LEFT             0x255c
#define BOXDRAW_DOUBLE_UP_LEFT             0x255d
    
#define BOXDRAW_VERTICAL_RIGHT_DOUBLE      0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT      0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT      0x2560
    
#define BOXDRAW_VERTICAL_LEFT_DOUBLE       0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT       0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT       0x2563
    
#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE     0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL     0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL     0x2566
    
#define BOXDRAW_UP_HORIZONTAL_DOUBLE       0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL       0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL       0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

//******************************************************
// EFI Required Block Elements Code Chart
//******************************************************

#define BLOCKELEMENT_FULL_BLOCK            0x2588
#define BLOCKELEMENT_LIGHT_SHADE           0x2591

//******************************************************
// EFI Required Geometric Shapes Code Chart
//******************************************************

#define GEOMETRICSHAPE_UP_TRIANGLE         0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE      0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE       0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE       0x25c4

//******************************************************
// EFI Required Arrow shapes
//******************************************************

#define ARROW_UP                           0x2191
#define ARROW_DOWN                         0x2193

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK                              0x00
#define EFI_BLUE                               0x01
#define EFI_GREEN                              0x02
#define EFI_CYAN                               0x03
#define EFI_RED                                0x04
#define EFI_MAGENTA                            0x05
#define EFI_BROWN                              0x06
#define EFI_LIGHTGRAY                          0x07
#define EFI_BRIGHT                             0x08
#define EFI_DARKGRAY                           0x08
#define EFI_LIGHTBLUE                          0x09
#define EFI_LIGHTGREEN                         0x0A
#define EFI_LIGHTCYAN                          0x0B
#define EFI_LIGHTRED                           0x0C
#define EFI_LIGHTMAGENTA                       0x0D
#define EFI_YELLOW                             0x0E
#define EFI_WHITE                              0x0F


#define EFI_BACKGROUND_BLACK                   0x00
#define EFI_BACKGROUND_BLUE                    0x10
#define EFI_BACKGROUND_GREEN                   0x20
#define EFI_BACKGROUND_CYAN                    0x30
#define EFI_BACKGROUND_RED                     0x40
#define EFI_BACKGROUND_MAGENTA                 0x50
#define EFI_BACKGROUND_BROWN                   0x60
#define EFI_BACKGROUND_LIGHTGRAY               0x70

/*
Macro to accept color values in their raw form to create a value that represents both 
a foreground and background color in a single byte.
For Foreground, and EFI_\* value is valid from EFI_BLACK(0x00) to EFI_WHITE (0x0F).
For Background, only EFI_BLACK, EFI_BLUE, EFI_GREEN, EFI_CYAN, EFI_RED, 
EFI_MAGENTA, EFI_BROWN, and EFI_LIGHTGRAY
are acceptable.

Do not use EFI_BACKGROUND_xxx values with this macro.
*/
#define EFI_TEXT_ATTR(Foreground,Background) ((Foreground) | ((Background) << 4))

#endif // _UEFI_SIMPLE_TEXT_PROTOCOL_H_