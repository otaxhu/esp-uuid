#include <esp_uuid.h>
#include <esp_random.h>
#include <string.h>
#include <stdio.h>

esp_err_t uuidv4_new(uint8_t *out, size_t out_len) {
    if (out == NULL || out_len < 16) {
        return ESP_ERR_INVALID_ARG;
    }

    // RFC 4122 Section 4.4
    // "Set all the other bits to randomly (or pseudo-randomly) chosen values"
    esp_fill_random(out, UUID_SIZE);

    // https://gitlab.gnome.org/GNOME/glib/-/blame/main/glib/guuid.c?ref_type=heads#L137
    out[6] &= 0x0f;
    out[6] |= 4 << 4;

    // https://gitlab.gnome.org/GNOME/glib/-/blame/main/glib/guuid.c?ref_type=heads#L143
    out[8] &= 0x3f;
    out[8] |= 0x80;

    return ESP_OK;
}

esp_err_t uuidv4_new_string(char *out, size_t out_len) {

    esp_err_t err = ESP_OK;

    if (out == NULL || out_len < UUID_SIZE_STR) {
        err = ESP_ERR_INVALID_ARG;
        goto exit;
    }

    // Using the same buffer "out" to store the uuid in raw format
    if (err = uuidv4_new((uint8_t *)out, out_len)) {
        goto exit;
    }

    // Function uuid_to_string already extracts the values from "out" before writing to it
    if (err = uuid_to_string((const uint8_t *)out, out, out_len)) {
        goto exit;
    }
exit:
    return err;
}

esp_err_t uuid_to_string(const uint8_t *in, char *out, size_t out_len) {
    if (in == NULL || out == NULL || out_len < UUID_SIZE_STR) {
        return ESP_ERR_INVALID_ARG;
    }

    // https://gitlab.gnome.org/GNOME/glib/-/blame/main/glib/guuid.c?ref_type=heads#L58
    snprintf(out, out_len, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             in[0], in[1], in[2], in[3],
             in[4], in[5],
             in[6], in[7],
             in[8], in[9],
             in[10], in[11], in[12], in[13], in[14], in[15]);

    return ESP_OK;
}

esp_err_t uuid_from_string(const char *in, uint8_t *out, size_t out_len) {
    if (in == NULL || out == NULL || out_len < UUID_SIZE) {
        return ESP_ERR_INVALID_ARG;
    }

    int n = 0;

    sscanf(in, "%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%n",
		   &out[0], &out[1], &out[2], &out[3],
           &out[4], &out[5],
           &out[6], &out[7],
           &out[8], &out[9],
           &out[10], &out[11], &out[12], &out[13], &out[14], &out[15], &n);

    if (n != 36 || in[n] != '\0') {
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

int uuid_compare(const uint8_t *uid1, const uint8_t *uid2) {
    return memcmp(uid1, uid2, UUID_SIZE);
}
