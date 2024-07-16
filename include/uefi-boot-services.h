#ifndef _UEFI_BOOT_SERVICES_H_
#define _UEFI_BOOT_SERVICES_H_

#include "uefi-runtime-services.h"

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef UINTN EFI_TPL;

// Raises a task’s priority level and returns its previous level.
typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL) (
    IN EFI_TPL                          NewTpl                      // The new task priority level. It must be greater than or equal to the current task priority level. See “Related Definitions.”  
);

// Restores a task’s priority level to its previous value.
typedef VOID (EFIAPI *EFI_RESTORE_TPL) (
    IN EFI_TPL                          OldTpl                      // The previous task priority level to restore (the value from a previous, matching call to EFI_BOOT_SERVICES.RaiseTPL() .
);

typedef enum {
    AllocateAnyPages,                   // Allocate any available range of pages that satisfies the request. On input, the address pointed to by Memory is ignored.
    AllocateMaxAddress,                 // Allocate any available range of pages whose uppermost address is less than or equal to the address pointed to by Memory on input.
    AllocateAddress,                    // Allocate any available range of pages whose uppermost address is less than or equal to the address pointed to by Memory on input.
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
    EfiReservedMemoryType,              // Not usable
    EfiLoaderCode,                      // The UEFI OS Loader and/or OS may use this memory as they see fit.
    EfiLoaderData,                      // The Loader and/or OS may use this memory as they see fit
    EfiBootServicesCode,                // Memory available for general use.
    EfiBootServicesData,                // Memory available for general use.
    EfiRuntimeServicesCode,             // The memory in this range is to be preserved by the UEFI OS loader and OS in the working and ACPI S1-S3 states.
    EfiRuntimeServicesData,             // The memory in this range is to be preserved by the UEFI OS l loader and OS in the working and ACPI S1-S3 states.
    EfiConventionalMemory,              // Memory available for general use.
    EfiUnusableMemory,                  // Memory that contains errors and is not to be used.
    EfiACPIReclaimMemory,               // This memory is to be preserved by the UEFI OS loader and OS until ACPI is enabled. Once ACPI is enabled, the memory in this range is available for general use.
    EfiACPIMemoryNVS,                   // This memory is to be preserved by the UEFI OS loader and OS in the working and ACPI S1-S3 states.
    EfiMemoryMappedIO,                  // This memory is not used by the OS. All system memory-mapped IO information should come from ACPI tables.
    EfiMemoryMappedIOPortSpace,         // This memory is not used by the OS. All system memory-mapped IO port space information should come from ACPI tables.
    EfiPalCode,                         // This memory is to be preserved by the UEFI OS loader and OS in the working and ACPI S1-S4 states. This memory may also have other attributes that are defined by the processor implementation.
    EfiPersistentMemory,                // A memory region that operates as EfiConventionalMemory. However, it happens to also support byte-addressable non-volatility.
    EfiUnacceptedMemoryType,            // A memory region that represents unaccepted memory, that must be accepted by the boot target before it can be used. Unless otherwise noted, all other EFI memory types are accepted. For platforms that support unaccepted memory, all unaccepted valid memory will be reported as unaccepted in the memory map. Unreported physical address ranges must be treated as not-present memory.
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

// Allocates memory pages from the system.
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES) (
    IN EFI_ALLOCATE_TYPE                Type,                       // The type of allocation to perform
    IN EFI_MEMORY_TYPE                  MemoryType,                 // The type of memory to allocate
    IN UINTN                            Pages,                      // The number of contiguous 4 KB pages to allocate
    IN OUT EFI_PHYSICAL_ADDRESS         *Memory                     // A pointer to store the base address of the allocated range of pages
);      

// Frees memory pages.      
typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES) (       
    IN EFI_PHYSICAL_ADDRESS             Memory,                     // The base physical address of the pages to be freed.
    IN UINTN                            Pages                       // The number of contiguous 4 KiB pages to free.
);      

