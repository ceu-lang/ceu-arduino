# Google Summer of Code'14 Report #

## Porting Gameduino demos to Céu - 19.05.14 to 18.08.14 ##

Student - Venkiteswaran R

Mentor - Francisco Sant'anna

#### 1. Project Introduction

During this year's Google Summer of Code, I worked on the project "Porting Gameduino demos to the Programming Language Céu" with Lablua organisation, Rio de Janeiro under the mentorship of Francisco Sant'anna.

The aim of this project was to port existing Gameduino 2 demos into the Céu programming language.
The existing demos, written in native C, cover all the essential aspects required to develop a game for the Gameduino 2 platform. This project was done to demonstrate the usage of the Céu programming language in developing programs for reactive applications. We hope this project would enable new developers to easily develop new games on Gameduino 2 using Céu. Moreover, since Céu is still under development, this project was done to understand through practical applications the advantages as well as the limitations of the language.

#### 2. Technical Aspects
  **2.1 Céu**

Céu is a programming language developed using Lua. 
Céu is a concurrent and reactive programming language that offers a safer and higher-level alternative to C.
Céu supports synchronous concurrency with shared memory and deterministic execution. 
Céu has a small memory footprint and integrates seamlessly with C. The two main peculiarities of Céu are the synchronous execution model and the use of organisms as abstractions. Céu is a language for real-time concurrency with complex control specifications, but not for algorithm-intensive or distributed applications.
Céu has been developed to be compatible with many platforms including Arduino and Android. The Céu-in-a-Box environment gives an easy to use readily avaialbe environment.
Céu is pretty much easy to learn once we get a hold of it. I learnt most of it on the go with the guidance of my mentor. The manual of the language given in the website is very helpful and decribes most of the aspects of the language and its usage. Still, parts of the manual is still under development. Those parts were described to me by my mentor. There are a lot of programs written in Céu for SDL and arduino platforms which are sufficiently documented and are helpful to learn the concepts not described in the manual.

  **2.2 Gameduino 2**

Gameduino 2 is a device pluggable into Arduino to play games. 
Gameduino 2 is a shield that adds a bright 4.3 inch touchscreen, an embedded GPU, headphone jack, accelerometer and microSD slot to Arduino - or anything else with an SPI interface.
  - video output is 480x272 pixels in 24-bit color
  - OpenGL-style command set
  - Up to 2000 sprites, any size
  - 256 Kbytes of video RAM
  - smooth sprite rotate and zoom with bilinear filtering
  - smooth circle and line drawing in hardware - 16x antialiased
  - JPEG loading in hardware
  - built-in rendering of gradients, text, dials and buttons

Gameduino 2 was the result of a successfull Kickstarter project from October 2013 - November 2013 and was developed by James Bowman.

  **2.3 Learning the samples**

The Gameduino 2 comes with 13 demos, each of which covers different aspects required to develop games for gameduino 2. They also give an introduction regarding the different functions that are part of the Gameduino 2 library. The demos as such are uncommented but mostly easy to understand. The gameduino 2 book that comes with the Gameduino 2 device describes all the features of the device and gives enough desciption of the methods defined in the Gameduino 2 library. 

Before porting the examples to Céu, I had to understand the existing games. This was done by running the existing code by commenting the different modules one by one to understand their function. The Gameduino 2 book was particularly helpful in this stage. The Gameduino 2 official forum is very active and came to my rescue very often during the project. 

The demos are:
  - Hello World - Prints Hello World on screen.
  - Blobs       - Program to introduce touch.
  - Sprites     - Program to introduce loading and displaying the game sprites on screen.
  - Abstract    - Program that shows some touch features.
  - Viewer      - Program to load image from SD card and diplay on screen.
  - Cobra       - Program that draws a shape using geometric functions.
  - Jnr         - Program that implements scroll bar.
  - Kenney      - Program that shows dynamic loading of game elements.       
  - Chess       - Self played chess AI based on an open source chess library.
  - Frogger     - The famous Frogger game on Gameduino 2.
  - Invaders    - The invaders game on Gameduino 2.
  - Nightstrike - The nightstrike game on gameduino 2.
  - Manicminer  - The manicminer game on gameduino 2.

**2.4 Porting easier demos to Céu**

The Hello World program was easy to begin with. After that, I struggled initially to get a start on writing programs using Céu. My mentor gave a huge helping hand by showing some example programs and explaining about them. The Blobs program was written largely with his help. Ater understanding the blobs program, we moved to the sprites program.

// TODO

**2.5 Working on the harder games**

// TODO

####3. Timeline and Completed Games

// TODO

####4. Experience & Takeaways

// TODO
