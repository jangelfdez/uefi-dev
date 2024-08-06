#ifndef UEFI_PROTOCOLS_RNG_H
#define UEFI_PROTOCOLS_RNG_H

#include "uefi-data-types.h"

/* Random Number Generator Protocol (37.5)
 https://uefi.org/specs/UEFI/2.10/37_Secure_Technologies.html#random-number-generator-protocol

 This protocol is used to provide random numbers for use in applications, 
 or entropy for seeding other random number generators. Consumers of the 
 protocol can ensure that drivers implementing the protocol produce RNG 
 values in a well-known manner.
*/

#define EFI_RNG_PROTOCOL_GUID \
    { 0x3152bca5, 0xeade, 0x433d,\
    { 0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44}}

typedef EFI_GUID EFI_RNG_ALGORITHM;

typedef struct _EFI_RNG_PROTOCOL EFI_RNG_PROTOCOL;

// This function returns information about supported RNG algorithms.
typedef EFI_STATUS (EFIAPI *EFI_RNG_GET_INFO) (
    IN EFI_RNG_PROTOCOL             *This,                      // A pointer to the EFI_RNG_PROTOCOL instance.
    IN OUT UINTN                    *RNGAlgorithmListSize,      // On input, the size in bytes of RNGAlgorithmList. On output with a return code of EFI_SUCCESS, the size in bytes of the data returned in RNGAlgorithmList. On output with a return code of EFI_BUFFER_TOO_SMALL, the size of RNGAlgorithmList required to obtain the list.
    OUT EFI_RNG_ALGORITHM           *RNGAlgorithmList           // A caller-allocated memory buffer filled by the driver with one EFI_RNG_ALGORITHM element for each supported RNG algorithm.
);

// Produces and returns an RNG value using either the default or specified RNG algorithm.
typedef EFI_STATUS (EFIAPI *EFI_RNG_GET_RNG) (
    IN EFI_RNG_PROTOCOL             *This,                      // A pointer to the EFI_RNG_PROTOCOL instance.
    IN EFI_RNG_ALGORITHM            *RNGAlgorithm, OPTIONAL     // A pointer to the EFI_RNG_ALGORITHM to use for the RNG value. If NULL, the default RNG algorithm is used.
    IN UINTN                        RNGValueLength,             // The length in bytes of the RNG value to produce.
    OUT UINT8                       *RNGValue                   // A caller-allocated memory buffer filled by the driver with the RNG value.
);

// Protocol interface structure
typedef struct _EFI_RNG_PROTOCOL{
    EFI_RNG_GET_INFO                GetInfo;                    // Returns the next set of random numbers.
    EFI_RNG_GET_RNG                 GetRNG;                     // Returns information about the random number generation implementation.
} EFI_RNG_PROTOCOL;

// GUID definitions for RNG algorithms
#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID \
 {0xa7af67cb, 0x603b, 0x4d42,\
 {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96}}

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID \
 {0xc5149b43, 0xae85, 0x4f53,\
 {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7}}

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID \
 {0x44f0de6e, 0x4d8c, 0x4045, \
 {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e}}

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID \
 {0x63c4785a, 0xca34, 0x4012,\
 {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46}}

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID \
 {0xacd03321, 0x777e, 0x4d3d,\
 {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9}}

#define EFI_RNG_ALGORITHM_RAW \
 {0xe43176d7, 0xb6e8, 0x4827,\
 {0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61}}


#endif // UEFI_PROTOCOLS_RNG_H