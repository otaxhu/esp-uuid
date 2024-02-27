if(${IDF_TARGET} STREQUAL "esp32p4")
    message(FATAL_ERROR "'${IDF_TARGET}' target chip at the moment cannot generate random values."
                        "Please writes an issue to https://github.com/otaxhu/esp-uuid when..."
                        "ESP-IDF add support to random number generation for '${IDF_TARGET}'"
                        "Aborting compilation of '${COMPONENT_NAME}'...")
endif()

message(STATUS "'${IDF_TARGET}' target")

idf_component_register(SRCS "src/esp_uuid.c"
                       INCLUDE_DIRS "include")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-parentheses")
