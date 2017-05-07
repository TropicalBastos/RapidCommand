# RapidCommand BETA


Hotkey for opening cmd, contextual to wherever you are!

If you are in File Explorer, pressing home (default hotkey) will open the cmd at your location!
If the hotkey is pressed anywhere that the program cannot trace the path, it will open up the cmd at root.

To run, simple run the exe found in Release. It runs as a background process but its lifespan dies when you either: 
turn the PC off or end its process in the task manager.

Future features include:
<ul>
<li>- Easier builds</li>
<li>- Runs automatically on startup</li>
</ul>

To change the hotkey to one of your choice you need to change the hex key in the keys.h header file 
by either changing the hex value or replacing the hex value with one of the VK key constants,
then re-compile using Visual Studio.
For a reference of hotkey hex codes and defined constants visit <a href="https://msdn.microsoft.com/en-GB/library/ms927178.aspx">here</a>
