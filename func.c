


void reboot(void) {
    int ret;
    char *argv[2], *envp[4];

    argv[0] = "/sbin/reboot";
    argv[1] = NULL;
    envp[0] = "HOME=/";
    envp[1] = "PWD=/";
    envp[2] = "PATH=/sbin";
    envp[3] = NULL;
    ret = call_usermodehelper(argv[0], argv, envp, 0);
    printk(KERN_INFO "trying to reboot (ret = %d)", ret);
}