project(Parser)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(parser
        zhi.yy
        ${CMAKE_CURRENT_SOURCE_DIR}/lzhi.tab.c
        DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lzhi.tab.h
        COMPILE_FLAGS "--debug"
        )

flex_target(lexer
        zhi.l
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
        COMPILE_FLAGS "-Cm -B --nounistd")

add_flex_bison_dependency(lexer parser)
include_directories(../interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

LINK_DIRECTORIES(
        /user/local/lib
)

add_library(parser Parser.cpp ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})
target_link_libraries(
        parser
        rudeconfig
)

add_executable(Parser example/main.cpp )


target_link_libraries(
        Parser
        parser
        fmt::fmt
)