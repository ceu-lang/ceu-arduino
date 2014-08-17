# Google Summer of Code'14 Report 

## Porting Gameduino demos to Céu - 19.05.14 to 18.08.14

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
Céu has been developed to be compatible with many platforms including Arduino and Android. The Céu-in-a-Box environment gives an easy to use readily available environment.

Céu is pretty much easy to learn once we get a hold of it. I learnt most of it on the go with the guidance of my mentor. The manual of the language given in the website is very helpful and describes most of the aspects of the language and its usage. Still, parts of the manual is still under development. Those parts were described to me by my mentor. There are a lot of programs written in Céu for SDL and arduino platforms which are sufficiently documented and are helpful to learn the concepts not described in the manual.

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

Gameduino 2 was the result of a successful Kickstarter project from October 2013 - November 2013 and was developed by James Bowman.

  **2.3 Learning the samples**

The Gameduino 2 comes with 13 demos, each of which covers different aspects required to develop games for gameduino 2. They also give an introduction regarding the different functions that are part of the Gameduino 2 library. The demos as such are uncommented but mostly easy to understand. The gameduino 2 book that comes with the Gameduino 2 device describes all the features of the device and gives enough description of the methods defined in the Gameduino 2 library. 

Before porting the examples to Céu, I had to understand the existing games. This was done by running the existing code by commenting the different modules one by one to understand their function. The Gameduino 2 book was particularly helpful in this stage. The Gameduino 2 official forum is very active and came to my rescue very often during the project. 

The demos are:
  - Hello World - Prints Hello World on screen.
  - Blobs       - Program to introduce touch.
  - Sprites     - Program to introduce loading and displaying the game sprites on screen.
  - Abstract    - Program that shows some touch features.
  - Viewer      - Program to load image from SD card and display on screen.
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
The sprites program was also complete in three days.

The next week, I worked on the kenney program. We built the individual components one-by-one, implemented all its features and in the end, integrated the whole program together. We followed the same strategy throughout the program.
The execution model of Céu was highly useful in developing the games as opposed to the native games. The structure of Céu makes it easy to write programs in the language. I also implemented the jnr demo in a week.

**2.5 Working on the harder games**

I worked on two hard games, namely Frogger and nightstrike, both of which are implementation of famous games by the same names, in Gameduino 2. 

Since the frogger game was the first large program, we had to undergo a lot of iterations of modifications to get the program to make it completely Céu-like. Thus involved removing a lot of state variables, that is common with C programs. This is because, with the native programs, the program cannot be structured in a easily readable and stateless way. Céu provides various features that help to make the program to be structured in a logically readable way, thereby avoiding the usage of state variables. My mentor gave a lot of suggestions in doing this and getting the program to perfection.

I gained a better idea about structuring the programs for Céu after the frogger game. Because of that, I was able to do better while programming the nightstrike game. Implementing the individual components of the game was pretty much easy. I faced difficulties in detecting the collision between the components. I came to know about interfaces in Céu from my mentor. I then implemented the collision referring the rocks example in Céu developed for the SDL platform. The rocks program, being well-documented, was hugely helpful in this task.

While coding the larger programs, like nightstrike, we faced various memory issues. Even with less than half the variables as the native program, the program was crashing. My mentor figured that they hadn't put effort on memory consumption for organisms and that this will have to be worked upon in the future in order to improve the language on that front.

####3. Timeline and Completed Games

The GSoC project was for a total duration of 13 weeks. The timeline followed was:

 - In the first two weeks, I worked on porting an SDL example in Céu to Gameduino 2 in order to get familiar with writing a basic program in Céu for Gameduino 2. I also read an academic paper on Céu and understood the video on dynamic models in Céu.
 - The third week was spent coding the blobs and sprites program.
 - In the fourth week I finished the kenney program. 
 - The next week I worked on the frogger and implemented some features. 
 - The next week I faced some personal problems ( relocated, presented a paper at a conference) and some environment issues. Hence, I couldn't make much progress this week. 
 - In the seventh week, I worked on the jnr program.
 - The next three weeks were spent in implementing all the components of the frogger program, restructuring the code multiple times and testing them. 

In between the frogger program we realize that we might not be able to complete all the demos as per the original plan. So, we decide to ignore the demos such as jnr, cobra and chess, which do not gain from being ported to Céu. The overall goals of the project was adjusted to complete fully polished versions of Frogger and Nightstrike. 

 - I finished the nightstrike game in the next two and a half weeks.
 - The last few days were spent testing all the codes once again, commenting all the programs and documenting my project.

####4. Experience & Takeaways

I had a very memorable GSoC experience. This was my first ever open source experience. I loved contributing to the community. This experience has led me to grow more interest towards open source. Through this project I was introduced to the very interesting language Céu, which finds applications in reactive applications like wireless sensor networks. 

I had a nice time working with my mentor Francisco Sant'anna. He was very helpful throughout the program. He explained things patiently whenever I was stuck and gave suggestions that helped the programs to achieve the final structure. I will be indebted to him for his valuable guidance. His great achievements through his career has inspired me further in the Computer Science field.

Going forward, I would like to develop the invaders and the manic miner program as well in my free time. I would also like to develop other simple games like ultimate tic-tac-toe and 2048 for Céu in the Gameduino platform as well as the SDL platform. I would also love to do all possible contributions from my part to the Céu/Lua community.
