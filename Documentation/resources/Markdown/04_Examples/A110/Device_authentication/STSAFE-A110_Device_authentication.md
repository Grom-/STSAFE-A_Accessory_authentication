# STSAFE-A110 Device Authentication {#STSAFE-A110_Device_authentication}

This example illustrates how to performs STSAFE-A110 SPL02/SPL03 device authentication using the STSecureElement library API set.

The example applicative flowchart is illustrated below :

@startuml{STSAFE-A110_Device_authentication.png} "STSAFE-A110_Device_authentication Example flowchart" width=5cm	
	:MAIN;
	:Initialize Apps terminal (baudrate = 115200)]
	:Print example title and instructions]
	:ret = <b>stse_init</b>|
	if(ret != STSE_OK) then (No)
	else (Yes)
		:Print ERROR]
		-[hidden]->
		detach
	endif

	:ret = <b>stse_get_device_certificate_size</b>|
	if(ret != STSE_OK) then (No)
	else (Yes)
		:Print ERROR]
		-[hidden]->
		detach
	endif
	
	:ret = <b>stse_get_device_certificate</b>|
	if(ret != STSE_OK) then (No)
	else (Yes)
		:Print ERROR]
		-[hidden]->
		detach
	endif
			
	:print <b>"Device Certificate"</b>]
	
	:ret = <b>stse_device_authenticate</b>|
	if(ret != STSE_OK) then (No)
	else (Yes)
		:Print ERROR]
		-[hidden]->
		detach
	endif
	
	while (while(1) )
	end while
	-[hidden]->
	detach		
@enduml

API used in this example :

- \ref stse_get_device_certificate_size
- \ref stse_get_device_certificate
- \ref stse_device_authenticate

When executed following logs can be seen on the host attached computer terminal window \n


```
----------------------------------------------------------------------------------------------------------------
                              STSAFE-A110 Device Authentication Example
----------------------------------------------------------------------------------------------------------------
This example illustrates how to authenticate an STSAFE-A110 SPL02/SPL03 device over ST root CA certificate

- Note :
         An update of the ST root CA certificate (CA_SELF_SIGNED_CERTIFICATE_01) is required
         to adapt this example to a custom STSAFE-A110 personalization .
----------------------------------------------------------------------------------------------------------------

 ## STSAFE-A110 Device zone 0 certificate :

  0x30 0x82 0x01 0x99 0x30 0x82 0x01 0x3F 0xA0 0x03 0x02 0x01 0x02 0x02 0x0B 0x02
  0x09 0xB0 0x84 0x61 0x59 0xE4 0x39 0x52 0x01 0x39 0x30 0x0A 0x06 0x08 0x2A 0x86
  0x48 0xCE 0x3D 0x04 0x03 0x02 0x30 0x4F 0x31 0x0B 0x30 0x09 0x06 0x03 0x55 0x04
  0x06 0x13 0x02 0x4E 0x4C 0x31 0x1E 0x30 0x1C 0x06 0x03 0x55 0x04 0x0A 0x0C 0x15
  0x53 0x54 0x4D 0x69 0x63 0x72 0x6F 0x65 0x6C 0x65 0x63 0x74 0x72 0x6F 0x6E 0x69
  0x63 0x73 0x20 0x6E 0x76 0x31 0x20 0x30 0x1E 0x06 0x03 0x55 0x04 0x03 0x0C 0x17
  0x53 0x54 0x4D 0x20 0x53 0x54 0x53 0x41 0x46 0x45 0x2D 0x41 0x20 0x50 0x52 0x4F
  0x44 0x20 0x43 0x41 0x20 0x30 0x31 0x30 0x20 0x17 0x0D 0x32 0x31 0x30 0x33 0x30
  0x35 0x30 0x30 0x30 0x30 0x30 0x30 0x5A 0x18 0x0F 0x32 0x30 0x35 0x31 0x30 0x33
  0x30 0x35 0x30 0x30 0x30 0x30 0x30 0x30 0x5A 0x30 0x51 0x31 0x0B

 ## Device authentication over ST SPL03 CA certificate : Successful

```

Applicative scenario : 

- Accessories and consumables Authentication 