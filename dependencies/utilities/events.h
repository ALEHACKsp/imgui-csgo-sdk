#pragma once
#include "../interfaces/i_game_event_manager.hpp"
#include <deque>

class event_listener : public i_game_event_listener2 {
public:
	void setup(const std::deque<const char*>& events);
	void release();

	virtual void fire_game_event(i_game_event* event) override;
};
