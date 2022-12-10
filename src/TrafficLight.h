#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"


#define TRAFFIC_LIGHT_MIN_WAIT_MS 4000  // traffic light wait duration lower limit in milliseconds
#define TRAFFIC_LIGHT_MAX_WAIT_MS 6000  // tarffic light wait duration upper limit in milliseconds


// forward declarations to avoid include cycle
class Vehicle;
enum class TrafficLightPhase;

template <class T>
class MessageQueue
{
public:
    void send(T&& msg);
    T receive();

private:
   std::deque<TrafficLightPhase> _queue;
   std::condition_variable _mqCondVar;
   std::mutex _mqMutex; 
};

enum class TrafficLightPhase 
{
    unknown,
    green,
    red,
};

class TrafficLight : public TrafficObject 
{
public:
    // constructor / desctructor
    TrafficLight();
    virtual ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    virtual void cycleThroughPhases();
    
    MessageQueue<TrafficLightPhase> _mq;
    TrafficLightPhase _currentPhase{TrafficLightPhase::unknown};
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif