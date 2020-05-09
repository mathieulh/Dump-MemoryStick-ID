#include <pspsdk.h> 
#include <pspkernel.h> 
#include <pspdebug.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdarg.h> 

PSP_MODULE_INFO("MemStickTest", 0, 1, 1);
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




int LoadStartModule(char *module, int partition)
{
	SceUID mod = kuKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, 0, NULL, NULL, NULL);
}

int main() 
{ 
        pspDebugScreenInit(); 
        printf("This program makes attr0.bin on the root of the memory stick.\n"); 
        
        	int mod = LoadStartModule("mstestmodule.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (mod < 0)
	{
		ErrorExit(5000, "Error 0x%08X loading/starting pspdecrypt.prx.\n", mod);
	}

        
        
        ErrorExit(10000, "\nFinished.\n"); 

        return 0; 
} 