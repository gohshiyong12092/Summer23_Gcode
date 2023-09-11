import difflib

file1_path = '/home/shiyong/Documents/Summer2023/Summer23_Gcode/benchy160_80.gcode'
file2_path = '/home/shiyong/Documents/Summer2023/Summer23_Gcode/benchyRemove_1_withPause160_80.gcode'
output_path = 'diff_results.txt'

with open(file1_path, 'r') as file1:
    file1_lines = file1.readlines()

with open(file2_path, 'r') as file2:
    file2_lines = file2.readlines()

differ = difflib.Differ()
diff_result = list(differ.compare(file1_lines, file2_lines))

with open(output_path, 'w') as output_file:
    output_file.write('\n'.join(diff_result))
