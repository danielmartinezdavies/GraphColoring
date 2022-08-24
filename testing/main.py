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
        command = [executable_path, "--input_file", input_file, "--disable_printing"]
        if len(sys.argv) > 5:
            parameters = str(sys.argv[5])
            for string in parameters.split():
                command.append(string)

        p2 = subprocess.run(command, stdout=subprocess.PIPE)

        cwd = os.getcwd()
        if p2.returncode != 0:
            print("Error while running program")
            print(f"{executable_path}, {input_file}")
        p = subprocess.run(["diff", cwd + "/" + output_file, test_file], stdout=subprocess.PIPE)
        if p.returncode != 0:
            print("File mismatch")
        exit(p.returncode)
