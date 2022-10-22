# Linux-semaphores-learning-exercise
Using fork() to create child processes and using semaphores to manage execution between parnet and child

## Learning objectives and challlenges:
* maked sure no race condition is happening i.e the child always print first.
* Make sure the child prints first then the parent
* Found difficulty in displaying the child print. Got arround it by makeing the print call first before calling semaphore P().

## How to run the code
```bash
  gcc LAB4.c
  ./a.out
```
### Output
```bash
  Child: It is the child process!
  Parent: It is the parent process!
```
## Things to Note:
* The code needs to run on a system which has a linux operating system
* This exercise covers topics from the book: Beginning Linux® Programming 4th Edition Neil Matthew Richard Stones
