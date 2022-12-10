#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */
template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> _mqMutexLock(_mqMutex);
    _mqCondVar.wait(_mqMutexLock);
    T received = std::move(_queue.front());
    return received;
} 

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> _mqMutexLock(_mqMutex);
    _queue.emplace_back(std::move(msg));
    _mqCondVar.notify_one();
}

/* Implementation of class "TrafficLight" */
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight()
{

}

void TrafficLight::waitForGreen()
{
    while (_mq.receive() != TrafficLightPhase::green);
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}


void TrafficLight::simulate()
{
    threads.emplace_back(std::thread{&TrafficLight::cycleThroughPhases, this});
}


// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // random cycleDuration generation between 4 and 6 seconds. 
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(TRAFFIC_LIGHT_MIN_WAIT_MS, TRAFFIC_LIGHT_MAX_WAIT_MS);
    double cycleDuration = dist(e2);

    // init stop watch
    auto lastUpdate = std::chrono::system_clock::now();
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        
        if(timeSinceLastUpdate >= cycleDuration) {
            if (_currentPhase == TrafficLightPhase::red)
            {
               _currentPhase = TrafficLightPhase::green; 
            }
            else
            {
               _currentPhase = TrafficLightPhase::red; 
            }

            // send message to MQ
            _mq.send(std::move(_currentPhase));

            // refresh last update
            lastUpdate = std::chrono::system_clock::now();

            // randomly choose a new cycle duration
            cycleDuration = dist(e2);
        }
    }
}