// Returns the current memory map.      
typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP) (       
    IN OUT UINTN *MemoryMapSize,                                    // On input, the size in bytes of the MemoryMap buffer. On output, the size in bytes of the MemoryMap buffer that was required for the memory map.
    OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,                           // A pointer to the buffer  in which firmware places the current memory map. 
    OUT UINTN *MapKey,                                              // A pointer to the location in which firmware returns the key for the current memory map.
    OUT UINTN *DescriptorSize,                                      // A pointer to the location in which firmware returns the size, in bytes, of an individual EFI_MEMORY_DESCRIPTOR.
    OUT UINT32 *DescriptorVersion                                   // A pointer to the location in which firmware returns the version number associated with the EFI_MEMORY_DESCRIPTOR.
);      

// Allocates pool memory.       
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL) (        
    IN EFI_MEMORY_TYPE                  PoolType,                   // The type of pool memory to allocate
    IN UINTN                            Size,                       // The number of bytes to allocate from the pool
    OUT VOID                            **Buffer                    // A pointer to a pointer to the allocated buffer if the call succeeds; undefined otherwise
);

// Returns pool memory to the system.
typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL) (
    IN VOID                             *Buffer                     // Pointer to the buffer to free.
);


typedef VOID (EFIAPI *EFI_EVENT_NOTIFY) (
    IN EFI_EVENT                        Event,                      // Event whose notification function is being invoked.
    IN VOID                             *Context                    // Pointer to the notification function’s context, which is implementation-dependent. Context corresponds to NotifyContext in EFI_BOOT_SERVICES.CreateEventEx() .
);

// Creates an event
typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT) (
    IN UINT32                           Type,                       // The type of event to create and its mode and attributes
    IN EFI_TPL                          NotifyTpl,                  // The task priority level of the event notifications
    IN EFI_EVENT_NOTIFY                 NotifyFunction, OPTIONAL    // The pointer to the event's notification function
    IN VOID                             *NotifyContext, OPTIONAL    // The pointer to the notification function's context; corresponds to the Context parameter of the notification function
    OUT EFI_EVENT                       *Event                      // The pointer to the newly created event if the call succeds; undefined otherwise
);

typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

// Sets the type of timer and the trigger time for a timer event.
typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER) (
    IN EFI_EVENT                        Event,                      // The timer event that is to be signaled at the specified time
    IN EFI_TIMER_DELAY                  Type,                       // The type of time that is specified in TriggerTime
    IN UINT64                           TriggerTime                 // The number of 100 ns units until the timer expires
);

// Stops execution until an event is signaled.
typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT) (
    IN UINTN                            NumberOfEvents,             // The number of events in the Event array
    IN EFI_EVENT                        *Event,                     // An array of EFI_EVENT.
    OUT UINTN                           *Index                      // Pointer to the index of the event which satisfied the wait condition.
);

// Signals an event.
typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT) (
    IN EFI_EVENT                        Event                       // The event to signal
);

// Closes an event.
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT) (
    IN EFI_EVENT                        Event                       // The event to close
);

// Signals an event.
typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT) (
    IN EFI_EVENT                        Event                       // The event to check
);

typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;


// Installs a protocol interface on a device handle. If the handle does not exist, 
// it is created and added to the list of handles in the system.
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
    IN OUT EFI_HANDLE                   *Handle,                    // A pointer to the EFI_HANDLE on which the interface is to be installed.
    IN EFI_GUID                         *Protocol,                  // The GUID of the protocol.
    IN EFI_INTERFACE_TYPE               InterfaceType,              // Indicates whether Interface is supplied in native form.
    IN VOID                             *Interface                  // A pointer to the protocol interface.
);

// Reinstalls a protocol interface on a device handle.
typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE                       Handle,                     // The handle on which the interface is to be reinstalled.
    IN EFI_GUID                         *Protocol,                  // The GUID of the protocol.
    IN VOID                             *OldInterface,              // A pointer to the old interface.
    IN VOID                             *NewInterface               // A pointer to the new interface.
);

// Removes a protocol interface from a device handle.
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE                       Handle,                     // The handle on which the interface was installed
    IN EFI_GUID                         *Protocol,                  // The GUID of the protocol.
    IN VOID                             *Interface                  // A pointer to the protocol interface.
);

