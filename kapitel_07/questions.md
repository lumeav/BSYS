
## 1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

## ./scheduler.py -p FIFO -j 3 -l 200,200,200 -c

Here is the job list, with the run time of each job:
Job 0 ( length = 200.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 200.0 )

** Solutions **

Execution trace:
[ time 0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
[ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
[ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
Job 0 -- Response: 0.00 Turnaround 200.00 Wait 0.00
Job 1 -- Response: 200.00 Turnaround 400.00 Wait 200.00
Job 2 -- Response: 400.00 Turnaround 600.00 Wait 400.00

Average -- Response: 200.00 Turnaround 400.00 Wait 200.00

----------------------------------------------------------------------------------------------------

## ./scheduler.py -p SJF -j 3 -l 200,200,200 -c

Here is the job list, with the run time of each job:
Job 0 ( length = 200.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 200.0 )

** Solutions **

Execution trace:
[ time 0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
[ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
[ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
Job 0 -- Response: 0.00 Turnaround 200.00 Wait 0.00
Job 1 -- Response: 200.00 Turnaround 400.00 Wait 200.00
Job 2 -- Response: 400.00 Turnaround 600.00 Wait 400.00

Average -- Response: 200.00 Turnaround 400.00 Wait 200.00

----------------------------------------------------------------------------------------------------

## 2. Now do the same but with jobs of different lengths: 100, 200, and 300.

## ./scheduler.py -p FIFO -j 3 -l 100,200,300 -c

Here is the job list, with the run time of each job:
Job 0 ( length = 100.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 300.0 )

** Solutions **

Execution trace:
[ time 0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
[ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
[ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
Job 0 -- Response: 0.00 Turnaround 100.00 Wait 0.00
Job 1 -- Response: 100.00 Turnaround 300.00 Wait 100.00
Job 2 -- Response: 300.00 Turnaround 600.00 Wait 300.00

Average -- Response: 133.33 Turnaround 333.33 Wait 133.33

----------------------------------------------------------------------------------------------------

## ./scheduler.py -p SJF -j 3 -l 100,200,300 -c

Here is the job list, with the run time of each job:
Job 0 ( length = 100.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 300.0 )

** Solutions **

Execution trace:
[ time 0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
[ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
[ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
Job 0 -- Response: 0.00 Turnaround 100.00 Wait 0.00
Job 1 -- Response: 100.00 Turnaround 300.00 Wait 100.00
Job 2 -- Response: 300.00 Turnaround 600.00 Wait 300.00

Average -- Response: 133.33 Turnaround 333.33 Wait 133.33

----------------------------------------------------------------------------------------------------

## 3. Now do the same, but also with the RR scheduler and a time-slice of 1.

## ./scheduler.py -p RR -j 3 -l 100,200,300 -c

Here is the job list, with the run time of each job:
Job 0 ( length = 100.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 300.0 )

** Solutions **

Execution trace:
[ time 0 ] Run job 0 for 1.00 secs
[ time 1 ] Run job 1 for 1.00 secs
[ time 2 ] Run job 2 for 1.00 secs
[ time 3 ] Run job 0 for 1.00 secs
[ time 4 ] Run job 1 for 1.00 secs
[ time 5 ] Run job 2 for 1.00 secs
[ time 6 ] Run job 0 for 1.00 secs
...

Final statistics:
Job 0 -- Response: 0.00 Turnaround 298.00 Wait 198.00
Job 1 -- Response: 1.00 Turnaround 499.00 Wait 299.00
Job 2 -- Response: 2.00 Turnaround 600.00 Wait 300.00

Average -- Response: 1.00 Turnaround 465.67 Wait 265.67

----------------------------------------------------------------------------------------------------

## 4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

J0 <= J1 <= J2

----------------------------------------------------------------------------------------------------

## 5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

Job length == quantum length

----------------------------------------------------------------------------------------------------

## 6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

Response time increases also.

----------------------------------------------------------------------------------------------------

## 7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

worst job:
rt = (N-1) * ql

average response time:
k = [0; N-1]
rt = Sum(k * ql) / N
