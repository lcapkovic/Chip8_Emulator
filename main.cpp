#include <SDL2/SDL.h>
#include "chip8.cpp"


chip8 myChip8;

bool handleKeys()
{
    SDL_Event event;
 while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
            break;

       	case SDL_KEYDOWN:
       		switch (event.key.keysym.sym)
            {
	            case SDLK_1:  myChip8.key[0x1] = 1; break;
	            case SDLK_2:  myChip8.key[0x2] = 1; break;
	            case SDLK_3:  myChip8.key[0x3] = 1; break;
	            case SDLK_4:  myChip8.key[0xC] = 1; break;

	            case SDLK_q:  myChip8.key[0x4] = 1; break;
	            case SDLK_w:  myChip8.key[0x5] = 1; break;
	            case SDLK_e:  myChip8.key[0x6] = 1; break;
	            case SDLK_r:  myChip8.key[0xD] = 1; break;

	            case SDLK_a:  myChip8.key[0x7] = 1; break;
	            case SDLK_s:  myChip8.key[0x8] = 1; break;
	            case SDLK_d:  myChip8.key[0x9] = 1; break;
	            case SDLK_f:  myChip8.key[0xE] = 1; break;

	            case SDLK_z:  myChip8.key[0xA] = 1; break;
	            case SDLK_x:  myChip8.key[0x0] = 1; break;
	            case SDLK_c:  myChip8.key[0xB] = 1; break;
	            case SDLK_v:  myChip8.key[0xF] = 1; break;
            }
        break;

        case SDL_KEYUP:
        	switch (event.key.keysym.sym)
            {
	            case SDLK_1:  myChip8.key[0x1] = 0; break;
	            case SDLK_2:  myChip8.key[0x2] = 0; break;
	            case SDLK_3:  myChip8.key[0x3] = 0; break;
	            case SDLK_4:  myChip8.key[0xC] = 0; break;

	            case SDLK_q:  myChip8.key[0x4] = 0; break;
	            case SDLK_w:  myChip8.key[0x5] = 0; break;
	            case SDLK_e:  myChip8.key[0x6] = 0; break;
	            case SDLK_r:  myChip8.key[0xD] = 0; break;

	            case SDLK_a:  myChip8.key[0x7] = 0; break;
	            case SDLK_s:  myChip8.key[0x8] = 0; break;
	            case SDLK_d:  myChip8.key[0x9] = 0; break;
	            case SDLK_f:  myChip8.key[0xE] = 0; break;

	            case SDLK_z:  myChip8.key[0xA] = 0; break;
	            case SDLK_x:  myChip8.key[0x0] = 0; break;
	            case SDLK_c:  myChip8.key[0xB] = 0; break;
	            case SDLK_v:  myChip8.key[0xF] = 0; break;
            }
        break;
      
        }
	}
	return false;
}

int main(int argc, char **argv){
	if(!myChip8.loadApplication(argv[1]))		
		return 1;

    bool quit;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("CHIP8 Emulator",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 64, 32);
    
    Uint32 * pixels = new Uint32[64 * 32];
	const int fps = 600;
	int counter = 0;
	Uint32 start;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  
	SDL_RenderSetLogicalSize(renderer, 64, 32);

	while (!quit)
    {
    	start = SDL_GetTicks();
       
    	quit = handleKeys();

    	myChip8.emulateCycle();
    	counter++;
    	if(counter >= 10)
    	{
    		if(myChip8.delay_timer > 0)
    			myChip8.delay_timer--;
    		if(myChip8.sound_timer > 0)
    			myChip8.sound_timer--;
    		counter = 0;
    	}
    	if(myChip8.drawFlag)
    	{

        	for(int i = 0; i<64*32; ++i)
        	{
        		if(myChip8.gfx[i] == 1)
        			pixels[i] = 0xFFFFFFFF;
        		else
        			pixels[i] = 0;
        	}

	        SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(Uint32));
	       	SDL_RenderClear(renderer);
	        SDL_RenderCopy(renderer, texture, NULL, NULL);
	        SDL_RenderPresent(renderer);
	        myChip8.drawFlag = false;
	        
    	}
    	
    	if(1000/fps > SDL_GetTicks()-start)
        {
        	SDL_Delay((1000/fps)-(SDL_GetTicks()-start));

    	}
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}

