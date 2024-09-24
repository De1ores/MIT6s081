#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


#define MAXLINE 256

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *args[MAXARG];
    int i;

    if (argc < 2) {
        fprintf(2, "Usage: xargs command [args...]\n");
        exit(1);
    }

    // 准备要执行的命令
    for (i = 1; i < argc; i++) {
        args[i - 1] = argv[i]; // 填充命令和参数
    }
    args[i - 1] = 0; // 以零终止参数数组

    while (1) {
        int j = 0;
        // 手动读取输入
        while (j < MAXLINE - 1) {
            char c;
            if (read(0, &c, 1) != 1) {
                break; // 如果没有更多输入，则退出
            }
            if (c == '\n') {
                break; // 遇到换行符停止读取
            }
            line[j++] = c; // 将字符存入行
        }
        line[j] = 0; // 以零终止字符串

        if (j == 0) { // 如果没有读取到任何字符，退出
            break;
        }

        // 创建新进程
        int pid = fork();
        if (pid < 0) {
            fprintf(2, "Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            // 子进程：准备参数
            args[i - 1] = line; // 将当前行作为最后一个参数
            exec(args[0], args); // 执行命令
            fprintf(2, "Exec failed\n");
            exit(1);
        } else {
            // 父进程：等待子进程完成
            wait(0);
        }
    }

    exit(0);
}