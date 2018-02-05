How-to use VADC example

VADC example can run on svf522revb board with DDR support. Since it requires big memory block to hold display buffer, 
intram version will fail in running.

The example streams analog data from video input (VIDEO 1) to DCU0 port using video subsystem (AFE, VDEC, VIU3 modules). 
The initial screen resolution is 720x340. After lunch example, video from analog input will show on LCD display.
In case of missing input, green rectangle will show up.
