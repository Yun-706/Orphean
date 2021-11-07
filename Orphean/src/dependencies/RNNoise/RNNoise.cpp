#include "RNNoise.h"

RNNoise::RNNoise() : m_denoiseState(rnnoise_create(nullptr)) {}

RNNoise::RNNoise(FILE* file) {
	m_rnnModel = rnnoise_model_from_file(file);
	m_denoiseState = rnnoise_create(m_rnnModel);
}


RNNoise::~RNNoise()
{
	if (m_rnnModel != nullptr) {
		rnnoise_model_free(m_rnnModel);
	}
	if (m_denoiseState != nullptr) {
		rnnoise_destroy(m_denoiseState);
	}
}

void RNNoise::doDenoise(float* pcm)
{
	rnnoise_process_frame(m_denoiseState, pcm, pcm);
}