#ifndef _UEFI_RUNTIME_SERVICES_H_
#define _UEFI_RUNTIME_SERVICES_H_

#include "uefi-data-types.h"

// EFI_RUNTIME_SERVICES (4.5.1)
// https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html?highlight=efi_boot_services#efi-runtime-services

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

// EFI_TABLE_HEADER (4.2.1)
typedef struct 
{   
    UINT64      Signature;
    UINT32      Revision;
    UINT32      HeaderSize;
    UINT32      CRC32;
    UINT32      Reserved;
} EFI_TABLE_HEADER;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef struct {
    UINT16                  Year;               // 1900 - 9999
    UINT8                   Month;              // 1 - 12
    UINT8                   Day;                // 1 - 31
    UINT8                   Hour;               // 0 - 23
    UINT8                   Minute;             // 0 - 59
    UINT8                   Second;             // 0 - 59
    UINT8                   Pad1;
    UINT32                  Nanosecond;         // 0 - 999,999,999
    INT16                   TimeZone;           // --1440 to 1440 or 2047
    UINT8                   Daylight;
    UINT8                   Pad2;
} EFI_TIME;


typedef struct {
    UINT32                          Resolution;             // Provides the reporting resolution of the real-time clock device in counts per second.
    UINT32                          Accuracy;               // Provides the timekeeping accuracy of the real-time clock in an error rate of 1E-6 parts per million.
    BOOLEAN                         SetsToZero;             // If TRUE, the real-time clock device maintains the time fields when the system is in a power-off state.
} EFI_TIME_CAPABILITIES;

// Returns the current time and date information, and the time-keeping capabilities of the hardware platform.
typedef EFI_STATUS (EFIAPI *EFI_GET_TIME) (
    OUT EFI_TIME                    *Time,                  // A pointer to storage to receive a snapshot of the current time.
    OUT EFI_TIME_CAPABILITIES       *Capabilities OPTIONAL  // An optional pointer to a buffer to receive the real time clock device’s capabilities.
);

// Sets the current local time and date information.
typedef EFI_STATUS (EFIAPI *EFI_SET_TIME) (
    IN EFI_TIME                     *Time                   // A pointer to the current time.
);

// Returns the current wakeup alarm clock setting.
typedef EFI_STATUS (EFIAPI *EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN                     *Enabled,               // Indicates if the alarm is currently enabled or disabled.
    OUT BOOLEAN                     *Pending,               // Indicates if the alarm signal is pending and requires acknowledgment.
    OUT EFI_TIME                    *Time                   // The current alarm setting.
);

// Sets the system wakeup alarm clock time.
typedef EFI_STATUS (EFIAPI *EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN                      Enable,                 // Enable or disable the wakeup alarm.
    IN EFI_TIME                     *Time OPTIONAL          // If Enable is TRUE, the time to set the wakeup alarm for. If Enable is FALSE, then this parameter is optional and may be NULL.
);


typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

typedef struct {
    UINT32                          Type;                   // Type of the memory region.
    EFI_PHYSICAL_ADDRESS            PhysicalStart;          // Physical address of the start of the memory region.
    EFI_VIRTUAL_ADDRESS             VirtualStart;           // Virtual address of the start of the memory region.
    UINT64                          NumberOfPages;          // Number of 4 KB pages in the memory region.
    UINT64                          Attribute;              // Attributes of the memory region.
} EFI_MEMORY_DESCRIPTOR;

// Changes the runtime addressing mode of EFI firmware from physical to virtual.
typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
    IN UINTN                        MemoryMapSize,          // The size, in bytes, of the VirtualMap buffer.
    IN UINTN                        DescriptorSize,         // The size, in bytes, of an entry in the VirtualMap buffer.
    IN UINT32                       DescriptorVersion,      // The version of the memory descriptor being passed into the EFI firmware.
    IN EFI_MEMORY_DESCRIPTOR        *VirtualMap             // An array of memory descriptors which contain new virtual address mapping information for all runtime ranges
);

// Determines the new virtual address that is to be used on subsequent memory accesses.
typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER) (
    IN UINTN                        DebugDisposition,       // Supplies type information for the pointer being converted.
    IN VOID                         **Address               // The pointer to a pointer that is to be fixed to be the value needed for the new virtual address mapping being applied.
);

// Returns the value of a variable.
typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE) (
    IN CHAR16                       *VariableName,          // A Null-terminated string that is the name of the vendor’s variable.
    IN EFI_GUID                     *VendorGuid,            // A unique identifier for the vendor.
    OUT UINT32                      *Attributes OPTIONAL,   // If not NULL, a pointer to the memory location to return the attributes bitmask for the variable.
    IN OUT UINTN                    *DataSize,              // On input, the size in bytes of the Data buffer. On output, the size of data returned in Data.
    OUT VOID                        *Data OPTIONAL          // The buffer to return the contents of the variable.
);

// Enumerates the current variable names.
typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)  (
    IN OUT UINTN                    *VariableNameSize,      // The size of the VariableName buffer. The size must be large enough to fit input string supplied in VariableName buffer.
    IN OUT CHAR16                   *VariableName,          // On input, supplies the last VariableName that was returned by * GetNextVariableName(). On output, returns the Null-terminated string of the current variable.
    IN OUT EFI_GUID                 *VendorGuid             // On input, supplies the last VendorGuid that was returned by GetNextVariableName(). On output, returns the VendorGuid of the current variable.
);

