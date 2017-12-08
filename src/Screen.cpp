
#include "Screen.h"


using namespace maa;

Screen::Screen():m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer1(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]),m_buffer2(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]) {}
void Screen::close()
{
	delete [] m_buffer1;
	delete [] m_buffer2;
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_Quit();
}
bool Screen::init(int color)
{
	m_window = SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

		if(m_window == NULL)
			return false;

	m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_PRESENTVSYNC);

		if(m_renderer == NULL)
		{
			return false;
		}

	m_texture = SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,SCREEN_WIDTH,SCREEN_HEIGHT);

		if(m_texture == NULL)
		{
			return false;
		}


		memset(m_buffer1,0xFF,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
		memset(m_buffer2,0xFF,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

		for(int i = 0;i<SCREEN_HEIGHT;i++)
		{new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
			for(int j = 0; j < SCREEN_WIDTH;j++)
			{
				m_buffer1[j+i*(SCREEN_WIDTH)] = color;
			}
		}

		SDL_UpdateTexture(m_texture,NULL,m_buffer1,SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
		SDL_RenderPresent(m_renderer);
		return true;
}
bool Screen::processEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type==SDL_QUIT)
			return true;
	}
return false;
}
void Screen::update()
{
	SDL_UpdateTexture(m_texture,NULL,m_buffer1,SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
	SDL_RenderPresent(m_renderer);
}
void Screen::setPixel(int x , int y , Uint8 red, Uint8 green, Uint8 blue)
{
	if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	Uint32 color = 0;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}
void Screen::boxBlur()
{
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for(int y=0; y < SCREEN_HEIGHT;y++)
	{
		for(int x =0 ; x < SCREEN_WIDTH;x++)
		{

			int totalRed = 0;
			int totalGreen = 0;
			int totalBlue = 0;

			for(int row = -1 ; row <=1;row++)
			{
				for (int col = -1;col <=1;col++)
				{
					int currentY = y + row;
					int currentX = x + col;

					if(currentX > 0 && currentX < SCREEN_WIDTH && currentY > 0 && currentY < SCREEN_HEIGHT)
					{
						Uint32 pixelColor = m_buffer2[(currentY * SCREEN_WIDTH) + currentX];
						unsigned char red = pixelColor >> 24;
						unsigned char green = pixelColor >> 16;
						unsigned char blue = pixelColor >> 8;

						totalRed += red;
						totalGreen += green;
						totalBlue += blue;
					}

				}



			}
			Uint8 red = totalRed/9;
			Uint8 green = totalGreen/9;
			Uint8 blue = totalBlue/9;

			setPixel (x,y,red,green,blue);

		}
	}

}

/* namespace maa */
