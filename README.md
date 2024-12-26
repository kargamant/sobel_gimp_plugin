# sobel_gimp_plugin
A plugin for gimp that performs sobel operator algorithm on image.  
This algorithm is quite popular for edge detection on images. It's based on concept of convolution matricies.  

![2024-12-2016-55-17-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/10de31f1-35d2-4b2f-8175-e08a7713724e)

## Examples and processed examples:  
![tesla_roadster_large](https://github.com/user-attachments/assets/ebbf6e07-e739-4667-8bba-97e22b7deb8a)  
![tesla-roadster_large_processed](https://github.com/user-attachments/assets/f8c031c9-1eb5-41b6-a90c-b673e71f7d1d)
![japan_street2](https://github.com/user-attachments/assets/4b8411f5-9155-4560-b08f-2cf759738346)
![japan_street2_processed](https://github.com/user-attachments/assets/5dbe8cf9-7a24-48f3-ac06-5f38b71d7467)
![Calton_Hill_Edinburgh](https://github.com/user-attachments/assets/d7d801e1-d6df-40fd-8218-8e0b7c189521)
![Calton_Hill_Edinburgh_processed](https://github.com/user-attachments/assets/6e8203eb-7174-4210-954d-039c6c0ce37f)
![red_rocket](https://github.com/user-attachments/assets/9747c105-bfe3-41b7-b8f3-2b80930dc8af)
![red_rocket_processed](https://github.com/user-attachments/assets/0d10c336-8727-4136-a718-9f75512eab2f)
## How to build this plug-in from source?  
1. Replace ```your_gimp_path``` variable value in Makefile with directory name where gimp is installed on your linux machine.
```
your_gimp_path = /home/kargamant/.config/GIMP/2.10
all:
	mkdir -p $(your_gimp_path)/plug-ins/sobel
	gcc  -pthread -I/usr/include/gegl-0.4 -I/usr/include/gio-unix-2.0 -I/usr/include/json-glib-1.0 -I/usr/include/babl-0.1 -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gimp-2.0 -o '$(your_gimp_path)/plug-ins/sobel/sobel' 'sobel.c' 'utils.c' 'buff.c' 'metrics.c' 'widget.c' -lgimpui-2.0 -lgimpwidgets-2.0 -lgimpmodule-2.0 -lgimp-2.0 -lgimpmath-2.0 -lgimpconfig-2.0 -lgimpcolor-2.0 -lgimpbase-2.0 -lgegl-0.4 -lgegl-npd-0.4 -lm -Wl,--export-dynamic -lgmodule-2.0 -pthread -ljson-glib-1.0 -lbabl-0.1 -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lharfbuzz -lfontconfig -lfreetype -w
```  
 
3. Built plugin will appear at ```Filters > MyFilters > sobel``` . Have fun :) 
