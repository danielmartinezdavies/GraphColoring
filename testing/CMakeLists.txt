
set(SOLUTION_FILENAME "best_solution_found_0.txt")

add_test(NAME test1 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test1_solution.txt "" t1)

add_test(NAME test2 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file2.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test2_solution.txt "" t2)

add_test(NAME test3 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_solution.txt "" t3)

add_test(NAME test4 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_mutation_prob_solution.txt "--mutation_prob 1000" t4)

add_test(NAME test5 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_pop_size_solution.txt "--population_size 50" t5)

add_test(NAME test6 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_tournament_size_solution.txt "--tournament_size 5" t6)

add_test(NAME test7 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_seed_solution.txt "--seed 400" t7)

add_test(NAME test8 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_num_runs_solution.txt "--num_runs 3" t8)

add_test(NAME test9 WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test9 COMMAND python3 ${CMAKE_SOURCE_DIR}/testing/main.py
        ${PROJECT_BINARY_DIR}/GraphColoring "${CMAKE_SOURCE_DIR}/examples/input_file3.txt"
        ${SOLUTION_FILENAME} ${CMAKE_SOURCE_DIR}/testing/test3_multiple_params.txt "--num_runs 3 --tournament_size 3 --population_size 1000" t9)
