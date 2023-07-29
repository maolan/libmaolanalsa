#include <maolan/audio/alsa/in.hpp>
#include <maolan/audio/alsa/out.hpp>

using namespace maolan::audio;

extern "C" HW *createAudioOut(const std::string &name,
                              const std::string &device, const size_t &size) {
  if (size == 1) {
    return new ALSAOut<int8_t>{name, device};
  }
  if (size == 2) {
    return new ALSAOut<int16_t>{name, device};
  }
  if (size == 4) {
    return new ALSAOut<int32_t>{name, device};
  }
  throw std::invalid_argument{"No such size"};
}

extern "C" HW *createAudioIn(const std::string &name, const std::string &device,
                             const size_t &size) {
  if (size == 1) {
    return new ALSAIn<int8_t>{name, device};
  }
  if (size == 2) {
    return new ALSAIn<int16_t>{name, device};
  }
  if (size == 4) {
    return new ALSAIn<int32_t>{name, device};
  }
  throw std::invalid_argument{"No such size"};
}
