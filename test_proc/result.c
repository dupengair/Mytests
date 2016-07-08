/*
 * An I2C driver for the Intersil ISL 12022
 *
 * Author: Roman Fietze <roman.fietze@telemotive.de>
 *
 * Based on the Philips PCF8563 RTC
 * by Alessandro Zummo <a.zummo@towertech.it>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 */
 
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#define DRV_VERSION "0.1"
#define DEVICE_NAME "test_proc"
#define PROCDIR  DEVICE_NAME
#define PROCREG "test_proc_entry1"
#define PROCDEV "test_proc_entry2"
struct proc_dir_entry *proc_dir = NULL;
/*------------------------------------------------------------------
 *	test_proc_Open
 *----------------------------------------------------------------*/
static int test_proc_Open(struct inode *inode, struct file *file)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
/*------------------------------------------------------------------
 *	test_proc_Close
 *----------------------------------------------------------------*/
static int test_proc_Close(struct inode *inode, struct file *file)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
/*------------------------------------------------------------------
 *	test_proc_Write
 *----------------------------------------------------------------*/
static ssize_t test_proc_Write(struct file *file, const char *buf, size_t count, loff_t *offset)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
/*------------------------------------------------------------------
 *	test_proc_Read
 *----------------------------------------------------------------*/
static ssize_t test_proc_Read(struct file *file, char *buf, size_t count, loff_t *offset)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
/*------------------------------------------------------------------
 *	文件操作结构体
 *----------------------------------------------------------------*/
static struct file_operations test_proc_fops = 
{
    .owner     = THIS_MODULE,
    .open	     = test_proc_Open,
    .release   = test_proc_Close,
    .write	     = test_proc_Write,
    .read	     = test_proc_Read,
};
/*------------------------------------------------------------------
 *	proc 文件 系统操作
 *----------------------------------------------------------------*/
static int test_proc_readReg(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
static int test_proc_readDev(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return 0;
}
static int test_proc_WriteDev(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    return count;
}
static int test_proc_ProcInit(void)
{
    struct proc_dir_entry *entry1;
    struct proc_dir_entry *entry2;
    int retval = 0;
    printk("in func : %s <%d> [%s] \n", __func__, __LINE__, __FILE__);
    proc_dir = proc_mkdir(PROCDIR, NULL);
    if (!proc_dir)
        {
        printk("%s: %s fail!\n", __func__, PROCDIR);
        retval = -ENOMEM;    
        }
    entry1 = create_proc_entry(PROCREG, S_IRUGO, proc_dir);
    if (entry1 == NULL) 
        {
        printk("%s: %s fail!\n", __func__, PROCREG);
        retval = -ENOMEM;
        } 
    else 
        {
        entry1->read_proc =  test_proc_readReg;
        entry1->proc_fops = &test_proc_fops;
        }
    entry2 = create_proc_entry(PROCDEV, S_IRUGO, proc_dir);
    if (entry2 == NULL) 
        {
        printk("%s: %s fail!\n", __func__, PROCDEV);
        retval = -ENOMEM;
        } 
    else 
        {
        entry2->read_proc =  test_proc_readDev;
        entry2->write_proc =  test_proc_WriteDev;
        entry2->proc_fops = &test_proc_fops;
        }
    return retval;
}
static int test_proc_ProcDel(void)
{
    remove_proc_entry(PROCREG, proc_dir);
    remove_proc_entry(PROCDEV, proc_dir);
    return 0;
}
/*------------------------------------------------------------------
 *	设备驱动模块加载
 *----------------------------------------------------------------*/
static int __init test_proc_Init(void)
{
    test_proc_ProcInit();
    printk(KERN_INFO"test_proc Driver sucessfully loaded, version : %s\n", DRV_VERSION);
    return 0;
}
/*------------------------------------------------------------------
 *	设备驱动模块卸载
 *----------------------------------------------------------------*/
static void __exit test_proc_Exit(void)
{
    test_proc_ProcDel();
    printk(KERN_INFO"test_proc Driver Release Complete.\n");
}
module_init(test_proc_Init);
module_exit(test_proc_Exit);
MODULE_AUTHOR("dup@lovebadminton.cn");
MODULE_DESCRIPTION("test _proc driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
