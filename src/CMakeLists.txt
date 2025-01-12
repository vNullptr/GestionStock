

add_library(stockLib STATIC
    CLI.c
    data.c
)

target_include_directories(stockLib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)