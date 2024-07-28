with open("filenames.txt", "w") as f:
    f.write("")

with open("files.txt", "r") as f2:
    for line in f2:
        with open("filenames.txt", "a") as f:
            f.write(line.split(" ")[-1])