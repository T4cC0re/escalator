# escalator
###### Sudo after the fact!

# Usage

```
echo <pid of process to escalate> | sudo tee /sys/kernel/escalator/escalate_process

# Install via
sudo make install
modprobe escalator pid=<pid of process to escalate - Optional>

# Load without install via
make # Youn need kernel headers installed!
sudo insmod ./escalator.ko pid=<pid of process to escalate - Optional>

```

# TODO

 - `pkill` like 'escalate all processes that match X'
 - set capabilities
 - set any UID/GID desired instead of always setting 0 (root)