// Queries a handle to determine if it supports a specified protocol.
typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL) (
    IN EFI_HANDLE                       Handle,                     // The handle being queried.
    IN EFI_GUID                         *Protocol,                  // The protocol ID being looked for.
    OUT VOID                            **Interface                 // Supplies the address where a pointer to the corresponding Protocol Interface is returned
);

// Creates an event that is to be signaled whenever an interface is installed for a specified protocol.
typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
    IN EFI_GUID                         *Protocol,                  // The GUID of the protocol.
    IN EFI_EVENT                        Event,                      // The event to signal when a protocol interface is installed for Protocol.
    OUT VOID                            **Registration              // A pointer to a memory location to receive the registration value
);

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

// Returns an array of handles that support a specified protocol.
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE) (
    IN EFI_LOCATE_SEARCH_TYPE           SearchType,                 // Specifies which handle(s) are to be returned
    IN EFI_GUID                         *Protocol OPTIONAL,         // Specifies the protocol to search by
    IN VOID                             *SearchKey OPTIONAL,        // Specifies the search key
    IN OUT UINTN                        *BufferSize,                // On input, the size of Buffer. On output, the amount of data returned in Buffer
    OUT EFI_HANDLE                      *Buffer                     // The buffer in which the array is returned
);

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

// Locates the handle to a device on the device path that supports the specified protocol.
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH) (
    IN EFI_GUID                         *Protocol,                  // The protocol to search for
    IN OUT EFI_DEVICE_PATH_PROTOCOL     **DevicePath,               // A pointer to the device path
    OUT EFI_HANDLE                      *Device                     // A pointer to the returned device handle
);

// Adds, updates, or removes a configuration table entry from the EFI System Table.
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
    IN EFI_GUID                         *Guid,                      // A pointer to the GUID for the entry to add, update, or remove.
    IN VOID                             *Table
);

// Loads an EFI image into memory.
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_LOAD) (
    IN BOOLEAN                          BootPolicy,                 // If TRUE, indicates that the request originates from the boot manager, and that the boot manager is attempting to load DevicePath as a boot selection
    IN EFI_HANDLE                       ParentImageHandle,          // The caller’s image handle
    IN EFI_DEVICE_PATH_PROTOCOL         *DevicePath OPTIONAL,       // The DeviceHandle specific file path from which the image is loaded
    IN VOID                             *SourceBuffer OPTIONAL,     // If not NULL, a pointer to the memory location containing a copy of the image to be loaded.
    IN UINTN                            SourceSize,                 // The size in bytes of SourceBuffer. Ignored if SourceBuffer is NULL.
    OUT EFI_HANDLE                      *ImageHandle                // Pointer to the returned image handle that is created when the image is successfully loaded. 
);

// Transfers control to a loaded image’s entry point.
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START) (
    IN EFI_HANDLE                       ImageHandle,                // Handle of image to be started.
    OUT UINTN                           *ExitDataSize,              // Pointer to the size, in bytes, of ExitData. 
    OUT CHAR16                          **ExitData OPTIONAL         // Pointer to a pointer to a data buffer that includes a Null-terminated string, optionally followed by additional binary data.
);

// Terminates a loaded EFI image and returns control to boot services.
typedef EFI_STATUS (EFIAPI *EFI_EXIT) (
    IN EFI_HANDLE                       ImageHandle,                // Handle that identifies the image. This parameter is passed to the image on entry.
    IN EFI_STATUS                       ExitStatus,                 // The image’s exit code.
    IN UINTN                            ExitDataSize,               // The size, in bytes, of ExitData.
    IN CHAR16                           *ExitData OPTIONAL          // A pointer to a data buffer that includes a Null-terminated string, optionally followed by additional binary data.
);

// Unloads an image.
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE                       ImageHandle                 // Handle that identifies the image to be unloaded.
);

// Terminates all boot services.
typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES) (
    IN EFI_HANDLE                       ImageHandle,                // Handle that identifies the exiting image
    IN UINTN                            MapKey                      // The key for the memory map that is to be preserved
);

