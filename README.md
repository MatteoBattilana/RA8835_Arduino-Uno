RA8835_Arduino-Uno
==================
# INFO
This is an experimental universal library for the RA8835 and SED1335 controller connected to the Arduino Uno.
I did this for a customer test long time ago. Please use this as a reference on writting the drivers.

# PIN Connection
|  Display  | Arduino Uno |
| ------------- | ------------- |
| WR  | Analog 0  |
| RD  | Analog 1  |
| A0  | Analog 2  |
| D0  | Digital 2 |
| D1  | Digital 3 |
| D2  | Digital 4 |
| D3  | Digital 5 |
| D4  | Digital 6 |
| D5  | Digital 7 |
| D6  | Digital 8 |
| D7  | Digital 9 |
| CS  | Analog 3  |
| Res | Reset     |

## G321D REV.4 Wiring Example
This example uses a LM7805 as voltage regulator, in order to get 5V form a commong ground.

![G321D Wiring](/images/wiring.png =450x)
