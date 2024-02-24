# Library to manipulate and generate UUIDs. Compatible with ESP-IDF

## Installation:
1. Create a project directory, inside of a directory create the `main` and `components` directories:
```sh
$ mkdir project-name
$ cd project-name
$ mkdir main && mkdir components
```

2. Go inside `components` directory and clone the repository:
```sh
$ cd components
$ git clone --depth 2 https://github.com/otaxhu/esp-uuid
```

3. Go inside `main` directory and initialize the main component:
```sh
$ cd ../main
$ touch main.c CMakeLists.txt
```

4. Initialize the `CMakeLists.txt` file content:
```cmake
idf_component_register(SRCS "main.c"
                       REQUIRES esp-uuid)
```

5. Use the library functions provided in your `main` component or whatever component you want :D

## Documentation:
For more documentation see the [header file](/include/esp_uuid.h)
