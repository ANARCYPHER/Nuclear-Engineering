import os
import shutil

os.system('pyinstaller --noconfirm --onedir --windowed --clean --name "Simulation Chernobyl" --add-data "data:data/" --add-data "img:img/" --add-data "txt:txt/"  "main.py"')

os.remove('Simulation Chernobyl.spec')
shutil.rmtree('build')
shutil.rmtree('__pycache__')
shutil.copytree('dist/', './', dirs_exist_ok=True)
shutil.rmtree('dist')

# to fix: windows not accepting png
# --icon "img/icon.png"
