import os
from shutil import copyfile

os.chdir('../x64/Debug')
for f in os.listdir():
    copyfile(f'./{f}', f'../../Bullet Hell Wave Game/bin/Debug/{f}')


os.chdir('../Release')
for f in os.listdir():
    copyfile(f'./{f}', f'../../Bullet Hell Wave Game/bin/Release/{f}')

os.chdir('../../Bullet Hell Wave Game')
copyfile('./config.lua', './bin/Debug/config.lua')
copyfile('./config.lua', './bin/Release/config.lua')
    
print('Successfully copied files')
