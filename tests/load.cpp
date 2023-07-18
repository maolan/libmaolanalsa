#include <maolan/dynamichw.hpp>


using namespace maolan;


int main()
{
  DynamicHW alsa{"./libmaolanalsa.so"};

  alsa.audio.out("AlsaAudioOut", "default", 4);
  alsa.audio.in("AlsaAudioOut", "default", 4);
  // alsa.midi.out("AlsaMidiOut", "default");
  // alsa.midi.in("AlsaMidiIn", "default");
  return 0;
}
