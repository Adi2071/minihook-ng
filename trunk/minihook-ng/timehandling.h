#ifndef TIMEHANDLING_H
#define TIMEHANDLING_H

//===============================================================
// class ClientTime:
//      provides a stable time base, independent of map changes.
//===============================================================
class ClientTime 
{
public:
	static void   reportMapTime(float newMapTime);
	static float  mapTime;  // how long did the current map run?

	static void   updateCurrentTime();
	static double current;    // seconds counter
	static unsigned int  current_ms; // ms counter

protected:
//	static double timeoffset;
};

//===============================================================
// class StopTimer
//      
//===============================================================
class StopTimer
{
public:
	StopTimer() :expirationTime(0)       {}

	void  countdown( double seconds ) { expirationTime = ClientTime::current + seconds; }
	bool  running () { return (ClientTime::current<=expirationTime); }
	bool  expired () { return (ClientTime::current> expirationTime); }
	float timeleft() { return float(expirationTime-ClientTime::current);  }
	void  setExpired() { expirationTime=0;                           }
	void  setRunning() { expirationTime=1000000;                     }

protected:
	double expirationTime;
};

//===============================================================
// class RunningStopTimer
//      
//===============================================================
class RunningStopTimer : public StopTimer { public: RunningStopTimer(){expirationTime=1000000;} };


//===============================================================
// class EventCounter
//      
//===============================================================
//template < float Interval  0.0f, int MaxEvents = 12 >
//template < class T = EventCounter,float Interval, int  >
class EventCounter
{
public:
	// returns number of events since last call, maximal 12
	int  get()
	{
		register int n = 0;
		while(reftime<ClientTime::current)
		{
			reftime += Interval;
			++n;
			if(n>MaxEvents) { reset(); return MaxEvents; }
		}
		return n;
	}
	void set(float fInterval){Interval= fInterval;}

	EventCounter()  {reset();MaxEvents = 12;}
	void   reset()  {reftime = ClientTime::current;}

protected:
	int MaxEvents;
	float Interval;
	double reftime;
};

#endif
