
set(SOLUTION_FILENAME "best_solution_found_0.txt")

add_test(NAME test1 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test1_solution.txt)

add_test(NAME test2 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file2.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test2_solution.txt)

add_test(NAME test3 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_solution.txt)

add_test(NAME test4 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_mutation_prob_solution.txt "--mutation_prob 1000")

add_test(NAME test5 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_pop_size_solution.txt "--population_size 50")

add_test(NAME test6 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_tournament_size_solution.txt "--tournament_size 5")

add_test(NAME test7 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_seed_solution.txt "--seed 400")