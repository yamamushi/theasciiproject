/*

  Mixer

  A generic class for handling audio output.


 */

#include "SDL/SDL_mixer.h"



class Mixer {

  private:

  Mix_Music *music;
  Mix_Chunk *effect;

  public:

  Mixer();
  virtual ~Mixer();

  bool Load_Music(char *file);
  void Unload_Music();

  bool Play_Music();
  void Pause_Music();
  void Stop_Music();

  bool Fade_In_Music(int ms, int loops = -1);

  bool Load_Effect(char *file);
  bool Play_Effect(int channel = -1, int loops = 0);

  void Global_Volume( int volume, int channel = -1);
  void Music_Volume( int volume );
  void Effect_Volume( int volume, int channel = -1);

};
