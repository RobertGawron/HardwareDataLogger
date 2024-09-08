# configure code coverage

# Find lcov and genhtml for generating coverage reports
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

if(LCOV_PATH AND GENHTML_PATH AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COVERAGE_DIR "${CMAKE_BINARY_DIR}/BuildArtifacts/CodeCoverage")
    file(MAKE_DIRECTORY ${COVERAGE_DIR})

    add_custom_target(coverage
    
        # Capture coverage data with a base directory set to the project's root
        COMMAND ${LCOV_PATH} --directory ${CMAKE_BINARY_DIR} --capture --output-file ${COVERAGE_DIR}/coverage.info --base-directory ${CMAKE_SOURCE_DIR}
        COMMAND ${LCOV_PATH} --remove ${COVERAGE_DIR}/coverage.info  --output-file ${COVERAGE_DIR}/coverage.filtered.info '*/Test/*' '/usr/*'

        # Generate HTML report, now with relative paths
        COMMAND ${GENHTML_PATH} --prefix ${CMAKE_SOURCE_DIR}/Software/ --output-directory ${COVERAGE_DIR} ${COVERAGE_DIR}/coverage.filtered.info

        COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in ${COVERAGE_DIR}/html/index.html"
        DEPENDS test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report..."
    )
endif()