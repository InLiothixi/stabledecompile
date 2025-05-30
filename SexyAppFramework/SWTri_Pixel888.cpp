// This file is included by SWTri.cpp and should not be built directly by the project.

	#if defined(TEXTURED)
	{
		#include "SWTri_GetTexel.cpp"
		
		if (alpha > 0x08)
		{
			#include "SWTri_TexelARGB.cpp"

			#if defined(GLOBAL_ARGB) || defined (TEX_ALPHA) || defined(MOD_ARGB)
			{
                if (alpha < 0xf0 || gTodTriangleDrawAdditive)
                {
					if (!gTodTriangleDrawAdditive)
                    {
						unsigned int trb, tg;
						#if !defined(LINEAR_BLEND)
						{
							trb = (((tex & 0xff00ff) * alpha) >> 8) & 0xff00ff;
							tg = (((tex & 0x00ff00) * alpha) >> 8) & 0x00ff00;
						}
						#else
						{
							trb = tex & 0xff00ff;
							tg = tex & 0x00ff00;
						}
						#endif

                        alpha = 0xff - alpha;

                        unsigned int prb = (((*pix & 0xff00ff) * alpha) >> 8) & 0xff00ff;
                        unsigned int pg = (((*pix & 0x00ff00) * alpha) >> 8) & 0x00ff00;

                        *pix = ((trb | tg) + (prb | pg));
                    }
                    else
                    {
						unsigned int blended = (tex & 0xff00ff) + (*pix & 0xff00ff); 
						unsigned int carry = blended & 0x1000100;                      
						blended = (blended | (carry - (carry >> 8))) & 0xff00ff;     

						unsigned int blendedGreen = (tex & 0xff00) + (*pix & 0xff00);
						unsigned int carryGreen = blendedGreen & 0x10000;                 
						blendedGreen = (blendedGreen | (carryGreen - (carryGreen >> 8))) & 0xff00; 

						*pix = blended | blendedGreen;
                    }
                }
                else
                {
                    *pix = tex;
                }
			}
			#else
			{
				*pix = tex;
			}
			#endif			
		}
	}
	#elif defined(MOD_ARGB)
	{
		if (a > 0xf00000)
		{
			*pix = ((r)&0xff0000)|((g>>8)&0xff00)|((b>>16)&0xff);
		}
		else if (a > 0x080000)
		{
			unsigned int	alpha = a >> 16;
			unsigned int	_rb = ((((r&0xff0000) | (b>>16)) * alpha)>> 8)&0xff00ff;
			unsigned int	_g  =  (((g&0xff0000)            * alpha)>>16)&0x00ff00;
			unsigned int	p = *pix;
			alpha = 0xff - alpha;
			unsigned int	prb = (((p&0xff00ff) * alpha) >> 8) & 0xff00ff;
			unsigned int	pg  = (((p&0x00ff00) * alpha) >> 8) & 0x00ff00;
			*pix =(_rb|_g)+(prb|pg);
		}
	}
	#endif
