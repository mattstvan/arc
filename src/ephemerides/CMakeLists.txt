target_include_directories(Arc PUBLIC ${Arc_SOURCE_DIR}/include/ephemerides)

file(GLOB SRC_FILES    
    "*.cpp"
)

target_sources(Arc PUBLIC ${SRC_FILES})