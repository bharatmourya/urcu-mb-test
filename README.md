# urcu-mb-test
For testing usage of urcu-mb and other flavours of RCU

TESTS : 

1. How read throughput is affected with and without memory-barriers based RCU

SETUP :
	a) 'n' readers , 'm' writers , one linked list with size 's'
	b) Reader takes rcu_read_lock and reads all the elements in list
	c) Writer selects a random element and writes to it and defer-frees the old-copy
	d) For different flavours do the according thing to run properly
		1)For QSBR add queiscent-state report, register_thread (and rcu_read_lock?)
		2)For MB based add rcu_read_lock (and register_thread?)
		3)For signal based same as MB-RCU  

Throughput for    :	R/W 99-1  :    R/W 90-10  :     R/W 80-20     :     R/W 70-30
---------------------------------------------------------------------------------------
qsbr-based-rcu    :               :               :                   :
mb-based rcu      :               :               :                   :
signal-based-rcu  :               :               :                   :

Result : If there is significal overhead caused by signal-based RCU then we can say automatically identifying
yield points can be a good problem as reduces a huge overhead.


2. Test how read throuput is affected when no-of writers increase with different ratios

Setup is similar to the previous experiment but now we see how read throughput is getting effected as well as the entire
execution time compared to a RW lock?

TODO: see boost:thread, shared_lock for an implementation of R/W lock.

Do it for QSBR and a RW lock?

no-of readers     : 99    90    80    70    60
no-of writers     : 1     10    20    30    40
throughput        : --    --    --    --    --

Result :
a. If the entire execution is degraded significantly than reader writer lock then we have some problem.
b. If write throughput is degradedd significantly then we are are more unfair to writers.
c. Find the tipping point compared to R/W lock.
