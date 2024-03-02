#include <unity.h>
#include <unity_test_runner.h>
#include <esp_uuid.h>

TEST_CASE("uuidv4_new()", "[esp-uuid]") {
    uint8_t out_buffer[UUID_SIZE];
    TEST_ASSERT(uuidv4_new(out_buffer, sizeof(out_buffer)) == ESP_OK);
    TEST_ASSERT(out_buffer[6] >> 4 == 4);
    TEST_ASSERT(out_buffer[8] >> 6 == 0b10);
}

TEST_CASE("uuidv4_new_string()", "[esp-uuid]") {
    char out_str[UUID_SIZE_STR + 1];

    TEST_ASSERT(uuidv4_new_string(out_str, sizeof(out_str)) == ESP_OK);

    TEST_ASSERT(strlen(out_str) == UUID_SIZE_STR);

    // Checking uuid version is '4'
    TEST_ASSERT(out_str[14] == '4');

    char temp = out_str[20];

    out_str[20] = '\0';

    // Getting two most significant bits (actually here we are getting four bits) of
    // clock_sequence_hi_and_reserved
    uint8_t int_rep = (uint8_t)strtoul(&out_str[19], NULL, 16);

    out_str[20] = temp;

    // Checking if two most significant bits are 0 and 1
    TEST_ASSERT(int_rep >> 2 == 0b10);
}

TEST_CASE("uuid_to_string()", "[esp-uuid]") {
    // 3d044bf1-40e0-4f5a-a2d4-344a6aa6cbdb -> uuidv4, should work fine with other versions of uuid
    const uint8_t test_uid[] = { 0x3d, 0x04, 0x4b, 0xf1,
                                 0x40, 0xe0,
                                 0x4f, 0x5a,
                                 0xa2, 0xd4,
                                 0x34, 0x4a, 0x6a, 0xa6, 0xcb, 0xdb };

    const char expected_string[] = "3d044bf1-40e0-4f5a-a2d4-344a6aa6cbdb";

    char out_str[UUID_SIZE_STR + 1];

    TEST_ASSERT(uuid_to_string(test_uid, out_str, sizeof(out_str)) == ESP_OK);

    TEST_ASSERT(strlen(out_str) == UUID_SIZE_STR);

    TEST_ASSERT(strcmp(out_str, expected_string) == 0);
}

TEST_CASE("uuid_from_string()", "[esp-uuid]") {
    const char test_str_uid[] = "3d044bf1-40e0-4f5a-a2d4-344a6aa6cbdb";

    // 3d044bf1-40e0-4f5a-a2d4-344a6aa6cbdb -> uuidv4, should work fine with other versions of uuid
    const uint8_t expected_uid[] = { 0x3d, 0x04, 0x4b, 0xf1,
                                     0x40, 0xe0,
                                     0x4f, 0x5a,
                                     0xa2, 0xd4,
                                     0x34, 0x4a, 0x6a, 0xa6, 0xcb, 0xdb };

    uint8_t out[UUID_SIZE];

    TEST_ASSERT(uuid_from_string(test_str_uid, out, sizeof(out)) == ESP_OK);

    TEST_ASSERT(memcmp(expected_uid, out, sizeof(out)) == 0);
}

TEST_CASE("uuid_compare()", "[esp-uuid]") {
    const uint8_t test_uid1[] = { 0x3d, 0x04, 0x4b, 0xf1,
                                  0x40, 0xe0,
                                  0x4f, 0x5a,
                                  0xa2, 0xd4,
                                  0x34, 0x4a, 0x6a, 0xa6, 0xcb, 0xdb };

    const uint8_t test_uid2[] = { 0x3d, 0x04, 0x4b, 0xf1,
                                  0x40, 0xe0,
                                  0x4f, 0x5a,
                                  0xa2, 0xd4,
                                  0x34, 0x4a, 0x6a, 0xa6, 0xcb, 0xdb };

    TEST_ASSERT(uuid_compare(test_uid1, test_uid2) == 0);
}
