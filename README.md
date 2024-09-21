# MIT6s081
### 安装运行环境
 sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 
 sudo apt-get remove qemu-system-misc
 wget https://download.qemu.org/qemu-5.1.0.tar.xz
 tar xf qemu-5.1.0.tar.xz
 cd qemu-5.1.0
 ./configure --disable-kvm --disable-werror --prefix=/usr/local --target-list="riscv64-softmmu"
 (如果缺包,放到gpt里面查询缺什么包之后安装)
 make


git clone 
git checkout -b branchname
..modify code and other
git status
git add .
git commit -m "some comments"
git push origin branchname 
..request merge
#after merge
git push -d origin branchname #delete branch
git pull origin main

## labs1 website
https://pdos.csail.mit.edu/6.828/2021/labs/util.html


(1) need to configure the environment of qemu(see README.md of S0681)<br/>
(2) git clone the source code of lab1(done)<br/>
(3) make qemu and run xv6<br/>
(4) supported command in xv6 <br/>
> ls:list the command supported

### task1:implent sleep 

> Implement the UNIX program sleep for xv6; your sleep should pause for a user-specified number of ticks. A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip.
Your solution should be in the file user/sleep.c.

tips:<br/>
use command line to call the user application,the applicaiton uses the system call to implment the sleep function.<br/>

(1)user/sleep.c , include user.h,which contains the system call that can be called.
> types.h:define int,short and other things.
> 

```cpp
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int n;
  if(argc!=2){
    fprintf(2, "Usage: sleep n...\n");
    exit(1);
  }
  n=atoi(argv[1]);
  sleep(n);
  exit(0);
}
```


(2) modify the makefile, like other user interface

```bash
UPROGS=\
	$U/_cat\
	$U/_echo\
	$U/_forktest\
	$U/_grep\
	$U/_init\
	$U/_kill\
	$U/_ln\
	$U/_ls\
	$U/_mkdir\
	$U/_rm\
	$U/_sh\
	$U/_stressfs\
	$U/_usertests\
	$U/_grind\
	$U/_wc\
	$U/_zombie\
	$U/_sleep\
```


### find(moderate)
要求用递归方式找到指定的文件夹下符合某个名字的文件，参考user/ls.c的实现方法.
```cpp
/user/find.c
void find(char *path, char *target) 