// Returns a monotonically increasing count for the platform.
typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
    OUT UINT64                          *Count                      // Pointer to the returned count
);

// Induces a fine-grained stall.
typedef EFI_STATUS (EFIAPI *EFI_STALL) (
    IN UINTN                            Microseconds                // The number of microseconds to stall execution
);

// Sets the system’s watchdog timer.
typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER) (
    IN UINTN                            Timeout,                    // The number of seconds to set the watchdog timer to. A value of zero disables the timer.
    IN UINT64                           WatchdogCode,               // The numeric code to log on a watchdog timer timeout event. 
    IN UINTN                            DataSize,                   // The size, in bytes, of WatchdogData.
    IN CHAR16                           *WatchdogData OPTIONAL      // A pointer to the data buffer that includes a Null-terminated string, optionally followed by additional binary data.
);

// Connects one or more drivers to a controller.
typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER) (
    IN EFI_HANDLE                       ControllerHandle,                   // The handle of the controller to which driver(s) are to be connected.
    IN EFI_HANDLE                       *DriverImageHandle OPTIONAL,        // A pointer to an ordered list handles that support the EFI_DRIVER_BINDING_PROTOCOL. 
    IN EFI_DEVICE_PATH_PROTOCOL         *RemainingDevicePath OPTIONAL,      // A pointer to the device path that specifies a child of the controller specified by ControllerHandle. 
    IN BOOLEAN                          Recursive                           // If TRUE, then ConnectController() is called recursively until the entire tree of controllers is connected.
);

// Disconnects one or more drivers from a controller.
typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER) (
    IN EFI_HANDLE                       ControllerHandle,           // The handle of the controller from which driver(s) are to be disconnected.
    IN EFI_HANDLE                       DriverImageHandle OPTIONAL, // The driver to disconnect from ControllerHandle. If DriverImageHandle is NULL, then all the drivers currently managing ControllerHandle are disconnected from ControllerHandle.
    IN EFI_HANDLE                       ChildHandle OPTIONAL        // The handle of the child controller to destroy. If ChildHandle is NULL, then all the child controllers are destroyed.
);

// Queries a handle to determine if it supports a specified protocol. 
// If the protocol is supported by the handle, it opens the protocol 
// on behalf of the calling agent. This is an extended version of the EFI boot service
typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL) (
    IN EFI_HANDLE                       Handle,                     // The handle for the protocol interface that is being opened.
    IN EFI_GUID                         *Protocol,                  // The published unique identifier of the protocol.
    OUT VOID                            **Interface OPTIONAL,       // Supplies the address where a pointer to the corresponding Protocol Interface is returned
    IN EFI_HANDLE                       AgentHandle,                // The handle of the agent that is opening the protocol interface specified by Protocol and Interface.
    IN EFI_HANDLE                       ControllerHandle,           // If the agent that is opening a protocol is a driver that follows the UEFI Driver Model, then this parameter is the controller handle that requires the protocol interface.
    IN UINT32                           Attributes                  // The open mode of the protocol interface specified by Protocol and Interface.
);

// Closes a protocol on a handle that was opened using EFI_BOOT_SERVICES.OpenProtocol() .
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL) (
    IN EFI_HANDLE                       Handle,                     // The handle for the protocol interface that was previously opened with OpenProtocol(), and is now being closed.
    IN EFI_GUID                         *Protocol,                  // The published unique identifier of the protocol.
    IN EFI_HANDLE                       AgentHandle,                // The handle of the agent that is closing the protocol interface
    IN EFI_HANDLE                       ControllerHandle            // If the agent that opened a protocol is a driver that follows the UEFI Driver Model, then this parameter is the controller handle that required the protocol interface. 
);

