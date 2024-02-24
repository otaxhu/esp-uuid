#include <esp_uuid.h>
#include <esp_random.h>

esp_err_t uuidv4_new(uint8_t *out, size_t out_len) {
    if (out == NULL || out_len < 16) {
        return ESP_ERR_INVALID_ARG;
    }

    // RFC 4122 Section 4.4
    // "Set all the other bits to randomly (or pseudo-randomly) chosen values"
    esp_fill_random(out, 16);

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
    uint8_t *rand_buf = NULL;

    if (out == NULL || out_len < 37) {
        err = ESP_ERR_INVALID_ARG;
        goto exit;
    }

    rand_buf = malloc(16);
    if (rand_buf == NULL) {
        err = ESP_ERR_NO_MEM;
        goto exit;
    }

    if (err = uuidv4_new(rand_buf, 16)) {
        goto exit;
    }

    if (err = uuid_to_string(rand_buf, out, out_len)) {
        goto exit;
    }
exit:
    free(rand_buf);
    return err;
}

esp_err_t uuid_to_string(const uint8_t *uid, char *out, size_t out_len) {
    if (uid == NULL || out == NULL || out_len < 37) {
        return ESP_ERR_INVALID_ARG;
    }

    // https://gitlab.gnome.org/GNOME/glib/-/blame/main/glib/guuid.c?ref_type=heads#L58
    snprintf(out, out_len, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             uid[0], uid[1], uid[2], uid[3],
             uid[4], uid[5],
             uid[6], uid[7],
             uid[8], uid[9],
             uid[10], uid[11], uid[12], uid[13], uid[14], uid[15]);

    return ESP_OK;
}
