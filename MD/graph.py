import matplotlib.pyplot as plt
lines = open('out.dat').readlines()
xss = []
for l in lines:
	if len(l.split()):
		xss.append([float(x) for x in l.split()])
for i, xs in enumerate(xss):
	plt.plot(xs, label=str(i))
plt.legend();
plt.show()
