# GoonBoxBadge
![](https://github.com/compukidmike/DC26/blob/master/GoonBoxBadge/BadgePic.jpeg)  
This unofficial Defcon badge has been an amazing experience. Thank you to everyone who backed our kickstarter and to those who bought one at Defcon. The response has been amazing.

You will find everything you need to build your own badge here. If I forgot something or you need clarification on something, don't hesitate to reach out.

## Basic Badge Usage
This is the instruction sheet that was in the bag with the badge.
![](https://github.com/compukidmike/DC26/blob/master/GoonBoxBadge/BasicInstructions.PNG)  

The most important thing to keep in mind is to not touch the slider or the mode button when turning on the badge. When the badge is first powered on, it goes through a quick calibration of the touch buttons. If you're touching the buttons during this, the calibration will be off and the buttons won't work. If that happens, simply turn the badge off and back on.

The mode button is the top gold ring on the screwdriver, just below the coil. When pressed quickly, it will indicate the current mode on the slider LEDs. If you hold it, it will change modes. Release it when it's on the mode you want (indicated by the slider LEDs, mode 1 is the bottom LEDs). It will remember the last mode, even when turned of.

The screwdriver has 3 modes:
1. Normal mode
    * In this mode the LEDs are off until you touch the slider. The LEDs will light up according to which part of the slider you're touching. The sound will also change frequency based on slider position.
2. Bling mode
    * In this mode the LEDs are always flashing. The speed will change based on the last slider position. The speed of the GoonBox pin LED pulse will also change based on slider position.
3. TV-B-Gone mode
    * This mode is for turning off/on TVs. If you touch the lower parts of the slider, it will transmit codes as long as you're holding it. If you toucht the top of the slider, it will automatically transmit all of the TV codes without you holding it. To cancel, touch the bottom of the slider.
    * Note that the slider is slower to react in this mode. This is due to the TV code transmitting being so timing sensitive. We can't update touch data as quickly as normal during code transmission.
    * After the main badge code, we were only able to fit about half the normal TV-B-Gone codes, so some TVs won't work. However, most of the major brands should be in there.

The GoonBox pin doesn't have any modes, etc.  Simply put in a CR2032 battery and it's ready. It will react to the screwdriver, as well as normal TV remotes.

## Code
The code is very ugly, and I'm sorry for anyone that chooses to look at it. I've sprinkled some comments throughout it, hopefully it makes sense.  
There were issues with the TV-B-Gone functionality. The IR LED was put on a pin that doesn't have hardware PWM functionality. This caused many problems as the standard TV-B-Gone code wouldn't work. I made serious modificaitons to both the code and the IR codes to get it to work.  

## Lessons Learned
  * Test everything you can on the prototypes. Even if you think it might not happen, test it anyway.
  * Assembling 600 badges by hand isn't a great idea. We got it done with time to spare, but still. It's a crazy amount of work/time.
  * Pickup times/locations need to be scheduled far in advance. There were a lot of people that had a hard time finding us or were unable to get to us quickly. We'll do much better about this next year.
  
### Thank you again to everyone who made this project possible!
