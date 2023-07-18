#pragma once
#include <string>

#include "maolan/audio/base.hpp"


namespace maolan::audio
{
template <typename T> class ALSAIn : public ALSA
{
public:
  ALSAIn(const std::string &name, const std::string &device);

  virtual void readhw();
  virtual void process();
};
} // namespace maolan::audio

