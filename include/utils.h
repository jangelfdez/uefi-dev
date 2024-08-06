


/**
 * Converts an unsigned 64-bit integer to a string representation.
 *
 * @param value The value to convert.
 * @param buffer The buffer to store the string representation.
 * @param buffer_size The size of the buffer.
 * @return A pointer to the buffer containing the string representation of the value.
 */
CHAR16* int_to_string(IN UINT64 value, IN OUT CHAR16* buffer, IN UINTN buffer_size){
    
    while (value > 0 && buffer_size > 0){
        buffer_size = buffer_size - sizeof(CHAR16);
        buffer[buffer_size] = (CHAR16) (value % 10) + '0';
        value /= 10;
    }

    return buffer;
}
