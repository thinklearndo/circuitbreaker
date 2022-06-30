# circuitbreaker
Turn a couple of NodeMCU's into a home electrical circuit finding team.

# Setup
Flash one NodeMCU with the circuitbreaker.ino file. Then flash the other one with the circuitbreakerclient.ino file.

# Usage
Plug the client NodeMCU into a 5v wall wart in the plug socket you want to find the circuit for. The nodeMCU onboard light will light up.

Plug the other NodeMCU into a 5v wall wart at your circuit breaker panel. The onboard light will turn on solid once the client has connected. Start flipping off circuit breakers. Wait a couple of seconds between each one. When you find the right circuit, the NodeMCU light will turn off.
