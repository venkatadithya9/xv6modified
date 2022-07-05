Steps to run the file:
make clean
make qemu (DEFAULT scheduler is used)
make qemu SCHEDULER=<DEFAULT, FCFS, PBS, MLFQ>

1. waitx system call ant time user program:

Implemented waitx in proc.c and included it in various other files: syscall.c, syscall.h, sysproc.c, user.h and usys.S
Implementation consisted of copyinf the pre-existing wait function and changin input paramaters and calculating rtime and wtime. Time values were found by initializing in allocproc() in proc.c and then incrementing while running in trap.c.
Additional variables ctime, rtime, iotime, etime were defined in the proc structure in proc.h.

2. FCFS Scheduling:

for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
      if(p->state != RUNNABLE)
      {
        continue;
      }
      else 
      {
        if(p->ctime < minctm)
        {
          flag = 1;
          minp = p;
          minctm = p->ctime;
        }
        else if(p->ctime == minctm && flag && p->pid < minp->pid)
        {
          minp = p;
        }
      }

As seen from the above code, based on creation time the process is picked and run.

3. PBS Scheduling:

 for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {

      if(p->state == RUNNABLE)
      {
        if(p->priority < minpr)
        {
          flag = 1;
          minp = p;
          minpr = p->priority;
        }
        else if(p->priority == minpr && flag && p->n_pick < minp->n_pick)
        {
          minp = p;
        }
      }
      else
      {
        continue;
      }
    }

Similar to FCFS but process is picked based on the priority variable in the proc structure, priority is initialized in allocproc() in proc.c

4. set_priority system call and setPriority user program

for(p1 = ptable.proc; p1 < &ptable.proc[NPROC]; p1++)
  {
    if(p1->pid == pid)
    {
      chk = 1;
      prevpr = p1->priority;
      p1->priority = priority;
      break;
    }
  }

As seen above, based on given PID the processes is found and its priority is altered.

in setPriority.c the set_priority system call is used.

5. MLFQ Scheduling

Added additional variables to proc structure to measure ticks in each queue, number of times picked, last executed time, etc.
Traverse over the proc table to check for processes which need to be pushed into lower priority queues based on time spent and those which need to be pushed up as part of ageing.
Then find runnable functions in each queue and execute them in order of priority of each queue.

Answer for question: If a process keeps exciting queue network and rejoining it will enjoy the same priority status for longer time, as every time it leaves the queue network its time spent in the queue is reeset, hence prolonging its stay in that same priority queue.

6. ps

ps system call has been impplemented in proc.c for two cases, MLFQ and non-MLFQ. ps.c gives the user ability to use ps system call.

7. Benchmark results

Round Robin Default: 
$ time benchmark
Wait time is 2008
Run Time is 3

FCFS :
$ time benchmark
Wait time is 2258
Run Time is 3

PBS:
$ time benchmark
Wait time is 2003
Run Time is 3

MLFQ:
$ time benchmark
Wait time is 2189
Run Time is 4
We can see  PBS and RR are almost same than MLFQ then FCFS as it has a lot of waiting time.MLFQ also has the overhead of maintaining multiple queues which adds to the waittinme of process.

6. 
      