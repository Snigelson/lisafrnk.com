from PIL import Image
import sys

input=Image.open(sys.argv[1])
pixels=input.load()

out_even=[]
out_odd=[]

for y in range(200):
	for x in range(0,200,4):
		out = (pixels[x+0,y] & 0x03) << 6
		out|= (pixels[x+1,y] & 0x03) << 4
		out|= (pixels[x+2,y] & 0x03) << 2
		out|= (pixels[x+3,y] & 0x03) << 0
		if (y%2):
			out_odd.append(out)
		else:
			out_even.append(out)



def hexify_rle_line(data):
	totc=0
	out=""

	curc=None;
	numc=0;
	for y in range(100):
		for x in range(50):
			c = data[y*50+x]
			if c != curc:
				if curc is not None:
					out+="0x{:02X},".format(curc)
					out+="0x{:02X},".format(numc)
					totc+=numc
				curc = c
				numc = 0
			numc+=1

	out+="0x{:02X},".format(curc)
	out+="0x{:02X},".format(numc)
	totc+=numc

	return out[:-1]

def hexify_straight(data):
	out=""
	for b in out_odd:
		out+="0x{:02X},".format(b)
	return out[:-1]


print ('#include "bmpdata.h"\n')

print("const unsigned char bmp_even[] = {")
print(hexify_rle_line(out_even))
print("};\n");

print("const unsigned char bmp_odd[] = {")
print(hexify_rle_line(out_odd))
print("};\n");


