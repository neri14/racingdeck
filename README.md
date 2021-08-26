# RacingDeck

Elgato Stream Deck plugin to dynamically update actions based on simulator state.


## in progress

- basic ACC integration


## Misc

Use following for packaging plugin:

https://developer.elgato.com/documentation/stream-deck/sdk/exporting-your-plugin/


Use following python to encode png images for embedding (add "data:image/png;base64," at the beginning):

import base64

base64.b64encode(open("headlights_off.png", "rb").read())