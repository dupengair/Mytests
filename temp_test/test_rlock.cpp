#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


#define test_file "test_rlock.sh"
#define test_file_content "#!/bin/sh\n\necho \"this is rlock test!\""

void close_file(int& fd);

void start_proc()
{
    printf("process %d start\n", getpid());
}


void open_file(int& fd)
{
    fd = open(test_file, O_RDWR|O_CREAT);
    if(fd == -1)
        printf("[%d] open %s failed\n", getpid(), test_file);
    else 
        printf("[%d] open write file %s success \n", getpid(), test_file);
}

void write_file(int& fd) 
{
    if(fd < 0) 
        return;
    
    char buf[]=test_file_content;
    int sz=sizeof(buf);
    if(write(fd, buf, sz) != sz) {
        printf("[%d] write %d failed\n", getpid(), sz);
        close_file(fd);
    } else
        printf("[%d] write file successed\n", getpid());
}

void close_file(int& fd)
{
    if(fd < 0) 
        return;
    
    printf("[%d] close file %s \n", getpid(), test_file);
    close(fd);
    fd = -1;
}


void set_lock(int& fd, short type, off_t start, short whence, off_t len)
{
    if(fd < 0)
        return;

    char tp[10];
    if(type == F_RDLCK)
        sprintf(tp, "%s", "rlock");
    else if(type == F_WRLCK)
        sprintf(tp, "%s", "wlock");
    else 
        sprintf(tp, "%s", "unlock");

    char st[10];
    if(whence == SEEK_SET)
        sprintf(st, "%s", "start");
    else if(whence == SEEK_END)
        sprintf(st, "%s", "end");
    else 
        sprintf(st, "%s", "current");        
    
    struct flock fk;
    fk.l_type = type;
    fk.l_start = start;
    fk.l_whence = whence;
    fk.l_len = len;
    fk.l_pid = getpid();

    if(fcntl(fd, F_SETLK, &fk) == -1) {
        printf("[%d] set [%s] from [%s] at [%d] length [%d] failed!\n", getpid(), tp, st, start, len);
        perror("F_GETLK");
    } else
        printf("[%d] set [%s] from [%s] at [%d] length [%d] success!\n", getpid(), tp, st, start, len);
}

void get_lock(int& fd, short type, off_t start, short whence, off_t len)
{
    if(fd < 0)
        return;

    char tp[10];
    if(type == F_RDLCK)
        sprintf(tp, "%s", "rlock");
    else if(type == F_WRLCK)
        sprintf(tp, "%s", "wlock");
    else 
        sprintf(tp, "%s", "unlock");

    char st[10];
    if(whence == SEEK_SET)
        sprintf(st, "%s", "start");
    else if(whence == SEEK_END)
        sprintf(st, "%s", "end");
    else 
        sprintf(st, "%s", "current");        

    struct flock fk;
    fk.l_type = type;
    fk.l_start = start;
    fk.l_whence = whence;
    fk.l_len = len;

    if(fcntl(fd, F_GETLK, &fk) == -1) {
        printf("[%d] get [%s] from [%s] at [%d] length [%d] failed!\n", getpid(), tp, st, start, len);
        perror("F_GETLK");
    } else {
        char rtp[10];
        if(fk.l_type == F_UNLCK) {
            sprintf(rtp, "%s", "unlocked");
            printf("[%d] get [%s] [%s] from [%s] at [%d] length [%d]!\n", getpid(), tp, rtp, st, start, len);
        } else {
            sprintf(rtp, "%s", "locked");
            printf("[%d] get [%s] [%s] from [%s] at [%d] length [%d] by process [%d]!\n", getpid(), tp, rtp, st, start, len, fk.l_pid);
        }
    }
}

#include <list>
#include <algorithm>
#include <iostream>
using std::list;
using std::remove_if;
using std::cout;
using std::endl;
void test() {
    list<int> coll = {1, 2, 3, 4, 5, 6, 7, 8};
    int count = 0;

    cout << "coll: ";
    for(auto iter = coll.begin(); iter != coll.end(); iter++) {
        cout << *iter << " " ;
    }
    cout << endl;

    #if 0
    list<int>::iterator pos = remove_if(coll.begin(), coll.end(), 
					//[count](int) mutable {
					[&count](int) {
					       cout << "count = " << count << endl;
						return ++count == 3;
					});
    coll.erase(pos, coll.end());
    #else
    auto func = [count]() mutable {
					//[&count](int) {
					       cout << "count = " << count << endl;
						return ++count;
					};
    func();
    func();
    func();
    #endif

    cout << "<<< count = " << count << endl;

    cout << "coll: ";
    for(auto iter = coll.begin(); iter != coll.end(); iter++) {
        cout << *iter << " " ;
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
    
    pid_t pid;    
    int testfd = -1;
    
    start_proc();
    
    open_file(testfd);
    write_file(testfd);

    get_lock(testfd, F_WRLCK, 0, SEEK_SET, 1);
    
    set_lock(testfd, F_WRLCK, 0, SEEK_SET, 1);

    get_lock(testfd, F_WRLCK, 0, SEEK_SET, 1);

    get_lock(testfd, F_WRLCK, 0, SEEK_SET, 1);

    if((pid = fork()) < 0)
        perror("fork");
    else if(pid == 0) {
        // test inherent
        int testfd1 = -1;
        open_file(testfd1);
        get_lock(testfd1, F_WRLCK, 0, SEEK_SET, 1);
        set_lock(testfd1, F_RDLCK, 0, SEEK_SET, 1);

        // test close fd
        sleep(3);
        printf("[%d] get lock after parent exit!\n", getpid());
        get_lock(testfd1, F_WRLCK, 0, SEEK_SET, 1);
        set_lock(testfd1, F_RDLCK, 0, SEEK_SET, 1);

        close_file(testfd1);
    } else {
        get_lock(testfd, F_WRLCK, 0, SEEK_SET, 1);
        sleep(2);
        close_file(testfd);
    }    

    
}


