struct pcx_hdr{
	unsigned char manufac;          /* manufacturer             */
	unsigned char version;          /* paintbrush version #     */
	unsigned char encode;           /* 1 = run length encoded   */
	unsigned char bits_pix;         /* bits per pixel           */
   int           xmin;             /* picture dimensions       */
   int           ymin;
   int           xmax;
   int           ymax;
   int           hres;             /* horizontal and vertical 	*/
   int           vres;             /* resolutions              */
   unsigned char palette[16][3];   /* palette info             */
   unsigned char reserve;          /* reserved                 */
   unsigned char planes;           /* number of color planes   */
   int           bytsline;         /* Bytes per line           */
   int           pal_info;         /* palette info             */
   unsigned char filler[58];       /* fill out 128 byte header */
};

