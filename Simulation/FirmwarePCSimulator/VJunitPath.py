import os

def find_and_replace_vjunit(base_path):
    # Define the path to search and the file name
    target_file = "vjunit.py"

    # Walk through the base_path to locate the file
    for root, dirs, files in os.walk(base_path):
        if target_file in files:
            file_path = os.path.join(root, target_file)
            print(f"Found {target_file} at: {file_path}")

            # Read and replace content in the file
            with open(file_path, 'r') as file:
                content = file.read()

            # Replace the specified line
            new_content = content.replace(
                "children = testcase.getchildren()",
                "children = list(testcase)"
            )

            # Write the updated content back to the file
            with open(file_path, 'w') as file:
                file.write(new_content)

            print(f"Updated {target_file} successfully.")
            return

    print(f"{target_file} not found in {base_path}.")

# Set the base path to search for vjunit.py
base_path = "/workspace/venv/"
find_and_replace_vjunit(base_path)
