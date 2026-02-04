# Zombie Maul
Play a zombie mauling people in a mall.

Remade from a [project I worked on at The Orlando Global Game Jam 2012](http://archive.globalgamejam.org/2012/zombie-maul.html).

# Description
You are constantly hungry for live human organs, primarily the brain if the donor has one. You are always moving forward, but you can control his direction with the 'a' or left arrow and the 'd' or right arrow. Try and satisfy your hunger and create your zombie horde. Watch out for the mall police, they don't take kindly to zombies starting the apocalypse. Also, don't run into your own, because their organs aren't the freshest to feast on. Try to infect as many humans as possible before your time runs out.

# Movement:
- 'a' or left arrow
- 'd' or right arrow

# Objective:
Run into living humans to feast on them and make them part of your ranks to gain points. Avoid Mall cops and other zombies as that will run down your time faster.

# Other
Configure with [cmake](https://cmake.org/) and build with [make](https://www.gnu.org/software/make/manual/make.html).

# Third Party Code:
The repo imports 3rd party code via cmake `FetchContent`.

- [SFML](https://www.sfml-dev.org/)
- [simdjson](https://simdjson.org/)
- [spdlog](https://github.com/gabime/spdlog)
