#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H

#include <chrono>
#include <thread>

class EngineBase {	
public:
	EngineBase();
	~EngineBase();

	void engineLoop();
	void ExitEngine();

	virtual void Update() = 0;
	virtual void Renderer() = 0;

	int frameRate;
	unsigned int FPS;

private:

	double clockToSeconds(clock_t ticks);
	double clockToMilliseconds(clock_t ticks);
	double clockToNanoseconds(clock_t ticks);

	double deltaTime;

	//unsigned int totalFrames;
	unsigned int timesUnderDeltaTime;

	bool quitEngineLoop;
};

#endif // !ENGINE_BASE_H
