#pragma once

extern "C"
{
#include "src/rnnoise.h"
}

#ifdef RNNOISE_BUILD_DLL
	#define RNNOISE_API __declspec(dllexport)
#else
	#define RNNOISE_API __declspec(dllimport)
#endif

class RNNOISE_API RNNoise
{
	DenoiseState* m_denoiseState;
	RNNModel* m_rnnModel = nullptr;
public:
	RNNoise();
	RNNoise(FILE* file);

	void doDenoise(float* pcm);

	~RNNoise();
};