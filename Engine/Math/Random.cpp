#include "Random.hpp"

#include "../System/Time.hpp"

#include <sstream>

namespace oe
{

Random Random::mRandom;

void Random::setSeed(U32 seed)
{
	mRandom.mSeed = seed;
	mRandom.mGenerator.seed(seed);
}

U32 Random::getSeed()
{
	return mRandom.mSeed;
}

Random::Random()
{
	setSeed(Time::getCurrentTime().asMicroseconds());
}

} // namespace oe
