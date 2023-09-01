## UID: 705512370
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# Hash Hash Hash

One line description of this code.
This code provides a serial hash table implementation, along with two concurrent hash table implementations that each using different locking strategies.

## Building

Explain briefly how to build your program.
To build, simply run:
> make

## Running

Show an example run of your (completed) program on using the `-t` and `-s` flags
of a run where the base hash table completes in between 1-2 seconds.
To run the program, use:
> ./hash-table-tester
It takes two command link arguments:
-t changes the number of threads to use
-s changes the number of hash table entries to add per thread

Example run:
> ./hash-table-tester -t 4 -s 50000
Generation: 71,789 usec
Hash table base: 1,150,533 usec
  - 0 missing
Hash table v1: 2,132,880 usec
  - 0 missing
Hash table v2: 341,565 usec
  - 0 missing

## First Implementation

Describe your first implementation strategy here (the one with a single mutex).
Argue why your strategy is correct.

My first implementation strategy uses a single global lock for the entire hash table. By protecting the entire data structure with a single lock, it guarantees that only one thread can access the hash table at a time, which prevents any concurrent access issues such as race conditions or deadlock. It is easy to implement and understand, but can lead to performance issues when multiple threads are contending for the lock. Nevertheless, although it may be inefficient in highly concurrent environments, it is correct in that it provides thread-safety to the hash table.

### Performance

Run the tester such that the base hash table completes in 1-2 seconds.
Report the relative speedup (or slow down) with a low number of threads and a
high number of threads. Note that the amount of work (`-t` times `-s`) should
remain constant. Explain any differences between the two.

> ./hash-table-tester -t 1 -s 450000
Generation: 78,697 usec
Hash table base: 1,441,658 usec
  - 0 missing
Hash table v1: 1,527,644 usec
  - 0 missing

> ./hash-table-tester -t 4 -s 112500
Generation: 80,420 usec
Hash table base: 1,508,780 usec
  - 0 missing
Hash table v1: 2,674,879 usec
  - 0 missing

As we can see from the tests, the first implementation is faster with a lower number of threads than a higher number of threads. With 4 threads, it took ~1.1 seconds longer than with 1 thread. When using a global lock, only one thread can access the hash table no matter the number of threads available. As the number of threads increases, the amount of time each thread spends waiting for the lock also increases, leading to a decrease in performance. There is less contention with fewer threads, leading to better performance.

## Second Implementation

Describe your second implementation strategy here (the one with a multiple
mutexes). Argue why your strategy is correct.

My second implementation strategy uses a lock for each bucket in the hash table. This allows multiple threads to access different buckets without waiting for each other, which can significantly improve performance. The idea is to separate the hash table into smaller parts (each different bucket), and protect these buckets with their own separate lock. By doing this, we can decrease contention because threads can work independently of one another if they are accessing different buckets. Unlike the first approach, threads no longer have to wait for the entire data structure, they can just access their own section that they need.

### Performance

Run the tester such that the base hash table completes in 1-2 seconds.
Report the relative speedup with number of threads equal to the number of
physical cores on your machine (at least 4). Note again that the amount of work
(`-t` times `-s`) should remain constant. Report the speedup relative to the
base hash table implementation. Explain the difference between this
implementation and your first, which respect why you get a performance increase.

> ./hash-table-tester -t 1 -s 450000
Generation: 87,345 usec
Hash table base: 1,764,195 usec
  - 0 missing
Hash table v2: 2,337,976 usec
  - 0 missing

> ./hash-table-tester -t 4 -s 112500
Generation: 82,382 usec
Hash table base: 1,717,350 usec
  - 0 missing
Hash table v2: 570,273 usec
  - 0 missing

As we can see from the tests, the second implementation is much slower with a lower number of threads than a higher number of threads. With 4 threads, we see a ~1.7 second speed increase. The performance increase observed can be attributed to the reduced contention for locks and the ability of multiple threads to work simultaneously on different buckets. With my first implementation, only one thread could access the hash table at a time, which decreased performance with multiple threads since they were all contending for the lock. With the new implementation, this is no longer the case. Multiple threads can now access the hash table at once, so increasing the number of threads actually helps the performance.

## Cleaning up

Explain briefly how to clean up all binary files.
To clean up, simply run:
> make clean
