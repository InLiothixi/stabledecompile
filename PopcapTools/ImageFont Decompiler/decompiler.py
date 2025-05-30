import os

current_directory = os.path.dirname(os.path.abspath(__file__))  
image_path = os.path.join(current_directory, "input.gif")  

print(os.path.exists(image_path)) 

import re

data_path = os.path.join(current_directory, "input.txt")  

# Function to extract the RectList from the text file
def extract_data(filename):
    with open(filename, "r", encoding="utf-8") as file:
        data = file.read()

    # Find the name after "Define"
    name_match = re.search(r"Define\s+(\w+)", data)
    name = name_match.group(1) if name_match else "Unknown"

    # Find all tuples in the format (x, y, width, height)
    pattern = re.findall(r"\(\s*(\d+),\s*(\d+),\s*(\d+),\s*(\d+)\)", data)

    # Convert to list of tuples with integers
    rect_list = [tuple(map(int, match)) for match in pattern]

    return {name: rect_list}

# Example usage
filename = data_path  # Replace with your actual file path
rect_list = extract_data(filename)
print(rect_list)

