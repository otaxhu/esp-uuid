#ifndef __ESP_UUID_HEADER
#define __ESP_UUID_HEADER

#include <esp_err.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Writes a formatted, newly and randomly generated uuidv4 to "out" and adds NUL terminator to it.
 * 
 * @param out Pointer to a buffer of characters
 * @param out_len Length of "out" in bytes, must be greater or equal than 37
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "out" is NULL or "out_len" is less than 37
 *  - ESP_ERR_NO_MEM if there was no available memory to allocate random bytes (internal error)
*/
esp_err_t uuidv4_new_string(char *out, size_t out_len);

/**
 * Writes a raw, unformatted, newly and randomly generated uuidv4 to "out"
 * @param out Pointer to a buffer of bytes
 * @param out_len Lenght of "out" in bytes, must be greater or equal than 16
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "out" is NULL or "out_len" is less than 16
 * @note The uuidv4 written to "out" is not NUL terminated nor formatted, just the raw random
 *       or pseudo-random bytes are written and the corresponding bits are modified to comply
 *       with RFC 4122 Section 4.4
*/
esp_err_t uuidv4_new(uint8_t *out, size_t out_len);

/**
 * Converts unformatted and raw bytes in "uid" to formatted uuid and writes it to "out" buffer,
 * then adds NUL terminator to "out".
 * 
 * Compatible with any uuid version.
 * 
 * @param uid Pointer to raw uuid
 * @param out Pointer to buffer of characters
 * @param out_let Lenght of "out" in bytes, must be greater or equal than 37
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "uid" or "out" are NULL, or "out_len" is less than 37
 * @note "uid" must be a pointer to a buffer of length 16 bytes, is undefined behaviour
 *       if "uid" points to a buffer that is less than 16 bytes.
*/
esp_err_t uuid_to_string(const uint8_t *uid, char *out, size_t out_len);

#ifdef __cplusplus
}
#endif
#endif /* __ESP_UUID_HEADER */
