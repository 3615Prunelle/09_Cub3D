_This project has been created as part of the 42 curriculum by [mlehmann](https://profile.intra.42.fr/users/mlehmann) and [schappuy](https://profile.intra.42.fr/users/schappuy)._

# Description
🎉 **Welcome to our Cub3D !** 🎉  
Take a seat, grab a drink, and be ready to have the time of your life !  
But before anything, you may wonder ...  
> **"What on Earth is this project about ?!"**

Well, this project is inspired by the world-famous Wolfenstein 3D game, which is considered the first FPS ever created.  
In short : we created a dynamic view inside a maze, using ray-casting.

Yup. You read it right.  
Yup. We did that.  
Impressive isn't it ?  
Yeah we know, we're pretty proud of it actually !

And here we are, noboby reads these README files but somehow I'm gonna put a ridiculous amount of time into it. Go figure.

**So what's the goal of this project ?**  
In a nutshell : Parse a map provided as an argument, and render it in a 3D style.  
That was an intense and amazing team work experience that we divided in two strategical sections :
* **The Parsing + The Character movements** (handled by Sophie)
* **The Rendering (Aka. The Scary Stuff)** (handled by Maxi)

_Required official description, just in case :_  
"Cub3D is a 42 project where you must create a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective. You have to create this representation using the ray-casting principles."

# Instructions
If you're here, you already know the drill : git clone, make, enjoy ! And ... That's pretty much it !  
When executing the game (called cub3d), you have to fetch the scene description (in .cub format) of your choice in the ./scene_descriptions/valid folder. If you feel creative, you can edit these files, or even create your own, as long as it respects the same synthax, and that all required elements are provided (you'll figure it out, it's pretty straightforward).  
Then you give that scene description as an argument, for the desired maze to be set up and launched.  

_Required official intructions, just in case :_
### Compilation
`git clone path_to_project_repo`  
`make`

### Execution
`./cub3d path_to_scene_description.cub`

# Resources
For this project, we used ...
* Google / Youtube / AI and all that jazz, obviously
* Unix manuals for authorized functions
* VSCode & GDB to code & debug
* Valgrind for mem leaks
* Wait, should we actually list all the tools we used during 3 months of research here ? 😅

So what about AI ? You bet ! We spent hours having fascinating exchanges with these, all along the project, but in a smart way.
Here's an idea of the prompts we used :
* Teach me the basics of _that_ new concept and _this_ function
* I'm stuck. Here's my code - help me to find out the solution by myself, by just giving me hints
* Don't provide any answers
* What can I do with the 3 eggs, 2 apples, corn flour and butter I have at home ? - WHOOPS, wrong copy-paste.

However guess what ?! We _(almost)_ didn't use AI for this README * Insert here a sunglasses emoji *

# Extra tips
Just in case you need a bit of help to build a scene description, here's what you need to know :
> * Except for the map content, each type of element can be separated by one or more empty lines.
> * Except for the map content which always has to be the last, each type of element can be set in any order in the file.
> * Except for the map, each type of information from an element can be separated by one or more spaces.
> * Except for the map, each element must begin with its type identifier (composed by one or two characters), followed by its specific information in a strict order :
>    * path to each texture in .png format (NO for North, SO for South, and so on) - Don't forget to add the png file in the texture folder.
>    * RGB codes (C for ceiling, F for floor) - You can use this [tool](https://www.csfieldguide.org.nz/en/interactives/rgb-mixer/) to help you out with that.
> * The map itself :
>    * It must be composed of only 6 possible characters:
>        * 0 for an empty space.
>        * 1 for a wall.
>        * N,S,E or W for the player’s start position and spawning orientation.
>    * The map must be closed/surrounded by walls.
> * If any misconfiguration of any kind is encountered in the file, the program will exit and return a somewhat explicit error message. If that error message is too vague, feel free to have a look at the ./scene_descriptions/invalid files - their names could give you a hint of what you've done wrong. Otherwise you can also decide to have fun and find out with a debugger, YOU SEXY NERD ^^'

Voilà, we wish you a safe journey aboard, au revoir ! Bon voyage !
