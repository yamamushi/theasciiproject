/*

  Mixer

  Class functions

 */

#include "Mixer.h"

#include "SDL/SDL_mixer.h"



Mixer::Mixer(){

  music = nullptr;
  effect = nullptr;

  Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
  
  int flags = MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_MP3;
  Mix_Init(flags);

}


Mixer::~Mixer(){
  
  // Stop_Music();

  if( music != nullptr )
    Mix_FreeMusic( music );
  if( effect != nullptr )
    Mix_FreeChunk( effect );

  Mix_CloseAudio();

  while(Mix_Init(0))
    Mix_Quit();

}



bool Mixer::Load_Music(char *file){

  Unload_Music();

  music = Mix_LoadMUS( file );

  if( music == NULL )
    return false;
  else
    return true;

}


void Mixer::Unload_Music(){

  if( music != nullptr ){
    Stop_Music();
    Mix_FreeMusic( music );
  }
}


bool Mixer::Play_Music(){

  if( music != nullptr){
    if( Mix_PlayingMusic() == 0 ){
      if( Mix_PlayMusic( music, -1 ) == -1 ){
        return false;
      }
      else
        return true;
    }
    else
      return false;
  }
  else
    return false;

}


void Mixer::Pause_Music(){

  if( Mix_PausedMusic() == 1 )
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();

}


void Mixer::Stop_Music(){

  Mix_HaltMusic();

}


bool Mixer::Fade_In_Music(int ms, int loops){

  if( music != nullptr){
    if(Mix_FadeInMusic(music, loops, ms) == -1) {
      // well, there's no music, but most games don't break without music...
      printf("Mix_FadeInMusic: %s\n", Mix_GetError());
      return false;
    }
    else
      return true;
  }
  else
    return false;

}



bool Mixer::Load_Effect(char *file){
  
  if( effect != nullptr ){
    Mix_FreeChunk( effect );
  }

  effect = Mix_LoadWAV( file );

  if( effect == NULL )
    return false;
  else
    return true;  

}


bool Mixer::Play_Effect(int channel, int loops){

  if( effect != nullptr){
    if( Mix_PlayChannel( channel, effect, loops) == -1 ){
      return false;
    }
    else
      return true;
  }
  else
    return false;

}



void Mixer::Global_Volume( int volume, int channel){

  Mix_Volume( channel, volume );

}



void Mixer::Music_Volume( int volume){

  Mix_VolumeMusic( volume );

}


void Mixer::Effect_Volume( int volume, int channel){

  

}

