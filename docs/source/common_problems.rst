.. Bullet Hell Game documentation master file, created by
   sphinx-quickstart on Mon Feb 10 17:19:13 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Common Problems
============================================
Missing :file:`{filename}.dll`
..............................
If the game displays a message similar to this one upon launch, this means that you are missing the dlls the game needs to run. 

Make sure you are running the game in the directory that it comes installed in!
Try re-downloading the game, as it should come with the dlls it needs to run. Once again, do not remove the dlls from the directory
that the executable is in, and make sure that you run the executable in the directory that it comes in.

Crashes upon launch
...................
If the game crashes upon launch, see the missing dll section above. Sometimes crashes can be caused by missing dlls. If that does not solve the problem, make sure that you have not modified the waves.dat files, or any mod files. Improper parsing of these can lead to crashes. If you are sure that you have not modified any of these files.


.. toctree::
   :maxdepth: 2
   :caption: Contents: