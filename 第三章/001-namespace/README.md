# 第三章实例代码
##### 001-fork_example.c代码功能说明
当程序调用fork()函数时，系统会创建新的进程，为其分配资源，例如存储数据和代码的空间，然后把原来进程的所有值都复制到新进程中，只有少量数值与原来的进程值不同，相当于复制了本身。

fork()调用一次，却能够返回两次（父进程与子进程各返回一次），通过返回值的不同就可以区分父进程与子进程。

1. 在父进程中，fork()返回新创建子进程的PID；
2. 在子进程中，fork()返回0;
3. 如果出现错误，fork()返回一个负值。 


在此段代码中，在语句fpid=fork()之前，只有一个进程在执行这段代码，在这条语句之后，就变成父进程和子进程同时执行了。

##### 002-uts.c和002-uts_v2.c代码功能说明
演示的是UTS namespace功能，此namespace提供了主机名和域名的隔离，这样每个Docker容器就可以拥有独立的主机名和域名了，在网络上可以被视作一个独立的节点，而非宿主机上的一个进程。

##### 003-ipc.c代码功能说明
IPC namespace演示IPC的隔离，运行程序前使用ipcmk -Q创建message queue，然后使用ipcs -q可以查看结果，进入程序后，使用ipcs -q查看不到之前声明的message queue，这说明IPC隔离成功了。

##### 004-pid.c代码功能说明
PID namespace表示PID隔离，不同的namespace中其pid可以和别的namespace下的相同。在运行程序后，进入了另一个namespace，输入echo $$可以看到pid为1。

##### 005-mount.c代码功能说明
MOUNT namespace表示文件挂载隔离，此时运行程序进入子进程后，先要执行mount -t proc proc /proc修复上次执行后带来的影响，然后运行ps -ef就只能看到两个进程，就看不到宿主机上的进程信息了，此时说明程序完成了所需的功能。

##### 006-network.c代码功能说明
NETWORK namespace用来隔离网络，进入程序后使用ip r命令看不到结果，说明成功了。在其他几个namespace中运行ip r命令后是可以正常输出的。          

##### 007-userns.c代码功能说明
User namespace这个代码在centos7上未能测试通过，但是他的实质功能是，进入这个namespace后，用户拥有所有权限，而不管进入用户的身份是什么。