typedef struct {
    EFI_HANDLE                          AgentHandle;
    EFI_HANDLE                          ControllerHandle;
    UINT32                              Attributes;
    UINT32                              OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

// Retrieves the list of agents that currently have a protocol interface opened.
typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
    IN EFI_HANDLE                       Handle,                     // The handle for which open protocol information is to be retrieved.
    IN EFI_GUID                         *Protocol,                  // The published unique identifier of the protocol.
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,          // A pointer to the buffer in which the array of EFI_OPEN_PROTOCOL_INFORMATION_ENTRY structures is returned.
    OUT UINTN                           *EntryCount                 // A pointer to the number of entries in EntryBuffer.
);

// Retrieves the list of protocol interface GUIDs that are installed on a handle in a buffer allocated from pool.
typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
    IN EFI_HANDLE                       Handle,                     // The handle from which to retrieve the list of protocol interface GUIDs.
    OUT EFI_GUID                        ***ProtocolBuffer,          // A pointer to the list of protocol interface GUID pointers that are installed on Handle. 
    OUT UINTN                           *ProtocolBufferCount        // A pointer to the number of GUID pointers present in ProtocolBuffer.
);

// Returns an array of handles that support the requested protocol in a buffer allocated from pool.
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
    IN EFI_LOCATE_SEARCH_TYPE           SearchType,                 // Specifies which handle(s) are to be returned
    IN EFI_GUID                         *Protocol OPTIONAL,         // Provides the protocol to search by. This parameter is only valid for a SearchType of ByProtocol.
    IN VOID                             *SearchKey OPTIONAL,        // Supplies the search key depending on the SearchType.
    OUT UINTN                           *NoHandles,                 // The number of handles returned in Buffer.
    OUT EFI_HANDLE                      **Buffer                    // A pointer to the buffer to return the requested array of handles that support Protocol.
);

// Returns the first protocol instance that matches the given protocol.
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL) (
    IN EFI_GUID                         *Protocol,                  // Provides the protocol to search for.
    IN VOID                             *Registration OPTIONAL,     // Optional registration key returned from EFI_BOOT_SERVICES.RegisterProtocolNotify() 
    OUT VOID                            **Interface                 // On return, a pointer to the first interface that matches Protocol and Registration.
);

// Installs one or more protocol interfaces into the boot services environment.
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN OUT EFI_HANDLE                   *Handle                     // The pointer to a handle to install the new protocol interfaces on, or a pointer to NULL if a new handle is to be allocated.
);

// Removes one or more protocol interfaces into the boot services environment.
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN EFI_HANDLE                       Handle                      // The handle on which the protocol interfaces are to be removed.
);

// Computes and returns a 32-bit CRC for a data buffer.
typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32)(
    IN VOID                             *Data,                      // A pointer to the buffer on which the 32-bit CRC is to be computed.
    IN UINTN                            DataSize,                   // The number of bytes in the buffer Data.
    OUT UINT32                          *Crc32                      // The 32-bit CRC that was computed for the data buffer specified by Data and DataSize.
);

// The CopyMem() function copies the contents of one buffer to another buffer.
typedef VOID (EFIAPI *EFI_COPY_MEM) (
    IN VOID                             *Destination,               // Pointer to the destination buffer of the memory copy.
    IN VOID                             *Source,                    // Pointer to the source buffer of the memory copy.
    IN UINTN                            Length                      // Number of bytes to copy from Source to Destination.
);

// The SetMem() function fills a buffer with a specified value.
typedef VOID (EFIAPI *EFI_SET_MEM) (
    IN VOID                             *Buffer,                    // Pointer to the buffer to fill.
    IN UINTN                            Size,                       // Number of bytes in Buffer to fill.
    IN UINT8                            Value                       // Value to fill Buffer with.
);

// Creates an event in a group.
typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT_EX) (      
    IN UINT32                           Type,                       // The type of event to create and its mode and attributes
    IN EFI_TPL                          NotifyTpl,                  // The task priority level of event notifications, if needed
    IN EFI_EVENT_NOTIFY                 NotifyFunction OPTIONAL,    // The pointer to the event’s notification function
    IN CONST VOID                       *NotifyContext OPTIONAL,    // The pointer to the notification function’s context
    IN CONST EFI_GUID                   *EventGroup OPTIONAL,       // The pointer to the GUID of the event group
    OUT EFI_EVENT                       *Event                      // The pointer to the newly created event if the call succeeds; undefined otherwise
);


