
file = open ("main.cpp")
out = open ("lineprint_main.cpp", "w")
i = 1

for line in file.read().split("\n"):
	i+=1
	if(line.endswith(";")):
		line+="cout<<\""+str(i)+"\"<<endl;\n"
		out.write(line)
	else:
		out.write(line+"\n")
