This is an arduino library for TCP connections to Port 2424. Currently running with Relais and DHT22 elements. Next updates:

    Temperature sensor One wire elements.
    Light intensity sensor.
    Modbus TCP weather station with wind and rain detection.

Prepare the sofware:

    Install Visual studio code
    Install platform IO
    Install arduino or arduino mega Boards from the Platform IO start page inside Visual studio code.

Prepare the hardware:

    Buy an Arduino or Arduino Mega
    Buy an Ethernet 2 Shield

Instructions for first setup:

    Check out this repository or download the zip file.
    Go to the platform IO Site and click Open Project.
    Open the folder where the zip file was unzipped. Click open
    Open platform IO ini file in the Visual studio code editor. 
    Check if you have an arduino or arduino mega, choose the correct platform.
    Compile the project with visual studio code with platform IO installed. This should be finished without errors.

Choose connected hardware:

    Open the src folder and than the folder AllYouNeedIsStartHere
    Open the file sensor_elements_initiate.cpp
    Setup the harware that is connected. There are 2 examples given.

 
    Setup the IP address. Open the file tcp_ip_settings.h and set the mac address and the IP Address of the device.


Domiq Base

Domiq Base is a product to visualize LCN smart home devices. Domiq base can also use tcp connections for incoming or outgoing data.

    Login to Domiq Base and in the status tab the new variables should already appear.

Setup a connection to the Relais in Domiq Base

You can use the variable in Domiq base just like any other Variable.

License

All Software is licensed under the GNU license V3. The library modules are licensed under the MIT license or are from https://github.com/krvarma/Dallas_DS18B20_SparkCore/blob/master/README.md