typedef struct {
    EFI_TABLE_HEADER                            Hdr;

    EFI_RAISE_TPL                               RaiseTPL; // EFI 1.0+
    EFI_RESTORE_TPL                             RestoreTPL; // EFI 1.0+

    EFI_ALLOCATE_PAGES                          AllocatePages; // EFI 1.0+
    EFI_FREE_PAGES                              FreePages; // EFI 1.0+
    EFI_GET_MEMORY_MAP                          GetMemoryMap; // EFI 1.0+

    EFI_ALLOCATE_POOL                           AllocatePool; // EFI 1.0+
    EFI_FREE_POOL                               FreePool; // EFI 1.0+

    EFI_CREATE_EVENT                            CreateEvent; // EFI 1.0+
    EFI_SET_TIMER                               SetTimer; // EFI 1.0+
    EFI_WAIT_FOR_EVENT                          WaitForEvent; // EFI 1.0+
    EFI_SIGNAL_EVENT                            SignalEvent; // EFI 1.0+
    EFI_CLOSE_EVENT                             CloseEvent; // EFI 1.0+
    EFI_CHECK_EVENT                             CheckEvent; // EFI 1.0+

    EFI_INSTALL_PROTOCOL_INTERFACE              InstallProtocolInterface; // EFI 1.

    EFI_REINSTALL_PROTOCOL_INTERFACE            ReinstallProtocolInterface; // EFI 1.
    
    EFI_UNINSTALL_PROTOCOL_INTERFACE            UninstallProtocolInterface; // EFI 1.

    EFI_HANDLE_PROTOCOL                         HandleProtocol; // EFI 1.

    VOID*                                       Reserved; // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY                RegisterProtocolNotify; // EFI 1.

    EFI_LOCATE_HANDLE                           LocateHandle; // EFI 1.

    EFI_LOCATE_DEVICE_PATH                      LocateDevicePath; // EFI 1.

    EFI_INSTALL_CONFIGURATION_TABLE             InstallConfigurationTable; // EFI 1.

    EFI_IMAGE_LOAD                              LoadImage; // EFI 1.0+
    EFI_IMAGE_START                             StartImage; // EFI 1.0+
    EFI_EXIT                                    Exit; // EFI 1.0+
    EFI_IMAGE_UNLOAD                            UnloadImage; // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES                      ExitBootServices; // EFI 1.0+

    EFI_GET_NEXT_MONOTONIC_COUNT                GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL                                   Stall; // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER                      SetWatchdogTimer; // EFI 1.0+

    EFI_CONNECT_CONTROLLER                      ConnectController; // EFI 1.1
    EFI_DISCONNECT_CONTROLLER                   DisconnectController; // EFI 1.1+

    EFI_OPEN_PROTOCOL                           OpenProtocol; // EFI 1.1+
    EFI_CLOSE_PROTOCOL                          CloseProtocol; // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION               OpenProtocolInformation;// EFI 1.1+

    EFI_PROTOCOLS_PER_HANDLE                    ProtocolsPerHandle; // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER                    LocateHandleBuffer; // EFI 1.1+
    EFI_LOCATE_PROTOCOL                         LocateProtocol; // EFI 1.1+
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES    InstallMultipleProtocolInterfaces; //

    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces; //

    EFI_CALCULATE_CRC32                         CalculateCrc32; // EFI 1.1+

    EFI_COPY_MEM                                CopyMem; // EFI 1.1+
    EFI_SET_MEM                                 SetMem; // EFI 1.1+
    EFI_CREATE_EVENT_EX                         CreateEventEx; // UEFI 2.0+
} EFI_BOOT_SERVICES;


//******************************************************
// Event Types
//******************************************************

/* These types can be "ORed" together as needed - for example,
 EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or
 EVT_NOTIFY_SIGNAL.
 */
