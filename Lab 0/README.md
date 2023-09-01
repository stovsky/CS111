# A Kernel Seedling

Adds a file /proc/count which reports the current number of running processes.

## Building

Build module:
> make
Insert module into kernel:
> sudo insmod proc_count.ko

## Running

Run module:
> cat /proc/count
  -Should expect a single integer representing the number of processes running on the machine.


## Cleaning Up

Remove module:
> sudo rmmod proc_count
Clean up:
> make clean

## Testing

Module tested on kernel release version 5.14.8-arch1-1