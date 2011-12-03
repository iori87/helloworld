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
  if(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
    printf("Video Capture supported \n");
  if(cap.capabilities & V4L2_CAP_VIDEO_OUTPUT)
    printf("Video Output supported \n");
  if(cap.capabilities & V4L2_CAP_VIDEO_OVERLAY)
    printf("Video Overlay supported \n");
  if(cap.capabilities & V4L2_CAP_VBI_CAPTURE)
    printf("Raw VBI capture supported \n");  
  if(cap.capabilities & V4L2_CAP_VBI_OUTPUT)
    printf("Raw VBI output supported \n");
  if(cap.capabilities & V4L2_CAP_SLICED_VBI_CAPTURE)
    printf("Sliced VBI capture supported \n");
  if(cap.capabilities & V4L2_CAP_SLICED_VBI_OUTPUT)
    printf("Sliced VBI output supported \n");
  if(cap.capabilities & V4L2_CAP_VIDEO_OUTPUT_OVERLAY)
    printf("Video output overlay OSD supported \n");
  if(cap.capabilities & V4L2_CAP_TUNER)
    printf("Tuner or modulator supported \n");
  if(cap.capabilities & V4L2_CAP_AUDIO)
    printf("Audio supported \n");
  if(cap.capabilities & V4L2_CAP_RADIO)
    printf("Radio receiver supported \n");
  if(cap.capabilities & V4L2_CAP_READWRITE)
    printf("Read and write I/O methods supported \n");
  if(cap.capabilities & V4L2_CAP_ASYNCIO)
    printf("Asynchronous I/O methods supported \n");
  if(cap.capabilities & V4L2_CAP_STREAMING)
    printf("Streaming I/O methods supported \n");  
  struct v4l2_fmtdesc  vfd;
  vfd.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
  vfd.index=0;
  struct v4l2_frmsizeenum vfse;
  vfse.index=0;  
  while(!ioctl(descriptor,VIDIOC_ENUM_FMT,&vfd)){ 
    vfd.index++;  
    printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
	    vfd.pixelformat & 0xFF, (vfd.pixelformat >> 8) & 0xFF,
	    (vfd.pixelformat >> 16) & 0xFF, (vfd.pixelformat >> 24) & 0xFF,
		vfd.description);
    if(vfd.flags & V4L2_FMT_FLAG_COMPRESSED)
      printf("This format is compressed\n");
    if(vfd.flags & V4L2_FMT_FLAG_EMULATED)
      printf("This format is not native but emulated\n");    
    vfse.pixel_format=vfd.pixelformat;    
    while(!ioctl(descriptor,VIDIOC_ENUM_FRAMESIZES,&vfse)){      
      printf("{ Frame Resolution = %u x %u }\n", vfse.discrete.width, vfse.discrete.height);
      vfse.index++;
    }
  } 
  return 1; 
}

int main(){
  get_dev_info("/dev/video0");  
  return 0;
}