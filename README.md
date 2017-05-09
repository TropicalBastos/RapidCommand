# RapidCommand BETA
### Windows only

Hotkey for opening cmd, contextual to wherever you are!

If you are in File Explorer, pressing home (default hotkey) will open the cmd at your current directory location!
If the hotkey is pressed anywhere that the program cannot trace the path, it will open up the cmd at root.
<br><br>
To run, simply run the exe found in Release. It runs as a background process but its lifespan dies when you either: 
turn the PC off or end its process in the task manager.
<br><br>
For making sure this application runs automatically on startup simply place a copy of the exe file into your windows startup folder
<br><br>
To change the hotkey to one of your choice you need to change the hex key in the keys.h header file 
by either changing the hex value or replacing the hex value with one of the VK key constants,
then re-compile using Visual Studio.
For a reference of hotkey hex codes and defined constants visit <a href="https://msdn.microsoft.com/en-GB/library/ms927178.aspx">here</a>
<br><br>
Changes that may be coming:
<ul>
<li>- XML config file for the key codes so that no recompilation is needed when changing the hotkey</li>
</ul>
