import difflib

def compare_files(file1_path, file2_path):
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        file1_lines = file1.readlines()
        file2_lines = file2.readlines()

    differ = difflib.Differ()
    diff = list(differ.compare(file1_lines, file2_lines))

    return diff

file1_path = '/home/shiyong/Documents/Summer2023/Summer23_Gcode/UMS5_3DBenchy_1_with_pause.gcode'
file2_path = '/home/shiyong/Documents/Summer2023/Summer23_Gcode/benchyRemove_1_withPause160_80.gcode'
differences = compare_files(file1_path, file2_path)

for line in differences:
    print(line)
