
local filename = "/lfs1/text.txt"

file = io.open(filename, "w+")
file:write("I love lua--\n")
file:write("I love zephyr--\n")
file:close()

for line in io.lines(filename) do
    print(line)
end
