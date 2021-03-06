#pragma once

#include <list>
#include <memory>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"
#include "EventT.hpp"

class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    struct Segment
    {
        int x;
        int y;
        int ttl;
    };
    void checkDirection(const Segment& currentHead, Segment& newHead);
    void checkSnakeCollision(Segment& newHead, bool& lost);

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    Direction m_currentDirection;
    std::list<Segment> m_segments;

    void checkFieldCollision(Segment& newHead, bool& lost);
    void moveSnake(Segment& newHead, bool& lost);
    void castTimeoutInd(EventT<TimeoutInd> e);
    void castDirectionInd(EventT<DirectionInd> e);
    void castFoodInd(EventT<FoodInd> e);
    void castFoodResp(EventT<FoodResp> e);
};

} // namespace Snake
