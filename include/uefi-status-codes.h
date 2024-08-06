#ifndef UEFI_STATUS_CODES_H
#define UEFI_STATUS_CODES_H

/* EFI_STATUS Code Ranges (Appendix D)
https://uefi.org/specs/UEFI/2.10/Apx_D_Status_Codes.html#status-codes
*/

typedef UINTN   UEFI_STATUS;

#define WARNING_CODE_BASE_ADDR_UEFI_SPEC   0x00000000000000
#define WARNING_CODE_BASE_ADDR_PIA_SPEC    0x20000000000000
#define WARNING_CODE_BASE_ADDR_OEM         0x40000000000000
#define ERROR_CODE_BASE_ADDR_UEFI_SPEC     0x80000000000000 
#define ERROR_CODE_BASE_ADDR_PIA_SPEC      0xa0000000000000 
#define ERROR_CODE_BASE_ADDR_OEM           0xc0000000000000 
 
#define EFI_SUCCESS                  0                           // The operation completed successfully.
 
 
#define EFI_LOAD_ERROR              ( 1 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The image failed to load.
#define EFI_INVALID_PARAMETER       ( 2 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A parameter was incorrect.
#define EFI_UNSUPPORTED             ( 3 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The operation is not supported.
#define EFI_BAD_BUFFER_SIZE         ( 4 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The buffer was not the proper size for the request. 
#define EFI_BUFFER_TOO_SMALL        ( 5 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The buffer was not large enough to hold the requested data.
#define EFI_NOT_READY               ( 6 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // There is no data pending upon return.
#define EFI_DEVICE_ERROR            ( 7 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The physical device reported an error while attempting the operation.
#define EFI_WRITE_PROTECTED         ( 8 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The device cannot be written to.
#define EFI_OUT_OF_RESOURCES        ( 9 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A resource has run out.
#define EFI_VOLUME_CORRUPTED        (10 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // An inconsistency was detected on the file system causing the operation to fail.
#define EFI_VOLUME_FULL             (11 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // There is no more space on the file system.
#define EFI_NO_MEDIA                (12 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The device does not contain any medium to perform the operation.
#define EFI_MEDIA_CHANGED           (13 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The medium in the device has changed since the last access.
#define EFI_NOT_FOUND               (14 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The item was not found.
#define EFI_ACCESS_DENIED           (15 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // Access was denied.
#define EFI_NO_RESPONSE             (16 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The server was not found or did not respond to the request.
#define EFI_NO_MAPPING              (17 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A mapping to the device does not exist.
#define EFI_TIMEOUT                 (18 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The timeout time expired.
#define EFI_NOT_STARTED             (19 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The protocol has not been started.
#define EFI_ALREADY_STARTED         (20 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The protocol has already been started.
#define EFI_ABORTED                 (21 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The operation was aborted.
#define EFI_ICMP_ERROR              (22 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // An ICMP error occurred during the network operation.
#define EFI_TFTP_ERROR              (23 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A TFTP error occurred during the network operation.
#define EFI_PROTOCOL_ERROR          (24 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A protocol error occurred during the network operation.
#define EFI_INCOMPATIBLE_VERSION    (25 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The function encountered an internal version that was incompatible with a version requested by the caller.
#define EFI_SECURITY_VIOLATION      (26 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The function was not performed due to a security violation.
#define EFI_CRC_ERROR               (27 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A CRC error was detected.
#define EFI_END_OF_MEDIA            (28 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // Beginning or end of media was reached.
#define EFI_END_OF_FILE             (31 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The end of the file was reached.
#define EFI_INVALID_LANGUAGE        (32 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The language specified was invalid.
#define EFI_COMPROMISED_DATA        (33 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // The security status of the data is unknown or compromised and the data must be updated or replaced to restore a valid security status.
#define EFI_IP_ADDRESS_CONFLICT     (34 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // There is an address conflict address allocation.
#define EFI_HTTP_ERROR              (35 | ERROR_CODE_BASE_ADDR_UEFI_SPEC   ) // A HTTP error occurred during the network operation.

#define EFI_WARN_UNKNOWN_GLYPH      ( 1 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The string contained one or more characters that the device could not render and were skipped.
#define EFI_WARN_DELETE_FAILURE     ( 2 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The handle was closed, but the file was not deleted.
#define EFI_WARN_WRITE_FAILURE      ( 3 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The handle was closed, but the data to the file was not flushed properly.
#define EFI_WARN_BUFFER_TOO_SMALL   ( 4 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The resulting buffer was too small, and the data was truncated to the buffer size.
#define EFI_WARN_STALE_DATA         ( 5 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The data has not been updated within the timeframe set by local policy for this type of data.
#define EFI_WARN_FILE_SYSTEM        ( 6 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The resulting buffer contains UEFI-compliant file system.
#define EFI_WARN_RESET_REQUIRED     ( 7 | WARNING_CODE_BASE_ADDR_UEFI_SPEC ) // The operation will be processed across a system reset.

#endif // UEFI_STATUS_CODES_H