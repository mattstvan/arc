target_include_directories(arc PUBLIC ${Arc_SOURCE_DIR}/include/coordinates)

file(GLOB SRC_FILES    
    "*.cpp"
)

target_sources(arc PUBLIC ${SRC_FILES})