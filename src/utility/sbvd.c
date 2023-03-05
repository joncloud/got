#include  <io.h>
#include  <dos.h>
#include  <bios.h>
#include  <stdio.h>
#include  <fcntl.h>
#include  <string.h>
#include  <stdlib.h>
#include  <alloc.h>
#include  <sbc.h>
#include  <sbcvoice.h>

char far *load_voice_file(char *filename) ;
char	  far *voice_buffer ;
char     far *vbuff;

int init_sbv(void)
{

	  /*   set io address as factory default   */

     ct_io_addx = 0x220 ;

     if (sbc_check_card() & 4)
     {
        if (sbc_scan_int())
	  {
		    if (!ctvm_init())
		    {
			 ctvm_speaker(0) ;
                      return 1;

		    }
	  }
         else return 0;
     }
     else{
	  printf("Sound Blaster card not found.\n") ;
         return 0;
     }
return 1;
}


/*------------------------------------------------------------------------*/

#pragma loop_opt(off)

char far*load_voice_file(char *filename)
{
	FILE *fp;
       int  total,bytes;
       char buff[256];
       char far *p;
       long fs;
	  /*   open voice file	 */
     vbuff=0;
     total=0;
     fp=fopen(filename,"rb");
     if(!fp) return 0;
     fseek(fp,0,SEEK_END);
     fs=ftell(fp);
     fseek(fp,0,SEEK_SET);
     vbuff=farmalloc(fs+15);
     if(!vbuff) return 0;
     p=vbuff;
     while(1){
          bytes=fread(buff,1,256,fp);
          if(bytes==0) break;
          total+=bytes;
          movedata(FP_SEG(buff),FP_OFF(buff),FP_SEG(p),FP_OFF(p),bytes);
          p+=bytes;
     }
     fclose(fp) ;
     if(total<256) vbuff=0;
     return vbuff;
}

#pragma loop_opt(on)


/*------------------------------------------------------------------------*/


#pragma loop_opt (off)

output_voice(char far *buffer)
{
//	unsigned    key ;

     buffer += ((VOCHDR far *)buffer)->voice_offset ;

     if(ct_voice_status) ctvm_stop();
//     ctvm_speaker(1) ;


     ctvm_output(buffer);
//     delay(1000);
//
//     {
//
//	  while (ct_voice_status)
//	  {
//	       if (kbhit())
//	       {
//		    if (key = getch())
//		    {
//			 switch(toupper(key & 0xff))
//			 {
//			      case 'S' : ctvm_stop() ;
//					 break ;
//			      case 'P' : ctvm_pause() ;
//					 break ;
//			      case 'C' : ctvm_continue() ;
//					 break ;
//			      case 'B' : ctvm_break_loop(1) ;
//					 break ;
//			 }
//		    }
//	       }
//	  }
//     }
//
//     ctvm_speaker(0) ;
//}
}
#pragma loop_opt(on)

