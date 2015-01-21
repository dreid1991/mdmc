import matplotlib.pyplot as plt
from numpy import std
from math import *

#lines = open('outThermostatTest.dat').readlines()
lines = open('out.dat').readlines()

class DataGlob:
	def __init__(self, tEquil, tRun, dataInt):
		self.tEquil = tEquil
		self.tRun = tRun
		self.dataInt = dataInt
		self.data = []

dataGlobs = []
currentDataGlob = None
i=0
while i < len(lines):
	l = lines[i]
	if 'NEW RUN' in l:
		if currentDataGlob != None:
			dataGlobs.append(currentDataGlob)
		i+=1
		l = lines[i]
		turnsEquil, turnsRun, dataInt = [int(x) for x in l.split()]
		currentDataGlob = DataGlob(turnsEquil, turnsRun, dataInt)
	else:
		data = tuple([float(x) for x in l.split()])
		currentDataGlob.data.append(data)
	i+=1
dataGlobs.append(currentDataGlob)
xs = []
ys = []
dataIdx = 3
lastN = dataGlobs[0].tRun / dataGlobs[0].dataInt
for glob in dataGlobs:
	interval = glob.dataInt
	numSamples = glob.tRun / glob.dataInt
	print 'trun and data int', glob.tRun, glob.dataInt
	data = [d[dataIdx] for d in glob.data]
	truncatedData = data[-numSamples:]
	print interval, len(data), numSamples, numSamples * dataInt
	dev = std(truncatedData)
	err = dev / sqrt(float(len(truncatedData)))
	xs.append(interval)
	ys.append(err)
plt.plot(xs, ys)
plt.xlabel('Data interval')
plt.ylabel('kinetic energy error')
plt.show()

