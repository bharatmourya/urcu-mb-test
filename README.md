# urcu-mb-test
For testing usage of urcu-mb

1. how read throughput is affected with and without memory-barriers based RCU


Throughput for    :     R/W 99-1  :    R/W 90-10  :     R/W 80-20     :     R/W 70-30
---------------------------------------------------------------------------------------
qsbr-based-rcu    :               :               :                   :
mb-based rcu      :               :               :                   :
signal-based-rcu  :               :               :                   :

2. Test how read throuput is affected when no-of writers increase with different rations 

no-of readers     : 99    90    80    70    60
no-of writers     : 1     10    20    30    40
throughput        : --    --    --    --    --

