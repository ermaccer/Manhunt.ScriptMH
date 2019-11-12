# Manhunt.ScriptMH
Adds new commands to script.

# Installation
ScriptMH requires Ultimate ASI Loader(https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases), place the .asi file in main Manhunt folder and you're good to go.


# Added commands

## PushMessage ##
Params: `message(string)`

Prints a mesage to CMD window, which can be enabled with PluginMH.

## WriteMemory ##
Params: `addr(integer), size(integer), value(integer)`

Patches game memory, address needs to be specified in decimal. Can patch char(size = 1), short (size = 2) and int (size = 4).

## ReadMemory ##
Params: `addr(integer), size(integer)`

Returns value from specified address, address needs to be decimal.

## KeyHit ##
Params ``key(integer``

True if key was hit, and false if not. VK_KEY codes in decimal.

### Check examples for more info. ###
