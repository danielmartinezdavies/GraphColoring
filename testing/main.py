import os
import subprocess
import sys

if __name__ == '__main__':
    if len(sys.argv) < 5:
        print("Invalid number of arguments. 5 needed. ")
        exit(1)
    else:
        print(os.getcwd() + "\n")
        executable_path = str(sys.argv[1])
        input_file = str(sys.argv[2])
        output_file = str(sys.argv[3])
        test_file = str(sys.argv[4])
        parameters = ""
        num_runs = 1
        command = [executable_path, "--input_file", input_file, "--disable_printing"]
        if len(sys.argv) > 5:
            parameters = str(sys.argv[5])
            i = 0
            for string in parameters.split():
                command.append(string)
                if string == "--num_runs" and i + 1 < len(parameters.split()):
                    num_runs = int(parameters.split()[i+1])
                i += 1

        p2 = subprocess.run(command, stdout=subprocess.PIPE)

        cwd = os.getcwd()
        if p2.returncode != 0:
            print("Error while running program")
            print(f"{executable_path}, {input_file}")
        p = None
        output_file_index = output_file.find(".txt")
        test_file_index = test_file.find(".txt")
        for i in range(num_runs):
            i_string = str(i)
            current_output_file = output_file[:output_file_index-1] + i_string + output_file[output_file_index:]
            if i == 0:
                i_string = ""
            current_test_file = test_file[:test_file_index] + i_string + test_file[test_file_index:]
            p = subprocess.run(["diff", cwd + "/" + current_output_file, current_test_file], stdout=subprocess.PIPE)
            if p.returncode != 0:
                print("File mismatch")
                exit(p.returncode)



