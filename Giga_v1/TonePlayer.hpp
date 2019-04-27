#ifndef TONE_PLAYER_hpp
#define TONE_PLAYER_hpp

class TonePlayer
{
  private:
    int size;
    int *melody;
    int *noteDurations;

  public:
    TonePlayer(int size, int *melody, int *noteDurations) : size(size), melody(melody), noteDurations(noteDurations) {}
    //~TonePlayer();
    void play();
};

#endif