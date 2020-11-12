#include "events.h"
#include "../interfaces/interfaces.hpp"

void event_listener::setup(const std::deque<const char*>& events) {
	if (events.empty()) return;

	for (auto event : events) {
		interfaces::event_manager->add_listener(this, event, false);
	}
}

void event_listener::release() {
	interfaces::event_manager->remove_listener(this);
}

void event_listener::fire_game_event(i_game_event* event) {
	if (event == nullptr) return;

	// Do event stuff :D
	/*if (strcmp(event->get_name(), "item_purchase") == 0)
		misc::item_purchase_indicator(event);*/
}