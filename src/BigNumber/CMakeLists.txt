aux_source_directory(. BigNumSrc)
link_directories(${PROJECT_BINARY_DIR}/include)
add_library(BigNumber ${BigNumSrc})