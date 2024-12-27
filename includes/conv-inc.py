#!/usr/bin/python3
import os,sys

try:
	os.makedirs("bin")
except:
	pass

try:
	os.makedirs("obj")
except:
	pass

try:
	fname = sys.argv[1]
except:
	fname = input("include file to convert?")

try:
	with open(fname+".inc","r") as f:
		lines = f.read().splitlines()
except:
	quit()

letters = {l:[] for l in "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_."}

def detectBase(line,i):
	j = i
	while line[j] in "0123456789ABCDEF":
		j+=1
		if j>=len(line): break
	base=10
	if j<len(line):
		if line[j]=='h': base=16
		if line[j]=='b': base=2
		if line[j]=='o': base=8
	return j,base

lx=0
while lx<len(lines):
	line=lines[lx]; lx+=1
	if not len(line):
		continue
	if line[0]==';' or not len(line):
		continue
	elif line[0]=='?':
		if ":=" in line:
			k = line.find(':=')
			i = k+2
			while line[i] in " \t":
				i+=1
				if i>=len(line): break
			if i<len(line):
				j,base = detectBase(line,i)
				if j>i:
					word = line[1:k].replace("\t","").replace(" ","")
					try:
						dt = [word,int(line[i:j],base)]
						letters[word[0]].append(dt)
					except Exception as e:
						print("[WARNING] Internal Error:",e)
		elif ":;basm-macro" in line:
			pass
			# k = line.find(":;basm_macro")
			# word = line[1:k].upper().replace("_","[").replace(".","[").replace("\t","").replace(" ","")
			# toasm = []
			# while line!=";end macro":
				# line = lines[lx]; lx+=1
				# toasm.append(line)

with open("obj/"+fname+".bin","wb") as f:
	s=b"eZ80 INC"
	f.write(s)
	tbloff = 8
	f.write(bytes([0]*108))
	tbl = []
	for letter in letters.keys():
		tbl.append(f.tell())
		for word in letters[letter]:
			f.write(bytes(word[0],'UTF-8'))
			arg=[word[1]&0xFF,(word[1]//0x100)&0xFF,(word[1]//0x10000)&0xFF]
			a=3
			for i in range(2, -1, -1):
				if arg[i]:
					break
				else:
					a-=1
			if not a: a=1
			f.write(bytes([0,a]+arg[:a]))
		f.write(bytes([0]))

	size=f.tell()
	if size>0xFFE8:
		print("File too large!",size)
		quit()

	f.seek(tbloff)
	for i in range(54):
		f.write(bytes([tbl[i]&0xFF,(tbl[i]//0x100)&0xFF]))

with open("obj/"+fname+".asm","w") as f:
	if len(fname)>8: name = fname[:8]
	else: name=fname
	f.write("include 'include/tiformat.inc'\nformat ti archived appvar '"+name+"'\nfile 'obj/"+fname+".bin'")

os.system("fasmg obj/"+fname+".asm bin/"+fname+".8xv")
