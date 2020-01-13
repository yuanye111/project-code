#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include "led_opr.h"

struct iomux {
volatile unsigned int unnames[23];
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08;
volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09;
};

struct imx6ull_gpio {
volatile unsigned int dr;
volatile unsigned int gdir;
volatile unsigned int psr;
volatile unsigned int icr1;
volatile unsigned int icr2;
volatile unsigned int imr;
volatile unsigned int isr;
volatile unsigned int edge_sel;
};

/*enable GPIO5 GPIO1*/
static volatile unsigned int *CCM_CCGR1; //0x20C406C
/*set GPIO5_IO03 as GPIO*/
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3; //0x2290014

struct iomux *IOmux;//
struct imx6ull_gpio *gpio1; //209_C000
struct imx6ull_gpio *gpio5; //20A_C000


/*init the GPIO5_IO03 GPIO1_IO03 GPIO1_IO05 GPIO1_IO06*/
static int board_qemuImull_led_init (int which) /* 初始化LED, which-哪个LED */	   
{
   if(!CCM_CCGR1)
   	{
		/*enale clc */
		CCM_CCGR1 = ioremap(0x20C406C,4);

		/*set iomux*/
		IOmux = ioremap(0x20e0000,sizeof(struct iomux));
		IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014,4);

		/*set dir reg*/
		gpio1 = ioremap(0x209C000,sizeof(struct imx6ull_gpio));
		gpio5 = ioremap(0x20AC000,sizeof(struct imx6ull_gpio));
   	}
   
   switch(which)
   	case 0:
		*CCM_CCGR1 = |(3<<30); // enable GPIO5
		*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = 5;// set GPIO5_IO03 as GPIO 
	    gpio5->gdir = |(1<<5);
		break;
    case 1:	
    	*CCM_CCGR1 = |(3<<26); // enable GPIO1
	    IOmux->IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 5;
	    gpio1->gdir |= (1<<3);
		break;
	case 2:	
    	*CCM_CCGR1 = |(3<<26); // enable GPIO1
	    IOmux->IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05 = 5;
	    gpio1->gdir |= (1<<5);
		break;
	case 3:
    	*CCM_CCGR1 = |(3<<26); // enable GPIO1
	    IOmux->IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06 = 5;
	    gpio1->gdir |= (1<<6);
		break;		
	
	printk("%s %s line %d, led %d\n", __FILE__, __FUNCTION__, __LINE__, which);
	return 0;
}

static int board_qemuImull_led_ctl (int which, char status) /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
{
   switch(which)
   	case 0:
		if(status)
		  	gpio5->dr &= ~(1<<3);
		else
			gpio5->dr |= (1<<3);
		break;
    case 1:	
    	if (status)  /* on : output 0 */
			gpio1->dr &= ~(1<<3);
		else         /* on : output 1 */
			gpio1->dr |= (1<<3);
		break;
	case 2:	
		if (status)  /* on : output 0 */
			gpio1->dr &= ~(1<<5);
		else         /* on : output 1 */
			gpio1->dr |= (1<<5);
		break;
	case 3:
		if (status)  /* on : output 0 */
			gpio1->dr &= ~(1<<6);
		else         /* on : output 1 */
			gpio1->dr |= (1<<6);
		break;	    
	printk("%s %s line %d, led %d, %s\n", __FILE__, __FUNCTION__, __LINE__, which, status ? "on" : "off");
	return 0;
}

static struct led_operations board_qemuImull_led_opr = {
	.num  = 4,
	.init = board_qemuImull_led_init,
	.ctl  = board_qemuImull_led_ctl,
};

struct led_operations *get_board_led_opr(void)
{
	return &board_qemuImull_led_opr;
}

