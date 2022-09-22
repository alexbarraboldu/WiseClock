#include "EngineBase.h"

EngineBase::EngineBase()
{
	frameRate = 30;

	deltaTime = 1000.0f / frameRate;

	//totalFrames = 0;

	FPS = 0;

	timesUnderDeltaTime = 0;

	quitEngineLoop = false;

}

EngineBase::~EngineBase() {}

void EngineBase::ExitEngine()
{
	quitEngineLoop = true;
}

void EngineBase::engineLoop()
{
	unsigned int T = 0;

	using dsec = std::chrono::duration<double>;
	auto invFpsLimit = std::chrono::round<std::chrono::system_clock::duration>(dsec{1./ frameRate});
	auto m_BeginFrame = std::chrono::system_clock::now();
	auto m_EndFrame = m_BeginFrame + invFpsLimit;
	unsigned frame_count_per_second = 0;
	auto prev_time_in_seconds = std::chrono::time_point_cast<std::chrono::seconds>(m_BeginFrame);

	std::chrono::high_resolution_clock::duration m_DeltaTime;

	while (!quitEngineLoop)
	{
		////----------------------------------------------
		////

		Update();
		Renderer();

		////
		////----------------------------------------------

		///	Engine Stuff
		auto time_in_seconds = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
		++frame_count_per_second;

		if (time_in_seconds > prev_time_in_seconds)	//	Frames per Second
		{
			FPS = frame_count_per_second;
			frame_count_per_second = 0;
			prev_time_in_seconds = time_in_seconds;
			deltaTime = 1000.0f / FPS;

			T++;

		//	printf("%u\n", FPS);
		}

		//	FPS Manager
		if (m_EndFrame > m_BeginFrame && invFpsLimit != dsec(1) )
		{
			std::this_thread::sleep_until(m_EndFrame);
			timesUnderDeltaTime++;
		}
		m_BeginFrame = m_EndFrame;
		m_EndFrame = m_BeginFrame + invFpsLimit;
		///-------------
	}
}

double EngineBase::clockToSeconds(clock_t ticks) {
	// units/(units/time) => time (seconds) = seconds
	return (ticks / (double)CLOCKS_PER_SEC);
}

double EngineBase::clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0f;
}

double EngineBase::clockToNanoseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000000 = nanoseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000000.0f;
}

