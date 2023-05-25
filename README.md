# GeneratorCofd
An unoptimized and fairly lackluster character generator for Chronicles of Darkness.
I did this because I wanted to try out c++ and learn some fun skills while doing something useful for myself. The code is full of cringe inducing lines... maybe one day i'll refactor everything into something more presentable.\
As of now, this library does correctly what I wanted it to: generating random human characters for Chronicles of Darkness.\
Many thanks to [dasmig](https://github.com/dasmig) and [nlohmann](https://github.com/nlohmann) for the name-generator and json libraries :)
## What do I do?
Include [Randomsheetgenerator.hpp](/headers/Randomsheetgenerator.hpp) and you are free to:
```
randomSheetGenerator r = randomSheetGenerator();
r.generateRandomChar();
```
The sheet will be generated inside the object. You can access it via:
```
r.sheet().prettyPrint(); \\ prints on cout
```
or:
```
 r.sheet().toJson() \\ returns json of the sheet
```
## About the generated characters
The merits with their relative descriptions have been scraped from [The Codex Of Darkness' Universal Merits](https://codexofdarkness.com/wiki/Merits,_Universal_(2nd_Edition)).\
I could not bear to make a system that checks the prerequisites of the various merits so the randomized merits are only those that do not have prerequisites. Maybe one day I'll manage to add them but it's not a priority.