// Sets the value of a variable. This service can be used to create a 
// new variable, modify the value of an existing variable, or to delete 
// an existing variable.
typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE) (
    IN CHAR16                       *VariableName,          // A Null-terminated string that is the name of the vendor’s variable. Each VariableName is unique for each VendorGuid. VariableName must contain 1 or more characters
    IN EFI_GUID                     *VendorGuid,            // A unique identifier for the vendor.
    IN UINT32                       Attributes,             // Attributes bitmask to set for the variable.
    IN UINTN                        DataSize,               // The size in bytes of the Data buffer.
    IN VOID                         *Data                   // The contents for the variable.
);  

// Returns the next high 32 bits of the platform’s monotonic counter.
typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT) (
    OUT UINT32                      *HighCount              // Pointer to returned value.
);

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

// Resets the entire platform. If the platform supports 
// See ref:EFI_RESET_NOTIFICATION_PROTOCOL, then prior to completing the reset of the platform, 
// all of the pending notifications must be called.

typedef VOID (EFIAPI *EFI_RESET_SYSTEM) (
    IN EFI_RESET_TYPE               ResetType,              // The type of reset to perform. 
    IN EFI_STATUS                   ResetStatus,            // The status code for the reset. If the platform does not support passing a status code to the ResetSystem() service, then the status code will be ignored.
    IN UINTN                        DataSize,               // The size, in bytes, of ResetData.
    IN VOID                         *ResetData OPTIONAL     // For a ResetType of EfiResetCold, EfiResetWarm, or EfiResetShutdown the data buffer starts with a Null-terminated string, optionally followed by additional binary data. The string is a description that the caller may use to further indicate the reason for the system reset. For a ResetType of EfiResetPlatformSpecific the data buffer also starts with a Null-terminated string that is followed by an EFI_GUID that describes the specific type of reset to perform.
);

typedef struct {
    EFI_GUID                        CapsuleGuid;            // A GUID that defines the contents of a capsule.
    UINT32                          HeaderSize;             // The size of the capsule header. This may be larger than the size of the EFI_CAPSULE_HEADER since CapsuleGuid may imply extended header entries.
    UINT32                          Flags;                  // The Flags[15:0] bits are defined by CapsuleGuid. Flags[31:16] are defined by this specification.
    UINT32                          CapsuleImageSize;       // The size of the capsule image in bytes.
} EFI_CAPSULE_HEADER;

// Passes capsules to the firmware with both virtual and physical 
// mapping. Depending on the intended consumption, the firmware may process 
// the capsule immediately. 
typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE) (
    IN EFI_CAPSULE_HEADER           **CapsuleHeaderArray,       // An array of virtual pointers to the capsules being passed into the firmware. The capsules are consumed by the firmware before the ResetSystem() call returns.
    IN UINTN                        CapsuleCount,               // The number of elements in the CapsuleHeaderArray.
    IN EFI_PHYSICAL_ADDRESS         ScatterGatherList OPTIONAL  // A physical pointer to the scatter/gather list. This parameter is only valid if the CAPSULE_FLAGS_PERSIST_ACROSS_RESET flag is set in the Flags field of the EFI_CAPSULE_HEADER. If this flag is set, then the scatter/gather list describes the mapping of the capsules into physical memory. If this flag is not set, then this parameter must be NULL.
);

// Returns if the capsule can be supported via UpdateCapsule().
typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES) (
    IN EFI_CAPSULE_HEADER           **CapsuleHeaderArray,   // An array of virtual pointers to the capsules being queried. The capsules are consumed by the firmware before the ResetSystem() call returns.
    IN UINTN                        CapsuleCount,           // The number of elements in the CapsuleHeaderArray.
    OUT UINT64                      *MaximumCapsuleSize,    // On output, the maximum size of the capsule that can be supported.
    OUT EFI_RESET_TYPE              *ResetType              // On output, the type of reset required for the capsule update.
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO) (
    IN UINT32                       Attributes,                     // Attributes to return information on.
    OUT UINT64                      *MaximumVariableStorageSize,    // On output, the maximum size of the storage space available for the EFI variables associated with the attributes specified.
    OUT UINT64                      *RemainingVariableStorageSize,  // On output, the remaining size of the storage space available for the EFI variables associated with the attributes specified.   
    OUT UINT64                      *MaximumVariableSize            // On output, the maximum size of an individual EFI variable associated with the attributes specified.
);

typedef struct {
    EFI_TABLE_HEADER                Hdr;

    EFI_GET_TIME                    GetTime;
    EFI_SET_TIME                    SetTime;
    EFI_GET_WAKEUP_TIME             GetWakeupTime;
    EFI_SET_WAKEUP_TIME             SetWakeupTime;

    EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
    EFI_CONVERT_POINTER             ConvertPointer;

    EFI_GET_VARIABLE                GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
    EFI_SET_VARIABLE                SetVariable;

    EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                ResetSystem;

    EFI_UPDATE_CAPSULE              UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;

    EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


//******************************************************
// Variable Attributes
//******************************************************
#define EFI_VARIABLE_NON_VOLATILE                           0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                     0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                         0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                  0x00000008 \
//This attribute is identified by the mnemonic 'HR' elsewhere
//in this specification.
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS             0x00000010
//NOTE: EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS is deprecated
//and should be considered reserved.
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS \0x00000020
#define EFI_VARIABLE_APPEND_WRITE                           0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS          0x00000080
//This attribute indicates that the variable payload begins
//with an EFI_VARIABLE_AUTHENTICATION_3 structure, and
//potentially more structures as indicated by fields of this
//structure. See definition below and in SetVariable().

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000

//******************************************************
// EFI_OPTIONAL_PTR
//******************************************************
#define EFI_OPTIONAL_PTR          0x00000001

#endif // _UEFI_RUNTIME_SERVICES_H_