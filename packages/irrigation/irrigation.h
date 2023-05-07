/*
 * A set of helpers that make the integration of ESPHome Sprinkler
 * with the relays and the display easier and shorter.
 */
#pragma once
#include "esphome.h"

namespace esphome {

/*
 * Toggle valve - start valve if inactive or shutdown controller
 */
void toggle(int valve,
            sprinkler::Sprinkler *sprinkler) {
              
  // sprinkler::SprinklerSwitch *sswitch =  id(sprinkler).valve_switch(valve - 1);

  if (id(sprinkler).active_valve() != valve - 1) {
    id(sprinkler).start_single_valve(valve - 1);
  } else {
    id(sprinkler).shutdown();
  }
  //   sprinkler::SprinklerSwitch *sswitch =  id(sprinkler).valve_switch(valve - 1);
  // if (!id(sswitch).state()) {
  //   id(sprinkler).start_single_valve(valve - 1);
  // } else {
  //   id(sprinkler).shutdown();
  // }
}

/*
 * Prevent starting single valve program when button state change was triggered
 * by the controller
 *
 * Useful when turning valve on by push of a button button,
 * that is also used to indicate that the valve is on.
 */
void conditional_on(int valve, switch_::Switch *relay,
                    sprinkler::Sprinkler *sprinkler) {
  if (!id(relay).state) {
    id(sprinkler).start_single_valve(valve - 1);
  }
}

/*
 * Prevent shutting down the conroller when button state change was triggered by
 * the controller
 *
 * Useful when turning valve off by push of a button button,
 * that is also used to indicate that the valve is on.
 */
void conditional_off(switch_::Switch *relay, sprinkler::Sprinkler *sprinkler) {
  if (id(relay).state) {
    id(sprinkler).shutdown();
  }
}

}  // namespace esphome