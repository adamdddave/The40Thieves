This is the online monitoring package, The 40 Thieves, for Alibava.
To compile, you need Qt 5.3 or higher, as well as Alibava installed. 
To get Qt, either use yum or apt-get in Linux. If you really want to,
download it from Qt's sourceforge page.

After Qt is installed, run 

qmake ExtraGuiQtLib.pro

This *should* generate the appropriate makefile. From there, simply say make.

To load into Alibava, go through the plugin menu. Use the dialogue to select 
the folder which contains the .pro file and the shared library. The "hook" 
is create_plugin. From there, you should be able to enter the TDC time window
and minimum ADC value.