#include <iostream>

#include <SDL_ttf.h>

#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"

int main(int argc, char *argv[])
{
    auto ctx = init_graphics();

    UI ui = UI(ctx);

    bool quit = false;

    while(not quit) {
	ui.update(); // Update UI

	UIEvent event;
	while(ui.poll(&event)) { // Keep polling events until there are no more
	    if(UIEvent_of_type<UIEvent_EXIT>(event)) {
		quit = true;
	    } else if(UIEvent_of_type<UIEvent_SEND_COMMAND>(event)) {
		UIEvent_SEND_COMMAND command_event = std::get<UIEvent_SEND_COMMAND>(event);
		if(command_event.diary) {
		    std::cout << "Received diary input: " << command_event.command << std::endl;
		} else {
		    std::cout << "Received non-diary input: " << command_event.command << std::endl;
		}
	    }
	}

	ui.render(); // Render UI

	SDL_Delay(10);
    }


    return 0;
}