#define EVT_TIMER                            0x80000000     // The event is a timer event and may be passed to EFI_BOOT_SERVICES.SetTimer(). Note that timers only function during boot services time.
#define EVT_RUNTIME                          0x40000000     // The event is allocated from runtime memory. If an event is to be signaled after the call to EFI_BOOT_SERVICES.ExitBootServices() 
                                                            // the event’s data structure and notification function need to be allocated from runtime memory. For more information, see SetVirtualAddressMap() .

#define EVT_NOTIFY_WAIT                      0x00000100     // If an event of this type is not already in the signaled state, then the event’s NotificationFunction will be queued at the event’s NotifyTpl whenever the event is being waited on via EFI_BOOT_SERVICES.WaitForEvent() or EFI_BOOT_SERVICES.CheckEvent() .
#define EVT_NOTIFY_SIGNAL                    0x00000200     // The event’s NotifyFunction is queued whenever the event is signaled.

#define EVT_SIGNAL_EXIT_BOOT_SERVICES        0x00000201     // This event is of type EVT_NOTIFY_SIGNAL. It should not be combined with any other event types. This event type is functionally equivalent to the EFI_EVENT_GROUP_EXIT_BOOT_SERVICES event group. Refer to EFI_EVENT_GROUP_EXIT_BOOT_SERVICES event group description in EFI_BOOT_SERVICES.CreateEventEx() section below for additional details.

#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE    0x60000202     // The event is to be notified by the system when SetVirtualAddressMap() is performed. This event type is a composite of EVT_NOTIFY_SIGNAL, EVT_RUNTIME, and EVT_RUNTIME_CONTEXT and should not be combined with any other event types.


//******************************************************
// Memory Attribute Definitions
//******************************************************
// These types can be "ORed" together as needed.
#define EFI_MEMORY_UC              0x0000000000000001       // The memory region supports uncacheable memory access.
#define EFI_MEMORY_WC              0x0000000000000002       // The memory region supports write-combined memory access.
#define EFI_MEMORY_WT              0x0000000000000004       // The memory region supports write-through memory access.
#define EFI_MEMORY_WB              0x0000000000000008       // The memory region supports write-back memory access.    
#define EFI_MEMORY_UCE             0x0000000000000010       // The memory region supports being configured as not cacheable, exported, and supports the “fetch and add” semaphore mechanism.
#define EFI_MEMORY_WP              0x0000000000001000       // The memory region supports being configured as write-protected by system hardware
#define EFI_MEMORY_RP              0x0000000000002000       // The memory region supports being configured as read-protected by system hardware.
#define EFI_MEMORY_XP              0x0000000000004000       // The memory region supports being configured so it is protected by system hardware from executing code.
#define EFI_MEMORY_NV              0x0000000000008000       // The memory region refers to persistent memory
#define EFI_MEMORY_MORE_RELIABLE   0x0000000000010000       // The memory region provides higher reliability relative to other memory in the system
#define EFI_MEMORY_RO              0x0000000000020000       // The memory region supports making this memory range read-only by system hardware.
#define EFI_MEMORY_SP              0x0000000000040000       // The memory is earmarked for specific purposes such as for specific device drivers or applications
#define EFI_MEMORY_CPU_CRYPTO      0x0000000000080000       // The memory region is capable of being protected with the CPU’s memory cryptographic capabilities
#define EFI_MEMORY_RUNTIME         0x8000000000000000       // The memory region needs to be given a virtual mapping by the operating system when SetVirtualAddressMap() is called
#define EFI_MEMORY_ISA_VALID       0x4000000000000000       // The memory region is described with additional ISA-specific memory attributes as specified in EFI_MEMORY_ISA_MASK 
#define EFI_MEMORY_ISA_MASK        0x0FFFF00000000000       // Defines the bits reserved for describing optional ISA-specific cacheability attributes that are not covered by the standard UEFI Memory Attributes cacheability bits

//******************************************************
// Memory Descriptor Version Number
//******************************************************
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

//******************************************************
// Task Priority Levels
//******************************************************
#define TPL_APPLICATION    4
#define TPL_CALLBACK       8
#define TPL_NOTIFY         16
#define TPL_HIGH_LEVEL     31

#endif // _UEFI_BOOT_SERVICES_H_