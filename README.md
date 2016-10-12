# ZM1001-Ornament
A single Nixie home-decor ornament with ZM1001.

The code randomizes the symbol to be shown. Each symbol is kept for a constant amount of time (30" default). Transition is done by looping through all symbols a random number of times at a random speed (50 to 300 milliseconds for each symbol).

That's it.

There is a fade-in/fade-out tentative code that has been left out because it doesn't work on my ZM1001 tube.

The code can be adapted to a different circuit layout if you re-map outputs in the "controls" array. Then you need to review the "symbols" matrix array to match your decoder circuitry (I used a 7441, pick your favourite driver). Blanking, that doesn't happen in my code, can be achieved by switching to an unused 7441 output.
