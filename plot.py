import sys

file_name1 = sys.argv[1]
file_name2 = sys.argv[2]

threads = []

print file_name1

for i in range(23):
	threads.append(i)

throughput_rcu = []
throughput_rw = []

with open(file_name1,'r') as file:
	for line in file:
		print line
		t = float(line)
		throughput_rcu.append(t)

with open(file_name2,'r') as file:
	for line in file:
		t = float(line.rstrip('\n'))
		throughput_rw.append(t)


import matplotlib.pyplot as plt

plt.plot(threads,throughput_rcu, '-bo', label = "Throughput for RCU")
plt.plot(threads,throughput_rw, '-ro', label = "Throughput for RW-lock")
plt.xlabel("Threads")
plt.legend()
plt.show()
