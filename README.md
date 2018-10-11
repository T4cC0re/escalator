# escalator
###### Sudo after the fact!

# Usage

```
make # Youn need kernel headers installed!
sudo insmod ./escalator.ko pid=<pid of process to escalate>
sudo rmmod ./escalator.ko
```

# TODO

 - Char dev based escalation / maybe sysfs instead?
   - load module once
   - escalate via `echo <pid> | sudo tee /dev/escalator`
   - dev should be only writable by root for security reasons
 - `pkill` like 'escalate all processes that match X'
 - set capabilities
