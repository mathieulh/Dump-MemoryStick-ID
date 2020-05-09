 #include <pspsdk.h> 
 #include <pspkernel.h> 
 #include <pspdebug.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <stdio.h> 
 #include <stdarg.h> 
 #include "ms_drv.h" 

 PSP_MODULE_INFO("MemStickTest", 0x1000, 1, 0); 

 PSP_MAIN_THREAD_ATTR(0); 

 #define printf  pspDebugScreenPrintf 


 void ErrorExit(int milisecs, char *fmt, ...) 
 { 
         va_list list; 
         char msg[256]; 

         va_start(list, fmt); 
         vsprintf(msg, fmt, list); 
         va_end(list); 

         printf(msg); 

         sceKernelDelayThread(milisecs*1000); 
         sceKernelExitGame(); 
 } 



 u8      buffer[1024*1024]; 
 int main() 
 { 
         int i; 
         u32 sysinfo_addr = 0; 
         u32 modname_addr = 0; 
         wbmspro_attribute_t *ptr_attr = 0; 
         wbmspro_device_info_entry_item_t *ptr_entry = 0; 
         wbmspro_sys_info_t* s_info = 0; 

         pspDebugScreenInit(); 
         printf("This program makes attr0.bin on the root of the memory stick.\n"); 

         printf("result for sector 0 = %08X\n", pspMsReadAttrB(0, buffer)); 
         printf("result for sector 1 = %08X\n", pspMsReadAttrB(1, buffer + 512)); 
         printf("result for sector 2 = %08X\n", pspMsReadAttrB(2, buffer + 1024)); 
         printf("read from attributes and... "); 
         int fd = sceIoOpen("ms0:/attr0.bin", PSP_O_WRONLY | PSP_O_CREAT, 0777); 
         sceIoWrite(fd, buffer, 3*512); 
         sceIoClose(fd); 
         printf("wrote to file! \n"); 

         ptr_attr = (wbmspro_attribute_t*) buffer; 
         printf("Signature: %04X (should be 0xA5C3)\n", WSBH(ptr_attr->signature)); 
         printf("Version: %04X\n", WSBH(ptr_attr->version)); 
         printf("Number of entries: %02X\n", ptr_attr->device_information_entry_count); 
         for (i = 0; i < ptr_attr->device_information_entry_count; i++){ 
                 ptr_entry = (wbmspro_device_info_entry_item_t*) (buffer+ 0x10 + 0xC*i); 
                 printf("Entry %d, ID is %01X\n", i, ptr_entry->info_id); 
                 printf("Address is %08X, size is %08X\n", (unsigned int)WSBW(ptr_entry->address), (unsigned int)WSBW(ptr_entry->size)); 

                 switch (ptr_entry->info_id){ 
                         case 0x10: sysinfo_addr = (int)buffer + WSBW(ptr_entry->address); break; 
                         case 0x15: modname_addr = (int)buffer + WSBW(ptr_entry->address); break; 
                         default: break; 
                 } 
         } 
         s_info = (wbmspro_sys_info_t*) sysinfo_addr; 
         printf("====================================================================\n"); 
         printf("Serial number: %08X\n", (unsigned int)s_info->serial_number); 
         printf("MSProID:\n"); 
         printf("0x"); 
         for(i = 0; i< 0x10; i++){ 
                 printf("%02X", s_info->mspro_id[i]); 
         } 
         printf("\nModel name: \"%s\"\n", (char*)modname_addr); 
         ErrorExit(37000, "\nFinished.\n"); 

         return 0; 
 }