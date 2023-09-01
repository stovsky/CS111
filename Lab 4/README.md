## UID: 705512370

(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# Hey! I'm Filing Here

This code implements a 1 MiB ext2 file system with 2 directories, 1 regular file, and 1 symbolic link.

## Building

To build the program, run:
> make

## Running

To compile, run:
> ./ext2-create
To mount, run:
> mkdir mnt
> sudo mount -o loop cs111-base.img mnt

Example output of 'ls -ain' in the mounted system:
total 7
     2 drwxr-xr-x 3    0    0 1024 Mar 15 18:52 .
942564 drwxr-xr-x 4 1000 1000 4096 Mar 15 18:52 ..
    13 lrw-r--r-- 1 1000 1000   11 Mar 15 18:52 hello -> hello-world
    12 -rw-r--r-- 1 1000 1000   12 Mar 15 18:52 hello-world
    11 drwxr-xr-x 2    0    0 1024 Mar 15 18:52 lost+found

## Cleaning up

To unmount, run:
> sudo umount mnt
To remove mount directory, run:
> rmdir mnt
To clean up, run:
> make clean
