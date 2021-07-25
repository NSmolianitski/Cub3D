# Cub3D
Cub3D is a study project which represents a raycasting game (like [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D))

It is rather simple. There is a maze with some sprites, where you can walk:
![screenshot](https://github.com/NSmolianitski/Cube3D/blob/master/screenshot.png)

## Installation

Just download, run ```make``` and launch ```cub3D``` with game_settings.cub as a first argument.
Also, you can use ```--save``` as a second argument if you want to get a game screenshot instead of playing.

This project was developed on Mac OS, there could be some compatibility troubles, sorry...

## Configuration

As mentioned above, you have a game_settings.cub file, which can be opened as a text file.
Inside you can configure a resolution, wall and sprite textures, ceiling and floor color and a map. NSWE are player starting direction.
'0' means an empty space, '1' means a wall, '2' means a sprite. Warning: Map should be covered by walls!
