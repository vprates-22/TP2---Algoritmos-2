import os
import platform

if(platform.system() == 'Windows'):
    flag = False
else:
    flag = True

os.system('make all')

open("tests/twiceAroundResults.txt", "w").close()
open("tests/christofidesResults.txt", "w").close()
open("tests/branchAndBoundResults.txt", "w").close()

ext = "" if flag else ".exe"
os.system("clear") if flag else os.system("cls")


print("Tests started:")
print("\n\n------------------------------------------------\n\n")
for f in sorted(os.listdir('data')):
    print(f)
    os.system(f'./bin/tat{ext} data/{f} S')
    os.system(f'./bin/chr{ext} data/{f} S')
    os.system(f'./bin/bnb{ext} data/{f} S')
print("\n\n------------------------------------------------\n\n")
print("Tests finished")
print("\n\n------------------------------------------------\n\n")