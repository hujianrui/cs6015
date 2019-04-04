import csv
import os
import subprocess

def frange(start, stop, step):
    i = start
    while i < stop:
        yield i
        i += step

def captureOutput(arrivalRate, serviceTime, listMarket, listBank):
    args = ["./simulator" , str(arrivalRate), str(serviceTime), "7890"]
    popen = subprocess.run(args, stdout=subprocess.PIPE)
    output = popen.stdout.decode("utf-8").split('\n')
    bank = output[0].split()
    supermarket = output[1].split()
    listBank.append(bank[len(bank) - 1])
    listMarket.append(supermarket[len(supermarket) - 1])

fileM = open("supermarket.csv", "w")
fileB = open("bank.csv", "w")
fileWriterM = csv.writer(fileM);
fileWriterB = csv.writer(fileB);
    
zAxis = ["Arrivalrate"]
for temp in frange(0.0, 5.0, 0.5):
    zAxis.append(temp)
fileWriterM.writerow(zAxis);
fileWriterB.writerow(zAxis);

for arrivalRate in range(0, 10, 1):
    listMarket = [arrivalRate]
    listBank = [arrivalRate]
    serviceTime = 0.0
    for serviceTime in frange(0.0, 5.0, 0.5):
        captureOutput(arrivalRate, serviceTime, listMarket, listBank)
    fileWriterM.writerow(listMarket)
    fileWriterB.writerow(listBank)

