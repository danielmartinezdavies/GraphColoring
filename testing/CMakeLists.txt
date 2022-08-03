
add_test(NAME test1 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file.txt" ${CMAKE_SOURCE_DIR}/testing/test1_solution.txt ${PROJECT_BINARY_DIR}/best_solution_found_0.txt)