import difflib

def compare_and_store_diff(file1_path, file2_path, output_path):
    with open(file1_path, 'r') as file1:
        file1_lines = file1.readlines()
        

    with open(file2_path, 'r') as file2:
        file2_lines = file2.readlines()
        
    print("here\n")
    differ = difflib.Differ()
    diff = list(differ.compare(file1_lines, file2_lines))
    
    different_lines = [line[2:] for line in diff if line.startswith('- ') or line.startswith('+ ')]
    
    with open(output_path, 'w') as output_file:
        output_file.write('\n'.join(different_lines))

if __name__ == "__main__":
    file1_path = "/home/shiyong/Documents/Summer2023/Summer23_Gcode/benchy160_80.gcode"
    file2_path = "/home/shiyong/Documents/Summer2023/Summer23_Gcode/benchyRemove_1_withPause160_80.gcode"
    output_path = "diff.txt"

    compare_and_store_diff(file1_path, file2_path, output_path)
    print("Differences have been stored in", output_path)
