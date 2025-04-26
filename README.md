# LiftBuddy Overview
Lift Buddy is designed to make it easy to control a boat lift using your smartphone and WIFI.
It does this by using an ESP32 module which is basically a souped up Arduino (Arduino+Wifi+Bluetooth).

ESP32 will be connected to via Wifi and serve a very simple html page which gives you some operations:
- Up/Down
- Preset times to run for (1 second, 30 seconds, etc.)
- Stop (press when needing to override)

When the up/down button is pressed along with a timer it will send that message to ESP32 which triggers
a relay which is connected to the boat lift.

# First Time Use
Let's test it before wiring up in the comfort of your home:
1. Plug in the black power cord
2. Connect to the WIFI that LiftBuddy is transmitting: **LIFT_BUDDY_2**
3. You will need to enter your password: **Ward9044031391**

Once the password is put in the first time, it should be easy to select in the future without needing to put in your password
In other words, you can simply click the Wifi button on your phone and select **LIFT_BUDDY_1** when you want to control it.

# Usage
Now that you are connected to the WIFI (this is essential, not optional), you will need to open the web page from your
mobile browser: Chrome for Android, Safari for Iphone

Type in the address: **192.168.10.1**

This should now show you the contols. I recommend you set a bookmark in your phone to easily pull this up whenever you want
to control LiftBuddy

To Operate, choose the direction you want the lift to move in (Up or Down) and simply click the Time you want it to run.
It will activate and start counting down the timer on your mobile device. If for any reason you need to stop it, click
the giant red stop button. You can resume by selecting direction and timer again as needed.

*Note: When you operate you will see the relay lights go out while moving up or down -- this is expected and useful to see it is working. You should also hear clicks when the relay is operating*

# Wiring
Now that everything has been tested, let's wire this bad boy up to the lift

Wire the relay into your Boat Lift Switch: 
1. Connect the common wire (black) into your common wire on the switch (also black)
2. Connect the Down Wire (yellow) into your down wire on the switch (also yellow)
3. Connect the Up Wire (blue with red tape) into your up wire on the switch (red)

*Note: (Alligator clips are a good way to hook this up quickly and test before more permanent splices are made)*

Now that you are wired up, plug in the Power Cord
You should see a few lights fire up on the LiftBuddy. The Relay will have a green light along with two Red Lights (each channel of relay)

# Troubleshooting
**The lift is going up when I select down, and down when I select Up**

Reverse the wires on your switch. Move the Yellow to the up, and Blue/Red to the down -- this should fix it.

**When I try to pull up the Web page but nothing shows up**

This is almost certainly due to you not being on the Wifi Address. Double-check that your wifi on your phone is connected to LIFT_BUDDY_1.
It will not work if you are not directly connected to it.

**I am connected to the right WIFI but the web page is still not coming up**

You likely typed in the address wrong. Try typing out the full address if it doesn't work by just putting in the numbers: http://192.168.10.1

