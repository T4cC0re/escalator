# escalator
###### Sudo after the fact!

Note: This repository is mainly hosted on [GitLab](https://https://gitlab.com/T4cC0re/escalator). To raise issues and contribute, please go there.

## Why?
We've all been there. We opened a file in an editor, spent 5 hours editing it and... "Dammit, didn't sudo..."

Not again! Use `escalator` to sudo the editor after the fact!

## What does it do?

This little kernel module will take the `task_struct` of the passed process, get it's `cred` & `real_cred` and patch them to be root. While in my tests that works awesome, **here be dragons** and it might not work for you!
It was developed towards a `4.18.12-arch1-1-ARCH` kernel on Arch Linux. Your results may vary on other kernels.

## Usage
Note: `/sys/kernel/escalate_process` is only writable by root!
```
# Compile
make # You need kernel headers installed!

# Install via
sudo make install
modprobe escalator pid=<pid of process to escalate - Optional>

# Load without install via
sudo insmod ./escalator.ko pid=<pid of process to escalate - Optional>

# Use with helper script:
escalator <pid ...>

# Use manually:
echo <pid> | sudo tee /sys/kernel/escalate_process
```

## TODOs

 - `pkill` like 'escalate all processes that match X'
 - set capabilities
 - set any UID/GID desired instead of always setting 0 (root)

## Is it any good?

[Yes](https://news.ycombinator.com/item?id=3067434)
