
# Linux Lab installation and usage

* Homepage: <http://tinylab.org/linux-lab>
* Git Repo: <https://gitee.com/tinylab/linux-lab>

## Installation

Please install docker at first, see [Docker Installation](https://docs.docker.com/install/)

**This document: `docker-ce-installation.pdf` is recommended to use a faster docker server.**

To use docker commands without root user, please issue this command and reboot your X windows:

    $ sudo usermod -aG docker $USER

Then just issue:

    $ git clone https://gitee.com/tinylab/cloud-lab
    $ cd cloud-lab
    $ tools/docker/run linux-lab

If got 'Could not resolve host gitee.com', please configure it as following:

    $ sudo sh -c 'echo 212.64.62.174   gitee.com >> /etc/hosts'

Afterwards, it will launch a web browser and login the lab automatically.

Make sure it is not cloned with root, if so, there will be permission issue, change the owner to your account please:

    $ cd /path/to/cloud-lab
    $ USER=Your Account
    $ sudo chown -R $USER:$USER ./

## Use it

Just open the 'Linux Lab' terminal on the desktop, it will enter into the working directory: `/labs/linux-lab`.

Clone our course repo:

    $ cd src/examples/
    $ git clone https://gitlab.com/tinylab/360-elf.git
    $ cd 360-elf/

### C examples

    $ cd 01-init/
    $ cd hello-c
    $ make

See README.md for more.

### Assembly examples

    $ cd 01-init/
    $ cd hello-asm
    $ make

See README.md for more.

### Login with command line tools

Login:

    $ tools/docker/bash
    (guest) su ubuntu

    or

    $ tools/docker/ssh

Boot Linux-0.11-Lab with curses based UI:

    $ cd /path/to/linux-0.11-lab
    $ make boot-hd G=0

Exit with 'ALT+2' or 'ESC+2' to qemu monitor shell and input 'quit':

    (qemu) quit

### Debugging method

If `tools/docker/run` not work, please check the images, containers one by one.

Firstly, please make sure the images are downloaded completely:

    $ docker images | grep linux-lab
    tinylab/linux-lab                               latest              7f8f1986a2f9        6 weeks ago         4.11GB
    $ docker images | grep web
    tinylab/cloud-ubuntu-web                        latest              0b8b06cb2338        23 months ago       555MB

Otherwise, please download them manually:

    $ docker pull tinylab/linux-lab
    $ docker pull tinylab/cloud-ubuntu-web

If the speed is too slow, please must read this document: docker-ce-installation.pdf

Then, check if the containers are running well:

    $ docker ps -a | grep tinylab | egrep "linux-lab|web"
    d2912ed5bb64 tinylab/linux-lab "/tools/lab/run" 3 days ago Up 40 hours 22/tcp, 5900/tcp linux-lab-60029
    79bbab5f2a0e tinylab/cloud-ubuntu-web "/startup.sh" 5 weeks ago Up 40 hours 5900/tcp ...  cloud-ubuntu-web

Both of them should in **UP** status, if **Exited** or **Created**, please
remove them, pull the images manually and restart linux-lab:

    $ docker rm -f d2912ed5bb64
    $ docker rm -f 79bbab5f2a0e

    $ docker pull tinylab/linux-lab
    $ docker pull tinylab/cloud-ubuntu-web

    $ tools/docker/rerun linux-lab

If network not work in Linux Lab, please try to clean up the environment and rerun your lab:

    $ tools/docker/clean linux-lab
    $ tools/docker/rerurn linux-lab

### Record the learning procedure

Issue `showterm` command to start recording and `exit` command to stop recording.

    // start recording
    $ showterm

    // do what you want here, for example
    $ cd 01-init/hello-c
    $ make

    // stop recording
    $ exit

It will upload the learning procedure and generate a url, share this url to our course wechat group if want.

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
