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

sd




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


git 