echo ~/$PWD
echo $?
cd /
echo $?
echo ~/$PWD
echo $?
echo ALLEZ=~/$PWD
echo $?
echo ALLEZ:~/$PWD
echo $?
echo ~+/$PWD
echo $?
cd /
echo ~+/$PWD
echo ALLEZ=~+/$PWD
echo ALLEZ:~+/$PWD
echo ~-/$PWD
cd /
echo ~-/$PWD
echo ALLEZ=~-/$PWD
echo ALLEZ:~-/$PWD
echo $?
echo ALLEZ:~~
echo $?
echo ALLEZ:~${GLOBAL_TOKEN}_UNKNOWNUSER
echo $?
echo ALLEZ:~+${GLOBAL_TOKEN}_SUBDIRECTORY
echo $?
echo ALLEZ:~-${GLOBAL_TOKEN}_OTHERDIRECTORY
echo $?
echo $
exit