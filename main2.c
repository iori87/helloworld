#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <libv4l2.h>
#include <linux/videodev2.h>



int get_dev_info(gchar * device_name){
  struct v4l2_capability cap;
  printf("Device name: %s \n", device_name);
  int descriptor;
  descriptor = v4l2_open(device_name, O_RDWR | O_NONBLOCK, 0);
  ioctl(descriptor,VIDIOC_QUERYCAP,&cap);
  printf("Device card: %s\n", cap.card);
  printf("Device driver: %s\n", cap.driver);
  printf("Device bus: %s\n", cap.bus_info);  
  printf("Device capabilities flag status: %p\n", (void*)cap.capabilities);
  int bit_mask=1;
  if(cap.capabilities & bit_mask)
    printf("Video Capture supported \n");
  bit_mask=2;
  if(cap.capabilities & bit_mask)
    printf("Video Output supported \n");
  bit_mask=4;
  if(cap.capabilities & bit_mask)
    printf("Video Overlay supported \n");
  bit_mask=16;
  if(cap.capabilities & bit_mask)
    printf("Raw VBI capture supported \n");
  bit_mask=32;
  if(cap.capabilities & bit_mask)
    printf("Raw VBI output supported \n");
  bit_mask=64;
  if(cap.capabilities & bit_mask)
    printf("Sliced VBI capture supported \n");
  bit_mask=128;
  if(cap.capabilities & bit_mask)
    printf("Sliced VBI output supported \n");
  bit_mask=512;
  if(cap.capabilities & bit_mask)
    printf("Video output overlay OSD supported \n");
  bit_mask=0x00010000;
  if(cap.capabilities & bit_mask)
    printf("Tuner or modulator supported \n");
  bit_mask=0x00020000;
  if(cap.capabilities & bit_mask)
    printf("Audio supported \n");
  bit_mask=0x00040000;
  if(cap.capabilities & bit_mask)
    printf("Radio receiver supported \n");
  bit_mask=0x01000000;
  if(cap.capabilities & bit_mask)
    printf("Read and write I/O methods supported \n");
  bit_mask=0x02000000;
  if(cap.capabilities & bit_mask)
    printf("Asynchronous I/O methods supported \n");
  bit_mask=0x04000000;
  if(cap.capabilities & bit_mask)
    printf("Streaming I/O methods supported \n");
  return 1; 
}

int main(){
  get_dev_info("/dev/video0");  
  return 0;
}