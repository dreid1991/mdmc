import matplotlib.pyplot as plt
nums = [float(x) for x in open('pos.dat').readlines()[0].split()]
plt.plot(nums)
plt.show()
