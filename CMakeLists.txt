if(CONFIG_AD4130)
    zephyr_library()
    zephyr_library_sources(
        src/ad4130.c
    )
    zephyr_include_directories(src)

endif()
