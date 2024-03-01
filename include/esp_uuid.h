#ifndef __ESP_UUID_HEADER
#define __ESP_UUID_HEADER

#include <esp_err.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* =============== MACROS =============== */

#define UUID_SIZE     16 // size of raw uuid's in bytes
#define UUID_SIZE_STR 37 // size of formatted uuid's in bytes; 36 characters + NUL terminator = 37 bytes

/* =============== FUNCTIONS =============== */

/**
 * Writes a formatted, newly and randomly generated uuidv4 to "out" and adds NUL terminator to it.
 * 
 * The uuidv4 generated complies with format specified in RFC 4122 Section 4.
 * 
 * @param out Pointer to a buffer of characters
 * @param out_len Length of "out" in bytes, must be greater or equal than UUID_SIZE_STR
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "out" is NULL or "out_len" is less than UUID_SIZE_STR
*/
esp_err_t uuidv4_new_string(char *out, size_t out_len);

/**
 * Writes a raw, unformatted, newly and randomly generated uuidv4 to "out".
 * 
 * The uuidv4 generated complies with RFC 4122 Section 4 specification.
 * 
 * @param out Pointer to a buffer of bytes
 * @param out_len Lenght of "out" in bytes, must be greater or equal than UUID_SIZE
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "out" is NULL or "out_len" is less than UUID_SIZE
 * @note The uuidv4 written to "out" is not NUL terminated nor formatted, just the raw random
 *       or pseudo-random bytes are written and the corresponding bits are modified to comply
 *       with RFC 4122 Section 4.4
*/
esp_err_t uuidv4_new(uint8_t *out, size_t out_len);

/**
 * Converts unformatted and raw bytes in "in" to formatted uuid and writes it to "out" buffer,
 * then adds NUL terminator to "out".
 * 
 * Compatible with any uuid version.
 * 
 * @param in Pointer to raw uuid buffer, must point to UUID_SIZE bytes lenght buffer
 * @param out Pointer to buffer of characters
 * @param out_let Lenght of "out" in bytes, must be greater or equal than UUID_SIZE_STR
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "in" or "out" are NULL, or "out_len" is less than UUID_SIZE_STR
 * @note "in" must be a pointer to a buffer of length UUID_SIZE bytes, is undefined behaviour
 *       if "uid" points to a shorter buffer.
*/
esp_err_t uuid_to_string(const uint8_t *in, char *out, size_t out_len);

/**
 * Converts formatted uuid string in "in" to raw uuid and writes it to "out" buffer.
 * 
 * Compatible with any uuid version.
 * 
 * @param in Pointer to NUL terminated string, must point to a valid and formatted uuid
 * @param out Pointer to buffer of bytes
 * @param out_len Length of "out" in bytes, must be greater or equal than 16
 * @returns
 *  - ESP_OK on success
 *  - ESP_ERR_INVALID_ARG if "in" or "out" are NULL; or "out_len" is less than UUID_SIZE; or "in"
 *    is not a valid uuid
*/
esp_err_t uuid_from_string(const char *in, uint8_t *out, size_t out_len);

/**
 * Compares two raw uuid's using memcmp, so rules from memcmp are also applied to this function
 * 
 * Compatible with any uuid version
 * 
 * @param uid1 Pointer to raw uuid
 * @param uid2 Pointer to raw uuid
 * @returns
 *  - 0 if both "uid1" and "uid2" are equal
 *  - -1 if "uid1" is lexically less than "uid2"
 *  - 1 if "uid1" is lexically greater than "uid2"
 * @note Both "uid1" and "uid2" must point to a buffer of lenght UUID_SIZE bytes, is undefined
 *       behaviour if some of the parameters points to shorter buffers.
*/
int uuid_compare(const uint8_t *uid1, const uint8_t *uid2);

#ifdef __cplusplus
}
#endif
#endif /* __ESP_UUID_HEADER */
