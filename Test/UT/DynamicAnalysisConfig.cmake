add_custom_target(dynamic_analyse ALL)

set(DYNAMIC_ANALYSIS_DIR ${CMAKE_BINARY_DIR}/dynamic_analyse)
file(MAKE_DIRECTORY ${DYNAMIC_ANALYSIS_DIR})


foreach(test_exec ${TEST_EXECUTABLES})
    if(ENABLE_VALGRIND)
        # Define the output files within the dynamic_analysis directory
        set(CALLGRIND_OUT ${DYNAMIC_ANALYSIS_DIR}/callgrind.out.${test_exec})
        set(SVG_OUT ${DYNAMIC_ANALYSIS_DIR}/${test_exec}.svg)

        # Add a custom command to run Valgrind with Callgrind and generate the callgrind output file
        add_custom_command(
            TARGET dynamic_analyse POST_BUILD
            COMMAND valgrind --tool=callgrind --callgrind-out-file=${CALLGRIND_OUT} $<TARGET_FILE:${test_exec}>
            COMMENT "Running Valgrind with Callgrind on ${test_exec} and generating ${CALLGRIND_OUT}..."
        )

        # Add a custom command to generate the SVG file from the callgrind output
        add_custom_command(
            TARGET dynamic_analyse POST_BUILD
            COMMAND gprof2dot -f callgrind ${CALLGRIND_OUT} | dot -Tsvg -o ${SVG_OUT}
            DEPENDS ${CALLGRIND_OUT}
            COMMENT "Generating SVG report for ${test_exec}..."
        )
    endif()
endforeach()